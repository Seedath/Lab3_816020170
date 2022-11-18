/* gpio example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
// Semaphore header file 
#include "freertos/semphr.h"

#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_system.h"

static const char *TAG = "main";

/**
 * Brief:
 * This test code shows how to configure gpio and how to use gpio interrupt.
 *
 * GPIO status:
 * GPIO2: output LED
 * GPIO1: input button
 *
 */

//GPIO2 set as output LED
#define GPIO_OUTPUT_IO			2
#define GPIO_OUTPUT_PIN_SEL 	(1ULL << GPIO_OUTPUT_IO)

/* Declaring variable type of SemaphoreHandle_t */
SemaphoreHandle_t xMutex = NULL;
TaskHandle_t handle1 = NULL;
TaskHandle_t handle2 = NULL;

unsigned int delay_count;

static void task1_on(void *pvParameters);
static void task2_off(void *pvParameters);
//static void task3_print(void *pvParameters);

static void task1_on(void *pvParameters)
{
	while (1) {
		if( xMutex != NULL ){
			
			/* See if we can obtain the semaphore.  If the semaphore is not
			available wait 10 ticks to see if it becomes free. */
			if ( xSemaphoreTake( xMutex, ( TickType_t ) 10) == pdTRUE){
				/* Turn LED ON */
				gpio_set_level(GPIO_OUTPUT_IO, 1);
				ESP_LOGI(TAG,"GPIO2 PIN set to %d : LED is ON\n", gpio_get_level(GPIO_OUTPUT_IO));
				
				/* Actively wait 0.5s */
				while (delay_count != 2650000){
					delay_count++;
				}
				
				ESP_LOGI(TAG, "Task 1 completed...\n");
				delay_count=0;
			
				/* Release Mutex*/
				xSemaphoreGive(xMutex);
			
				/* Task delay 1s */
				vTaskDelay(1000/portTICK_RATE_MS);
			}
			else{
				//ESP_LOGI(TAG,"Task 1 could not obtain Semaphore...\n");
				/* We could not obtain the semaphore and can therefore not access
				the shared resource safely. */
			}
		}
	}
}

static void task2_off(void *pvParameters)
{
	while (1) {
		if( xMutex != NULL ){
			
			/* See if we can obtain the semaphore.  If the semaphore is not
			available wait 10 ticks to see if it becomes free. */
			if ( xSemaphoreTake( xMutex, ( TickType_t ) 10) == pdTRUE){
				/* Turn LED ON */
				gpio_set_level(GPIO_OUTPUT_IO, 0);
				ESP_LOGI(TAG,"GPIO2 PIN set to %d : LED is OFF\n", gpio_get_level(GPIO_OUTPUT_IO));
				
				/* Actively wait 0.5s */
				while (delay_count != 2650000){
					delay_count++;
				}
				
				ESP_LOGI(TAG, "Task 2 completed...\n");
				delay_count=0;
			
				/* Release Mutex*/
				xSemaphoreGive(xMutex);
			
				/* Task delay 1s */
				vTaskDelay(1000/portTICK_RATE_MS);
			}
			else{
				//ESP_LOGI(TAG,"Task 2 could not obtain Semaphore...\n");
				/* We could not obtain the semaphore and can therefore not access
				the shared resource safely. */
			}
		}
	}
}

static void task3_print(){
	while(1){
		ESP_LOGI(TAG,"STATUS of GPIO2: %d\n", gpio_get_level(GPIO_OUTPUT_IO));
		ESP_LOGI(TAG,"Task 3 completed...\n");
		
		/* Task delay 1s */
		vTaskDelay(1000/portTICK_RATE_MS);
	}
}

/*Driver functions to test task3_print*/
static void drive_on(void *pvParameters){
	/*Stub to set the LED to 1*/
	gpio_set_level(GPIO_OUTPUT_IO, 1);
	
	/*RTOS task function to call task3_print*/
    task3_print();
}

static void drive_off(void *pvParameters){
	/*Stub to set the LED to 0*/
	gpio_set_level(GPIO_OUTPUT_IO,0);

	/*RTOS task function to call task3_print*/
	task3_print();
}

void app_main(void)
{
    gpio_config_t io_conf;

    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO2
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

	delay_count = 0;
    //create a mutux for the tasks
    xMutex = xSemaphoreCreateMutex();

	xTaskCreate(drive_on,"Driver for LED ON", 2048, NULL, 3, &handle1);
	
	if(handle1 != NULL){
		vTaskDelete(handle1);
	}else {
		ESP_LOGI(TAG, "Error: drive_on did not run\n");
	}

	xTaskCreate(drive_off,"Driver for LED OFF", 2048, NULL, 2, &handle2);
	
	if(handle2 != NULL){
		vTaskDelete(handle2);
	}else {
		ESP_LOGI(TAG, "Error: drive_off did not run\n");
	}
	/* Commented out to run Unit test
    xTaskCreate(task1_on, "LED ON", 2048, NULL, 3, NULL);

    xTaskCreate(task2_off, "LED OFF", 2048, NULL, 2, NULL);
	
    xTaskCreate(task3_print, "Print Status", 2048, NULL, 1, NULL);
	*/
}
