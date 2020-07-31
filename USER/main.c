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
	senddata 先置位USART2_RX_STA，														
	串口接收中断里面，如果收到数据量大于1024或者10ms(通过tim4中断完成)
	没有收到新的数据，							
	USART2_RX_STA [15]为1，														
	正常收数据，然后放到缓冲数组，通过字符串操作提取数据         
************************************************************/
char dataprint[50];
int main(void)
{	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
    Adc_Init();
    uart_init(115200);
	USART3_Init(115200);                            //初始化串口2波特率为115200
    printf("ENTER\n");
    atk_8266_wifiap_test();
	printf("success\n");
	USART3_RX_BUF[0]='\0';
    while(1)
	{
		// if(set_WaterPump_open_status){
		// 	if(Get_Adc_Average(0, 5) > 2500){
        //    		pump0 = 0;//打开
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


