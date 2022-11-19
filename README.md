# _Verification Test_

For verifiction testing, two tests were conducted. The first test (i) used a stub function to set the GPIO 2 pin to 1 and then create the task for task2_off and turn the LED off. The second test (ii) was done to check if task2_off would work with task1_on to turn the LED on and off.

## (i) Testing turning LED off
* Pre-Conditions: GPIO 2 pin configured for the ESP8266, LED circuit connect to the GPIO 2 pin, 3.3V power supply
* Input: Create task using "xTaskCreate()" for function "task2_off"
* Expected Output: The LED does not light
* Actual Output: The LED did not light

## (ii) Testing blinking the LED 
* Pre-Conditions: GPIO 2 pin configured for the ESP8266, LED circuit connect to the GPIO 2 pin, 3.3V power supply
* Input: Create tasks using "xTaskCreate()" for the function "task2_off" and "task1_on"
* Expected Output: The LED blinks
* Actual Output: The LED blinked
