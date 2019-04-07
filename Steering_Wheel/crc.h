/*
 * crc.h
 *
 *  Created on: Apr 7, 2019
 *      Author: a
 */

#ifndef CRC_H_
#define CRC_H_
#include "RS485.h"
void crc8_update(Frame& f);
bool crc8_check(const Frame& f);

#endif /* CRC_H_ */
