#include "dht11.h"

static uint8_t temp = 0;
static uint8_t humi = 0;

#define DHT_PIN    GPIO_PIN_13
#define DHT_PORT   GPIOB

// 微秒延时（72MHz主频，FreeRTOS下仅用于DHT11时序，不阻塞调度）
static void delay_us(uint32_t us)
{
    uint32_t d = us * 7;
    while(d--);
}

// 读取一个字节
uint8_t DHT_ReadByte(void)
{
    uint8_t i, dat = 0;

    for(i = 0; i < 8; i++)
    {
        // 等待高电平
        while(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_RESET);
        delay_us(40);
        dat <<= 1;
        // 判断电平
        if(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_SET)
            dat |= 1;
        // 等待低电平
        while(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_SET);
    }
    return dat;
}

void dht11_update(void)
{
    uint8_t buf[5];

    // 1. 发送起始信号：拉低18ms
    HAL_GPIO_WritePin(DHT_PORT, DHT_PIN, GPIO_PIN_RESET);
    delay_us(18000); // 18ms微秒延时
    // 2. 拉高20us，等待DHT11响应
    HAL_GPIO_WritePin(DHT_PORT, DHT_PIN, GPIO_PIN_SET);
    delay_us(20);

    // 3. 等待DHT11响应信号
    if(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_RESET)
    {
        // 等待响应低电平结束
        while(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_RESET)
        // 等待响应高电平结束
        while(HAL_GPIO_ReadPin(DHT_PORT, DHT_PIN) == GPIO_PIN_SET)

        // 4. 读取4个数据字节+1个校验字节
        buf[0] = DHT_ReadByte(); // 湿度整数
        buf[1] = DHT_ReadByte(); // 湿度小数
        buf[2] = DHT_ReadByte(); // 温度整数
        buf[3] = DHT_ReadByte(); // 温度小数
        buf[4] = DHT_ReadByte(); // 校验和

        // 5. 校验数据
        if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
        {
            humi = buf[0];
            temp = buf[2];
        }
    }
    // 6. 通信结束，拉高引脚，等待下一次采集
    HAL_GPIO_WritePin(DHT_PORT, DHT_PIN, GPIO_PIN_SET);
}

uint8_t dht11_get_temp(void) { return temp; }
uint8_t dht11_get_humi(void) { return humi; }