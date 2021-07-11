
#include "delay.h"
#include "LCD.h"
//дָ��

GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

void Send_Com(unsigned char Send_Com)
{
   u16 Temp;//��������ͱ���Temp������STM32F103C8��GPIOAǡ����16��IO�ڡ�
   Delay(0xAFFFF);
   CLR_RS;
   Temp=GPIO_ReadOutputData(GPIOA);//����GPIOA���ͼĴ��������ݡ�
   Temp&=0xff00;//��GPIOA�ĸ�8λ��������8λ��0.
   Temp|=(u16)Send_Com;//��char�ͱ���Send_Comǿ��ת����short(������)�����и�8λ��0���棬��8λ��Send_Com��ֵ
   GPIO_Write(GPIOA,Temp);
   Delay(100);
   Set_EN;
   Delay(100);
   CLR_EN;
}
//д����
void Send_Dat(unsigned char Send_Dat)
{
    u16 Temp;//��������ͱ���Temp������STM32F103C8��GPIOAǡ����16��IO�ڡ�
   Set_RS;
 Temp=GPIO_ReadOutputData(GPIOA);//���ط��ͼĴ����ڵ�����
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
  Send_Com(0x38);    //�ó�ֵ//
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
