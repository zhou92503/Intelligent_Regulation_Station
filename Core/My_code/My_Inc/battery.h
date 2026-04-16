//
// Created by zhouzhan on 2026/4/14.
//

#ifndef INTELLIGENT_REGULATION_STATION_BATTERY_H
#define INTELLIGENT_REGULATION_STATION_BATTERY_H

#include "main.h"

float battery_get_voltage(void);
uint8_t battery_get_percent(void);
void battery_update(void);
void Start_Battery_Task(void *argument);


extern uint8_t battery_percent;

extern uint8_t is_charging;

#endif //INTELLIGENT_REGULATION_STATION_BATTERY_H