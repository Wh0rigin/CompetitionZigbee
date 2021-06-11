#include<ioCC2530.h>

unsigned char flag = 0;

void delay(int i){
  while(i--);
}


void main(){
  P1SEL &= ~0x03;
  P1DIR |= 0x03;
  P1 = 0;
  EA = 1;
  IEN2 |= 0x10;
  P1IEN |= 0x04;
  PICTL |= 0x02;
  
  while(1){
    
    
    if(flag){
      
      int low,high = 600;
      for(low = 1;low < high;low++){
        P1 = 0x03;
        delay(low);
        P1 = 0x00;
        delay(high - low);
      }
      
      for(low = high - 1;low > 0;low--){
        P1 = 0x03;
        delay(low);
        P1 = 0x00;
        delay(high - low);
      } 
    }
  } 
}

#pragma vector = 0x7b
__interrupt void zd (){
  if((P1IFG & 0x04) == 0x04){
    flag = 1;
  }
  P1IFG = 0;
  P1IF = 0;
}