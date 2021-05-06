/*H**************************************************************************
* $RCSfile: mcu.h,v $         
*----------------------------------------------------------------------------
* Copyright (c) 2003 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      $Name:  $      
* REVISION:     $Revision: 1.6.6.4 $     
* FILE_CVSID:   $Id: mcu.h,v 1.6.6.4 2003/12/17 07:04:06 jberthy Exp $       
*----------------------------------------------------------------------------
* PURPOSE: 
* SFR Description file for Atmega128CAN11.
*****************************************************************************/
#ifndef MCU_H
#define MCU_H
        
/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/
#if 0
SFR_B(PINA,   0x00) /* Input Pins, Port A */
SFR_B(DDRA,   0x01) /* Data Direction Register, Port A */
SFR_B(PORTA,  0x02) /* Data Register, Port A */

SFR_B(PINB,   0x03) /* Input Pins, Port B */
SFR_B(DDRB,   0x04) /* Data Direction Register, Port B */
SFR_B(PORTB,  0x05) /* Data Register, Port B */

SFR_B(PINC,   0x06) /* Input Pins, Port C */
SFR_B(DDRC,   0x07) /* Data Direction Register, Port C */
SFR_B(PORTC,  0x08) /* Data Register, Port C */

SFR_B(PIND,   0x09) /* Input Pins, Port D */
SFR_B(DDRD,   0x0A) /* Data Direction Register, Port D */
SFR_B(PORTD,  0x0B) /* Data Register, Port D */

SFR_B(PINE,   0x0C) /* Input Pins, Port E */
SFR_B(DDRE,   0x0D) /* Data Direction Register, Port E */
SFR_B(PORTE,  0x0E) /* Data Register, Port E */

SFR_B(PINF,   0x0F) /* Input Pins, Port F */
SFR_B(DDRF,   0x10) /* Data Direction Register, Port F */
SFR_B(PORTF,  0x11) /* Data Register, Port F */

SFR_B(PING,   0x12) /* Input Pins, Port G */
SFR_B(DDRG,   0x13) /* Data Direction Register, Port G */
SFR_B(PORTG,  0x14) /* Data Register, Port G */

SFR_B(TIFR0,   0x15) /* Timer/Counter Interrupt Flag register 0*/
SFR_B(TIFR1,   0x16) /* Timer/Counter Interrupt Flag register 1*/
SFR_B(TIFR2,   0x17) /* Timer/Counter Interrupt Flag register 2*/
SFR_B(TIFR3,   0x18) /* Timer/Counter Interrupt Flag register 3*/

SFR_B(EIFR,   0x1C)     /* External Interrupt Flag Register */
SFR_B(EIMSK,  0x1D)     /* External Interrupt Mask Register */

SFR_B(GPIOR0,  0x1E)     /* General Purpose Register 0 */

SFR_B(EECR,   0x1F)     /* EEPROM Control Register */
SFR_B(EEDR,   0x20)     /* EEPROM Data Register */
SFR_W(EEAR,   0x21)     /* EEPROM Address Register */

SFR_B(GTCCR,  0x23)     /* General Purpose Register */

SFR_B(TCCR0A,  0x24)     /* Timer/Counter 0 Control Register */
SFR_B(TCNT0,   0x26)     /* Timer/Counter 0 */
SFR_B(OCR0A,   0x27)     /* Timer/Counter 0 Output Compare Register */

SFR_B(GPIOR1,  0x2A)     /* General Purpose Register 1 */
SFR_B(GPIOR2,  0x2B)     /* General Purpose Register 2 */

SFR_B(SPCR,   0x2C)     /* SPI Control Register */
SFR_B(SPSR,   0x2D)     /* SPI Status Register */
SFR_B(SPDR,   0x2E)     /* SPI I/O Data Register */

SFR_B(ACSR,   0x30)     /* Analog Comparator Control and Status Register */

SFR_B(OCDR,   0x31)     /* On-Chip Debug Register */

SFR_B(SMCR,   0x33)    /* Sleep Mode Control Register */
SFR_B(MCUSR,  0x33)    /* MCU Status Register */
SFR_B(MCUCR,  0x33)    /* MCU Control Register */

SFR_B(SPMCSR, 0x37)     /* Store Program Memory Control and Status Register */

SFR_B(RAMPZ,  0x3B)     /* RAM Page Z Select Register */

