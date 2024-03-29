#include "stm32f4xx.h"
//#include "usart.h"
#include "delay.h"
#include "chuankou2.h"
#include "sys.h"

//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

//10的几次幂函数
int pow(u16 a)
{
	int x,y;
		for(x=0;x<=a;x++)
	  {
			if(x==0) y=0;
			else if(x==1) y=1;
			y=y*10;
		}
	if(x==1) y=1;
	return y;
}

//串口会以16进制的数发送
void fasong(u16 l)
{
	u8 k[2];//用来储存2个u8的数据
	int i;
	int y;
	for(i=0;i<2;i++)
	{
		//取出l的前8位16进制数
		if(i==0)
		{
			k[i]=(uint8_t)(l>>8&0xFF); //强制转换成u8
//			printf("0=%d\r\n",k[0]);
		}

		//取出l的后8位16进制数
	  if(i==1)
		{
			k[i]=(uint8_t)(l&0xFF); 
			//发送数据//用u8发送
//			while()
//			{				
//				delay_us(100);
//				//k[0]的u8数据从数据缓冲区到移位寄存器后，k[1]的u8数据去数据缓冲区
//				//k[0]数据从移位寄存器发送完后k[1]的数据送到数据缓存区
//				//使数据两个u8数据发完到TDR寄存器
//				//发送寄存器TDR已空的事件TXE
//				//数据发送完成事件TC
//			}
//			printf("1=%d\r\n",k[1]);
			for(y=0;y<2;y++)
			{
				if(y==0) 
				{
					USART_SendData(USART2,0x66);
					delay_ms(100);
				}
				USART_SendData(USART2,k[y]);
				delay_ms(100);
				if(y==1) USART_SendData(USART2,0x99);
			}
		}
			
		
	}
}

int main(void)
{
	
 int i;
//	uart_init(115200);
	delay_init(168);
	k=1;
	uart2_init(115200);
//	uart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	A=1;
	B=1;
	C=1;
	u16 XIE;
	u16 CHEN;
	u16 HE;
	 XIE=0;
	 CHEN=0;
	 HE=0;
	
	
  while(1){
    while(flag==1)//如果已经接收完一组数据了
		{
//				 printf("几号:");
				 for(i=0;i<(A-1);i++)
				 {
//					 printf("A");
//					 USART_SendData(USART2,jihao[i]);
//					 printf("\r\n");	
					 XIE=XIE+(jihao[i]-'0')*(pow(A-i-1-1));
//					 printf("XIE=%d\r\n",XIE);
					         
				 }
//				 printf("\r\n");
				 fasong(XIE);
//				 printf("\r\n");
				 delay_ms(500);
//				 printf("几度:");
				 for(i=0;i<(B-1);i++)
				 {
//					 printf("B");
//					 USART_SendData(USART2,jidu[i]);
//					 printf("\r\n");
					 CHEN=CHEN+(jidu[i]-'0')*(pow(B-i-1-1));
//					 printf("CHEN=%d\r\n",CHEN);
					 
				 }
				 fasong(CHEN);
//					 printf("\r\n");
			   delay_ms(500);
//				 printf("转速:");
				 for(i=0;i<(C-1);i++)
				 {
//					 printf("C");
//					 USART_SendData(USART2,zhuansu[i]);
//					 printf("\r\n");
					 HE=HE+(zhuansu[i]-'0')*(pow(C-i-1-1));
//					 printf("HE=%d\r\n",HE);
				 }
				  fasong(HE);
//						 printf("\r\n");
//				 delay_ms(500);
//				 printf("\r\n");
					t=0;
				 //清空数组
				 flag=0;
				 A=1;
				 B=1;
				 C=1;
				 XIE=0;
				 CHEN=0;
				 HE=0;
			
		 }
				
	
	}
    
}




/*
手册中讲解到步骤15的时候的main.c源码如下：
#include "stm32f4xx.h"

//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
  
void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}

int main(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  while(1){
		GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		Delay(0x7FFFFF);
		GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		Delay(0x7FFFFF);
	
	}
}
*/


