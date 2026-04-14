#include "cmsis_os2.h"

#include "fan.h"
#include "dht11.h"

static uint8_t fan_gear = 0;

void fan_set_gear(uint8_t gear)
{
    if(gear>5) gear=5;
    fan_gear=gear;
    uint16_t pwm[]={0,200,400,600,800,999};
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,pwm[gear]);
}


uint8_t fan_get_gear(void) {
    return fan_gear;
}

void fan_auto_ctrl(void)
{
    uint8_t t = dht11_get_temp();
    if(t>=30) fan_set_gear(5);
    else if(t>=27) fan_set_gear(3);
    else if(t<=25) fan_set_gear(0);
}




void Start_FAN_Task(void *argument)
{
    for(;;)
    {




        osDelay(1);
    }
}