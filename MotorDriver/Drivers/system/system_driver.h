/*
 * system.h
 */

#ifndef DRIVERS_SYSTEM_H_
#define DRIVERS_SYSTEM_H_


#include <stdint.h>


void SYS_Init(void);
uint32_t SYS_GetTick(void);
void SYS_KickWatchdog(void);
void __attribute__((weak)) SYS_Tick(void);


#endif /* DRIVERS_SYSTEM_H_ */
