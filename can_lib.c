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

 
/*C**************************************************************************
* $RCSfile: can_lib.c,v $
*----------------------------------------------------------------------------
* Copyright (c) 2003 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      $Name:  $      
* REVISION:     $Revision: 1.2 $     
* FILE_CVSID:   $Id: can_lib.c,v 1.2 2003/07/04 13:16:54 jberthy Exp $       
*----------------------------------------------------------------------------
* PURPOSE: 
* This template file can be parsed by langdoc for automatic documentation
* generation.
* FILE_PURPOSE: provide low level functions for CAN controller   
*
* Timing with 8 MHz oscillator and compiled IAR_AVR
* note:  xx : ICCAVR optimization size low
*       (xx): ICCAVR optimization speed high
*       [xx]: CC01 perf., 12 MHz oscillator and compiled with Keil V6.00i
*
* - CANSetBRP       : 2.2 (2.2) [14] us                                 
* - CANSetSJW       : 4.0 (3.6) [18] us                             
* - CANSetPRS       : 3.8 (3.2) [16] us                                 
* - CANSetPHS2      : 3.8 (3.2) [17] us                                                                               
* - CANSetPHS1      : 3.8 (3.2) [16] us                                                        
* - FindFirstChIt   : 2.2 (2.2) [24] us max (it on channel_14)                                                       
* - ConfChannel_Rx  : xx (xx) [110] us max(ide with mask),
*                     xx (xx) [ 59] us max(std with mask)                                                       
* - SendCanMsg      : 44 (33.2) [333] us max(ide, 8 data),
*                     40 (29.4) [306] us max(std, 8 data)                                                        
* - ReadCanMsg_Rx   : xx (xx) [392] us max(ide, 8 data),
*                     xx (xx) [326] us max(std, 8 data)                                                         
* - RazAllMailbox   : 187.6 (147.4) [890]  us
******************************************************************************/

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "config.h"
#include "can_lib.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define TRUE 1
#define FALSE 0
#define SET 1
#undef    USER_CAN_FCT_IT_TXOK
/*_____ G L O B A L S ________________________________________________________*/

/* variables used by everybody */
conf_t   conf_rx, conf_tx;

/* variables used by ConfChannel_Rx. */
can_id_t   can_rx_filt, can_rx_msk;

/* variables used by SendCanMsg. */
//Uchar       * pt_candata_tx; 
//can_id_t      can_tx_id;

/* variables used by ReadCanMsg. */
//can_msg_t   * pt_st_can_rx;

/*
unsigned char CANSTMOB_check,CANCDMOB_check,
	CANGCON_check,CANGSTA_check,CANGIT_check,
	CANGIE_check,CANEN1_check,CANEN2_check,
   CANIE1_check,CANIE2_check,channel_check;
   
unsigned char CANIDT1_check,CANIDT2_check,CANIDT3_check,CANIDT4_check;


extern long int id_std;
extern unsigned int f_recept_can_message;
extern int recv_counter;
*/
#define IT_TXOK bit_6
#define IT_RXOK bit_5


/*_____ P R I V A T E - F U N C T I O N S - D E C L A R A T I O N ____________*/


/*_____ L O C A L S __________________________________________________________*/


/*_____ P U B L I C - F U N C T I O N S ______________________________________*/


/*_____ P R I V A T E - F U N C T I O N S ____________________________________*/


/*F****************************************************************************
* FUNCTION_NAME: RazAllMailbox                                                  
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 13/10/99                                                 
*   AVR RELEASE  : 23/05/03 - JT                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Mailbox, status and control registers reset    
* FUNCTION_INPUTS : void                                                          
* FUNCTION_OUTPUTS: void                                                       
******************************************************************************/
void RazAllMailbox (void)
{
  Uchar num_channel, num_data;

  for (num_channel = 0; num_channel < NB_CHANNEL; num_channel++)
  {
    CANPAGE  = (num_channel << MOBNB);
    CANSTMOB = 0;
    CANCDMOB = 0;
    CANIDT4  = 0;
    CANIDT3  = 0;
    CANIDT2  = 0;
    CANIDT1  = 0;
    CANIDM4  = 0;
    CANIDM3  = 0;
    CANIDM2  = 0;
    CANIDM1  = 0;
    for (num_data = 0; num_data < NB_DATA_MAX; num_data++)
    {
      CANMSG = 0;
    }
  }

}





