#include "battery.h"

static float bat_volt = 0.0f;
static uint8_t bat_percent = 0;

void battery_update(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100);

    uint16_t adc_val = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_Stop(&hadc1);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

    bat_volt = adc_val * 3.3f / 4095 * 2.0f;

    if (bat_volt>=4.2f)  bat_percent=100;
    else if (bat_volt>=4.0f) bat_percent=80;
    else if (bat_volt>=3.8f)  bat_percent=60;
    else if (bat_volt>=3.6f)  bat_percent=40;
    else if (bat_volt>=3.4f)  bat_percent=20;
    else bat_percent = 0;

}

uint8_t battery_get_percent(void)
{
    return bat_percent;
}

float battery_get_voltage(void)
{
    return bat_volt;
}