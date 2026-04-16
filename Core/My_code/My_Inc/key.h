//
// Created by zhouzhan on 2026/4/14.
//

#ifndef INTELLIGENT_REGULATION_STATION_KEY_H
#define INTELLIGENT_REGULATION_STATION_KEY_H
#include <stdint.h>

extern uint8_t oled_page;

void key_scan(void);
void Start_key_Task(void *argument);


#endif //INTELLIGENT_REGULATION_STATION_KEY_H