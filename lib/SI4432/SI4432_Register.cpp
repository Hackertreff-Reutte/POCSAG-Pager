#include "SI4432.h"


//data is not constistent through the datasheets so it is not possible
//to say whats in this register
//register address: 0x00
uint8_t SI4432::getDeviceTypeCode(){
    return spiRead(0x00);
}

//returns the version code of the chip (bits 4:0) 
//(7:5 are reservered and not used)
//Rev X4 = 01      Rev V2: 02     Rev A0:  03
uint8_t SI4432::getVersionCode(){
    return spiRead(0x00);
}

//returns the satus of the device (errors and so on)
//TODO: create functions to get those infos on their own
/*
BIT     FUNCTION:
7       ffovfl RX/TX FIFO Overflow Status.

6       ffunfl RX/TX FIFO Underflow Status.

5       rxffem RX FIFO Empty Status.

4       headerr Header Error Status.
        Indicates if the received packet has a header check error.

3       freqerr Frequency Error Status.
        Indicates if the programmed frequency is outside of the operating range. The actual frequency is saturated to the max/min value.

2       lockdet Synthesizer Lock Detect Status.

1:0     cps[1:0] Chip Power State.
            00:     Idle State
            01:     RX State10:TX State
*/
uint8_t SI4432::getDeviceStatus(){
    return spiRead(0x02);
}