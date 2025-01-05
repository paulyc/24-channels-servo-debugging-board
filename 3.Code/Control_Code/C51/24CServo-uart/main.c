
#include <reg52.h>

sbit beep=P2^3;
sbit dula=P2^6;
sbit wela=P2^7;
unsigned char i=100;
unsigned char j,k,temp,key;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned char date1,date2,date3;

void Delay_Us(int i)
{
	while(--i);
}
void delay(unsigned char m)
{
	unsigned char i;
 	while(m--)
	{
		i = 10;
		while(i--)
		{
			Delay_Us(125);
		}
	 	
	}
}
void init(void)				//���ڳ�ʼ��
{
    SCON=0x50;   //UART��ʽ1:8λUART;   REN=1:������� 
    PCON=0x00;   //SMOD=0:�����ʲ��ӱ� 
    TMOD=0x20;   //T1��ʽ2,����UART������ 
    TH1=0xFD; 
    TL1=0xFD;   //UART����������:FDFD��9600;FFFF,57600
    TR1=1;	 //����T1���� 
    EA=1;
}

void send(unsigned char d)		  //����һ���ֽڵ����ݣ��β�d��Ϊ���������ݡ�
{
	SBUF = d;
	while(!TI);		//������Ϊ1 
	TI = 0;
}

bit UART_Servo(unsigned char servonum,unsigned char angle)
{
  
  servonum = 64 + servonum;
    date1 = angle/100 + 48;
    date2 = (angle%100)/10 + 48;
    date3 = angle%10 + 48;
    send(0x24);//���Ͱ�ͷ
	send(servonum);//���Ͷ�����
	send(date1);//���ͽǶ�
	send(date2);//���ͽǶ�
	send(date3);//���ͽǶ�
	send(0x23);//���Ͱ�β
	delay(100);
   	return(1);

}
void display(unsigned char num)
{
         P0=table[num];
         dula=1;
         dula=0;
         P0=0x00;
         wela=1;
         wela=0;
}

void main()
{
	init();
	while(1)
	{ 
		delay(1);
		UART_Servo(1,0);
		delay(1);
		UART_Servo(1,90); 
		delay(1);
		UART_Servo(1,180); 
		delay(1);
	}
}
