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
#define PAN_ID                    0x1021     //����id 
#define MY_ADDR                   0x0002     //����ģ���ַ
#define SEND_ADDR                 0x0001     //���͵�ַ
/**************************************************/
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

uint8 recv = 0x02;



/********************MAIN************************/
void main(void)
{
    halBoardInit();//ѡ�ֲ����ڴ˺�������Ӵ���
    ConfigRf_Init();//ѡ�ֲ����ڴ˺�������Ӵ���
    halUartInit(38400);
    while(1)
    {
    /* user code start */
      
      if(basicRfPacketIsReady()){
        basicRfReceive(&recv,1,NULL);
        switch(recv){
        case 0x01:
          halUartWrite("����",strlen("����"));
          break;
        case 0x00:
          halUartWrite("����",strlen("����"));
          break;
        }
      }
      
    /* user code end */
    }
}