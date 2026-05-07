#include "air_sensor.h"

#include "cmsis_os2.h"
#include "main.h"

uint16_t tvoc=0;
#define AGS02MA_ADDR 0x3A



// AGS02MA 标准 CRC8 算法
uint8_t AGS02MA_CRC8(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0xFF;
    for(uint8_t i=0; i<len; i++)
    {
        crc ^= data[i];
        for(uint8_t j=0; j<8; j++)
        {
            if(crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc <<= 1;
        }
    }
    return crc;
}

uint16_t AGS02MA_Read(void)
{
    uint8_t buf[5] = {0};
    uint8_t cmd = 0x00;  // 读 TVOC 命令

    // 1. 先发命令：0x00
    if(HAL_I2C_Master_Transmit(&hi2c2, AGS02MA_ADDR, &cmd, 1, 100) != HAL_OK)
    {
        return 0xFFFF;
    }

    // 2. 延时 20~30ms（传感器必须要转换时间）
    osDelay(25);

    // 3. 读取 5 字节数据
    if(HAL_I2C_Master_Receive(&hi2c2, AGS02MA_ADDR, buf, 5, 100) != HAL_OK)
    {
        return 0xFFFF;
    }

    // 4. 正确 CRC 校验（前4字节校验，第5字节是校验值）
    uint8_t crc_cal = AGS02MA_CRC8(buf, 4);
    if(crc_cal != buf[4])
    {
        return 0xFFFF;
    }

    // 5. 正确解析 TVOC
    uint16_t tvoc_val = ((uint16_t)buf[1] << 8) | buf[2];
    return tvoc_val;
}

void Start_air_sensor_Task(void *argument)
{
    for(;;)
    {
        tvoc = AGS02MA_Read();

        osDelay(50);
    }
}

