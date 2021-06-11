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
/*****��Ե�ͨѶ��ַ����******/
#define RF_CHANNEL                21         // Ƶ�� 11~26
#define PAN_ID                    0x1234     //����id 
#define MY_ADDR                   0x0001     //����ģ���ַ
#define SEND_ADDR                 0x0002     //���͵�ַ
/**************************************************/

uint8 flag = 0;
static basicRfCfg_t basicRfConfig;
// ����RF��ʼ��
void ConfigRf_Init(void)
{
    basicRfConfig.panId       =   PAN_ID;
    basicRfConfig.channel     =   RF_CHANNEL;
    basicRfConfig.myAddr      =   MY_ADDR;
    basicRfConfig.ackRequest  =   TRUE;
    while(basicRfInit(&basicRfConfig) == FAILED);
    basicRfReceiveOn();
}

void delay(int i){
  int k,j;
  for(k = 0; k < i;k++)
    for(j = 0; j < 535;j++);
}

/********************MAIN************************/
void main(void)
{
    halBoardInit();//ѡ�ֲ����ڴ˺�������Ӵ���
    ConfigRf_Init();//ѡ�ֲ����ڴ˺�������Ӵ���

    P1SEL &= ~0x1b;
    P1DIR |= 0x1b;
    P1 = 0;
    
    EA = 1;
    IEN2 |= 0x10;
    P1IEN |= 0x04;
    PICTL |= 0x02;
    
    while(1)
    {
    /* user code start */
      if(flag){
        uint8 data = 0x01;
        basicRfSendPacket(SEND_ADDR,&data,1);
        P1 = 0x00;
        delay(2000);
        P1 = 0x02;
        delay(2000);
        P1 = 0x01;
        delay(2000);
        P1 = 0x10;
        delay(2000);
        P1 = 0x08;
        delay(2000);
        P1 = 0x00;
        data = 0x00;
        basicRfSendPacket(SEND_ADDR,&data,1);
        flag = 0;
      }
      

    /* user code end */
    }
}

#pragma vector = 0x7b
__interrupt void zd(){
  if((P1IFG & 0x04) == 0x04){
    flag = 1;
  }
  P1IFG = 0;
  P1IF = 0;
}