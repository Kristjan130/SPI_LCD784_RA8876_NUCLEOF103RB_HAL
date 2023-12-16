#include "main.h"
#include "TP.h"
#include "RA8876.h"
#define uchar unsigned char
#define uint unsigned int
struct _ts_event ts_event;
//_ts_event ts_event;
unsigned char GTP_CFG_DATA[]=
{
/*
0x63,0x00,0x04,0x58,0x02,0x0A,0x3D,0x00,
0x01,0x08,0x28,0x0F,0x50,0x32,0x03,0x05,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x17,
0x19,0x1D,0x14,0x90,0x2F,0x89,0x23,0x25,
0xD3,0x07,0x00,0x00,0x00,0x02,0x03,0x1D,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x19,0x32,0x94,0xD5,0x02,
0x07,0x00,0x00,0x04,0xA2,0x1A,0x00,0x90,
0x1E,0x00,0x80,0x23,0x00,0x73,0x28,0x00,
0x68,0x2E,0x00,0x68,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x16,0x15,0x14,0x11,0x10,0x0F,0x0E,0x0D,
0x0C,0x09,0x08,0x07,0x06,0x05,0x04,0x01,
0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x28,
0x27,0x26,0x25,0x24,0x23,0x22,0x21,0x20,
0x1F,0x1E,0x1C,0x1B,0x19,0x14,0x13,0x12,
0x11,0x10,0x0F,0x0E,0x0D,0x0C,0x0A,0x08,
0x07,0x06,0x04,0x02,0x00,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x71,0x01	 */

0x5A,0x00,0x05,0x90,0x01,0x05,0x0D,0x00,
0x01,0x08,0x28,0x05,0x50,0x32,0x03,0x05,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x8B,0x2B,0x0A,0x22,0x24,
0x31,0x0D,0x00,0x00,0x00,0x01,0x03,0x2D,
0x00,0x00,0x00,0x00,0x00,0x03,0x64,0x32,
0x00,0x00,0x00,0x1A,0x40,0x94,0xC5,0x02,
0x07,0x00,0x00,0x04,0x95,0x1C,0x00,0x7F,
0x22,0x00,0x71,0x28,0x00,0x62,0x31,0x00,
0x58,0x3A,0x00,0x58,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,0x10,
0x12,0x14,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x16,0x18,
0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x24,
0x26,0x13,0x12,0x10,0x0F,0x0C,0x0A,0x08,
0x06,0x04,0x02,0x00,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xE3,0x01
};

//IIC start
void TOUCH_Start(void)
{
	HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET);
	delay_us(3);
	HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_RESET);
	delay_us(3);
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
//	delay_us(1);
}

//IIC stop
void TOUCH_Stop(void)
{
	HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET);
	delay_us(3);
	HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_SET);
	delay_us(3);
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
//	delay_us(1);
}


//Wait for an answer signal
uchar TOUCH_Wait_Ack(void)
{
	uchar errtime=0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_SET);
//	delay_us(1);
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET);
//	delay_us(1);
	/*Configure GPIO pin : SSD2828_SDI_Pin */
	GPIO_InitStruct.Pin = CTP_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(CTP_SDA_GPIO_Port, &GPIO_InitStruct);
  	while(HAL_GPIO_ReadPin(CTP_SDA_GPIO_Port, CTP_SDA_Pin) == GPIO_PIN_SET)
	{
	    errtime++;
	    if(errtime>250)
		{
		  TOUCH_Stop();
		  return 1;
		}
	}
  	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  	HAL_GPIO_Init(CTP_SDA_GPIO_Port, &GPIO_InitStruct);
  	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
//	delay_us(1);
	return 0;
}



//Acknowledge
void TOUCH_Ack(void)
{
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_RESET);
	delay_us(2);
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
}

//NO Acknowledge
void TOUCH_NAck(void)
{
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
	delay_us(1);
	HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET);
	delay_us(2);
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
}


//IIC send one byte
void TOUCH_Send_Byte(uchar Byte)
{	uchar t;
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
//	delayus(5);
    for(t=0;t<8;t++)
    {
    	HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, (Byte & 0x80)?GPIO_PIN_SET:GPIO_PIN_RESET);
	   	Byte <<=1;
		delay_us(2);
		HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET);
		delay_us(2);
		HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
	//	delayus(5);
    }
}


