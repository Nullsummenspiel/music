#ifndef __LCD_H
#define	__LCD_H
#include "stm32f10x.h"
//定义LCD的RS，RW，EN=0时分别是 Set_RS，Set_RW，Set_EN
#define Set_RS (GPIO_SetBits(GPIOB,GPIO_Pin_0))
#define Set_RW (GPIO_SetBits(GPIOB,GPIO_Pin_1))
#define Set_EN (GPIO_SetBits(GPIOB,GPIO_Pin_2))
//定义RS，RW，EN=1时分别是CLR_RS，CLR_RW，CLR_EN
#define CLR_RS (GPIO_ResetBits(GPIOB,GPIO_Pin_0))
#define CLR_RW (GPIO_ResetBits(GPIOB,GPIO_Pin_1))
#define CLR_EN (GPIO_ResetBits(GPIOB,GPIO_Pin_2))

void Send_Com(unsigned char Send_Com);
void Send_Dat(unsigned char Send_Dat);
void init(void);
void GPIO_Configuration(void);
void RCC_Configuration(void);
#endif /* __LCD_H */
