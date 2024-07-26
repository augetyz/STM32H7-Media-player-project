#ifndef STM32H750XBH6_7_CACHE_TEST_TOUCH_H
#define STM32H750XBH6_7_CACHE_TEST_TOUCH_H
#include "main.h"

#define TS_RST_0 HAL_GPIO_WritePin(TS_RST_GPIO_Port, TS_RST_Pin, GPIO_PIN_RESET) // 根据实际引脚修改
#define TS_RST_1 HAL_GPIO_WritePin(TS_RST_GPIO_Port, TS_RST_Pin, GPIO_PIN_SET)   // 根据实际引脚修改
// FT5206 I2C地址
#define T_S_ADDR 0XBA

// I2C读写命令
#define FT_CMD_WR 0XBA // 写命令
#define FT_CMD_RD 0XBB // 读命令

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

//I2C读写命令
#define GT_CMD_WR         0X28         //写命令
#define GT_CMD_RD         0X29        //读命令

#define GT911_READ_XY_REG    0x814E /* 坐标寄存器 */

#define GT911_CLEARBUF_REG   0x814E /* 清除坐标寄存器 */

#define GT911_CONFIG_REG     0x8047 /* 配置参数寄存器 */

#define GT911_MAXXY_REG      0x8048 /*GT911触摸板的分辨率*/

#define GT911_COMMAND_REG    0x8040 /* 实时命令 */

#define GT911_PRODUCT_ID_REG 0x8140 /* 芯片ID */

#define GT911_VENDOR_ID_REG  0x814A /* 当前模组选项信息 */

#define GT911_CONFIG_VERSION_REG   0x8047 /* 配置文件版本号 */

#define GT911_CONFIG_CHECKSUM_REG  0x80FF /* 配置文件校验码 */

#define GT911_FIRMWARE_VERSION_REG 0x8144 /* 固件版本号 */

#define GT_GSTID_REG 	        0X814E  /* GT9147当前检测到的触摸情况 */
#define GT_TP1_REG 		        0X8150  /* 第一个触摸点数据地址 */
#define GT_TP2_REG 		        0X8158	/* 第二个触摸点数据地址 */
#define GT_TP3_REG 		        0X8160  /* 第三个触摸点数据地址 */
#define GT_TP4_REG 		        0X8168  /* 第四个触摸点数据地址  */
#define GT_TP5_REG 		        0X8170	/* 第五个触摸点数据地址   */



void touch_RST();
void touch_test();
void Touch_Init(void);
void Touch_Read_Reg(uint16_t reg_address,uint8_t * pdate,uint16_t size);
void Touch_Write_Reg(uint16_t reg_address,uint8_t * pdate,uint16_t size);
void Touch_ReadMaxXY(uint16_t *X,uint16_t *Y);
void Touch_scan(void);
void Touch_SoftRst();
#endif //STM32H750XBH6_7_CACHE_TEST_TOUCH_H
