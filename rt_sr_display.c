/**********************************************************
   Modified by John Martin for NHTSA
   by adding:
   
   1) Interrupt driven UART transmit
   of binary CAN data
   2) Listen Mode only
   3) only accepts J1939 CAN frames with the following PGNs
      61449,61443,65265,65103,61440,61444
   4) gcc compatibility stuff
	6/1/2006
*********************************************************/

/***************************************************************************
* File Name: CAN_Analizer.c
*----------------------------------------------------------------------------
* Copyright (c) 2002 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      Name:
* REVISION:     Revision: 1.0
*----------------------------------------------------------------------------
* PURPOSE: 
* ATmega128CAN11 Demo
* 
*****************************************************************************/
 
/*_____ I N C L U D E S ____________________________________________________*/
#include "config.h"
#include "can_lib.h"
#include "stdio.h"
#include "uart.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define PGN_65215 0xfebf00
#define PGN_61444 0xf00400
#define PGN_61449 0xf00900
#define PGN_64905 0xfd8900
#define PGN_65103 0xfe4f00
#define PGN_61443 0xf00300
#define CIR_BUF_SIZE 256
#define CIR_BUF_MASK 0xff
#define WAITING_FOR88   1
#define READING_MESSAGE 2
#define WAITING_FOR31 3
#define WAITING_FOR_ABS_CONT 4
#define WAITING_FOR97 5
#define WAITING_FOR_ASR1 6
#define WAITING_FOR_ASR2 7
#define J1708_LED 0x01
#define J1939_LED 0x04
#define ESC_FAULT_LED 0x10
#define RSC_FAULT_LED 0x40
#define PORTE_STATUS_LED 0x10
#define SERIAL_DEBUG 0
#define F_CPU 16000000UL

#define BRAKING     1
#define NOT_BRAKING 2

typedef struct {
  uint8_t buffer[21];
  uint8_t message[21];
  float timestamp;
  int state;
  int current_byte;
} StateM;

typedef struct {
  uint8_t abs_cont;
  uint8_t atc1;
  uint8_t atc2;
} ABS_Struct;


void can_init(void);
float get_current_time();
uint8_t get_UBRR0L(char *spd_str);
uint8_t get_UBRR0H(char *spd_str);
int serial_state_machine(StateM *state_m,uint8_t byte);
void init_state(StateM *state_m);
void update_leds_1708(ABS_Struct abs_info);
uint32_t get_switch_value();
void putchar0(char c);
void putchar1(char c);
void delay(uint16_t millis);
void putint_with_decimal(int32_t val);
void putint0_with_decimal(int32_t val);
/*_____ D E C L A R A T I O N S ____________________________________________*/
long int id_std,error_count=0;
long int id_ext,id_std;
unsigned int f_recept_can_message=0;
unsigned int test_global=0;
Uint32 quarter_seconds=0;
unsigned char compteurligne=0;
can_msg_t msgrx;
Uchar dlc;
unsigned char datarx [8];
Uint32 last_secs,the_count=0;
unsigned char last_fracs;
unsigned char serial_buffer[CIR_BUF_SIZE];
uint8_t buf_pos=0,write_pos=0;
uint8_t porta_temp;


