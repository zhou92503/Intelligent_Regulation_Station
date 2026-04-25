#include "encoder.h"

#include <stdint.h>

#include "cmsis_os2.h"
#include "main.h"
#include "stm32f1xx_hal_tim.h"
#include "encoder.h"


uint8_t fan_target_percent = 50;  // 默认 50%
static int16_t last_cnt = 50;
int16_t target;
int16_t diff;

void Encoder_Init(void)
{
    // 开启编码器
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    // 初始值设为 50
    __HAL_TIM_SET_COUNTER(&htim3, 50);
    last_cnt = 50;
}




void Encoder_Scan(void)
{
    // 读取硬件值
    int16_t now = (int16_t)__HAL_TIM_GET_COUNTER(&htim3);

    // ==============================================
    // 【核心】只算变化量，不管硬件跳变
    // ==============================================
    diff = now -last_cnt;

    // 处理跳变（0往下转会变成-65535，这里强制修正）
    if (diff < -32767) diff += 65536;
    if (diff >  32767) diff -= 65536;

    last_cnt = now;

    // ==============================================
    // 用差值去更新我们自己的变量
    // ==============================================
    target = fan_target_percent + diff;

    // 硬限位
    if(target < 0)   target = 0;
    if(target > 100) target = 100;

    fan_target_percent = target;
}


void Fan_PWM_Init(void)
{
    // 启动TIM3通道3的PWM输出
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

// 核心函数：0~100 → 映射成 PWM 0~1000
void Fan_SetSpeed(uint8_t percent)
{
    uint16_t pwm_val;

    // 限位保护
    if(percent > 100) percent = 100;

    // 映射公式：0~100 → 0~1000
    pwm_val = (uint16_t)(percent * 10);

    // 设置PWM比较值（决定占空比）
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm_val);
}
void Start_encoder_Task(void *argument)
{

    Encoder_Init();
    Fan_PWM_Init();

    for(;;)
    {
        Encoder_Scan();
        Fan_SetSpeed(0);
        osDelay(20);
    }

}