/*
 * bus_driver.h
 */

#ifndef BUS_DRIVER_H_
#define BUS_DRIVER_H_

#include <stdint.h>


#define BUS_BUFF_LEN	60 //po dobraniu odpowiednich timingów powinna być w nim tylko jedna ranka.
#define BUS_BUFF_NUM	6

#define BAUD 4800 //todo
#define MYUBRR F_CPU/16/BAUD-1
#define PRIORITY 1


//! Initialization function
void BUS_Init(void);
//! Send passed buff to the bus
void BUS_Send(uint8_t *buff, uint8_t len);
//! Send passed buff to the bus in blocking function
void BUS_SendBlocking(uint8_t *buff, uint8_t len);
//! Function called after receive. Has to be implemented in other file
void __attribute__((weak)) BUS_Received(uint8_t *buff, uint8_t len);


#endif
