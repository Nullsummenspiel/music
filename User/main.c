#include "stm32f10x.h"
#include "delay.h"
#include "LCD.h"
#include "pwm.h"
#include "music.h"
#include "key.h"
#include "sys.h"
#include "bsp_TiMbase.h"
#include "bsp_usart.h"

#define uchar unsigned char
#define uint unsigned int

static void Show_Message(void);
unsigned char table[]="music";
unsigned char table1[]="qinghuaci   1";
unsigned char table2[]="aiqingmaimai  2";
volatile uint32_t time = 0; // ms ��ʱ���� 


int main(void)
{
	char ch;
	KEY_Init(); 
	BASIC_TIM_Init();
	BASIC_TIM_APBxClock_FUN(BASIC_TIM_CLK, ENABLE);
  #ifdef DEBUG
  debug();
  #endif
  unsigned char num;
  RCC_Configuration();
  GPIO_Configuration();
  init();
  for(;;)
  {
		uchar *temp;
    uint n = 0;
		temp = table;
    while(*temp ++ != '\0')   n++;    //�����ַ�����Ч�ַ��ĸ���
    for(num=0;num<n;num++)
  {
   Send_Dat(table[num]);
   Delay(2000000);
  }
  //while(1);
  // Send_Com(0x01);
	u16 led0pwmval=7200;    
	delay_init();	    	 //��ʱ������ʼ��	  
	TIM1_PWM_Init(14400,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
	USART_Config();
	/* ��ӡָ��������ʾ��Ϣ */
  Show_Message();
   	while(1)
	{
		if(KEY0==0)
{
		/* ��ȡ�ַ�ָ�� */
    ch=getchar();
    printf("���յ��ַ���%c\n",ch);
    
    /* �����ַ�ָ�����RGB�ʵ���ɫ */
    switch(ch)
    {
      case '1':
					n = 0;
					temp = table1;
					while(*temp ++ != '\0')   n++;    //�����ַ�����Ч�ַ��ĸ���
					Delay(20000);
					Send_Com(0x80+0x40);
					for(num=0;num<n;num++)
					{
					Send_Dat(table1[num]);
					Delay(2000000);
					}
					delay_ms(10);	
					TIM1->ARR=14400;
					TIM_SetCompare1(TIM1,led0pwmval);
					music_run(1);
					Music_Task(1);
					Music_Init();
					time=0;
					break;
      case '2':
					n = 0;
					temp = table2;
					while(*temp ++ != '\0')   n++;    //�����ַ�����Ч�ַ��ĸ���
					Delay(20000);
					Send_Com(0x80+0x40);
					for(num=0;num<n;num++)
					{
					Send_Dat(table2[num]);
					Delay(2000000);
					}
					delay_ms(10);
					TIM1->ARR=14400;
					TIM_SetCompare1(TIM1,led0pwmval);
					music_run(1);
					Music_Task(2);
					Music_Init();
					time=0;
					break;
      default:
       /*  �������ָ��ָ���ַ�����ӡ��ʾ��Ϣ */
        Show_Message();
        break;      
    }
		//delay_ms(10);	 					 
		//TIM_SetCompare1(TIM1,led0pwmval);	   
		//music_run(1);
		//Music_Task();
	}
	if(time==20000)
	{
		time=0;
		printf("����ô��ѡ����\n");
	}
}
	} 
}

static void Show_Message(void)
{
  printf("\r\n   ����һ��ͨ������ͨ��ָ��������ֲ��ŵĿ��� \n");
  printf("ʹ��  USART  ����Ϊ��%d 8-N-1 \n",DEBUG_USART_BAUDRATE);
  printf("������ӵ�ָ�����Ʒ������������֣�ָ���Ӧ���£�\n");
  printf("   ָ��   ------ �������� \n");
  printf("     1    ------    �໨�� \n");
  printf("     2    ------    �������� \n"); 
}