SFR_W(SP,     0x3D)     /* Stack Pointer */
SFR_B(SREG,   0x3F)     /* Status Register */

SFR_B_EXT(WDTCR,  0x60)     /* Watchdog Timer Control Register */
SFR_B_EXT(CLKPR,  0x61)     /* Clock Prescale Register */
SFR_B_EXT(OSCCAL, 0x66)     /* Oscillator Calibration Register */

SFR_B_EXT(EICRA,  0x69)     /* External Interrupt Control Register A */
SFR_B_EXT(EICRB,  0x6A)     /* External Interrupt Control Register B */

SFR_B_EXT(TIMSK0,  0x6E)     /* Timer/Counter 0 Interrupt Mask Register */
SFR_B_EXT(TIMSK1,  0x6F)     /* Timer/Counter 1 Interrupt Mask Register */
SFR_B_EXT(TIMSK2,  0x70)     /* Timer/Counter 2 Interrupt Mask Register */
SFR_B_EXT(TIMSK3,  0x71)     /* Timer/Counter 3 Interrupt Mask Register */

SFR_B_EXT(XMCRA,  0x74)     /* External Memory Control Register A */
SFR_B_EXT(XMCRB,  0x75)     /* External Memory Control Register B */

SFR_W_EXT(ADC,    0x78)     /* ADC Data register */
SFR_B_EXT(ADCSRA, 0x7A)     /* ADC Control and Status Register A */
SFR_B_EXT(ADCSRB, 0x7B)     /* ADC Control and Status Register B */
SFR_B_EXT(ADMUX,  0x7C)     /* ADC Multiplexer Selection Register */

SFR_B_EXT(DIDR0,  0x7E)     /* Digital Input Disable Register 0 */
SFR_B_EXT(DIDR1,  0x7F)     /* Digital Input Disable Register 1 */

SFR_B_EXT(TCCR1A, 0x80)     /* Timer/Counter 1 Control Register A */
SFR_B_EXT(TCCR1B, 0x81)     /* Timer/Counter 1 Control Register B */
SFR_B_EXT(TCCR1C, 0x82)     /* Timer/Counter 1 Control Register C */
SFR_W_EXT(TCNT1,  0x84)     /* Timer/Counter 1 Register */
SFR_W_EXT(ICR1,   0x86)     /* Timer/Counter 1 Input Capture Register */
SFR_W_EXT(OCR1A,  0x88)     /* Timer/Counter 1 Output Compare Register A */
SFR_W_EXT(OCR1B,  0x8A)     /* Timer/Counter 1 Output Compare Register B */
SFR_W_EXT(OCR1C,  0x8C)     /* Timer/Counter 1 Output Compare Register C */

SFR_B_EXT(TCCR3A, 0x90)     /* Timer/Counter 3 Control Register A */
SFR_B_EXT(TCCR3B, 0x91)     /* Timer/Counter 3 Control Register B */
SFR_B_EXT(TCCR3C, 0x92)     /* Timer/Counter 3 Control Register C */
SFR_W_EXT(TCNT3,  0x94)     /* Timer/Counter 3 Register */
SFR_W_EXT(ICR3,   0x96)     /* Timer/Counter 3 Input Capture Register */
SFR_W_EXT(OCR3A,  0x98)     /* Timer/Counter 3 Output Compare Register A */
SFR_W_EXT(OCR3B,  0x9A)     /* Timer/Counter 3 Output Compare Register B */
SFR_W_EXT(OCR3C,  0x9C)     /* Timer/Counter 3 Output Compare Register C */

SFR_B_EXT(TCCR2A, 0xB0)     /* Timer/Counter 2 Control Register A */
SFR_B_EXT(TCNT2,  0xB2)     /* Timer/Counter 2 Register */
SFR_B_EXT(OCR2A,  0xB3)     /* Timer/Counter 2 Output Compare Register A */

SFR_B_EXT(ASSR,   0xB6)     /* Asynchronous mode Status Register */

SFR_B_EXT(TWBR,   0xB8)     /* TWI Bit Rate Register */
SFR_B_EXT(TWSR,   0XB9)     /* TWI Status Register */
SFR_B_EXT(TWAR,   0xBA)     /* TWI Address Register */
SFR_B_EXT(TWDR,   0xBB)     /* TWI Data Register */
SFR_B_EXT(TWCR,   0xBC)     /* TWI Control Register */

