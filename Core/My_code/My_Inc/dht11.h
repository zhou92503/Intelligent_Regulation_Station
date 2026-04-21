#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"

// 你自己根据实际引脚改这里
#define DHT11_PORT    GPIOB
#define DHT11_PIN     GPIO_PIN_13

void DHT11_Init(void);
uint8_t DHT11_ReadData(uint8_t *temp, uint8_t *humi);
void Start_dht_Task(void *argument);

// 全局变量：温度、湿度
extern uint8_t dht_temp;
extern uint8_t dht_humi;
#endif