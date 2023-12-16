#ifndef __TP_H__
#define __TP_H__

//Touch Status	 
#define Key_Down 0x01
#define Key_Up   0x00 


struct _ts_event
{
	unsigned int    x1;
	unsigned int    y1;
	unsigned int    x2;
	unsigned int    y2;
	unsigned int    x3;
	unsigned int    y3;
	unsigned int    x4;
	unsigned int    y4;
	unsigned int    x5;
	unsigned int    y5;

    unsigned char     touch_point;
    unsigned char     Key_Sta;
};

#define WRITE_ADD	0xba 
#define READ_ADD	0xbb

#define CT_MAX_TOUCH    5		//

// Registers define
#define GTP_READ_COOR_ADDR    0x814e
#define GTP_REG_SLEEP         0x8040
#define GTP_REG_SENSOR_ID     0x814a
#define GTP_REG_CONFIG_DATA   0x8047
#define GTP_REG_VERSION       0x8440

//#define CT_READ_XY_REG 	0x814E  	//
//#define CT_CONFIG_REG   0x8047	//
void TOUCH_Init(void);
void TOUCH_Start(void);
void TOUCH_Stop(void);
unsigned char TOUCH_Wait_Ack(void);
void TOUCH_Ack(void);
void TOUCH_NAck(void);

void TOUCH_Send_Byte(unsigned char txd);
unsigned char TOUCH_Read_Byte(unsigned char ack);
void Draw_Big_Point(unsigned int x,unsigned int y,unsigned int colour);
unsigned char GT911_read_data(void);
void inttostr(unsigned int value,unsigned char *str);
void GT911_RD_Reg(unsigned int reg,unsigned char *buf,unsigned char len);
unsigned char GT911_WR_Reg(unsigned int reg,unsigned char *buf,unsigned char len);

void TPTEST(void);

#endif//__TP_H__