uchar TOUCH_Read_Byte(uchar ack)
{
	uchar t,receive=0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
//	delayus(5);
	HAL_GPIO_WritePin(CTP_SDA_GPIO_Port, CTP_SDA_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = CTP_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(CTP_SDA_GPIO_Port, &GPIO_InitStruct);
//	delayus(5);
	for(t = 0; t < 8; t++)
	{
		HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_RESET);
		delay_us(4);
		HAL_GPIO_WritePin(CTP_SCL_GPIO_Port, CTP_SCL_Pin, GPIO_PIN_SET);
		delay_us(4);
	 	receive<<=1;
	 	if(HAL_GPIO_ReadPin(CTP_SDA_GPIO_Port, CTP_SDA_Pin) == GPIO_PIN_SET)receive=receive|0x01;
	//	delayus(5);
	}


   	if (ack)  TOUCH_NAck();//NO Acknowledge
   	else       TOUCH_Ack(); //Send Acknowledge

	 return receive;
}

uchar GT911_WR_Reg(uint reg,uchar *buf,uchar len)
{
	uchar i;
	uchar ret=0;
	TOUCH_Start();
 	TOUCH_Send_Byte(WRITE_ADD);
	TOUCH_Wait_Ack();
	TOUCH_Send_Byte(reg>>8);
	TOUCH_Wait_Ack();
	TOUCH_Send_Byte(reg&0XFF);
	TOUCH_Wait_Ack();
	for(i=0;i<len;i++)
	{
    	TOUCH_Send_Byte(buf[i]);
		ret=TOUCH_Wait_Ack();
		if(ret)break;
	}
    TOUCH_Stop();
	return ret;
}


void GT911_RD_Reg(uint reg,uchar *buf,uchar len)
{
	uchar i;
 	TOUCH_Start();
 	TOUCH_Send_Byte(WRITE_ADD);
	TOUCH_Wait_Ack();
 	TOUCH_Send_Byte(reg>>8);
	TOUCH_Wait_Ack();
 	TOUCH_Send_Byte(reg&0XFF);
 	TOUCH_Wait_Ack();

 	TOUCH_Start();
	TOUCH_Send_Byte(READ_ADD);
	TOUCH_Wait_Ack();
	for(i=0;i<len;i++)
	{
    	buf[i]=TOUCH_Read_Byte(i==(len-1)?1:0); //


	//	if(i==(len-1))  buf[i]=TOUCH_Read_Byte(1);
	//	else            buf[i]=TOUCH_Read_Byte(0);

	}
     TOUCH_Stop();//
}

uchar GT911_Send_Cfg(uchar * buf,uint cfg_len)
{
	uchar ret=0;
	uchar retry=0;
	for(retry=0;retry<5;retry++)
	{
		ret=GT911_WR_Reg(GTP_REG_CONFIG_DATA,buf,cfg_len);
		if(ret==0)break;
		delay_ms(10);
	}
	return ret;
}

/******************************************************************************************
*********************************************************************************************/
void Draw_Big_Point(uint x,uint y,uint colour)
{    Graphic_Mode();
	 Goto_Pixel_XY(x-1,y-1);
	 LCD_CmdWrite(0x04);
	LCD_DataWrite(colour);
	LCD_DataWrite(colour>>8);
	LCD_DataWrite(colour);
	LCD_DataWrite(colour>>8);
	LCD_DataWrite(colour);
	LCD_DataWrite(colour>>8);
	Goto_Pixel_XY(x-1,y);//Memory write position
	LCD_CmdWrite(0x04);
	LCD_DataWrite(colour);
	LCD_DataWrite(colour>>8);
	LCD_DataWrite(colour);
	LCD_DataWrite(colour>>8);
	LCD_DataWrite(colour);
	LCD_DataWrite(colour>>8);
 	Goto_Pixel_XY(x-1,y+1);//Memory write position
	LCD_CmdWrite(0x04);
	LCD_DataWrite(colour);
	LCD_DataWrite(colour>>8);
	LCD_DataWrite(colour);
	LCD_DataWrite(colour>>8);
	LCD_DataWrite(colour);
	LCD_DataWrite(colour>>8);
}

