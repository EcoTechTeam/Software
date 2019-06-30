/*
 * button_driver.c
 */

#include "led_driver.h"
#include "msg_Lib.h"
#include "hardware.h"

static uint8_t  _CrcTable[256];


void MSG_CrcInit(void)
{
	uint8_t remainder;
	uint8_t dividend = 0;
    //! Compute the remainder of each possible dividend.
    do
    {
        remainder = dividend;
        //! Perform modulo-2 division, a bit at a time.
        for (uint8_t bit=8; bit>0; bit--)
        {
            //! Try to divide the current data bit.
            if(remainder & 0x80)
                remainder = (remainder << 1) ^ POLYNOMIAL;
            else remainder = (remainder << 1);
        }
        //! Store the result into the table.
        _CrcTable[dividend++] = remainder;
    } while(dividend);
}


uint8_t MSG_CalculateCrc(uint8_t *data, uint8_t len)
{
    uint8_t remainder = 0;
    //! Divide the message by the polynomial, a byte at a time
    for (uint8_t byte=0; byte<len; byte++)
    {
        uint8_t d = data[byte] ^ remainder;
        remainder = _CrcTable[d];
    }
    //! The final remainder is the CRC.
    return remainder;
}
bool MSG_ValidateCrc(uint8_t *data, uint8_t len, uint8_t crc)
{
    if(MSG_CalculateCrc(data, len) == crc) return true; //tu chyba len-1
    else return false;
}

void BUS_Received(uint8_t *buff, uint8_t len)
{
	int i=0;
	//for(i;i<len;i++)
	//{
		if(buff[i]==ADDRESS /*&& (MSG_ValidateCrc(&data[i],data[i+2]+4,data[i+data[i+2]+3]))*/)
		MSG_Received((&buff[i],len-i);

	//}
}
