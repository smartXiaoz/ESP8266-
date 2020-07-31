#include "process.h"

u16 humidity_high = 3620;
u16 humidity_low = 1620;
char humidity_str[30];
u8 set_WaterPump_open_status = 0;//0关闭水泵1打开水泵
u8 get_WaterPump_open_status;//0关闭状态1打开状态
void process_APP_CMD(char *cmdStr){
    char *cmd0 = 0;
    char *cmd1 = 0;
    u8 getHumidity_ch = 0;//
    cmd0 = strstr(cmdStr,(const char*)"humidity");
    cmd1 = strstr(cmdStr,(const char*)"led");
    if(cmd0){
        getHumidity_ch = (u8)(*(cmdStr + 8) - '0');
        process_humidity(getHumidity_ch);
        printf("enter");
        USART3_RX_BUF[0] = '\0';
    }
    if(cmd1){
        getHumidity_ch = (u8)(*(cmdStr + 3) - '0');
        process_watering(getHumidity_ch);
        USART3_RX_BUF[0] = '\0';
    }
}
void process_humidity(u8 ch){
    char *p = (char *)getHumidity_ch(ch);
    printf(p);
    esp8266_send_data(p);
    
}
void process_watering(u8 ch){
    if(ch == 1){
        PUMP0 = 0;
        set_WaterPump_open_status = 1;
    }else if (ch == 0){
        PUMP0 = 1;
        set_WaterPump_open_status = 0;
    }        
}

//0,1,2,3,4,5,6,7,8,9通道
const char * getHumidity_ch(u8 ch){
    u16 res = 0;
    float humidity = 0;
    
    res = Get_Adc_Average(ch, 5);
    if(res > humidity_high)
        humidity = 0;
    else if(res < humidity_low)
        humidity = 100;
    else
    {
        humidity = (float)(humidity_high - res) / 20.0;
    }
    
    sprintf(humidity_str, "ch:%d  data:%.2f",ch, humidity);
    return (const char *)humidity_str;//不能返回局部变量,可能在后面就被销毁了
}



