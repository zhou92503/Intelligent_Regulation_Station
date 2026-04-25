#include "air_sensor.h"

#include "cmsis_os2.h"
#include "main.h"

uint16_t tvoc=0;
#define AGS02MA_ADDR 0x1A <<1

uint16_t AGS02MA_Read(void)
{
    uint8_t buf[5] = {0};

    // I2C读取
    if(HAL_I2C_Master_Receive(&hi2c2, AGS02MA_ADDR, buf, 5, 100) != HAL_OK)
    {
        return 0xFFFF;
    }

    // CRC校验
    uint8_t crc = 0;
    for(int i=0; i<4; i++) crc += buf[i];
    if(crc != buf[4]) return 0xFFFF;

    // 计算TVOC
    uint16_t tvoc = ((uint16_t)buf[1] << 8) | buf[2];
    return tvoc;
}

void Start_air_sensor_Task(void *argument)
{

    for(;;)
    {
        tvoc = AGS02MA_Read();

        osDelay(50);
    }

}

