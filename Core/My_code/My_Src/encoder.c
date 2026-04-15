#include "encoder.h"

#include <stdint.h>

#include "fan.h"
#include "main.h"
#include "stm32f1xx_hal_tim.h"

void encoder_scan(void)
{
    static int16_t last = 0;

    int16_t now = __HAL_TIM_GET_COUNTER(&htim3);  // 你配置的TIM3

    // 右转 → 加档
    if(now - last >= 4)
    {
        uint8_t g = fan_get_gear();
        if(g < 5) fan_set_gear(g + 1);
        last = now;
    }

    // 左转 → 减档
    else if(last - now >= 4)
    {
        uint8_t g = fan_get_gear();
        if(g > 0) fan_set_gear(g - 1);
        last = now;
    }
}

void Start_encoder_Task(void *argument)
{

    for(;;)
    {
        if (encoder_key_press()) {


        }
        osDelay(1);
    }
    /* USER CODE END Start_encoder_Task */
}