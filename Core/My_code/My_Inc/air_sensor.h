

#ifndef INTELLIGENT_REGULATION_STATION_AIR_SENSOR_H
#define INTELLIGENT_REGULATION_STATION_AIR_SENSOR_H

#include "main.h"

void air_sensor_init(void);
void air_sensor_update(void);
uint16_t air_sensor_get_tvoc(void);

void Start_air_sensor_Task(void *argument);

extern  uint16_t tvoc;



#endif //INTELLIGENT_REGULATION_STATION_AIR_SENSOR_H