SFR_B_EXT(UCSR0A, 0xC0)     /* USART0 Control and Status Register A */
SFR_B_EXT(UCSR0B, 0xC1)     /* USART0 Control and Status Register B */
SFR_B_EXT(UCSR0C, 0xC2)     /* USART0 Control and Status Register C */
SFR_W_EXT(UBRR0,  0xC4)     /* USART0 Baud Rate Register Low */
SFR_B_EXT(UDR0,   0xC6)     /* USART0 I/O Data Register */

SFR_B_EXT(UCSR1A, 0xC8)     /* USART1 Control and Status Register A */
SFR_B_EXT(UCSR1B, 0xC9)     /* USART1 Control and Status Register B */
SFR_B_EXT(UCSR1C, 0xCA)     /* USART1 Control and Status Register C */
SFR_W_EXT(UBRR1,  0xCC)     /* USART1 Baud Rate Register Low */
SFR_B_EXT(UDR1,   0xCE)     /* USART1 I/O Data Register */


SFR_B_EXT(CANGCON  ,0xD8)   /* CAN General Control Register */
SFR_B_EXT(CANGSTA  ,0xD9)   /* CAN General Status Register */
SFR_B_EXT(CANGIT   ,0xDA)   /* CAN General Interrupt Register */
SFR_B_EXT(CANGIE   ,0xDB)   /* CAN General Interrupt Enable Register */
SFR_B_EXT(CANEN2   ,0xDC)   /* CAN Enable Mob 2 Register */
SFR_B_EXT(CANEN1   ,0xDD)   /* CAN Enable Mob 1 Register */
SFR_B_EXT(CANIE2   ,0xDE)   /* CAN Enable Interrupt Mob 2 Register */
SFR_B_EXT(CANIE1   ,0xDF)   /* CAN Enable Interrupt Mob 1 Register */
SFR_B_EXT(CANSIT2  ,0xE0)   /* CAN Status Interrupt Mob 2 Register */
SFR_B_EXT(CANSIT1  ,0xE1)   /* CAN Status Interrupt Mob 1 Register */

SFR_B_EXT(CANBT1   ,0xE2)   /* CAN Bit Timing 1 Register */
SFR_B_EXT(CANBT2   ,0xE3)   /* CAN Bit Timing 2 Register */
SFR_B_EXT(CANBT3   ,0xE4)   /* CAN Bit Timing 3 Register */
SFR_B_EXT(CANTCON  ,0xE5)   /* CAN Timer Control Register */
SFR_W_EXT(CANTIM   ,0xE6)   /* CAN Timer Register */
SFR_W_EXT(CANTTC   ,0xE8)   /* CAN Time TTC Register */
SFR_B_EXT(CANTEC   ,0xEA)   /* CAN TEC Counter Register */
SFR_B_EXT(CANREC   ,0xEB)   /* CAN REC Counter Register */
SFR_B_EXT(CANHPMOB ,0xEC)   /* CAN Highest Priority Mob Register */

SFR_B_EXT(CANPAGE  ,0xED)   /* CAN Page Mob Register */
SFR_B_EXT(CANSTMOB ,0xEE)   /* CAN Mob Status Register */
SFR_B_EXT(CANCDMOB ,0xEF)   /* CAN Mob Control & DLC Register */
SFR_B_EXT(CANIDT4  ,0xF0)   /* CAN Identifier tag 4 Register */
SFR_B_EXT(CANIDT3  ,0xF1)   /* CAN Identifier tag 3 Register */
SFR_B_EXT(CANIDT2  ,0xF2)   /* CAN Identifier tag 2 Register */
SFR_B_EXT(CANIDT1  ,0xF3)   /* CAN Identifier tag 1 Register */
SFR_B_EXT(CANIDM4  ,0xF4)   /* CAN Identifier Mask 4 Register */
SFR_B_EXT(CANIDM3  ,0xF5)   /* CAN Identifier Mask 3 Register */
SFR_B_EXT(CANIDM2  ,0xF6)   /* CAN Identifier Mask 2 Register */
SFR_B_EXT(CANIDM1  ,0xF7)   /* CAN Identifier Mask 1 Register */

SFR_W_EXT(CANSTMP  ,0xF8)   /* CAN Time Stamp Register */
SFR_B_EXT(CANMSG   ,0xFA)   /* CAN Message Data Regiter */

