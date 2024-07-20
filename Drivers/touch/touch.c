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
    HAL_I2C_Mem_Read(&hi2c1, FT5206_ADDR, reg_address, I2C_MEMADD_SIZE_8BIT, pdate, size,100);
}
void FT5206_write_reg(uint16_t reg_address,uint8_t * pdate,uint16_t size)
{
    HAL_I2C_Mem_Write(&hi2c1, FT5206_ADDR, reg_address, I2C_MEMADD_SIZE_8BIT, pdate, size,100);
}
// ��ʼ��FT5206
void FT5206_Init(void) {
    uint8_t mode = 0x00;
    uint8_t reg_value[2]={0};
    TS_RST_0; // ��λ������
    HAL_Delay(10);
    TS_RST_1; // �ͷŸ�λ
    HAL_Delay(10);

    // ���ù���ģʽ
    mode = 0x00; // ����Ϊ��������ģʽ
    FT5206_write_reg(FT_DEVIDE_MODE, &mode, 1);

    mode = 0x01; // ����Ϊ�ж�ģʽ
    FT5206_write_reg(FT_ID_G_MODE, &mode, 1);

    FT5206_read_reg(FT_CHIP_ID_REG, reg_value, 1);
    printf("Touch screen chip id:%#X\r\n", reg_value[0]);

    FT5206_read_reg(FT_IDGLIB_VERSION, reg_value, 2);
    printf("Touch screen Version:%#X\r\n", ((unsigned short)reg_value[0] << 8) + reg_value[1]);
}

// ��ȡ��������
void FT5206_Read_Touch(void) {
    uint8_t num_fingers=0;

    FT5206_read_reg(FT_REG_NUM_FINGER,&num_fingers, 1);

    // ������Ϣ
    printf("Number of fingers: %d\n", num_fingers);
    // ���������������
    num_fingers = (num_fingers > 5) ? 5 : num_fingers;

    TouchPoint touch_points[5]; // �洢����������

    for (uint8_t i = 0; i < num_fingers; i++) {
        uint8_t data[6];
        FT5206_read_reg(FT_TP1_REG + (i * 6), data, 6);

        // ��������������
        touch_points[i].id = data[0] & 0x0F; // ������ID
        touch_points[i].x = ((data[1] & 0x0F) << 8) | data[2]; // X����
        touch_points[i].y = ((data[3] & 0x0F) << 8) | data[4]; // Y����
        touch_points[i].pressure = data[5]; // ѹ��ֵ
    }

    // ������������
    for (uint8_t i = 0; i < num_fingers; i++) {
        // ���������Ӵ����߼��������ӡ��洢��������Ϣ
//        printf("Touch Point %d: ID=%d, X=%d, Y=%d, Pressure=%d\n",
//               touch_points[i].id, touch_points[i].id, touch_points[i].x, touch_points[i].y, touch_points[i].pressure);
    }
}