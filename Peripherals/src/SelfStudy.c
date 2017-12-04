
///**
//  ********************************  STM32F0x1  *********************************
//  * @�ļ���     �� SelftStudy.c
//  * @����       �� HarryZeng
//  * @��汾     �� V1.5.0
//  * @�ļ��汾   �� V1.0.0
//  * @����       �� 2017��11��24��
//  * @ժҪ       �� ���ݴ���
//  ******************************************************************************/
///*----------------------------------------------------------------------------
//  ������־:
//  2017-11-24 V1.0.0:��ʼ�汾
//  ----------------------------------------------------------------------------*/
///* ������ͷ�ļ� --------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "PG120.h"
#include "key.h"
#include "SelfStudy.h"
#include "flash.h"
#include "display.h"
#include "stm32f10x_tim.h"

/*��һ��SET�������´�����*/
uint8_t  ATTcalibration(void) ;

/*�ڶ���SET�������´�����*/
void GetMAXADCValue(void);

uint8_t SelftStudyflag=0;
uint8_t ATTcalibrationFlag=0;
uint8_t 	selfDisplayEndFlay=0;
uint32_t  SET1ADC_Value=0;

extern int16_t adc_dma_tab[4];
void selfstudy(void)
{
	uint8_t OUT1_STATUS,OUT2_STATUS,OUT3_STATUS;
	

	if(SetButton.Status == Press && ModeButton.Status==Press)
	{
		
	}
	else
	{
			/*��һ�ν���SETģʽ*/
			while(SetButton.Status == Press )     //ֻҪ����ʾģʽ�µ�һ�ΰ���SET����
			{	
					/*����OUT1��״̬*/
					OUT1_STATUS = GPIO_ReadInputDataBit(OUT1_GPIO_Port,OUT1_Pin);/*��ȡ��ǰ��OUT1״̬*/
				GPIO_WriteBit(OUT1_GPIO_Port,OUT1_Pin,(BitAction)OUT1_STATUS);/*������OUT1״̬*/
					OUT2_STATUS = GPIO_ReadInputDataBit(OUT2_GPIO_Port,OUT2_Pin);/*��ȡ��ǰ��OUT2״̬*/
				GPIO_WriteBit(OUT2_GPIO_Port,OUT2_Pin,(BitAction)OUT2_STATUS);/*������OUT1״̬*/
					OUT3_STATUS = GPIO_ReadInputDataBit(OUT3_GPIO_Port,OUT3_Pin);/*��ȡ��ǰ��OUT3״̬*/
				GPIO_WriteBit(OUT3_GPIO_Port,OUT3_Pin,(BitAction)OUT3_STATUS);/*������OUT1״̬*/
				
				/*���Ű���3����*/
				SMG_DisplaySET_Step_1_Mode(0,Threshold);
				if(SetButton.Status == Release) break;
				//Test_Delay(1000);
		//		/*����Ҫ��ʾSET1*/
		//		if(EventFlag&Blink500msFlag) 
		//		{
		//			EventFlag = EventFlag &(~Blink500msFlag);  //�����־λ
		//			SMG_DisplaySET_Step_1_Mode(0,ADCValue);
		//		}
				//EventFlag = EventFlag &(~ADVtimeFlag);
				//GetADCValue(&SET1ADC_Value);
				
	
						
					/*3�뵽��,��˸����*/
					//if(EventFlag&Blink500msFlag) 
					//{
					//	EventFlag = EventFlag &(~Blink500msFlag);  //�����־λ
						//if(EventFlag&ADVtimeFlag) //���µ�3���ڣ�һֱ��ʱ�ɼ�ADCֵ
						//{
							//EventFlag = EventFlag &(~ADVtimeFlag);  //�����־λ
							//GetADCValue(&SET1ADC_Value);		//��ʱADC����
							
					//	}
							
					//}
					else if(SetButton.Effect == PressLong && SetButton.Status==Press ) /*�����ﵽ3��󣬵�һ�ν�����ѧϰ���ȴ��ڶ��ΰ���SET 3��*/
					{	
						ATTcalibration();
						
						/*3�뵽�ˣ����ͷ��˰���*/
						
						/*һֱ�ȴ��ڶ���SET�İ���*
						**************************/
						SetButton.LastCounter = SetButton.PressCounter;
						SetButton.Effect = PressShort;
						UpButton.PressCounter=0;
						UpButton.Effect=PressNOEffect;
						DownButton.PressCounter=0;
						DownButton.Effect=PressNOEffect;
						ModeButton.PressCounter=0;
						ModeButton.Effect=PressNOEffect;
						//selfDisplayEndFlay =0;
						//GetMAXADCValue();
						while(SetButton.Status==Press)
						{
							SMG_DisplaySET_Step_1_Mode(2,Threshold);
							SetButton.Effect = PressShort;
						}
					}
				
			}
	}
}