#endif
/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/
/* NB! vectors are specified as byte addresses */
#define    RESET_vect           (0x00)

#define    INT0_vect            (0x04)
#define    INT1_vect            (0x08)
#define    INT2_vect            (0x0C)
#define    INT3_vect            (0x10)
#define    INT4_vect            (0x14)
#define    INT5_vect            (0x18)
#define    INT6_vect            (0x1C)
#define    INT7_vect            (0x20)

#define    TIMER2_COMP_vect     (0x24)
#define    TIMER2_OVF_vect      (0x28)

#define    TIMER1_CAPT_vect     (0x2C)
#define    TIMER1_COMPA_vect    (0x30)
#define    TIMER1_COMPB_vect    (0x34)
#define    TIMER1_COMPC_vect    (0x38)
#define    TIMER1_OVF_vect      (0x3C)

#define    TIMER0_COMP_vect     (0x40)
#define    TIMER0_OVF_vect      (0x44)

#define    CANIT_vect		(0x48)	 					
#define    CANTOVF_vect		(0x4C) 		

#define    SPI_STC_vect         (0x50)

#define    USART0_RXC_vect      (0x54)
#define    USART0_UDRE_vect     (0x58)
#define    USART0_TXC_vect      (0x5C)

#define    ANA_COMP_vect        (0x60)

#define    ADC_vect             (0x64)

#define    EE_RDY_vect          (0x68)

#define    TIMER3_CAPT_vect     (0x6C)
#define    TIMER3_COMPA_vect    (0x70)
#define    TIMER3_COMPB_vect    (0x74)
#define    TIMER3_COMPC_vect    (0x78)
#define    TIMER3_OVF_vect      (0x7C)

#define    USART1_RXC_vect      (0x80)
#define    USART1_UDRE_vect     (0x84)
#define    USART1_TXC_vect      (0x88)

#define    TWI_vect             (0x8C)
#define    SPM_RDY_vect         (0x90)


/*==========================*/
/* Bit Position Definitions */
/*==========================*/
/* PINA : Input Pins, Port A */
#define    PINA7    7
#define    PINA6    6
#define    PINA5    5
#define    PINA4    4
#define    PINA3    3
#define    PINA2    2
#define    PINA1    1
#define    PINA0    0

/* DDRA : Data Direction Register, Port A */
#define    DDA7     7
#define    DDA6     6
#define    DDA5     5
#define    DDA4     4
#define    DDA3     3
#define    DDA2     2
#define    DDA1     1
#define    DDA0     0

/* PORTA : Data Register, Port A */
#define    PORTA7   7
#define    PORTA6   6
#define    PORTA5   5
#define    PORTA4   4
#define    PORTA3   3
#define    PORTA2   2
#define    PORTA1   1
#define    PORTA0   0

/* PORTA : Data Register, Port A */
#define    PA7      7
#define    PA6      6
#define    PA5      5
#define    PA4      4
#define    PA3      3
#define    PA2      2
#define    PA1      1
#define    PA0      0
 
/* PINB : Input Pins, Port B */
#define    PINB7    7
#define    PINB6    6
#define    PINB5    5
#define    PINB4    4
#define    PINB3    3
#define    PINB2    2
#define    PINB1    1
#define    PINB0    0

/* DDRB : Data Direction Register, Port B */
#define    DDB7     7
#define    DDB6     6
#define    DDB5     5
#define    DDB4     4
#define    DDB3     3
#define    DDB2     2
#define    DDB1     1
#define    DDB0     0
 
/* PORTB : Data Register, Port B */
#define    PB7      7
#define    PB6      6
#define    PB5      5
#define    PB4      4
#define    PB3      3
#define    PB2      2
#define    PB1      1
#define    PB0      0
 
/* PORTB : Data Register, Port B */
#define    PORTB7   7
#define    PORTB6   6
#define    PORTB5   5
#define    PORTB4   4
#define    PORTB3   3
#define    PORTB2   2
#define    PORTB1   1
#define    PORTB0   0
 
/* PINC : Input Pins, Port C */
#define    PINC7    7
#define    PINC6    6
#define    PINC5    5
#define    PINC4    4
#define    PINC3    3
#define    PINC2    2
#define    PINC1    1
#define    PINC0    0

