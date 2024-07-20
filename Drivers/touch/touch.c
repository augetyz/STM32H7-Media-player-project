#include "touch.h"
#include "i2c.h"

void touch_RST()
{
    TS_RST_0;
    HAL_Delay(10);
    TS_RST_1;
}
void FT5206_read_reg(uint16_t reg_address,uint8_t * pdate,uint16_t size)
{
    HAL_I2C_Mem_Read(&hi2c4, FT_CMD_RD, reg_address, I2C_MEMADD_SIZE_8BIT, pdate, size,100);
}
void FT5206_write_reg(uint16_t reg_address,uint8_t * pdate,uint16_t size)
{
    HAL_I2C_Mem_Write(&hi2c4, FT_CMD_WR, reg_address, I2C_MEMADD_SIZE_8BIT, pdate, size,100);
}
// 初始化FT5206
void FT5206_Init(void) {
    uint8_t mode = 0x00;
    uint8_t reg_value[2]={0};
    TS_RST_0; // 复位触摸屏
    HAL_Delay(10);
    TS_RST_1; // 释放复位
    HAL_Delay(10);

    // 配置工作模式
    mode = 0x00; // 设置为正常工作模式
    FT5206_write_reg(FT_DEVIDE_MODE, &mode, 1);

    mode = 0x01; // 设置为中断模式
    FT5206_write_reg(FT_ID_G_MODE, &mode, 1);

    FT5206_read_reg(FT_CHIP_ID_REG, reg_value, 1);
    printf("Touch screen chip id:%#X\r\n", reg_value[0]);

    FT5206_read_reg(FT_IDGLIB_VERSION, reg_value, 2);
    printf("Touch screen Version:%#X\r\n", ((unsigned short)reg_value[0] << 8) + reg_value[1]);
}

// 读取触摸数据
void FT5206_Read_Touch(void) {
    uint8_t num_fingers=0;

    FT5206_read_reg(FT_REG_NUM_FINGER,&num_fingers, 1);

    // 调试信息
    printf("Number of fingers: %d\n", num_fingers);
    // 限制最大触摸点数量
    num_fingers = (num_fingers > 5) ? 5 : num_fingers;

    TouchPoint touch_points[5]; // 存储触摸点数据

    for (uint8_t i = 0; i < num_fingers; i++) {
        uint8_t data[6];
        FT5206_read_reg(FT_TP1_REG + (i * 6), data, 6);

        // 解析触摸点数据
        touch_points[i].id = data[0] & 0x0F; // 触摸点ID
        touch_points[i].x = ((data[1] & 0x0F) << 8) | data[2]; // X坐标
        touch_points[i].y = ((data[3] & 0x0F) << 8) | data[4]; // Y坐标
        touch_points[i].pressure = data[5]; // 压力值
    }

    // 处理触摸点数据
    for (uint8_t i = 0; i < num_fingers; i++) {
        // 这里可以添加处理逻辑，例如打印或存储触摸点信息
//        printf("Touch Point %d: ID=%d, X=%d, Y=%d, Pressure=%d\n",
//               touch_points[i].id, touch_points[i].id, touch_points[i].x, touch_points[i].y, touch_points[i].pressure);
    }
}