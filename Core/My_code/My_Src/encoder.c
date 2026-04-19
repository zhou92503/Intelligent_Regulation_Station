#include "encoder.h"

#include <stdint.h>

#include "cmsis_os2.h"
#include "main.h"
#include "stm32f1xx_hal_tim.h"

uint8_t fan_target_percent=0;


void encoder_scan(void)
{
    //1.读取TIM3的计数器值
     //注意：编码器每一格数值+1或-1

    int16_t count = __HAL_TIM_GET_COUNTER(&htim3);  // 你配置的TIM3

    // 右转 → 加档
    if (count<0) count=0;
    if (count>100)  count=100;

    //3.将计数器直接映射为风扇转速的百分比
    fan_target_percent=(uint8_t)count;

    uint16_t pwm_val = (uint16_t)(count*999/100);
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,pwm_val);
}

void Start_encoder_Task(void *argument)
{

    for(;;)
    {
        encoder_scan();

        osDelay(5);
    }

}