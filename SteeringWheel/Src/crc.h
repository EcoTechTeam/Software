/*
 * crc.h
 *
 *  Created on: Apr 7, 2019
 *      Author: a
 */

#ifndef CRC_H_
#define CRC_H_
#include "RS485.h"
#include <stdbool.h>

void crc8_update(Frame *f);
bool crc8_check(Frame *f);
uint8_t gencrc8(uint8_t* data, uint8_t size);

#endif /* CRC_H_ */