/* DDRC : Data Direction Register, Port C */
#define    DDC7     7
#define    DDC6     6
#define    DDC5     5
#define    DDC4     4
#define    DDC3     3
#define    DDC2     2
#define    DDC1     1
#define    DDC0     0
 
/* PORTC : Data Register, Port C */
#define    PC7      7
#define    PC6      6
#define    PC5      5
#define    PC4      4
#define    PC3      3
#define    PC2      2
#define    PC1      1
#define    PC0      0
 
/* PORTC : Data Register, Port C */
#define    PORTC7   7
#define    PORTC6   6
#define    PORTC5   5
#define    PORTC4   4
#define    PORTC3   3
#define    PORTC2   2
#define    PORTC1   1
#define    PORTC0   0
 
/* PIND : Input Pins, Port D */
#define    PIND7    7
#define    PIND6    6
#define    PIND5    5
#define    PIND4    4
#define    PIND3    3
#define    PIND2    2
#define    PIND1    1
#define    PIND0    0

/* DDRD : Data Direction Register, Port D */
#define    DDD7     7
#define    DDD6     6
#define    DDD5     5
#define    DDD4     4
#define    DDD3     3
#define    DDD2     2
#define    DDD1     1
#define    DDD0     0
 
/* PORTD : Data Register, Port D */
#define    PD7      7
#define    PD6      6
#define    PD5      5
#define    PD4      4
#define    PD3      3
#define    PD2      2
#define    PD1      1
#define    PD0      0
 
/* PORTD : Data Register, Port D */
#define    PORTD7   7
#define    PORTD6   6
#define    PORTD5   5
#define    PORTD4   4
#define    PORTD3   3
#define    PORTD2   2
#define    PORTD1   1
#define    PORTD0   0
 
/* PINE : Input Pins, Port E */
#define    PINE7    7
#define    PINE6    6
#define    PINE5    5
#define    PINE4    4
#define    PINE3    3
#define    PINE2    2
#define    PINE1    1
#define    PINE0    0

/* DDRE : Data Direction Register, Port E */
#define    DDE7     7
#define    DDE6     6
#define    DDE5     5
#define    DDE4     4
#define    DDE3     3
#define    DDE2     2
#define    DDE1     1
#define    DDE0     0
 
/* PORTE : Data Register, Port E */
#define    PE7      7
#define    PE6      6
#define    PE5      5
#define    PE4      4
#define    PE3      3
#define    PE2      2
#define    PE1      1
#define    PE0      0
 
/* PORTE : Data Register, Port E */
#define    PORTE7   7
#define    PORTE6   6
#define    PORTE5   5
#define    PORTE4   4
#define    PORTE3   3
#define    PORTE2   2
#define    PORTE1   1
#define    PORTE0   0
 
/* PINF : Input Pins, Port F */
#define    PINF7    7
#define    PINF6    6
#define    PINF5    5
#define    PINF4    4
#define    PINF3    3
#define    PINF2    2
#define    PINF1    1
#define    PINF0    0

/* DDRF : Data Direction Register, Port F */
#define    DDF7     7
#define    DDF6     6
#define    DDF5     5
#define    DDF4     4
#define    DDF3     3
#define    DDF2     2
#define    DDF1     1
#define    DDF0     0

/* PORTF : Data Register, Port F */
#define    PF7      7
#define    PF6      6
#define    PF5      5
#define    PF4      4
#define    PF3      3
#define    PF2      2
#define    PF1      1
#define    PF0      0
 
/* PORTF : Data Register, Port F */
#define    PORTF7   7
#define    PORTF6   6
#define    PORTF5   5
#define    PORTF4   4
#define    PORTF3   3
#define    PORTF2   2
#define    PORTF1   1
#define    PORTF0   0
 
/* Input Pins, Port G */
#define    PING4    4
#define    PING3    3
#define    PING2    2
#define    PING1    1
#define    PING0    0

/* DDRG : Data Direction Register, Port G */
#define    DDG4     4
#define    DDG3     3
#define    DDG2     2
#define    DDG1     1
#define    DDG0     0

/* PORTG : Data Register, Port G */
#define    PG4      4
#define    PG3      3
#define    PG2      2
#define    PG1      1
#define    PG0      0

/* PORTG : Data Register, Port G */
#define    PORTG4   4
#define    PORTG3   3
#define    PORTG2   2
#define    PORTG1   1
#define    PORTG0   0

