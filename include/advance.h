#ifndef _ADVANCE_H
#define _ADVANCE_H

#include <msp430.h>
#include "NRF24L01.h"


/* Available states for the transceiver's state machine */
#define RF24_STATE_NOTPRESENT  0x00
#define RF24_STATE_POWERDOWN   0x01
#define RF24_STATE_STANDBY_I   0x02
#define RF24_STATE_STANDBY_II  0x03
#define RF24_STATE_PTX         0x04
#define RF24_STATE_PRX         0x05
#define RF24_STATE_TEST        0x06


void flush_tx();
void flush_rx();
void pulse_ce();
void nrf24l01_powerdown();
void nrf24l01_standby();
void nrf24l01_activate_tx();
void nrf24l01_activate_rx();

#endif