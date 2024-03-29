#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "sys.h"
#include "stm32f4xx_conf.h"

void uart2_init(u32 bound);
//void uart_init(u32 bound);

extern u16 jieshou;

extern u8 jihao[5];
extern u8 jidu[5];
extern u8 zhuansu[5];

extern int t;
extern int k;
extern int A;
extern int B;
extern int C;
extern int flag;
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#endif
