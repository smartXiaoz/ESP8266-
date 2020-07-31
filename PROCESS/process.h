#ifndef __PROCESS_H
#define __PROCESS_H	 
#include "common.h"
#include "adc.h"
#include "usart.h"

void process_APP_CMD(char *cmdStr);
const char *getHumidity_ch(u8 ch);
void process_humidity(u8 ch);
void process_watering(u8 ch);

extern u8 set_WaterPump_open_status;//0关闭水泵1打开水泵
extern u8 get_WaterPump_open_status;//0关闭状态1打开状态
#endif
