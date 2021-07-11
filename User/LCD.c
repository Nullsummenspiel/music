
#include "delay.h"
#include "LCD.h"
//写指令

GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

void Send_Com(unsigned char Send_Com)
{
   u16 Temp;//定义短整型变量Temp，由于STM32F103C8的GPIOA恰好有16个IO口。
   Delay(0xAFFFF);
   CLR_RS;
   Temp=GPIO_ReadOutputData(GPIOA);//读回GPIOA发送寄存器的数据。
   Temp&=0xff00;//将GPIOA的高8位保留，低8位清0.
   Temp|=(u16)Send_Com;//将char型变量Send_Com强制转换成short(短整型)，其中高8位由0代替，低8位是Send_Com的值
   GPIO_Write(GPIOA,Temp);
   Delay(100);
   Set_EN;
   Delay(100);
   CLR_EN;
}
//写数据
void Send_Dat(unsigned char Send_Dat)
{
    u16 Temp;//定义短整型变量Temp，由于STM32F103C8的GPIOA恰好有16个IO口。
   Set_RS;
 Temp=GPIO_ReadOutputData(GPIOA);//读回发送寄存器内的数据
 Temp&=0xff00;
 Temp|=(u16)Send_Dat;
 GPIO_Write(GPIOA,Temp);
 Delay(100);
    Set_EN;
 Delay(500);
    CLR_EN;
}
void init(void)
{
 
  CLR_EN;
  //Delay(0xAFFF);
  Send_Com(0x38);    //置初值//
  Send_Com(0x0c);
  Send_Com(0x06);
  Send_Com(0x80);
}
 void GPIO_Configuration(void)
 {
  
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
  
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
   GPIO_Init(GPIOB,&GPIO_InitStructure);
 
  
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void RCC_Configuration(void)
{
 

  RCC_DeInit();



 
 
     RCC_HSEConfig(RCC_HSE_ON);

     HSEStartUpStatus= RCC_WaitForHSEStartUp();
   
 
  if(HSEStartUpStatus==SUCCESS)
 
 {

  
  
   RCC_HCLKConfig(RCC_SYSCLK_Div1);
 
  
  
  
   RCC_PCLK2Config(RCC_HCLK_Div1);


      RCC_PCLK1Config(RCC_HCLK_Div2);

   
    FLASH_SetLatency(FLASH_Latency_2);
 

    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
   
    RCC_PLLCmd(ENABLE);

 
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
    {
   
    }

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  
    while(RCC_GetSYSCLKSource()!=0x08)
    {
   
    }


       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                              RCC_APB2Periph_GPIOC , ENABLE);
      }
}