///*��һϵ�е�ADCvalue��Ѱ������ADV MAX*/
//uint32_t 			ADCMAX=0;
//uint32_t 		NewThreshold=0;
//uint32_t 		TempMaxADCValue=0;
//void GetMAXADCValue(void)
//{
//		uint32_t 		TempADCValue=0;
////		static uint8_t lastCounter;
//	  TempMaxADCValue =0;
//		while(selfDisplayEndFlay==0)     //�ڶ��ΰ���SET����
//		{
//			SMG_DisplaySET_Step_1_Mode(0,ADCValue);
//			while(SetButton.Status == Press )
//			{
//				//if(EventFlag&ADVtimeFlag) //���µ�3���ڣ�һֱ��ʱ�ɼ�ADCֵ
//				//{
//				//	EventFlag = EventFlag &(~ADVtimeFlag);  //�����־λ
//					//GetADCValue(&TempADCValue);					//��ʱADC����
//					
//					if(TempADCValue>=TempMaxADCValue)
//							TempMaxADCValue = TempADCValue;
//				//}
//				/*����Ҫ��ʾSET2*/
//				if(EventFlag&Blink500msFlag) 
//				{
//					EventFlag = EventFlag &(~Blink500msFlag);  //�����־λ
//					SMG_DisplaySET_Step_2_Mode(0,ADCValue,0);
//				}
//				
//				while(SetButton.Effect == PressLong) /*���°����Ѿ�����ʱ�䣬����û���ͷţ���˸����*/
//				{	/*3�뵽��,��˸����*/
//					if(EventFlag&Blink500msFlag) 
//					{
//						EventFlag = EventFlag &(~Blink500msFlag);  //�����־λ
//						SMG_DisplaySET_Step_2_Mode(1,0,0);     
//					}				
//					while(SetButton.Effect == PressLong && SetButton.Status == Release) /*�����ﵽ3��󣬽����ڶ���SET����*/
//					{		/*3�뵽�ˣ����ͷ��˰���*/
//					//	arm_max_f32(TempADCValue_f[1],i,&ADCMAX,&MAX_Index);  /*�������ADCINֵ*/
//						
//						ADCMAX = TempMaxADCValue;
//						NewThreshold = (CalibrateADCValue+ADCMAX)/2;				/*��ñ�����ѧϰ��OUT1��ֵ*/
//						
//						GPIO_WriteBit(OUT1_GPIO_Port,OUT1_Pin,(BitAction)GPIO_ReadInputDataBit(OUT1_GPIO_Port,OUT1_Pin));
//						GPIO_WriteBit(OUT2_GPIO_Port,OUT2_Pin,(BitAction)GPIO_ReadInputDataBit(OUT2_GPIO_Port,OUT2_Pin));
//						
////							while(1)
////							{
////								SMG_DisplaySET_Step_2_Mode(2,ADCValue,NewThreshold);
//								
////								
////													/*Up Button*/
////							if(UpButton.PressCounter !=lastCounter && UpButton.Effect==PressShort)
////							{
////								lastCounter = UpButton.PressCounter;
////								UpButton.PressCounter = 0;
////								NewThreshold = NewThreshold+1;
////							}
////							else 	if(UpButton.Status==Press&&(UpButton.Effect==PressLong))
////							{				/*�����Ű���������ʱ�䳬������ʱ��*/
////								UpButton.PressCounter = 0;
////								if(UpButton.PressTimer<1000)
////								{
////									if(UpButton.PressTimer%40==0)
////										NewThreshold = NewThreshold+1;
////								}
////								else if(UpButton.PressTimer>1000&&UpButton.PressTimer<3000)
////								{
////									if(UpButton.PressTimer%10==0)
////										NewThreshold = NewThreshold+1;
////								}
////								else 
////								{
////									if(UpButton.PressTimer%2==0)
////										NewThreshold = NewThreshold+1;
////								}
////							}	
////							else
////							{
////								UpButton.Effect = PressShort;
////							}
////								/*Down Button*/
////							if(DownButton.PressCounter !=lastCounter && DownButton.Effect==PressShort)
////							{
////								DownButton.PressCounter = 0;
////								NewThreshold = NewThreshold-1;
////							}
////							else if(DownButton.Status==Press&&(DownButton.Effect==PressLong))
////							{
////								DownButton.PressCounter = 0;
////								if(DownButton.PressTimer<1000)
////								{
////									if(DownButton.PressTimer%40==0)
////										NewThreshold = NewThreshold-1;
////								}
////								else if(DownButton.PressTimer>1000&&DownButton.PressTimer<3000)
////								{
////									if(DownButton.PressTimer%10==0)
////										NewThreshold = NewThreshold-1;
////								}
////								else 
////								{
////									if(DownButton.PressTimer%2==0)
////										NewThreshold = NewThreshold-1;
////								}
////							}
////							else
////							{
////								DownButton.Effect = PressShort;
////							}
////							if(NewThreshold>4000)
////									NewThreshold = 0;
////							else if(NewThreshold<=0)
////									NewThreshold = 4000;
//								
////								if(SetButton.Effect == PressShort)	/*��һ�ΰ���SET�����˳�SET��ѧϰģʽ*/
////								{
//									Threshold = NewThreshold;
//									selfDisplayEndFlay = 1;
//									SetButton.PressCounter = 0;					/*�����������*/
//									SetButton.Status = Release;					/*�ͷŰ���*/
//									SetButton.Effect = PressNOEffect;
//	
//									WriteFlash(Threshold_FLASH_DATA_ADDRESS,NewThreshold);
//									WriteFlash(DACOUT_FLASH_DATA_ADDRESS,DACOUT);