uchar GT911_read_data(void)
{	uchar buf[80] = {0xff}; uchar ret = 0;	uchar ss[4];


	GT911_RD_Reg(GTP_READ_COOR_ADDR,buf,80);

	ss[0]=0;
 	GT911_WR_Reg(GTP_READ_COOR_ADDR,ss,1);	  //Must clear  Buffer status

  	ts_event.touch_point = buf[0] & 0x0f;




  	if (ts_event.touch_point == 0)
		{

			return 0;
  		}


					switch (ts_event.touch_point)
					{
 					/*		case 10:
				           			ts_event.x10 = (uint)(buf[75] )<<8 | (uint)buf[74];
				           			ts_event.y10 = (uint)(buf[77] )<<8 | (uint)buf[76];

  							case 9:
				           			ts_event.x9 = (uint)(buf[67] )<<8 | (uint)buf[66];
				           			ts_event.y9 = (uint)(buf[69] )<<8 | (uint)buf[68];

  							case 8:
				           			ts_event.x8 = (uint)(buf[59] )<<8 | (uint)buf[58];
				           			ts_event.y8 = (uint)(buf[61] )<<8 | (uint)buf[60];

  							case 7:
				           			ts_event.x7 = (uint)(buf[51] )<<8 | (uint)buf[50];
				           			ts_event.y7 = (uint)(buf[53] )<<8 | (uint)buf[52];

							case 6:
				           			ts_event.x6 = (uint)(buf[43] )<<8 | (uint)buf[42];
				           			ts_event.y6 = (uint)(buf[45] )<<8 | (uint)buf[44];	 	  */

							case 5:
				           			ts_event.y5 = (uint)(buf[35] )<<8 | (uint)buf[34];
				           			ts_event.x5 = (uint)(buf[37] )<<8 | (uint)buf[36];

						    case 4:
						           	ts_event.y4 = (uint)(buf[27] )<<8 | (uint)buf[26];
						           	ts_event.x4 = (uint)(buf[29] )<<8 | (uint)buf[28];

						    case 3:
						           	ts_event.y3 = (uint)(buf[19] )<<8 | (uint)buf[18];
						           	ts_event.x3 = (uint)(buf[21] )<<8 | (uint)buf[20];

						    case 2:
						           	ts_event.y2 = (uint)(buf[11] )<<8 | (uint)buf[10];
						           	ts_event.x2 = (uint)(buf[13] )<<8 | (uint)buf[12];

						    case 1:
						           	ts_event.y1 = (uint)(buf[3] )<<8 | (uint)buf[2];
						           	ts_event.x1 = (uint)(buf[5] )<<8 | (uint)buf[4];

				    break;
						    default:
						    return 0;
					}



	return ret;
}


void inttostr(uint value,uchar *str)
{
	str[0]=value/1000+48;
	str[1]=value%1000/100+48;
	str[2]=value%1000%100/10+48;
 	str[3]=value%1000%100%10+48;
}



void TOUCH_Init(void)
{
	HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(CTP_INT_GPIO_Port, CTP_INT_Pin, GPIO_PIN_RESET);
	delay_ms(50);
	HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_SET);
	delay_ms(200);
	//ACC=PEN_INT;  	    //CTP INT  SET CTP IIC ADDRESS
	//ACC=PEN_INT;  	   //CTP INT  SET CTP IIC ADDRESS
 	delay_ms(200);
}


