#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"


//ALIENTEK ̽����STM32F407������ ʵ��4
//����ͨ��ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK


int main(void)
{ 
 
//	u8 t;
//	u8 len;	
//	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();			//��ʼ����LED���ӵ�Ӳ���ӿ� 

// 	int y[3];
	while(1)
	{
		LED0=!LED0;
		delay_ms(100);
		if(flag==1)//����յ�һ������
		{
			int i;
			for(i=0;i<2;i++)
			{
				USART_SendData(USART2,y[i]);
				delay_ms(100);
			}
			LED1=!LED1;
			flag=0;
		}
	}
}

