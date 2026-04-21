#include "dht11.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"

extern TIM_HandleTypeDef htim4;

// 全局变量：温度、湿度
uint8_t dht_temp = 0;
uint8_t dht_humi = 0;

// 微秒延时（TIM4 1us精度）
void delay_us(uint32_t us)
{
    __HAL_TIM_SET_COUNTER(&htim4, 0);
    HAL_TIM_Base_Start(&htim4);
    while(__HAL_TIM_GET_COUNTER(&htim4) < us);
 //   HAL_TIM_Base_Stop(&htim4);
}

// 设置为输出模式
void DHT11_GPIO_Out(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

// 设置为输入模式
void DHT11_GPIO_In(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

// DHT11 启动信号
void DHT11_Start(void)
{
    DHT11_GPIO_Out();
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
    delay_us(20000);   // 20ms 启动
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
    delay_us(30);
}

// 检测 DHT11 响应
uint8_t DHT11_Check_Response(void)
{
    uint8_t retry = 0;
    DHT11_GPIO_In();

    // 等待低电平
    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) && retry < 100)
    {
        delay_us(1);
        retry++;
    }
    if (retry >= 100) return 0;

    retry = 0;
    // 等待高电平
    while (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) && retry < 100)
    {
        delay_us(1);
        retry++;
    }
    if (retry >= 100) return 0;

    return 1;
}

// 读取一个字节
uint8_t DHT11_Read_Byte(void)
{
    uint8_t i, dat = 0;

    for (i = 0; i < 8; i++)
    {
        while (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
        delay_us(40);

        dat <<= 1;
        if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
            dat |= 1;

        while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
    }
    return dat;
}

// 读取温湿度
uint8_t DHT11_ReadData(uint8_t *temp, uint8_t *humi)
{
    uint8_t data[5];

    DHT11_Start();
    if (!DHT11_Check_Response())
        return 0;

    data[0] = DHT11_Read_Byte();
    data[1] = DHT11_Read_Byte();
    data[2] = DHT11_Read_Byte();
    data[3] = DHT11_Read_Byte();
    data[4] = DHT11_Read_Byte();

    if (data[0] + data[1] + data[2] + data[3] != data[4])
        return 0;

    *humi = data[0];
    *temp = data[2];

    return 1;
}

// 初始化
void DHT11_Init(void)
{
    DHT11_GPIO_Out();
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
    osDelay(1000);
}



// DHT11 任务
void Start_dht_Task(void *argument)
{
    DHT11_Init();

    for (;;)
    {
        HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET); // 拉低
        osDelay(500);
        HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);   // 拉高
        osDelay(500);
    }
}