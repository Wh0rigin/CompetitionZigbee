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
#define MY_ADDR                   0x0001     //本机模块地址
#define SEND_ADDR                 0x0002     //发送地址
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

void delay_ms(int i){
  int k,j;
  for(k = 0;k < i;k++)
    for(j = 0;j < 535;j++);
}

/********************MAIN************************/
void main(void)
{
    halBoardInit();//选手不得在此函数内添加代码
    ConfigRf_Init();//选手不得在此函数内添加代码

    P1SEL &= ~0x1b;
    P1DIR |= 0x1b;
    P1 = 0;
    P0SEL &= ~0x02;
    P0DIR &= ~0x02;
    
    
    while(1)
    {
      delay_ms(1000);
    /* user code start从节点 */
      if(!(P0 & 0x02)){
        P1 |= 0x01;
        uint8 data = 0x01;
        basicRfSendPacket(SEND_ADDR,&data,1);
      }else{
        P1 &= ~0x01;
        uint8 data = 0x00;
        basicRfSendPacket(SEND_ADDR,&data,1);
      }
    /* user code end */
    }
}