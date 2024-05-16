#ifndef TWI_H
#define TWI_H

#include <stdint.h>

void twi_init_master();
void twi_init_slave(unsigned char address);
void twi_start();
void twi_stop();
void twi_write(unsigned char data);
int twi_read_nack();

#endif // TWI_H