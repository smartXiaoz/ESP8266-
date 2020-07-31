#include "common.h"
#include "process.h"
u8 is_connet[5] = {1, 0, 0, 0, 0};//当前连接的端口，1代表连接，0代表没有连接。默认0端口连接
u8 receive_status = 0;
char receiveCMD[500];

u8 atk_8266_wifiap_test(void){
	// sprintf((char*)p,"AT+CWSAP=\"%s\",\"%s\",1,4",wifiap_ssid,wifiap_password);    //配置模块AP模式无线参数
	// atk_8266_send_cmd(p,"OK",1000);	
	atk_8266_send_cmd("AT+CWMODE=2","",2000);
	delay_ms(100);
	atk_8266_send_cmd("AT+RST","",2000);
    delay_ms(1000);
	atk_8266_send_cmd("AT+CIPMUX=1","",2000);
	delay_ms(100);
	atk_8266_send_cmd("AT+CIPSERVER=1,333","",2000);
	delay_ms(100);	
	atk_8266_at_response(1);
    PUMP0 = 0;
    return 0;
}

//返回值:0,发送成功(得到了期待的应答结果)
u8 esp8266_send_data(const char *str)
{
    u8 p[50];
    u8 res = 0;
    u8 ptr = 0;
    for (; ptr < 5; ptr++){     
        if(is_connet[ptr]){			
			sprintf((char*)p,"AT+CIPSEND=%d,%d",ptr,strlen(str));		
			res |= atk_8266_send_cmd(p,"OK",100);			
            res |= atk_8266_send_data((u8 *)str,"OK",100); 		
		}		
	}
    return res;
}

//处理app发送过来的指令
void esp8266_ReceivedData_from_app(){
	char *str0=0;
	char *str1=0;
	char *str2=0;
    char lenthStr;
    int lenth = 0;
    
	u8 index = 7;//+IPD,0,4正好第7位
    if(USART3_RX_STA&0X8000){      
		str0=strstr((const char*)USART3_RX_BUF,(const char*)"CONNECT");
		str1=strstr((const char*)USART3_RX_BUF,(const char*)"CLOSED");
		str2=strstr((const char*)USART3_RX_BUF,(const char*)"+IPD");
        if(str0){
            USART3_RX_STA = 0;
			printf("connect:%d\r\n",USART3_RX_BUF[0]-'0');
            is_connet[USART3_RX_BUF[0]-'0'] = 1;
			USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;
        }
		if(str1){
			USART3_RX_STA = 0;
			printf("closed:%d\r\n",USART3_RX_BUF[0]-'0'); 
			is_connet[USART3_RX_BUF[0]-'0'] = 0;
			USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;	           
        }				
		if(str2){ //是否接收到数据
			USART3_RX_STA = 0;
			USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//添加结束符
			while(lenthStr!=':')
            {
                lenth *= 10;
                lenthStr = *(str2 + index++);
                lenth += lenthStr - '0';
            }
            lenth /= 10;//去前两位            
            memcpy(receiveCMD, str2 + index, lenth);//复制字符串
            receive_status = 1;
            process_APP_CMD(receiveCMD);
        }		
		USART3_RX_STA = 0;
    } 

}


