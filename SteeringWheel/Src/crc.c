#include <stdint.h>
#include <stdbool.h>
#include "RS485.h"
#include "crc.h"


uint8_t gencrc8(uint8_t* data,uint8_t size)
{
    uint8_t crc = 0x8A;
    for (uint8_t i = 0; i < size; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
    return crc;
}

void crc8_update(Frame *f){
	   f->crc=gencrc8(f->bytes, FRAME_LENGTH-1);


}

bool crc8_check(Frame *f){
	if(gencrc8(f->bytes,FRAME_LENGTH)){
		return false; //jak crc != od 0, coś poszło nie tak.
	}else{
		return true; //jak crc == 0 wszystko się zgadza
	}

}
