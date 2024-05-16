#include "twi.h"
#include <avr/io.h>
#include "bit.h"
#include "usart.h"

void twi_init_master(void) {
    // Set up TWI module for master mode
    TWSR = 0; // Set prescalar for 1
    TWBR = 72; // Set bit rate register (see datasheet)
    TWCR = (1<<TWEN); // Enable TWI
}

void twi_start(void) {
    // Send start condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    // Wait for TWINT Flag set. This indicates that the START condition has been transmitted
    while (!(TWCR & (1<<TWINT)));
}

void twi_stop(void) {
    // Transmit STOP condition
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

    // Wait for stop condition to be executed on bus
    // TWINT is not set after a stop condition!
    while(TWCR & (1<<TWSTO));
}

void twi_write(uint8_t data)
{
    // Load data into TWI data register
    TWDR = data;
    
    // Clear TWINT to start transmission
    TWCR = (1 << TWINT) | (1 << TWEN);
    
    // Wait for transmission to complete
    while (!(TWCR & (1 << TWINT)));
}

void twi_init_slave(uint8_t address)
{
    // Set slave address
    TWAR = (address << 1);
    // Enable TWI and enable TWI interrupt
    TWCR = (1 << TWEN) | (1 << TWIE);
}