/*F**************************************************************************
* FUNCTION_NAME: ConfChannel_Rx                                             
*----------------------------------------------------------------------------
* FUNCTION_AUTHOR: BERTHY J.S.                                              
* FUNCTION_DATE  : 28/09/99                                                 
*   AVR RELEASE  : 23/05/03 - JT                                                 
*----------------------------------------------------------------------------
* FUNCTION_PURPOSE: Configure the MOb (or channel) in reception,
*        The identifier filtered and mask are initialized with the 
*        value contain in global variables can_rx_id and can_rx_msk.     
*        The configuration is defined in globale variable conf_rx.                   
*                          
* FUNCTION_INPUTS : void
* FUNCTION_OUTPUTS: void                                                    
*----------------------------------------------------------------------------
* GLOBAL VARIABLES USED :
*	- conf_rx
*	- can_rx_filt
*	- can_rx_msk
******************************************************************************
* The variable conf_rx must contain information:                                   
*    - on ide:
*           standart (CONF_NOIDE) or 
*           extended (CONF_IDE)                     
*    - on ide mask, 
*           no mask on ide bit(CONF_NOMSK_IDE) or
*           mask on ide bit   (CONF_MSK_IDE) 
*    - on rtr:
*           data frame   (CONF_NORTR) or 
*           remote frame (CONF_RTR)                     
*    - on rtr mask, 
*           no mask on rtr bit(CONF_NOMSK_RTR) or 
*           mask on rtr bit   (CONF_MSK_RTR) 
*    - on buffer mode
*           channel is not for buffer mode (CONF_NOBUFFER) or 
*           channel is for the buffer mode (CONF_BUFFER)
*
* Exemple of configuration:                                                                   
* ------------------------                                                                   
* conf_rx = CONF_IDE | CONF_NOMSK_IDE | CONF_NORTR | CONF_NOMSK_RTR | CONF_NOBUFFER                                       
*                                                                            
******************************************************************************
* NOTE:                                                                      
*     It's very important to be sure that channel is free.                 
*     No verification is perform by this function.                          
*     The corresponding MOb (or channel) must be selected before calling
*     this function.
*
*     When conf_rx = 0 -> CONF_NOIDE | CONF_NOMSK_IDE | CONF_NORTR |
*                         CONF_NOMSK_RTR | NO_BUFFER 
*
* Exemple of use:
*---------------
*
*  can_rx_filt.ext = 0x5555555;
*  can_rx_msk.ext  = 0x00;
*  conf_rx         = CONF_IDE|CONF_MSK_IDE|CONF_NOBUFFER;
*  CAN_SET_CHANNEL(CHANNEL_1);
*  ConfChannel_Rx();
*
******************************************************************************/
void ConfChannel_Rx(void)
{

  CANSTMOB = 0x00;
  CANCDMOB = 0x00;

//  if (ide == TRUE)
  if ((conf_rx & CONF_IDE) != FALSE)
  { /* 29-bit identifier tag  */  
    CANIDT1 = CAN_SET_EXT_ID_28_21 (can_rx_filt.ext);
    CANIDT2 = CAN_SET_EXT_ID_20_13 (can_rx_filt.ext);
    CANIDT3 = CAN_SET_EXT_ID_12_5  (can_rx_filt.ext);
    CANIDT4 = CAN_SET_EXT_ID_4_0   (can_rx_filt.ext);
                                   /* RTRTAG and RBnTAG cleared */
    /* 29-bit identifier mask */
    CANIDM1 = CAN_SET_EXT_MSK_28_21 (can_rx_msk.ext);
    CANIDM2 = CAN_SET_EXT_MSK_20_13 (can_rx_msk.ext);
    CANIDM3 = CAN_SET_EXT_MSK_12_5  (can_rx_msk.ext);
    CANIDM4 = CAN_SET_EXT_MSK_4_0   (can_rx_msk.ext);
                                   /* RTRMSK and IDEMSK cleared */
                            
    CANCDMOB |= (SET<<IDE);        /* set IDE bit in CANCDMOB */
  }
  else
  { /* 11-bit identifier tag  */ 
    //printf("setting 11 bit flt and msk\n\r!"); 
    CANIDT1 = CAN_SET_STD_ID_10_4 (can_rx_filt.std);
    CANIDT2 = CAN_SET_STD_ID_3_0 (can_rx_filt.std);
    CANIDT4 = 0;                   /* Clear RTRTAG and RB0TAG */
    /* 11-bit identifier mask */
    CANIDM1 = CAN_SET_STD_MSK_10_4 (can_rx_msk.std);
    CANIDM2 = CAN_SET_STD_MSK_3_0 (can_rx_msk.std);
    //CANIDM3 = 0; /* optional */
    CANIDM4 = 0;                   /* Clear RTRMSK and IDEMSK */

    /* IDE=0 in CANCDMOB already done at the beginning */
  }

  CANCDMOB |= NB_DATA_MAX;
  /* If DLC of received message < NB_DATA_MAX, DLCW will be set */

//  if (rtr == TRUE)
  if ((conf_rx & CONF_RTR) != FALSE)
  {
    CANIDT4 |= (SET<<RTRTAG);      /* set RTRTAG bit in CANIDT4.   */   
  }
  /* else already done */

//  if (msk_rtr == TRUE)
  if ((conf_rx & CONF_MSK_RTR) != FALSE)
  {
    CANIDM4 |= (SET<<RTRMSK);	 /* set RTRMSK bit in CANIDM4.   */ 
  }
  /* else already done */
  
//  if (msk_ide == TRUE)
  if ((conf_rx & CONF_MSK_IDE) != FALSE)
  {
    CANIDM4 |= (SET<<IDEMSK);      /* set IDEMSK bit in CANIDM4.   */
  }
  /* else already done */

//  if (buffer == TRUE)
  if ((conf_rx & CONF_BUFFER) != FALSE)
  {
   ENABLE_CHANNEL_BUFFER; /* Buffer Reception enabled.*/
  }
  else
  {
    ENABLE_CHANNEL_RX; /* Reception enabled.*/
  }

}































