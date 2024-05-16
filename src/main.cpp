#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "bit.h"
#include "timer.h"
#include "twi.h"

#define SLA 0x22

volatile uint8_t toSend = 0;
volatile uint8_t rx_twi = 0;
bool flag_new = 0;

ISR(TWI_vect);

int main()
{
  usart_init(103);
  _delay_ms(1000);
  usart_tx_string("USART initialized");
  usart_transmit('\n');
  // bitClear(DDRD, PD0); // PD0 - SCL
  // bitClear(DDRD, PD1); // PD1 - SDA
  // bitSet(PORTD, PD0); // PD0 - SCL
  // bitSet(PORTD, PD1); // PD1 - SDA
  // twi_init_slave(SLA);
  // bitSet(TWCR, TWIE);
}