int main (void)
{	
  unsigned int display_count=0;
  long int i,id_local;
  int j,out_state=NOT_BRAKING;
  
  uint8_t *temp_ptr;
  uint32_t display_range;
  int16_t res_range=10000;
  unsigned char data_local[8];
  char temp_string[300];
  unsigned char out_string[80],accel_pos=0,engine_torque=0;
  // wdt_enable(WDTO_2S);
  float wheel_speed=0,wheel_fl=0,wheel_fr=0,wheel_bl=0,wheel_br=0;
  float engine_rpm;
  Uint16 vdsc1_code=0;
  Uint32 temp_uint32,time_last_receive,time_diff;
  Uint16 speed_value=570;
  float the_current_time,temp_float;
  unsigned char data61449[8],data64905[8],data65103[8];
  StateM state_m;
  ABS_Struct abs_info;
  /*set clock prescaler such that we are running at 16Mhz*/
  CLKPR=0x80; CLKPR=0x00;
  DDRE=PORTE_STATUS_LED | 0xa0;
#if 1
  TIMSK2 &= ~((1 << TOIE2) | (1 << OCIE2A));
  ASSR |= (1 << AS2);
  TCNT2=0x00;
  TCCR2A=0x03;	
  while(ASSR & 0x07);
  TIMSK2 |= (1 <<TOIE2);
#endif

  can_init();
  uart_init(); 
  
  delay(200);
  putchar1('D');putchar1(0x09);putchar1(0x08);putchar1(0x07);putchar1(0x06);
  delay(200);
  putchar1('D');putchar1(0x00);putchar1(0x00);putchar1(0x00);putchar1(0x00);
  putchar1('P');putchar1(0x00);putchar1('~');

  delay(200);
  putchar0('D');putchar0(0x09);putchar0(0x08);putchar0(0x07);putchar0(0x06);
  delay(200);
  putchar0('D');putchar0(0x10);putchar0(0x10);putchar0(0x10);putchar0(0x10);
  putchar0('P');putchar0(0x00);putchar0('~');

  putchar0('B');putchar0(0x7d);putchar0('~');
  putchar1('B');putchar1(0x7d);putchar1('~');

  i=0;
  SREG=0x80;
  while(1) {

    time_diff=quarter_seconds-time_last_receive;

    

    display_count++;
    if ((display_count % 1000)==0) {
      temp_float=speed_value;
      //temp_float*=.22369362920544;
      temp_float*=.36;
      temp_float+=0.5;
      display_range=temp_float;
      putint_with_decimal(display_range);
      
      temp_float=res_range;
      temp_float*=0.01; // put into tenths of meters
      temp_float*=3.28084; // put into tenths of feet
      display_range=temp_float;
      display_range=abs(display_range);
      putint0_with_decimal(display_range);
    }
    if (f_recept_can_message) {
      //      porta_temp^=J1939_LED;
      
      CAN_IT_DISABLE;
      id_local=id_std;
      for(i=0;i<8;i++) data_local[i]=datarx[i];		
      CAN_IT_ENABLE;
      
      switch(id_local & 0x7ff) {
      case 0x723:
	PORTE^=PORTE_STATUS_LED | 0x80;
	temp_ptr=(uint8_t *) &speed_value;
	temp_ptr[0]=data_local[6];
	temp_ptr[1]=data_local[7];
	break;

      case 0x7a1:
	temp_ptr=(uint8_t *) &res_range;
	temp_ptr[0]=data_local[0];
	temp_ptr[1]=data_local[1];
	//temp_ptr[2]=data_local[2];
	//temp_ptr[3]=data_local[3];
	
	break;



      default:
	//	print_string("unhandled packet received!!\n\r");
	break;
      }
      
      f_recept_can_message=0;
    }

    
  }
}




float get_current_time()
{
  Uint32 secs;
  unsigned char fracs;
  float retval;
  fracs=TCNT2;
  secs=quarter_seconds;
  if ((fracs<last_fracs)&&(secs==last_secs)) secs++;
  last_fracs=fracs;
  last_secs=secs;

  retval=secs*0.25+fracs*(0.25/256.0);

  return(retval);
}




ISR(TIMER2_OVF_vect)
{
    ++quarter_seconds;
}


void putchar0(char c) {
  while (!(UCSR0A & _BV(UDRE0)));
  UDR0= c;
}


void putchar1(char c) {
  while (!(UCSR1A & _BV(UDRE1)));
  UDR1= c;
}


