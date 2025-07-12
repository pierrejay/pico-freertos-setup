#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

void mainTask(void* param) {
    while (true) {
        printf("Hello from FreeRTOS task!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{
    stdio_init_all();

    // Launch main task
    xTaskCreate(
        /*pxTaskCode*/    mainTask, 
        /*pcName*/        "mainTask", 
        /*uxStackDepth*/  512,
        /*pvParameters*/  NULL, 
        /*uxPriority*/    tskIDLE_PRIORITY+1, 
        /*pxCreatedTask*/ NULL
    );
    
    // Start the FreeRTOS scheduler
    vTaskStartScheduler();
    
    // Never reached
    printf("FATAL: Scheduler returned!\n");
    while (1) sleep_ms(1000);
}