#include <stdio.h>
#include "dual_core.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hello_world.h"
#include "blinky.h"

void dualcore(void)
{
    nvs_flash_init();
    xTaskCreatePinnedToCore(&blink,"blink_task",1024*4,NULL,configMAX_PRIORITIES-1,NULL,0);
    xTaskCreatePinnedToCore(hello,"hello_task",1024*4,NULL,configMAX_PRIORITIES-1,NULL,1);

}
