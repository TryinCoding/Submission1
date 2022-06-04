#include <stdio.h>
#include "dual_core.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hello_world.h"
#include "blinky.h"
#include <freertos/semphr.h>
#include <esp_system.h>

void equal_priority(void)
{
    nvs_flash_init();
    xTaskCreatePinnedToCore(blink,"blink_task",1024*4,NULL,configMAX_PRIORITIES-1,NULL,0);
    xTaskCreatePinnedToCore(hello,"hello_task",1024*4,NULL,configMAX_PRIORITIES-1,NULL,0);
}
void non_preemptive(void)
{
    nvs_flash_init();
    xTaskCreatePinnedToCore(blink,"blink_task",1024*4,NULL,0,NULL,0);
    xTaskCreatePinnedToCore(hello,"hello_task",1024*4,NULL,1,NULL,0);
}

void LowPriority(void *arg)
{
    while (1)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);

        for (uint8_t i = 0; i < 10; i++)
        {
            ESP_LOGI(TAG, "Turning the LEDs on Low Priority %d", i);

            gpio_set_level(GPIO_NUM_2, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(GPIO_NUM_2, 0);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
        xSemaphoreGive(xMutex);
    }
}
void HighPriority(void *arg)
{

    while (1)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        for (uint8_t i = 0; i < 10; i++)
        {
            ESP_LOGI(TAG, "Turning the LEDs on High Priority %d", i);
            gpio_set_level(GPIO_NUM_15, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(GPIO_NUM_15, 0);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        xSemaphoreGive(xMutex);
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}