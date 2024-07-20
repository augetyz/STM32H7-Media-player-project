#ifndef STM32H750XBH6_7_CACHE_TEST_TOUCH_H
#define STM32H750XBH6_7_CACHE_TEST_TOUCH_H
#include "main.h"

#define TS_RST_0 HAL_GPIO_WritePin(TS_RST_GPIO_Port, TS_RST_Pin, GPIO_PIN_RESET) // ����ʵ�������޸�
#define TS_RST_1 HAL_GPIO_WritePin(TS_RST_GPIO_Port, TS_RST_Pin, GPIO_PIN_SET)   // ����ʵ�������޸�
// FT5206 I2C��ַ
#define FT5206_ADDR 0x70

// I2C��д����
#define FT_CMD_WR 0x70 // д����
#define FT_CMD_RD 0x71 // ������

// FT5206�Ĵ�������
#define FT_DEVIDE_MODE 0x00 // FT5206ģʽ���ƼĴ���
#define FT_REG_NUM_FINGER 0x02 // ����״̬�Ĵ���
#define FT_TP1_REG 0x03 // ��һ�����������ݵ�ַ
#define FT_TP2_REG 0x09 // �ڶ������������ݵ�ַ
#define FT_TP3_REG 0x0F // ���������������ݵ�ַ
#define FT_TP4_REG 0x15 // ���ĸ����������ݵ�ַ
#define FT_TP5_REG 0x1B // ��������������ݵ�ַ
#define FT_IDGLIB_VERSION	0XA1 	//�̼��汾�Ĵ���
#define FT_CHIP_ID_REG      0xA8
#define FT_ID_G_MODE 0xA4 // FT5206�ж�ģʽ���ƼĴ���
#define FT_ID_G_THGROUP 0x80 // ������Чֵ���üĴ���
#define FT_ID_G_PERIODACTIVE 0x88 // ����״̬�������üĴ���

// ���������ݽṹ
typedef struct {
    uint8_t id;        // ������ID
    uint16_t x;       // X����
    uint16_t y;       // Y����
    uint8_t pressure; // ѹ��
} TouchPoint;


void touch_RST();
void FT5206_Read_Touch(void);
void FT5206_Init(void);
void FT5206_read_reg(uint16_t reg_address,uint8_t * pdate,uint16_t size);
void FT5206_write_reg(uint16_t reg_address,uint8_t * pdate,uint16_t size);
#endif //STM32H750XBH6_7_CACHE_TEST_TOUCH_H
