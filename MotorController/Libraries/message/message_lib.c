
#include <stdint.h>
#include <stdbool.h>
#include "bus_driver.h"
#include "message_lib.h"


//####################         Queue         #####################################
static bool _BusReady= true;
struct {
	uint8_t FrameBuff[Frames_BUFF_LEN*10];
	MSG_Message framePtr[Frames_BUFF_LEN];
	uint8_t headBuff;
	uint8_t tailBuff;
	uint8_t headPtr;
	uint8_t tailPtr;
}_Queue = {.headBuff=0,.tailBuff=0,.headPtr=0,.tailPtr=0 };


MSG_Message MSG_FromQue()
 {

	MSG_Message temp =_Queue.framePtr[_Queue.headPtr];
	_Queue.headPtr =(_Queue.headPtr+1)%Frames_BUFF_LEN;



	_Queue.headBuff =(_Queue.headBuff+temp.Length)%(Frames_BUFF_LEN*10);

    return temp;
}


void MSG_ToQue(uint8_t frame[], uint8_t len, uint8_t address)
{

	 	 //BUS_SendBlocking(b,2);
	 	//BUS_SendBlocking(&_Queue.headBuff,4);
	 	//BUS_SendBlocking(b,2);
	 if((_Queue.tailBuff+len+4)>(Frames_BUFF_LEN*10))
	 {
		 _Queue.headBuff=(_Queue.headBuff+((Frames_BUFF_LEN*10)-(_Queue.tailBuff)))%(Frames_BUFF_LEN*10);
		 _Queue.tailBuff=0;

	 }

	 uint8_t temp =_Queue.tailBuff;

	 _Queue.FrameBuff[_Queue.tailBuff] = START_BYTE;
	 _Queue.tailBuff =(_Queue.tailBuff+1)%(Frames_BUFF_LEN*10);
	 _Queue.FrameBuff[_Queue.tailBuff] = address;
	 _Queue.tailBuff =(_Queue.tailBuff+1)%(Frames_BUFF_LEN*10);
	 _Queue.FrameBuff[_Queue.tailBuff] = len;
	 _Queue.tailBuff =(_Queue.tailBuff+1)%(Frames_BUFF_LEN*10);
	 for(uint8_t i=0; i<len; i++)
	 {
		 _Queue.FrameBuff[_Queue.tailBuff] = frame[i];
		 _Queue.tailBuff =(_Queue.tailBuff+1)%(Frames_BUFF_LEN*10);
	 }
	 _Queue.FrameBuff[_Queue.tailBuff] = MSG_Crc(&_Queue.FrameBuff[temp],len+3);
	 _Queue.tailBuff =(_Queue.tailBuff+1)%(Frames_BUFF_LEN*10);

	 _Queue.framePtr[_Queue.tailPtr].Payload = &_Queue.FrameBuff[temp];
	 _Queue.framePtr[_Queue.tailPtr].Length = len+4;
	 _Queue.tailPtr =(_Queue.tailPtr+1)%Frames_BUFF_LEN;

}


bool MSG_IsQueFull(uint8_t space) //sorry xD
 {

    if ((_Queue.tailPtr==(Frames_BUFF_LEN-1) && _Queue.headPtr == 0) || (_Queue.headPtr == (_Queue.tailPtr + 1)) )
    {
    	return true;


    }
    if(_Queue.tailBuff < _Queue.headBuff &&
       _Queue.tailBuff+space > _Queue.headBuff)
    {

    	return true;

    }
    if ( (_Queue.tailBuff+space)>(Frames_BUFF_LEN*10) &&
    		(((_Queue.tailBuff+space)%(Frames_BUFF_LEN*10)) > _Queue.headBuff))
    {
    	return true;
    }


        return false;
}

bool MSG_IsQueEmpty()
{
    if(_Queue.headPtr == _Queue.tailPtr)
        return true;
    else
        return false;
}






//#####################       CRC         ###############################################
static uint8_t  crcTable[256];

void MSG_CrcInit(void)
{
	uint8_t  remainder;
	uint8_t  dividend=0;

    /*
     * Compute the remainder of each possible dividend.
     */
    while(1)
    {
        remainder = dividend ;

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (uint8_t bit = 8; bit > 0; bit--)
        {
            /*
             * Try to divide the current data bit.
             */
            if (remainder & 0x80)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }

        /*
         * Store the result into the table.
         */
        crcTable[dividend] = remainder;
        dividend++;
        if(dividend==0xff) return;
    }


}



uint8_t MSG_Crc(uint8_t const message[], uint8_t nBytes)
{
    uint8_t data;
    uint8_t remainder = 0;


    /*
     * Divide the message by the polynomial, a byte at a time.
     */
    for (uint8_t byte = 0; byte < nBytes; byte++)
    {
        data = message[byte] ^ (remainder);
        remainder = crcTable[data];
    }

    /*
     * The final remainder is the CRC.
     */
    return (remainder);

}

//####################################################


void BUS_Received(uint8_t *buff, uint8_t len)
{

	for(uint8_t i=0; i<len-4; i++)
	{
		if(buff[i]==START_BYTE && buff[i+1]==MY_ADDRESS && ((i+buff[i+2]+3)<len)  ) //Example frame: 7e 01 02 dd ee c6
				{
						if(!MSG_Crc(&buff[i], buff[i+2]+4)) //CrcGenerate returns 0 if everything is ok.
						{
							MSG_Received(&buff[i+3],buff[i+2]);

						}


				}

	}


}

void MSG_Send(uint8_t* data, uint8_t len, uint8_t address)
{

	if(!MSG_IsQueFull(len+4)) {

		MSG_ToQue(data,len,address); //to troche głupie ze wrzucam to do kolejki tylko zeby potem ją z niej wyjąć

		if(_BusReady)
			{
				_BusReady=false;
				MSG_Message temp = MSG_FromQue();
				BUS_Send(temp.Payload,temp.Length);
			}

	}




}

void BUS_BusFree(void)
{
	if(MSG_IsQueEmpty())
	{
		_BusReady=true;
	}
	else
	{
		_BusReady=false;
		MSG_Message temp = MSG_FromQue();
		BUS_Send(temp.Payload,temp.Length);

	}


}