/* TFR0 : Timer/Counter Interrupt Flag Register 0 */
#define    OCF0A    1
#define    TOV0     0

/* TFR1 : Timer/Counter Interrupt Flag Register 1 */
#define    ICF1     5
#define    OCF1C    3
#define    OCF1B    2
#define    OCF1A    1
#define    TOV1     0

/* TFR2 : Timer/Counter Interrupt Flag Register 2 */
#define    OCF2A    1
#define    TOV2     0

/* TFR3 : Timer/Counter Interrupt Flag Register 3 */
#define    ICF3     5
#define    OCF3C    3
#define    OCF3B    2
#define    OCF3A    1
#define    TOV3     0

/* EIFR : External Interrupt Flag Register */
#define    INTF7    7
#define    INTF6    6
#define    INTF5    5
#define    INTF4    4
#define    INTF3    3
#define    INTF2    2
#define    INTF1    1
#define    INTF0    0

/* EIMSK : External Interrupt Mask Register */
#define    INT7     7
#define    INT6     6
#define    INT5     5
#define    INT4     4
#define    INT3     3
#define    INT2     2
#define    INT1     1
#define    INT0     0

/* EECR : EEPROM Control Register */
#define    EERIE    3
#define    EEMWE    2
#define    EEWE     1
#define    EERE     0

/* GTCCR : General Timer Control Register */
#define    TSM      7
#define    PSR2     1
#define    PSR310   0


/* TCCR0A : Timer/Counter 0 Control Register */
#define    FOC0A     7
#define    WGM00    6
#define    COM0A1    5
#define    COM0A0    4
#define    WGM01    3
#define    CS02     2
#define    CS01     1
#define    CS00     0

/* SPCR : SPI Control Register */
#define    SPIE     7
#define    SPE      6
#define    DORD     5
#define    MSTR     4
#define    CPOL     3
#define    CPHA     2
#define    SPR1     1
#define    SPR0     0

/* SPSR : SPI Status Register */
#define    SPIF     7
#define    WCOL     6
#define    SPI2X    0

/* ACSR : Analog Comparator Control and Status Register */
#define    ACD      7
#define    ACBG     6
#define    ACO      5
#define    ACI      4
#define    ACIE     3
#define    ACIC     2
#define    ACIS1    1
#define    ACIS0    0

/* OCDR : On-Chip Debug Register */
#define    IDRD     7
#define    OCDR7    7
#define    OCDR6    6
#define    OCDR5    5
#define    OCDR4    4
#define    OCDR3    3
#define    OCDR2    2
#define    OCDR1    1
#define    OCDR0    0

/* SMCR : Sleep Mode Control Register */
#define    SM2      3
#define    SM1      2
#define    SM0      1
#define    SE       0

/* MCUSR : MCU general Status Register */
#define    JTRF     4
#define    WDRF     3
#define    BORF     2
#define    EXTRF    1
#define    PORF     0

/* MCUCR : MCU general Control Register */
#define    JTD      7
#define    PUD      4
#define    IVSEL    1
#define    IVCE     0

/* SPMCR : Store Program Memory Control and Status Register */
#define    SPMIE    7
#define    RWWSB    6
#define    RWWSRE   4
#define    BLBSET   3
#define    PGWRT    2
#define    PGERS    1
#define    SPMEN    0

/* RAMPZ : RAM Page Z Select Register */
#define    RAMPZ0   0

/* SPH : Stack Pointer High */
#define    SP15     7
#define    SP14     6
#define    SP13     5
#define    SP12     4
#define    SP11     3
#define    SP10     2
#define    SP9      1
#define    SP8      0

/* SPL : Stack Pointer Low */
#define    SP7      7
#define    SP6      6
#define    SP5      5
#define    SP4      4
#define    SP3      3
#define    SP2      2
#define    SP1      1
#define    SP0      0

/* WTDCR : Watchdog Timer Control Register */
#define    WDCE     4
#define    WDE      3
#define    WDP2     2
#define    WDP1     1
#define    WDP0     0

/* CLKPR : Source Clock Prescaler Register */
#define    CKLPCE   7 
#define    CKLPS3   3
#define    CKLPS2   2
#define    CKLPS1   1
#define    CKLPS0   0

/* TIMSK0 : Timer Interrupt Mask Register0 */
#define    OCIE0A   1
#define    TOIE0    0

