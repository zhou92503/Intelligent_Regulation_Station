#include "cmsis_os2.h"
#include "key.h"
#include "dht11.h"
#include "encoder.h"
#include "air_sensor.h"
#include "battery.h"
#include "oled.h"


void Start_OLED_Task(void *argument)
{
    OLED_Init();

    OLED_Clear();

    for(;;)
    {
        switch(oled_page)
        {
            case 0:
                // ----- 界面 1：环境监测 -----
                OLED_ShowString(1, 1, "Env: Monitor");      // 标题
                OLED_ShowString(2, 1, "T: ");
                OLED_ShowNum(2, 4, dht_temp, 2);           // 温度
                OLED_ShowChar(2, 6, 'C');

                OLED_ShowString(3, 1, "TVOC: ");
                OLED_ShowNum(3, 7, tvoc, 4);          // 空气质量
                break;

            case 1:
                // ----- 界面 2：风扇控制 -----
                OLED_ShowString(1, 1, "Fan Control");
                OLED_ShowString(2, 1, "Speed: ");
                OLED_ShowNum(2, 7, fan_target_percent, 3);   // 风扇转速 (0-100%)
                OLED_ShowChar(2, 10, '%');

                OLED_ShowString(3, 1, "PWM: ");
                OLED_ShowNum(3, 6, fan_target_percent * 999 / 100, 4); // PWM值
                break;

            case 2:
                // ----- 界面 3：电源信息 -----
                OLED_ShowString(1, 1, "Power Info");
                OLED_ShowString(2, 1, "Bat: ");
                OLED_ShowNum(2, 5, battery_percent, 3);     // 电池电量
                OLED_ShowChar(2, 8, '%');

                OLED_ShowString(3, 1, "Charge: ");
                OLED_ShowString(3, 8, is_charging ? "ON " : "OFF"); // 充电状态
                break;
        }

        osDelay(10);
    }

}
