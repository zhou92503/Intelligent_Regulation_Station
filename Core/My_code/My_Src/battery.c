#include "battery.h"

#include "cmsis_os2.h"

uint8_t battery_percent =0;
uint8_t is_charging = 0;

void battery_update(void)
{

    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 100)==HAL_OK);
    {
        uint16_t adc_val = HAL_ADC_GetValue(&hadc1);
        ///分压比1：2，3.3V/4095
        ///
        float volt = adc_val * 3.3f / 4095.0f*2.0f;
        //3.0V=0% 4.2V=100%,线性运算

        if (volt<3.0f) battery_percent=0;
        else if (volt>4.2f)battery_percent=100;

        else battery_percent = (uint8_t)(volt-3.0f)/(1.2f*100);
    }
    HAL_ADC_Stop(&hadc1);

    //充电状态检测（PB0引脚，高电平=充电）
    is_charging =(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_SET)?1:0;
}



uint8_t battery_get_percent(void)
{
    return battery_percent;
}


void Start_Battery_Task(void *argument)
{

    for(;;)
    {
        battery_update();

        osDelay(1000);
    }

}