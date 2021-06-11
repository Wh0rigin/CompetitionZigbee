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

void delay(int i){
  int k,j;
  for(k=i;k>0;k--)
     for(j=0;j<525;j++);
}

char data_recv;

/*****点对点通讯地址设置******/
#define RF_CHANNEL                21         // 频道 11~26
#define PAN_ID                    0x1234     //网络id 
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

/********************MAIN************************/
void main(void)
{
    halBoardInit();//选手不得在此函数内添加代码
    ConfigRf_Init();//选手不得在此函数内添加代码
    int i = 0;

    //U0CSR |= 0xc0;
    //URX0IF = 0;
    //IEN0 = 0x84;
    
    EA = 1;
    IEN2 |= 0x10;
    P1IEN |= 0x04;
    PICTL |= 0x02;
    P1DIR &= ~0x04;
    P1SEL &= ~0x04;
    P1INP &- ~0x04;
    P2INP &= ~0x40;
    
    while(1)
    {
    /* user code start */
      
     
    }
    /* user code end */
}

#pragma vector = 0x7b
__interrupt void p1_init(){
  if((P1IFG & 0x04) == 0x04){
    unsigned char data_send = 0x01;
    basicRfSendPacket(SEND_ADDR,&data_send,1);
  }
  P1IFG = 0;
  P1IF = 0;
}