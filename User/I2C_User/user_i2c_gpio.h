/*
*********************************************************************************************************
*
*	模块名称 : I2C总线驱动模块
*	文件名称 : bsp_i2c_gpio.h
*	版    本 : V1.0
*	说    明 : 头文件。
*
*	Copyright (C), 2012-2013, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef _USER_I2C_GPIO_H
#define _USER_I2C_GPIO_H

#include "main.h"

#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */

void bsp_InitI2C(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);
uint8_t User_I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress,uint8_t *pData, uint16_t Size);
uint8_t User_I2C_Mem_Read(uint16_t DevAddress, uint16_t MemAddress,uint8_t *pData, uint16_t Size);
#endif
