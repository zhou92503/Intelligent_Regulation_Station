#include "air_sensor.h"
#include "main.h"

uint16_t tvoc_value =0;
#define AGSS02MA_ADDR 0x1A <<1

void air_sensor_update(void)
{
   uint8_t buf[3];
   if (HAL_I2C_Mem_Read(&hi2c1, AGSS02MA_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, buf, 3, 1000)==HAL_OK) {
       tvoc_value = (buf[0]<<8) | buf[1];
   }
}


uint16_t air_sensor_get_tvoc(void)
{
    return tvoc_value;
}


