#include "sys.h"
//#include "usart.h"
#include "chuankou2.h"
//
u16 USART_RX_STA=0;
u8 jihao[5];
u8 jidu[5];
u8 zhuansu[5];//[1,0,0,0];
u16 time = 1000;//����ֻ�ܷ���u8 ���ݣ���Ҫ��ַ��� u16 Ϊ�����ֽڣ����ڷ���ÿ��ֻ�ܷ���һ���ֽڣ���Ҫ��ֵ�������
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  

//Ҫ��printf������Ҫ��
#if 1                     //��ֹ����ʱ���Ż���
#pragma import(__use_no_semihosting)   //#pragma ���������趨��������״̬������ָʾ���������һЩ�ض��Ķ��������������Ϊ�˹رհ�����ģʽ           
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x)             //������rt_sys.h�ж���Ŀ��˳����������е����г������ն������_sys_exit()  //����_sys_exit()�Ա���ʹ�ð�����ģʽ    
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	

	 while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
	 USART2->DR = (u8) ch;      
	 return ch;
}
#endif                                                                   
                                                                       //�ض���printf����                                                                 
// //��ʼ��IO ����1 
////bound:������
//void uart_init(u32 bound){
//   //GPIO�˿�����
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NV0IC_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
// 
//	//����1��Ӧ���Ÿ���ӳ��
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
//	
//	//USART1�˿�����
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
//	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

//   //USART1 ��ʼ������
//	USART_InitStructure.USART_BaudRate = bound;//����������
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
//  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
//	
//  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
//	
//	//USART_ClearFlag(USART1, USART_FLAG_TC);
//	
//#if EN_USART1_RX	  //ʹ�ܴ���1�Ľ���
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������жϣ����յ������ж�
//	                                              // RXNE�������ݼĴ����ǿգ�����1��ʾ�Ѿ������ݱ����յ����ҿ��Զ������ˣ�ͨ����USART_DR���Խ���λ���㣬Ҳ�������λд0��ֱ�����

//	//Usart1 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

//#endif
//	
//}                                                                    

void uart2_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART2_RX	  //ʹ�ܴ���1�Ľ���
  
	 

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������жϣ����յ������ж�
	                                              // RXNE�������ݼĴ����ǿգ�����1��ʾ�Ѿ������ݱ����յ����ҿ��Զ������ˣ�ͨ����USART_DR���Խ���λ���㣬Ҳ�������λд0��ֱ�����

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

#endif
	
}

int A,B,C;
int q;
int t=0;
int k;//�����ж�����Ҫȡ�ڼ�����
int flag;
void USART2_IRQHandler(void)
{
	u16 jieshou;//������Ž��յ�������
	
//	u16 a[15];//������Ž��յ�������
////	int i;
	//��ʾ�ڼ�������	
	
//	t=0;//��ʼ��t
	//һ��һ�����ݽ���
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β�������жϣ�) //�����ж϶����ݼĴ����Ƿ�գ���Ϊ���ܵ����ַ��Ż�����жϣ����Բ��ǿյģ�����жϳ���
	{
		jieshou=USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
		if(jieshou=='#')//��ʾ���յ���ʼ����
		{
			t=1;//��ʾ��һ�����ݿ�ʼ
			q=0;
		}
		else if(t==1&&jieshou!='P')//��ʾ��һ�����ݵĴ���
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
