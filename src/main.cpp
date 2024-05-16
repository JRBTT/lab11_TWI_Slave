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
volatile bool flag_new = 0;

ISR(TWI_vect);

void twi_print_twsr()
{
  usart_tx_reg(TWSR);
  usart_transmit('\n');
}

ISR(TWI_vect)
{
  switch (TWSR & 0b11111100)
  {
    case 0x60:
    case 0x68:
      TWCR |= 1 << TWINT | 1 << TWEA;
      break;
    case 0x80:
      rx_twi = TWDR;
      flag_new = 1;
      TWCR |= 1 << TWINT | 1 << TWEA;
      break;
    case 0xA0:
    case 0xC0:
    case 0xC8:
      TWCR |= 1 << TWINT;
      break;
    case 0xA8:
    case 0xB8:
    case 0xB0:
      TWDR = rx_twi + 1;
      TWCR |= 1 << TWINT | 1 << TWEA;
      break;
    default:
      TWCR |= 1 << TWINT | 1 << TWEA;
    break;
  }
}

int main()
{
  usart_init(103);

  bitClear(DDRD, PD0); // PD0 - SCL
  bitClear(DDRD, PD1); // PD1 - SDA
  // bitSet(PORTD, PD0); // PD0 - SCL
  // bitSet(PORTD, PD1); // PD1 - SDA

  twi_init_slave(SLA);
  bitSet(TWCR, TWIE);
  twi_print_twsr();

  sei();

  while (1)
  {
    if (flag_new)
    {
      usart_tx_float(rx_twi, 3, 0);
      flag_new = 0;
    }

    _delay_ms(1);
  }
}