/* TIMSK1 : Timer Interrupt Mask Register1 */
#define    ICIE1    5
#define    OCIE1C   3
#define    OCIE1B   2
#define    OCIE1A   1
#define    TOIE1    0

/* TIMSK2 : Timer Interrupt Mask Register2 */
#define    OCIE2A   1
#define    TOIE2    0

/* TIMSK3 : Timer Interrupt Mask Register3 */
#define    ICIE3    5
#define    OCIE3C   3
#define    OCIE3B   2
#define    OCIE3A   1
#define    TOIE3    0

/* XMCRA : External Memory Control A Register */
#define    SRE      7
#define    SRL2     6
#define    SRL1     5
#define    SRL0     4
#define    SRW11    3
#define    SRW10    2
#define    SRW01    1
#define    SRW00    0

/* XMCRB : External Memory Control B Register */
#define    XMBK     7
#define    XMM2     2
#define    XMM1     1
#define    XMM0     0

/* ADCSRA : ADC Control and Status Register A*/
#define    ADEN     7
#define    ADSC     6
#define    ADRF     5
#define    ADIF     4
#define    ADIE     3
#define    ADPS2    2
#define    ADPS1    1
#define    ADPS0    0

/* ADCSRB : ADC Control and Status Register B*/
#define    ADCHSM   7
#define    ACME     6
#define    ADST2    2
#define    ADST1    1
#define    ADST0    0

/* ADMUX : ADC Multiplexer Selection Register */
#define    REFS1    7
#define    REFS0    6
#define    ADLAR    5
#define    MUX4     4
#define    MUX3     3
#define    MUX2     2
#define    MUX1     1
#define    MUX0     0

/* TCCR1A : Timer/Counter 1 Control Register A */
#define    COM1A1   7
#define    COM1A0   6
#define    COM1B1   5
#define    COM1B0   4
#define    COM1C1   3
#define    COM1C0   2
#define    WGM11    1
#define    WGM10    0

/* TCCR1B : Timer/Counter 1 Control Register B */
#define    ICNC1    7
#define    ICES1    6
#define    WGM13    4
#define    WGM12    3
#define    CS12     2
#define    CS11     1
#define    CS10     0

/* TCCR1C : Timer/Counter 1 Control Register C */
#define    FOC1A    7
#define    FOC1B    6
#define    FOC1C    5

/* TCCR3A : Timer/Counter 3 Control Register A */
#define    COM3A1   7
#define    COM3A0   6
#define    COM3B1   5
#define    COM3B0   4
#define    COM3C1   3
#define    COM3C0   2
#define    WGM31    1
#define    WGM30    0

/* TCCR3B : Timer/Counter 3 Control Register B */
#define    ICNC3    7
#define    ICES3    6
#define    WGM33    4
#define    WGM32    3
#define    CS32     2
#define    CS31     1
#define    CS30     0

/* TCCR3C : Timer/Counter 3 Control Register C */
#define    FOC3A    7
#define    FOC3B    6
#define    FOC3C    5

/* TCCR2A : Timer/Counter 2 Control Register A*/
#define    FOC2     7
#define    WGM20    6
#define    COM21    5
#define    COM20    4
#define    WGM21    3
#define    CS22     2
#define    CS21     1
#define    CS20     0

/* ASSR : Asynchronous mode Status Register */
#define    EXCLK    4
#define    AS2      3
#define    TCN2UB   2
#define    OCR2UB   1
#define    TCR2UB   0

/* TWSR : TWI Status Register */
#define    TWS7     7
#define    TWS6     6
#define    TWS5     5
#define    TWS4     4
#define    TWS3     3
#define    TWPS1    1
#define    TWPS0    0

/* TWAR : TWI (slave) Address Register */
#define    TWA6     7
#define    TWA5     6
#define    TWA4     5
#define    TWA3     4
#define    TWA2     3
#define    TWA1     2
#define    TWA0     1
#define    TWGCE    0

/* TWCR : TWI Control Register */
#define    TWINT    7
#define    TWEA     6
#define    TWSTA    5
#define    TWSTO    4
#define    TWWC     3
#define    TWEN     2
#define    TWIE     0

/* UCSR0A : USART0 Control and Status Register A */
#define    RXC0     7
#define    TXC0     6
#define    UDRE0    5
#define    FE0      4
#define    DOR0     3
#define    UPE0     2
#define    U2X0     1
#define    MPCM0    0

