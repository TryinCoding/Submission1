#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void hello(void *pvParameters)
{
    while(1){
        printf("Hello, from component %d \n",xPortGetCoreID());
        vTaskDelay(1200 / portTICK_PERIOD_MS);
        fflush(stdout);
    }
}