void putfloat(float val) {  // not using sprintf, too much machinery
  int32_t fi;
  uint8_t i;
  
  fi= (val+0.05)*10.0;
  putchar1('D');
  i= fi/1000;
  putchar1(i);
  fi -= i*1000;
  i= fi/100;
  putchar1(i);
  fi -= i*100;
  i= fi/10;
  putchar1(i);
  fi -= i*10;
  i= fi;
  putchar1(i);
}


void putint(int32_t val) {  // not using sprintf, too much machinery
  int32_t fi;
  uint8_t i;
  
  if (val>9998) fi= 9998;
  else fi=val;
  putchar1('D');
  i= fi/1000;
  putchar1(i);
  fi -= i*1000;
  i= fi/100;
  putchar1(i);
  fi -= i*100;
  i= fi/10;
  putchar1(i);
  fi -= i*10;
  i= fi;
  putchar1(i);
}

void putint_with_decimal(int32_t val) {  // not using sprintf, too much machinery
  int32_t fi;
  uint8_t i;
  int thousands_not_blank=0;

  putchar1('P'); putchar1(4); putchar1('~');
  if (val>9998) fi= 9998;
  else fi=val;
  putchar1('D');
  i= fi/1000;
  if (i!=0) {
    putchar1(i);
    thousands_not_blank=1;
  }
  else {
    putchar1(10);
    thousands_not_blank=0;
  }
  fi -= i*1000;
  i= fi/100;
  if ((i!=0)||(thousands_not_blank)) putchar1(i);
  else putchar1(10);
  fi -= i*100;
  i= fi/10;
  putchar1(i);
  fi -= i*10;
  i= fi;
  putchar1(i);
}


void putint0_with_decimal(int32_t val) {  // not using sprintf, too much machinery
  int32_t fi;
  uint8_t i;
  int thousands_not_blank=0;

  putchar0('P'); putchar0(4); putchar0('~');
  if (val>9998) fi= 9998;
  else fi=val;
  putchar0('D');
  i= fi/1000;
  if (i!=0) {
    putchar0(i);
    thousands_not_blank=1;
  }
  else {
    putchar0(10);
    thousands_not_blank=0;
  }
  fi -= i*1000;
  i= fi/100;
  if ((i!=0)||(thousands_not_blank)) putchar0(i);
  else putchar0(10);
  fi -= i*100;
  i= fi/10;
  putchar0(i);
  fi -= i*10;
  i= fi;
  putchar0(i);
}





void can_init(void)
{
  int mob;
  // Init the CAN
  
  CAN_CONTROLLER_RESET;

  //CANBT1=0x0e;  // 250k for Tclk 16Mhz
  //CANBT2=0x04;  // 250k for Tclk 16Mhz
  //CANBT3=0x13;  // 250k for Tclk 16Mhz
  //   CANBT1=0x06;  // 500k for Tclk 16Mhz
  //  CANBT2=0x04;  // 500k for Tclk 16Mhz
  //  CANBT3=0x13;  // 500k for Tclk 16Mhz

  CANBT1=0x02;  // 1000k for Tclk 16Mhz
  CANBT2=0x04;  // 1000k for Tclk 16Mhz
  CANBT3=0x13;  // 1000k for Tclk 16Mhz

  RazAllMailbox();
  CAN_RX_IT_ENABLE;
  CAN_ERCH_IT_ENABLE;  //mob errors enable
  CAN_IT_ENABLE;  //master enable
  conf_rx=CONF_NOIDE | CONF_NOMSK_IDE | CONF_NOBUFFER;
  //conf_rx=CONF_IDE | CONF_NOMSK_IDE | CONF_NOBUFFER;
  //  CANGCON=CANGCON | (1<<LISTEN);

  can_rx_filt.std=0x723;  
  can_rx_msk.std= 0x7ff;
  CAN_SET_CHANNEL(0);
  ConfChannel_Rx();
  CAN_CHANNEL_IT_ENABLE(0);  


  can_rx_filt.std=0x7a1;  
  can_rx_msk.std= 0x7ff;
  CAN_SET_CHANNEL(1); 
  ConfChannel_Rx();
  CAN_CHANNEL_IT_ENABLE(1);  


  for (mob=2;mob<=15;mob++)
    {
      can_rx_filt.std=0x00;
      can_rx_msk.std=0x00;
      CAN_SET_CHANNEL(mob);
      ConfChannel_Rx();
      CAN_CHANNEL_IT_DISABLE(mob);
    }  

#if 0
  can_rx_filt.ext=0x12f81010;  
  can_rx_msk.ext= 0xffffffff;
  CAN_SET_CHANNEL(0);
  ConfChannel_Rx();
  CAN_CHANNEL_IT_ENABLE(0);  
  for (mob=1;mob<=15;mob++)
    {
      can_rx_filt.ext=0x0;
      can_rx_msk.ext=0x00;
      CAN_SET_CHANNEL(mob);
      ConfChannel_Rx();
      CAN_CHANNEL_IT_DISABLE(mob);
    }  
#endif
  
  
  CAN_IT_ENABLE; //master int enable
  CAN_CONTROLLER_ENABLE;  
}


