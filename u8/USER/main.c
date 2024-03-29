#include "stm32f4xx.h"
//#include "usart.h"
#include "delay.h"
#include "chuankou2.h"
#include "sys.h"

//ALIENTEK ̽����STM32F407������ ʵ��0
//STM32F4����ģ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

//10�ļ����ݺ���
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

//���ڻ���16���Ƶ�������
void fasong(u16 l)
{
	u8 k[2];//��������2��u8������
	int i;
	int y;
	for(i=0;i<2;i++)
	{
		//ȡ��l��ǰ8λ16������
		if(i==0)
		{
			k[i]=(uint8_t)(l>>8&0xFF); //ǿ��ת����u8
//			printf("0=%d\r\n",k[0]);
		}

		//ȡ��l�ĺ�8λ16������
	  if(i==1)
		{
			k[i]=(uint8_t)(l&0xFF); 
			//��������//��u8����
//			while()
//			{				
//				delay_us(100);
//				//k[0]��u8���ݴ����ݻ���������λ�Ĵ�����k[1]��u8����ȥ���ݻ�����
//				//k[0]���ݴ���λ�Ĵ����������k[1]�������͵����ݻ�����
//				//ʹ��������u8���ݷ��굽TDR�Ĵ���
//				//���ͼĴ���TDR�ѿյ��¼�TXE
//				//���ݷ�������¼�TC
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
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
    while(flag==1)//����Ѿ�������һ��������
		{
//				 printf("����:");
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
//				 printf("����:");
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
//				 printf("ת��:");
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
				 //�������
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
�ֲ��н��⵽����15��ʱ���main.cԴ�����£�
#include "stm32f4xx.h"

//ALIENTEK ̽����STM32F407������ ʵ��0
//STM32F4����ģ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
  
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


