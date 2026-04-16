#include "key.h"

#include "cmsis_os2.h"
#include "main.h"

uint8_t oled_page=0;   //0:主界面  1：风扇界面  2：电源界面

void key_scan(void)
{
    //KEY1 :PB0  ->切第0页（环境）

    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
    {
        osDelay(20);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
        {
            oled_page = 0;
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==GPIO_PIN_RESET);
        }
    }

    // KEY2: PB1 → 风扇界面(1)
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
    {
        osDelay(20);
        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
        {
            oled_page = 1;
            while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET);
        }
    }

    // KEY3: PB9 → 电源界面(2)
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
    {
        osDelay(20);
        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
        {
            oled_page = 2;
            while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET);
        }
    }
}




void Start_key_Task(void *argument)
{
    for(;;)
    {

        key_scan();
        osDelay(20);
    }

}