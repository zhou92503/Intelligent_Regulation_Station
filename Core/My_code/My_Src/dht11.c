#include "dht11.h"

static uint8_t temp = 0;
static uint8_t humi = 0;

#define DHT11_ADDR 0x5C <<1

// 微秒延时（72MHz主频，FreeRTOS下仅用于DHT11时序，不阻塞调度）
static void delay_us(uint32_t us)
{
    uint32_t d = us * 7;
    while(d--);
}

// 读取一个字节
void dht11_update(void)
{
     uint8_t buf[4];
    if (HAL_I2C_Mem_Read(&hi2c1, DHT11_ADDR, 0, 1, buf, 4, 100)==HAL_OK)
    {

       dht11_humi = buf[0];
        dht11_temp =buf[2];
    }
}

uint8_t dht11_get_temp(void)
{
    return dht11_temp;
}

uint8_t dht11_get_humi(void)
{
    return dht11_humi;
}