#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"


//ALIENTEK 探索者STM32F407开发板 实验4
//串口通信实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


int main(void)
{ 
 
//	u8 t;
//	u8 len;	
//	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();			//初始化与LED连接的硬件接口 

// 	int y[3];
	while(1)
	{
		LED0=!LED0;
		delay_ms(100);
		if(flag==1)//如果收到一组数据
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

