# _Integration Test_

For integration testing, a driver function was used to call the task2_off() function. The same structure was used from the unit test where there was a user_main.c which only ran the test, a user_main.h which contained the original code for the system but was placed in a header file for conducting the tests and a inte_test.h file which contained the integration test to be ran which in this case called the driver function.

## Testing task2_off

* Pre-Conditions: GPIO 2 pin configured for the ESP8266, LED circuit connect to the GPIO 2 pin, 3.3V power supply
* Input: Call "driver_off(NULL)", verify GPIO level by "gpio_get_level"
* Expected Output: "gpio_get_level" returns a value of 0 and passes the test
* Actual Output: "gpio_get_level" returns a value of 0 and passes the test

