#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PIN 2

void blink(void *pvParameters)
{
    gpio_pad_select_gpio(PIN);
    gpio_set_direction(PIN,GPIO_MODE_OUTPUT);

    while(true)
    {
        gpio_set_level(PIN, 0);
        
        vTaskDelay(1000/portTICK_PERIOD_MS);
        printf("Led Task %d \n",xPortGetCoreID());
        gpio_set_level(PIN,1);
        
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
