#include "sys.h"
//#include "usart.h"
#include "chuankou2.h"
//
u16 USART_RX_STA=0;
u8 jihao[5];
u8 jidu[5];
u8 zhuansu[5];//[1,0,0,0];
u16 time = 1000;//串口只能发送u8 数据，需要拆分发送 u16 为两个字节，串口发送每次只能发送一个字节，需要拆分单独发送
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  

//要用printf函数就要加
#if 1                     //防止编译时被优化掉
#pragma import(__use_no_semihosting)   //#pragma 的作用是设定编译器的状态或者是指示编译器完成一些特定的动作，这条语句是为了关闭半主机模式           
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x)             //这是在rt_sys.h中定义的库退出函数。库中的所有出口最终都会调用_sys_exit()  //定义_sys_exit()以避免使用半主机模式    
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	

	 while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
	 USART2->DR = (u8) ch;      
	 return ch;
}
#endif                                                                   
                                                                       //重定向printf函数                                                                 
// //初始化IO 串口1 
////bound:波特率
//void uart_init(u32 bound){
//   //GPIO端口设置
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NV0IC_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
// 
//	//串口1对应引脚复用映射
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
//	
//	//USART1端口配置
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
//	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

//   //USART1 初始化设置
//	USART_InitStructure.USART_BaudRate = bound;//波特率设置
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
//  USART_Init(USART1, &USART_InitStructure); //初始化串口1
//	
//  USART_Cmd(USART1, ENABLE);  //使能串口1 
//	
//	//USART_ClearFlag(USART1, USART_FLAG_TC);
//	
//#if EN_USART1_RX	  //使能串口1的接收
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断，接收到数据中断
//	                                              // RXNE（读数据寄存器非空）：置1表示已经有数据被接收到并且可以读出来了，通过读USART_DR可以将该位清零，也可以向该位写0，直接清除

//	//Usart1 NVIC 配置
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器

//#endif
//	
//}                                                                    

void uart2_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART2, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART2_RX	  //使能串口1的接收
  
	 

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断，接收到数据中断
	                                              // RXNE（读数据寄存器非空）：置1表示已经有数据被接收到并且可以读出来了，通过读USART_DR可以将该位清零，也可以向该位写0，直接清除

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器

#endif
	
}

int A,B,C;
int q;
int t=0;
int k;//串口中断现在要取第几个数
int flag;
void USART2_IRQHandler(void)
{
	u16 jieshou;//用来存放接收到的数据
	
//	u16 a[15];//用来存放接收到的数据
////	int i;
	//表示第几组数据	
	
//	t=0;//初始化t
	//一个一个数据接收
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾（下面判断）) //这是判断读数据寄存器是否空，因为接受到了字符才会产生中断，所以不是空的，这个判断成立
	{
		jieshou=USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
		if(jieshou=='#')//表示接收到起始数据
		{
			t=1;//表示第一组数据开始
			q=0;
		}
		else if(t==1&&jieshou!='P')//表示第一组数据的储存
		{
			jihao[q]=jieshou;
			q++;		
			A++;
//			printf("A=%d\r\n",A);
			
		}
		if(jieshou=='P')
		{
			 t=2;
			 q=0;
		}
		else if(t==2&&jieshou!='T')
		{
			jidu[q]=jieshou;
			q++;
			B++;
//			printf("B=%d\r\n",B);
			
		}
		if(jieshou=='T')
		{
			t=3;
			q=0;
		}
		else if(t==3&&jieshou!='!')
		{
			zhuansu[q]=jieshou;
			q++;
			C++;
//			printf("C=%d\r\n",C);
		}
		if (jieshou=='!')
		{
			t=4;
			flag=1;
			q=0;
		}

			
		
  } 
}
