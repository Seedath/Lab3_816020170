# _Unit Test_

For unit testing, the chosen function to test was task2_off. The user_main.c file only contained the unit test to be ran while the actual test is found in unit_test.h header file. The original user_main.c file for the system was renamed as user_main.h for unit testing and this header file was included in unit_test.h to call the task2_off function.

## Testing task2_off

*Pre-Conditions: GPIO 2 pin configured for the ESP8266, LED circuit connect to the GPIO 2 pin, 3.3V power supply
*Input: Call "task2_off()", verify GPIO level by "gpio_get_level"
*Expected Output: "gpio_get_level" returns a value of 0 and passes the test
*Actual Output: "gpio_get_level" returns a value of 0 and passes the test
