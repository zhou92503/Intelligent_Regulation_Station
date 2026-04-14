#include "key.h"

#include "cmsis_os2.h"
#include "fan.h"
#include "main.h"

void key_scan(void)
{
    // KEY1 风扇+
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == GPIO_PIN_RESET)
    {
        uint8_t g = fan_get_gear();
        if(g < 5) fan_set_gear(g+1);
        osDelay(30); // 这里用 osDelay！符合RTOS
    }

    // KEY2 风扇-
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2) == GPIO_PIN_RESET)
    {
        uint8_t g = fan_get_gear();
        if(g > 0) fan_set_gear(g-1);
        osDelay(30); // 这里用 osDelay！
    }
}
