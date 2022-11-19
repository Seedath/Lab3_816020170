#include "user_main.h"

static const char *TEST = "Test";

void unit_test_task2_off(void *arg){
    /*Unit Test for task2_off, i.e. function to set GPIO 2 to 0*/

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

	//delay_count = 0;
    //create a mutux for the tasks
    xMutex = xSemaphoreCreateMutex();

    /*Stub to set GPIO 2 level to 1, i.e. LED ON*/
    gpio_set_level(GPIO_OUTPUT_IO, 1);
    
    /*Run task to set GPIO 2 level to 0*/
    task2_off(NULL);

    int check;
    check = gpio_get_level(GPIO_OUTPUT_IO);
    /*Check if GPIO 2 was actually set to 0 from function call*/
    if(check == 0){
        ESP_LOGI(TEST, "Unit Test for task2_off PASSED.\n");
    }
    else{
        ESP_LOGI(TEST, "Unit Test for task2_off FAILED.\n");
    }
}