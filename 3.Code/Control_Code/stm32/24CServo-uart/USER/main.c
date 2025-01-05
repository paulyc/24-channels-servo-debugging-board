#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"
#include "timer.h"  
#include "malloc.h"  

#define usart2_baund  9600//����2������
unsigned char date1,date2,date3;
int  i;
	
//���ڷ���һ���ֽ�
static void MYUSART_SendData(u8 data)
{
	while((USART2->SR&0X40)==0); 
	USART2->DR = data;
}
void UART_Servo(unsigned char servonum,unsigned char angle)
{
  servonum = 64 + servonum;
    date1 = angle/100 + 48;
    date2 = (angle%100)/10 + 48;
    date3 = angle%10 + 48;
  MYUSART_SendData(0x24);//���Ͱ�ͷ
	MYUSART_SendData(servonum);//���Ͷ�����
	MYUSART_SendData(date1);//���ͽǶ�
	MYUSART_SendData(date2);//���ͽǶ�
	MYUSART_SendData(date3);//���ͽǶ�
	MYUSART_SendData(0x23);//���Ͱ�β
	delay_ms(100);
}

int main(void)
{
	
	//��ʼ������
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();  	    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ������1������Ϊ115200������֧��USMART
	usart2_init(usart2_baund);//��ʼ������2,������ģ��ͨѶ
	mem_init();
	delay_ms(2000); //�ӳ�2s�������ư�����������
	for(i = 0;i<180;i+=5){
		UART_Servo(1,i);
	}
	UART_Servo(1,0);
	
	while(1){
	}

}