uint8_t
get_UBRR0L(char *spd_str)
{
  uint8_t retval;
  if ((spd_str[0]=='3')&&(spd_str[1]=='8')&&(spd_str[2]=='4')) retval=25;
  else if ((spd_str[0]=='1')&&(spd_str[1]=='9')&&(spd_str[2]=='2')) retval=51;
  else if ((spd_str[0]=='9')&&(spd_str[1]=='6')&&(spd_str[2]=='0')) retval=103;
  else if ((spd_str[0]=='1')&&(spd_str[1]=='1')&&(spd_str[2]=='5')) retval=8;
  else retval=25;
  
  return(retval);
}

uint8_t
get_UBRR0H(char *spd_str)
{
  return(0);
}



ISR(CANIT_vect)
{
  Uchar i;
  long int out1,out2,out3,out4;
  
  Uchar num_channel,save_canpage;
  save_canpage=CANPAGE;
  num_channel = (CANHPMOB >> HPMOB);
  num_channel=(num_channel <= LAST_CHANNEL_NB) ? num_channel : NO_CHANNEL;
  if (num_channel != NO_CHANNEL)
    {
      CAN_SET_CHANNEL(num_channel);
      if ((CANSTMOB & (1<<RXOK)) != FALSE)
	{
	  //	  out1=CANIDT1 >> 3;	
	  //	  out2=(CANIDT1 << 5) | (CANIDT2 >> 3);
	  //	  out3=(CANIDT2 << 5) | (CANIDT3 >> 3);
	  //	  out4=(CANIDT3 << 5) | (CANIDT4 >> 3);
	  
	  //  id_ext=(out1 << 24) | (out2 << 16) | 
	  //  (out3 << 8) | out4;
	  out1=(CANIDT2 >> 5) | (CANIDT1 << 3);
	  out2=CANIDT1 >> 5;
	  id_std=(out2 << 8) | out1;
	  f_recept_can_message++;
	  
	  the_count++;
	  dlc = (CANCDMOB & MSK_CTRL_DLC); 
	  if (dlc<8) dlc=8;
	  for(i=0;i<dlc;i++) datarx[i]=CANMSG;
	}
      
    }
  else {
    error_count++;
    CANGIT = INT_GEN_msk;
  }
  CANCDMOB |=  (CH_RxENA  << CONMOB);
  CANSTMOB = CANSTMOB & (~INT_MOB_msk);
  CANPAGE=save_canpage;
}



void delay(uint16_t millis) {
  uint16_t cnt= F_CPU/10000;
  uint32_t i;
  while ( millis ) {
    // _delay_loop_2(cnt);
    for(i=0;i<cnt;i++);
    millis--;
  }
}

