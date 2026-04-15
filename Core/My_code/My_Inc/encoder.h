//
// Created by zhouzhan on 2026/4/14.
//

#ifndef INTELLIGENT_REGULATION_STATION_ENCODER_H
#define INTELLIGENT_REGULATION_STATION_ENCODER_H

#include "main.h"

extern uint8_t fan_target_percent;
void encoder_scan(void);
void Start_encoder_Task(void *argument);

#endif //INTELLIGENT_REGULATION_STATION_ENCODER_H