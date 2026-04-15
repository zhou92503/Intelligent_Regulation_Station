//
// Created by zhouzhan on 2026/4/14.
//

#ifndef INTELLIGENT_REGULATION_STATION_DHT11_H
#define INTELLIGENT_REGULATION_STATION_DHT11_H

#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"

extern uint8_t dht11_temp;
extern uint8_t dht11_humi;


void dht11_init(void);
void dht11_update(void);

uint8_t dht11_get_temp(void);
uint8_t dht11_get_humi(void);

#endif

#endif //INTELLIGENT_REGULATION_STATION_DHT11_H