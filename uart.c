/* John Martin added interrupt driven UART xmit-- generaly
   futzed with it-- 6/1/2006*/
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Stdio demo, UART implementation
 *
 * $Id: uart.c,v 1.1.2.1 2005/12/28 22:35:08 joerg_wunsch Exp $
 */

#include "defines.h"

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

#define MAX_BUF_SIZE 64
unsigned char xmit_count=0;
unsigned char xmit_buffer[256];
unsigned char posa=0,posb=0;
unsigned int uart_buffer_size;
/*
 * Initialize the UART to 9600 Bd, tx/rx, 8N1.
 */
void
uart_init(void)
{


	//UBRR0L=48; //set up 9600 n 8 1 8Mhz
	//UBRR0L=3; //set up 115200 n 8 1 8Mhz
	//UBRR0L=12; //set up 38.4 at 8Mhz
	UBRR0L=52; //set up 19200 at 16Mhz
	UBRR0H=0;
	//UCSR0B = _BV(TXCIE0) | _BV(TXEN0);
	UBRR1L = 52; //19200
	//	UBRR1L = 104; //9600
	UBRR1H = 0x00;
        UCSR1B = _BV(TXEN1);
	DDRD = 0x08;
	PORTD |= 0x08;
	DDRE |=0x02;
	PORTE |= 0x02;
	UCSR0B=_BV(TXEN0);
	posa=0;
	posb=0;
	uart_buffer_size=0;



 //   UCSR0C = _BV(UMSEL0)
}

ISR(USART0_TX_vect) //vector 23
{
   if (posb!=posa) {
	  UDR0=xmit_buffer[posb++];
	  uart_buffer_size--;
   }
}

//ISR(USART0_TX_vect) //vector 23
//{
//  if(posa!=posb) {
//     UDR0=xmit_buffer[posb];
//     posb++;   
//     if (posb==MAX_BUF_SIZE)
//		  posb=0;
//  }
//}

/*
 * Send character c down the UART Tx, wait until tx holding register
 * is empty.
 */
void
print_string(char *str)
{
  
  while(*str!=0) {
    uart_putchar(*str,NULL);
    str++;
  }
}

#if 1

// a polling putchar
int
uart_putchar(char c, FILE *stream)
{
 // unsigned char next;
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = c;
  
  return 0;
}
#endif

// non-polling putchar
#if 0
int
uart_putchar(char c, FILE *stream)
{
  cli();
  if ((posa!=posb)||(!(UCSR0A & _BV(UDRE0)))) {
     xmit_buffer[posa++]=c;
     uart_buffer_size++;
  }
  else { // if buffer is empty and UDR0 is empty just xmit
	UDR0=c;
  }
  sei();
  return 0;
}
#endif


/*
 * Receive a character from the UART Rx.
 *
 * This features a simple line-editor that allows to delete and
 * re-edit the characters entered, until either CR or NL is entered.
 * Printable characters entered will be echoed using uart_putchar().
 *
 * Editing characters:
 *
 * . \b (BS) or \177 (DEL) delete the previous character
 * . ^u kills the entire input buffer
 * . ^w deletes the previous word
 * . ^r sends a CR, and then reprints the buffer
 * . \t will be replaced by a single space
 *
 * All other control characters will be ignored.
 *
 * The internal line buffer is RX_BUFSIZE (80) characters long, which
 * includes the terminating \n (but no terminating \0).  If the buffer
 * is full (i. e., at RX_BUFSIZE-1 characters in order to keep space for
 * the trailing \n), any further input attempts will send a \a to
 * uart_putchar() (BEL character), although line editing is still
 * allowed.
 *
 * Input errors while talking to the UART will cause an immediate
 * return of -1 (error indication).  Notably, this will be caused by a
 * framing error (e. g. serial line "break" condition), by an input
 * overrun, and by a parity error (if parity was enabled and automatic
 * parity recognition is supported by hardware).
 *
 * Successive calls to uart_getchar() will be satisfied from the
 * internal buffer until that buffer is emptied again.
 */
int
uart_getchar(FILE *stream)
{
  uint8_t c;
  char *cp, *cp2;
  static char b[RX_BUFSIZE];
  static char *rxp;

  if (rxp == 0)
    for (cp = b;;)
      {
        loop_until_bit_is_set(UCSR0A, RXC);
        if (UCSR0A & _BV(FE))
	  return _FDEV_EOF;
        if (UCSR0A & _BV(DOR))
	  return _FDEV_ERR;
        c = UDR0;
	/* behaviour similar to Unix stty ICRNL */
	if (c == '\r')
	  c = '\n';
	if (c == '\n')
	  {
	    *cp = c;
	    uart_putchar(c, stream);
	    rxp = b;
	    break;
	  }
	else if (c == '\t')
	  c = ' ';

	if ((c >= (uint8_t)' ' && c <= (uint8_t)'\x7e') ||
	    c >= (uint8_t)'\xa0')
	  {
	    if (cp == b + RX_BUFSIZE - 1)
	      uart_putchar('\a', stream);
	    else
	      {
		*cp++ = c;
		uart_putchar(c, stream);
	      }
	    continue;
	  }

	switch (c)
	  {
	  case 'c' & 0x1f:
	    return -1;

	  case '\b':
	  case '\x7f':
	    if (cp > b)
	      {
		uart_putchar('\b', stream);
		uart_putchar(' ', stream);
		uart_putchar('\b', stream);
		cp--;
	      }
	    break;

	  case 'r' & 0x1f:
	    uart_putchar('\r', stream);
	    for (cp2 = b; cp2 < cp; cp2++)
	      uart_putchar(*cp2, stream);
	    break;

	  case 'u' & 0x1f:
	    while (cp > b)
	      {
		uart_putchar('\b', stream);
		uart_putchar(' ', stream);
		uart_putchar('\b', stream);
		cp--;
	      }
	    break;

	  case 'w' & 0x1f:
	    while (cp > b && cp[-1] != ' ')
	      {
		uart_putchar('\b', stream);
		uart_putchar(' ', stream);
		uart_putchar('\b', stream);
		cp--;
	      }
	    break;
	  }
      }

  c = *rxp++;
  if (c == '\n')
    rxp = 0;

  return c;
}

