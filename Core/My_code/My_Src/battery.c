#include "battery.h"

#include "cmsis_os2.h"

uint8_t battery_percent =0;
uint8_t is_charging = 0;
uint16_t adc_val;
void battery_update(void)
{

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    osDelay(10);  // 等待电压稳定

    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 100)==HAL_OK)
    {
        adc_val = HAL_ADC_GetValue(&hadc1);
        ///分压比1：2，3.3V/4095
        ///
        adc_val = ADC1->DR;
        float volt = adc_val * 3.3f / 4095.0f*2.0f;
        //3.0V=0% 4.2V=100%,线性运算

        if (volt<3.0f) battery_percent=0;
        else if (volt>4.2f)battery_percent=100;

        else battery_percent = (uint8_t)((volt-3.0f)/(1.2f*100));
    }
    HAL_ADC_Stop(&hadc1);

    //充电状态检测（PB0引脚，高电平=充电）
   // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
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

        osDelay(100);
    }

}