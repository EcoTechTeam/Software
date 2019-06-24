/*
 * encoder_driver.h
 */

#ifndef ENCODER_DRIVER_H_
#define ENCODER_DRIVER_H_


#include "hardware.h"


void ENC_Init(void);
int16_t ENC_ReadAndReset(void);
int16_t ENC_Read(void);
void __attribute__((weak)) ENC_FullRotation(void);


#endif /* ENCODER_DRIVER_H_ */