/* UCSR0B : USART0 Control and Status Register B */
#define    RXCIE0   7
#define    TXCIE0   6
#define    UDRIE0   5
#define    RXEN0    4
#define    TXEN0    3
#define    UCSZ02   2
#define    RXB80    1
#define    TXB80    0

/* UCSR0C : USART0 Control and Status Register C */
#define    UMSEL0   6
#define    UPM01    5
#define    UPM00    4
#define    USBS0    3
#define    UCSZ01   2
#define    UCSZ00   1
#define    UCPOL0   0

/* UCSR1A : USART1 Control and Status Register A */
#define    RXC1     7
#define    TXC1     6
#define    UDRE1    5
#define    FE1      4
#define    DOR1     3
#define    UPE1     2
#define    U2X1     1
#define    MPCM1    0

/* UCSR1B : USART1 Control and Status Register B */
#define    RXCIE1   7
#define    TXCIE1   6
#define    UDRIE1   5
#define    RXEN1    4
#define    TXEN1    3
#define    UCSZ12   2
#define    RXB81    1
#define    TXB81    0

/* UCSR1C : USART1 Control and Status Register C */
#define    UMSEL1   6
#define    UPM11    5
#define    UPM10    4
#define    USBS1    3
#define    UCSZ11   2
#define    UCSZ10   1
#define    UCPOL1   0

/* CANGCON : CAN General Control Register */
#define    ABRQ     7
#define    OVRQ     6
#define    TTC      5
#define    SYNCTTC  4
#define    LISTEN   3
#define    ENA      1
#define    SWRES    0

/* CANGSTA : CAN General Status Register */
#define    OVFG     6
#define    TXBSY    4
#define    RXBSY    3
#define    ENFG     2
#define    BOFF     1
#define    ERRP     0

/* CANGIT : CAN General Interrupt Register */
#define    CANIT    7
#define    BOFFIT   6
#define    OVRTIM   5
#define    OVRBUF   4
#define    SERG     3
#define    CERG     2
#define    FERG     1
#define    AERG     0

#define    ERR_GEN_msk   0x0F
#define    INT_GEN_msk   0x5F

/* CANGIE : CAN General Interrupt Enable Register */
#define    ENIT     7
#define    ENBOFF   6
#define    ENRX     5
#define    ENTX     4
#define    ENERMOB  3
#define    ENBUF    2
#define    ENERG    1
#define    ENOVRT   0

/* CANBT1: CAN Bit Timing 1 Register */
#define    BRP      1
#define    BRP_msk  0x7E

/* CANBT2: CAN Bit Timing 2 Register */
#define    SJW      5
#define    SJW_msk  0x60
#define    PRS      1
#define    PRS_msk  0x0E

/* CANBT3: CAN Bit Timing 3 Register */
#define    PHS2     4
#define    PHS2_msk 0x70
#define    PHS1     1
#define    PHS1_msk 0x0E
#define    SMP      0

/* CANHPMOB : CAN Highest Priority MOB Register */
#define    HPMOB    4
#define    HPMOB_msk 0xF0

/* CANPAGE : CAN MOB Page Register */
#define    AINC     3
#define    MOBNB    4
#define    MOBNB_msk 0xF0

/* CANSTMOB : CAN MOB Status Register */
#define    DLCW     7
#define    TXOK     6
#define    RXOK     5
#define    BERR     4
#define    SERR     3
#define    CERR     2
#define    FERR     1
#define    AERR     0

#define    ERR_MOB_msk   0x1F
#define    INT_MOB_msk   0x7F

/* CANCDMOB : CAN MOB Control Register */
#define    CONMOB   6
#define    CONMOB_msk 0xC0

#define    RPLY     5
#define    IDE      4
#define    DLC      0
#define    DLC_msk 0x0F

/* CANIDT4 : CAN Identifier Tag 4 Register */
#define    RTRTAG   2
#define    RB1TAG   1
#define    RB0TAG   0

/* CANIDM4 : CAN Identifier Mask 4 Register */
#define    RTRMSK   2
#define    IDEMSK   0

/* Pointer definition */
#define    XL     r26
#define    XH     r27
#define    YL     r28
#define    YH     r29
#define    ZL     r30
#define    ZH     r31




#endif  /* _MCU_H*/














