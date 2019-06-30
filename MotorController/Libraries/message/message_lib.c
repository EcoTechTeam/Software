/*
 * message_lib.c
 */


#include "message_lib.h"


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
    if(MSG_CalculateCrc(data, len) == crc) return true;
    else return false;
}


uint8_t MSG_Pack(MSG_Command cmd, uint8_t *data, uint8_t len, uint8_t *buff)
{
    MSG_Message *msg = (MSG_Message *) buff;
    //! Set address and command
    msg->Address = ADDRESS;
    msg->Command = cmd;
    msg->Length = len;

    //! Copy passed data to buffer
    for(uint8_t i=0; i<len; i++)
        msg->Payload[i] =data[i];
    //! Append CRC
    msg->Payload[len] = MSG_CalculateCrc(buff, len + 3);// tu bylo +2
    //! Return size of packed message
    return len + 4;
}


uint8_t MSG_PackButtonStates(bool a, bool b, bool c, bool d, uint8_t *buff)
{
    uint8_t data[4] = {a, b, c, d};
    return MSG_Pack(MSG_BTN_STATE, data, 4, buff);
}