//								//	break;															/*����SET��ѧϰģʽ*/
//							//	}
//							}
//					}
//				}
//			}
//}

/*ADCIN�����ݵ���*/

extern uint8_t S_Final_FinishFlag;
extern uint32_t 	S[4];
extern uint32_t 	S_Final;
uint16_t ATT=600;  //Ĭ��600

/*
	5.125us    	30us

	328					1920
	1						100
��ʽת���ó�ԼΪ��y=2x+254
*/
void ATTSet(uint16_t ATTvalue)
{
	uint16_t TimerValue=0;
	
	TimerValue=16*ATTvalue+311;
	
	TIM_SetCompare2(TIM2,TimerValue);
	
}

/*��ȡ�ĸ�ADCͨ����������ƽ����ֵ*/
uint8_t  JudgeSvalue(uint32_t *S_Value)
{
	uint8_t flag=0x00;
		if(S_Value[0]>4000) flag |= 0x01;/*0000 0001*/
	else flag &= 0xFE;/*1111 1110*/
	
		if(S_Value[1]>4000) flag |= 0x02;/*0000 0010*/
	else flag &= 0xFD;/*1111 1101*/
	
		if(S_Value[2]>4000) flag |= 0x04;/*0000 0100*/
	else flag &= 0xFB;/*1111 1011*/
	
		if(S_Value[3]>4000) flag |= 0x08;/*0000 1000*/
	else flag &= 0xF7;/*1111 0111*/
	
	if(flag==0x0f)
		return 1;
	else 
		return 0;
}


uint8_t  ATTcalibration(void) 
{
		
		SelftStudyflag = 1;
			/*�ȴ�DMA��ADC���������*/
		while(SelftStudyflag)
		{
			
		}
		return 0;
}

