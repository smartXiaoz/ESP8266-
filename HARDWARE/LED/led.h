#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define PUMP0 PBout(12)
#define PUMP1 PBout(13)
#define PUMP2 PBout(14)

#define PUMP3 PBout(8)
#define PUMP4 PBout(9)
#define PUMP5 PBout(5)
#define PUMP6 PBout(6)
#define PUMP7 PBout(7)


void LED_Init(void);//��ʼ��

		 				    
#endif
