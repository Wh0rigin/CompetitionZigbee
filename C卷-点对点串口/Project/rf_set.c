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
unsigned int two=0,one=0;
char* temp = "FA 00 FB\n";
void delay(int i){
  int k,j;
  for(k=i;k>0;k--)
     for(j=0;j<525;j++);
}

unsigned char data_recv;

/*****点对点通讯地址设置******/
#define RF_CHANNEL                21         // 频道 11~26
#define PAN_ID                    0x1234     //网络id 
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

/********************MAIN************************/
void main(void)
{
    halBoardInit();//选手不得在此函数内添加代码
    ConfigRf_Init();//选手不得在此函数内添加代码
    halUartInit(19200);
    unsigned int i = 0;

    //U0CSR |= 0xc0;
    //URX0IF = 0;
    //IEN0 = 0x84;
    
    while(1)
    {
    /* user code start */

      //接受数据
      while(halUartRxLen()){
        halUartRead(temp,9);
      }
      //halUartWrite(temp,strlen(temp));
      delay(100);
        //接受成功
        if(basicRfPacketIsReady()){
          basicRfReceive(&data_recv,1,NULL);
          if(data_recv == 0x01){
          
          switch(temp[4]){
          case 'A':
            one = 10;
            break;
          case 'B':
            one = 11;
            break;
          case 'C':
            one = 12;
            break;
          case 'D':
            one = 13;
            break;
          case 'E':
            one = 14;
            break;
          case 'F':
            one = 15;
            break;
          default:
            one = temp[4] - '0';
            break;
          }
        
          switch(temp[3]){
          case 'A':
            two = 10 * 16;
            break;
          case 'B':
            two = 11 * 16;
            break;
          case 'C':
            two = 12 * 16;
            break;
          case 'D':
            two = 13 * 16;
            break;
          case 'E':
            two = 14 * 16;
            break;
          case 'F':
            two = 15 * 16;
            break;
          default:
            two = (temp[3] - '0') * 16;
            break;
          }
        
            i = two + one;
            i++;
            if( i < 16){
              int len = sprintf(temp,"FA 0%x FB\n",i);
              halUartWrite(temp,len);
            }else{
              int len = sprintf(temp,"FA %x FB\n",i);
              halUartWrite(temp,len);
            }
          } 
        }
        
      }
    }
    /* user code end */

