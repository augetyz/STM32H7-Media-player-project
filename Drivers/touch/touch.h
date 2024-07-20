#ifndef STM32H750XBH6_7_CACHE_TEST_TOUCH_H
#define STM32H750XBH6_7_CACHE_TEST_TOUCH_H
#include "main.h"

#define TS_RST_0 HAL_GPIO_WritePin(TS_RST_GPIO_Port, TS_RST_Pin, GPIO_PIN_RESET) // 根据实际引脚修改
#define TS_RST_1 HAL_GPIO_WritePin(TS_RST_GPIO_Port, TS_RST_Pin, GPIO_PIN_SET)   // 根据实际引脚修改
// FT5206 I2C地址
#define FT5206_ADDR 0x70

// I2C读写命令
#define FT_CMD_WR 0x70 // 写命令
#define FT_CMD_RD 0x71 // 读命令

// FT5206寄存器定义
#define FT_DEVIDE_MODE 0x00 // FT5206模式控制寄存器
#define FT_REG_NUM_FINGER 0x02 // 触摸状态寄存器
#define FT_TP1_REG 0x03 // 第一个触摸点数据地址
#define FT_TP2_REG 0x09 // 第二个触摸点数据地址
#define FT_TP3_REG 0x0F // 第三个触摸点数据地址
#define FT_TP4_REG 0x15 // 第四个触摸点数据地址
#define FT_TP5_REG 0x1B // 第五个触摸点数据地址
#define FT_IDGLIB_VERSION	0XA1 	//固件版本寄存器
#define FT_CHIP_ID_REG      0xA8
#define FT_ID_G_MODE 0xA4 // FT5206中断模式控制寄存器
#define FT_ID_G_THGROUP 0x80 // 触摸有效值设置寄存器
#define FT_ID_G_PERIODACTIVE 0x88 // 激活状态周期设置寄存器

// 触摸点数据结构
typedef struct {
    uint8_t id;        // 触摸点ID
    uint16_t x;       // X坐标
    uint16_t y;       // Y坐标
    uint8_t pressure; // 压力
} TouchPoint;


void touch_RST();
void FT5206_Read_Touch(void);
void FT5206_Init(void);
void FT5206_read_reg(uint16_t reg_address,uint8_t * pdate,uint16_t size);
void FT5206_write_reg(uint16_t reg_address,uint8_t * pdate,uint16_t size);
#endif //STM32H750XBH6_7_CACHE_TEST_TOUCH_H
