#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "malloc.h" 
#include "usart3.h"
#include "common.h"
#include "adc.h"
#include "process.h"
/***********************************************************
	senddata ����λUSART2_RX_STA��														
	���ڽ����ж����棬����յ�����������1024����10ms(ͨ��tim4�ж����)
	û���յ��µ����ݣ�							
	USART2_RX_STA [15]Ϊ1��														
	���������ݣ�Ȼ��ŵ��������飬ͨ���ַ���������ȡ����         
************************************************************/
char dataprint[50];
int main(void)
{	
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
    Adc_Init();
    uart_init(115200);
	USART3_Init(115200);                            //��ʼ������2������Ϊ115200
    printf("ENTER\n");
    atk_8266_wifiap_test();
	printf("success\n");
	USART3_RX_BUF[0]='\0';
    while(1)
	{
		// if(set_WaterPump_open_status){
		// 	if(Get_Adc_Average(0, 5) > 2500){
        //    		pump0 = 0;//��
       	// 	}else{
        //     	pump0 = 1;
        // 	}
		// }else
		// {
        //     pump0 = 1;
        // }
		
		
        // esp8266_ReceivedData_from_app();
        PUMP0 = 1;PUMP1 = 1;PUMP2 = 1;PUMP3 = 1;PUMP4 = 1;PUMP5 = 1;PUMP6 = 1;PUMP7 = 1;
        delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
        PUMP0 = 0;PUMP1 = 0;PUMP2 = 0;PUMP3 = 0;PUMP4 = 0;PUMP5 = 0;PUMP6 = 0;PUMP7 = 0;
		delay_ms(1000);
        delay_ms(1000);
        delay_ms(1000);
    }
}