void TPTEST(void)
{uchar ss[4]; uchar re=1;//	uchar i;  uchar bb[187];
   	ts_event.Key_Sta=Key_Up;

	  					ts_event.x1=0;
						ts_event.y1=0;
						ts_event.x2=0;
						ts_event.y2=0;
						ts_event.x3=0;
						ts_event.y3=0;
						ts_event.x4=0;
						ts_event.y4=0;
						ts_event.x5=0;
						ts_event.y5=0;



		Select_Main_Window_16bpp();
		Main_Image_Start_Address(0);
		Main_Image_Width(400);
		Main_Window_Start_XY(0,0);

    	Canvas_Image_Start_address(0);//Layer 1
		Canvas_image_width(400);//
    	Active_Window_XY(0,0);
		Active_Window_WH(400,1280);

		Foreground_color_65k(Black);
		Line_Start_XY(0,0);
		Line_End_XY(399,1279);
		Start_Square_Fill();

		 Foreground_color_65k(Black);
	Background_color_65k(Blue2);
	CGROM_Select_Internal_CGROM();
	Font_Select_12x24_24x24();
 	Goto_Text_XY(0,Line1);
	Show_String("www.buydisplay.ocm  CTP test");

 	Goto_Text_XY(0,Line52);
	Show_String("exit");
 	Goto_Text_XY(330,Line52);
	Show_String("clear");



  	Foreground_color_65k(White);
	Background_color_65k(Black);
	CGROM_Select_Internal_CGROM();
	Font_Select_8x16_16x16();


				TOUCH_Init();

			re=GT911_Send_Cfg((uchar*)GTP_CFG_DATA,sizeof(GTP_CFG_DATA));
			if(re==0)
			{Goto_Text_XY(0,60);Show_String("send CFG OK");}
	 		else  {Goto_Text_XY(0,60);Show_String("send CFG NOK");}


 /*
	 	GT911_RD_Reg(GTP_REG_CONFIG_DATA,bb,sizeof(GTP_CFG_DATA));


		i=0;
		  Text_Mode();
		 Goto_Text_XY(0,100);
	 while(i<186)
		{	inttostr(bb[i],ss);
		 LCD_CmdWrite(0x04);
		LCD_DataWrite(ss[0]);	delay_us(2); Check_Mem_WR_FIFO_not_Full();
		LCD_DataWrite(ss[1]);	delay_us(2); Check_Mem_WR_FIFO_not_Full();
		LCD_DataWrite(ss[2]);	delay_us(2);  Check_Mem_WR_FIFO_not_Full();
		LCD_DataWrite(ss[3]);	delay_us(2);  Check_Mem_WR_FIFO_not_Full();
		LCD_DataWrite(',');	delay_us(2);   Check_Mem_WR_FIFO_not_Full();
		i+=1;
		}
*/

	   	ss[0]=0;
 	GT911_WR_Reg(GTP_READ_COOR_ADDR,ss,1);	  //Must clear  Buffer status

 	buttonClicked = 0;
	while(buttonClicked == 0)
	{	   	Foreground_color_65k(White);
			Background_color_65k(Black);
			CGROM_Select_Internal_CGROM();
			Font_Select_8x16_16x16();


		  	Goto_Text_XY(0,465);
		  	Show_String("Coordinate");



	   GT911_RD_Reg(GTP_READ_COOR_ADDR,ss,1);
	   if(ss[0]&0x80)
			{
					GT911_read_data();
					ts_event.Key_Sta=Key_Up;

					if(ts_event.x1<=50&&ts_event.x1>5&&ts_event.y1<=28&&ts_event.y1>5)return;
					if(ts_event.x1>=340&&ts_event.y1<=28)
					{
						Select_Main_Window_16bpp();
						Main_Image_Start_Address(0);
						Main_Image_Width(400);
						Main_Window_Start_XY(0,0);

				    	Canvas_Image_Start_address(0);//Layer 1
						Canvas_image_width(400);//
				    	Active_Window_XY(0,0);
						Active_Window_WH(400,1280);

						Foreground_color_65k(Black);
						Line_Start_XY(0,0);
						Line_End_XY(399,1279);
						Start_Square_Fill();

							 Foreground_color_65k(Black);
						Background_color_65k(Blue2);
						CGROM_Select_Internal_CGROM();
						Font_Select_12x24_24x24();
					 	Goto_Text_XY(0,Line1);
						Show_String("www.buydisplay.ocm  CTP test");

					 	Goto_Text_XY(0,Line52);
						Show_String("exit");
					 	Goto_Text_XY(330,Line52);
						Show_String("clear");
					}

					 else{

					inttostr(ts_event.x1,ss);


				  	Goto_Text_XY(100,465);   //Set the display position

				  	Show_String("X=");
					Text_Mode();
					LCD_CmdWrite(0x04);
				  	LCD_DataWrite(ss[0]);
					 Check_Mem_WR_FIFO_not_Full();
				  	LCD_DataWrite(ss[1]);
					 Check_Mem_WR_FIFO_not_Full();
				  	LCD_DataWrite(ss[2]);
					 Check_Mem_WR_FIFO_not_Full();
 				  	LCD_DataWrite(ss[3]);
					 Check_Mem_WR_FIFO_not_Full();

					inttostr(ts_event.y1,ss);
				  	Goto_Text_XY(200, 465);   //Set the display position

				  	Show_String("Y=");
 					Text_Mode();
					LCD_CmdWrite(0x04);
				  	LCD_DataWrite(ss[0]);
					 Check_Mem_WR_FIFO_not_Full();
				  	LCD_DataWrite(ss[1]);
					 Check_Mem_WR_FIFO_not_Full();
				  	LCD_DataWrite(ss[2]);
					 Check_Mem_WR_FIFO_not_Full();
				  	LCD_DataWrite(ss[3]);
					  Check_Mem_WR_FIFO_not_Full();



					Draw_Big_Point(ts_event.x1,1280-ts_event.y1,color65k_red);
					Draw_Big_Point(ts_event.x2,1280-ts_event.y2,color65k_green);
					Draw_Big_Point(ts_event.x3,1280-ts_event.y3,color65k_blue);
					Draw_Big_Point(ts_event.x4,1280-ts_event.y4,color65k_cyan);
					Draw_Big_Point(ts_event.x5,1280-ts_event.y5,color65k_purple);




					}

						ts_event.x1=0;
						ts_event.y1=0;
						ts_event.x2=0;
						ts_event.y2=0;
						ts_event.x3=0;
						ts_event.y3=0;
						ts_event.x4=0;
						ts_event.y4=0;
						ts_event.x5=0;
						ts_event.y5=0;


			}


    }
	buttonClicked = 0;


}
