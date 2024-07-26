#include "touch.h"
#include "i2c.h"
#include "user_i2c_gpio.h"

void touch_RST()
{
    TS_RST_0;
    HAL_Delay(10);
    TS_RST_1;
    HAL_Delay(10);
}
void Touch_Read_Reg(uint16_t reg_address,uint8_t * pdate,uint16_t size)
{
    User_I2C_Mem_Read(T_S_ADDR, reg_address, pdate, size);
}
void Touch_Write_Reg(uint16_t reg_address,uint8_t * pdate,uint16_t size)
{
    User_I2C_Mem_Write(T_S_ADDR, reg_address, pdate, size);
}
// 初始化屏幕
void Touch_Init(void) {
    uint8_t mode = 0x00;
    uint8_t buffer[8]={0};
    uint16_t X_Max,Y_Max;
    TS_RST_0; // 复位触摸屏
    HAL_Delay(20);
    TS_RST_1; // 释放复位
    HAL_Delay(200);
    /*检测I2C设备地址是否有回应，并在调用"i2c_CheckDevice()"过程中初始化软件I2C的SDA、SCL总线*/
    if(i2c_CheckDevice(T_S_ADDR)==0)
        printf("i2c_CheckDevice:True\n");
    else
    {
        printf("i2c_CheckDevice:False\n");
        return;
    }
    Touch_Read_Reg(GT911_PRODUCT_ID_REG,buffer,6);
    buffer[6]=buffer[4];
    buffer[4]=0;
    printf("Touch screen Version:%s\r\n",buffer);
    printf("Default Ver:%#x\r\n",((buffer[5]<<8) | buffer[6]));   /* 打印固件版本 */

    if(buffer[0] != 0x31)
    {
        Touch_Read_Reg(0x804D,buffer,1);
        buffer[0]&= 0x3;     /* 获取中断模式 */
        printf("buffer[0] != 0x31\r\n");
    }
    else {
        Touch_Read_Reg(0x8056,buffer,1);
        buffer[0]&= 0x3;     /* 获取中断模式 */
    }
    switch(buffer[0]) {
        case 0x0:
            printf("InterruptMode:IntRisingEdge\r\n");
            break;
        case 0x1:
            printf("InterruptMode:IntFallingEdge\r\n");
            break;
        case 0x2:
            printf("InterruptMode:IntLowLevel\r\n");
            break;
        case 0x3:
            printf("InterruptMode:IntHighLevel\r\n");
            break;
        default : printf("InterruptMode: Error\r\n");
            break;
    }

    Touch_ReadMaxXY(&X_Max,&Y_Max);
    printf("Touch_ReadMaxXY X:%d Y:%d\r\n",X_Max,Y_Max);
    Touch_SoftRst();
}
void Touch_ReadMaxXY(uint16_t *X,uint16_t *Y)
{
    uint8_t buf[4];
    Touch_Read_Reg(GT911_MAXXY_REG,buf,4);
    *X = buf[0] + buf[1] * 256;
    *Y = buf[2] + buf[3] * 256;
}
// 读取触摸数据
void Touch_scan(void) {
    uint8_t num_fingers=0;
    uint8_t buffer[9];
    uint8_t temp=0;
    uint16_t coord_X,coord_Y;
    Touch_Read_Reg(GT911_READ_XY_REG,&num_fingers, 1);
    Touch_Write_Reg(GT911_CLEARBUF_REG,&temp,1);//清标志
    num_fingers&=0XF;
    printf("Number of fingers: %d\n", num_fingers);
    for (uint8_t i = 0; i < num_fingers; i++) {
        Touch_Read_Reg(GT911_READ_XY_REG + 1 + (i * 4), buffer, 4);
        coord_X=((uint16_t )buffer[1] << 8) + buffer[0];
        coord_Y=((uint16_t )buffer[3] << 8) + buffer[2];
        printf("The Coord:X:%d,Y:%d\n",coord_X,coord_Y);
    }
}

void touch_test()
{
    touch_RST();
    printf("i2c_CheckDevice:%d\n",i2c_CheckDevice(T_S_ADDR));
}
void Touch_SoftRst()
{
    uint8_t temp=0;
    temp=2;
    Touch_Write_Reg(GT911_COMMAND_REG,&temp,1);
    HAL_Delay(100);
    temp=0;
    Touch_Write_Reg(GT911_COMMAND_REG,&temp,1);
}