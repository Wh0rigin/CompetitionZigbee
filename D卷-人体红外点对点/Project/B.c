#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_uart.h" 
#include "sensor_drv/sensor.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
/*****点对点通讯地址设置******/
#define RF_CHANNEL                21         // 频道 11~26
#define PAN_ID                    0x1021     //网络id 
#define MY_ADDR                   0x0002     //本机模块地址
#define SEND_ADDR                 0x0001     //发送地址
/**************************************************/
static basicRfCfg_t basicRfConfig;
// 无线RF初始化
void ConfigRf_Init(void)
{
    basicRfConfig.panId       =   PAN_ID;
    basicRfConfig.channel     =   RF_CHANNEL;
    basicRfConfig.myAddr      =   MY_ADDR;
    basicRfConfig.ackRequest  =   TRUE;
    while(basicRfInit(&basicRfConfig) == FAILED);
    basicRfReceiveOn();
}

uint8 recv = 0x02;



/********************MAIN************************/
void main(void)
{
    halBoardInit();//选手不得在此函数内添加代码
    ConfigRf_Init();//选手不得在此函数内添加代码
    halUartInit(38400);
    while(1)
    {
    /* user code start */
      
      if(basicRfPacketIsReady()){
        basicRfReceive(&recv,1,NULL);
        switch(recv){
        case 0x01:
          halUartWrite("有人",strlen("有人"));
          break;
        case 0x00:
          halUartWrite("无人",strlen("无人"));
          break;
        }
      }
      
    /* user code end */
    }
}