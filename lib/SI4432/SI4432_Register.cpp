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
7       ffovfl (R) RX/TX FIFO Overflow Status.

6       ffunfl (R) RX/TX FIFO Underflow Status.

5       rxffem (R) RX FIFO Empty Status.

4       headerr (R) Header Error Status.
        Indicates if the received packet has a header check error.

3       freqerr (R) Frequency Error Status.
        Indicates if the programmed frequency is outside of the operating range
        The actual frequency is saturated to the max/min value.

2       lockdet (R) Synthesizer Lock Detect Status.

1:0     cps[1:0] (R) Chip Power State.
            00:     Idle State
            01:     RX State10:TX State
*/
uint8_t SI4432::getDeviceStatus(){
    return spiRead(0x02);
}

/*
BIT     FUNCTION:
7       ifferr (R) FIFO Underflow/Overflow Error.
        When set to 1 the TX or RX FIFO has overflowed or underflowed.

6       itxffafull (R) TX FIFO Almost Full.
        When set to 1 the TX FIFO has met its almost full threshold and needs to
        be transmitted.

5       itxffaem (R) TX FIFO Almost Empty.
        When set to 1 the TX FIFO is almost empty and needs to be filled.

4       irxffafull (R) RX FIFO Almost Full.When set to 1 the RX FIFO has met its 
        almost full threshold and needs to be read by the microcontroller.

3       iext (R) External Interrupt.
        When set to 1 an interrupt occurred on one of the GPIO’s if it is 
        programmed so. The status can be checked in register 0Eh. 7
        See GPIOx Configuration section for the details.

2       ipksent (R) Packet Sent Interrupt.
        When set to1 a valid packet has been transmitted.

1       ipkvalid (R) Valid Packet Received.When set to 1 a valid packet has been 
        received.

0       icrcerror (R) CRC Error.
        When set to 1 the cyclic redundancy check is failed.
*/
uint8_t SI4432::getInterruptStatus1(){
    return spiRead(0x03);
}


/*

BIT     FUNCTION:
7       iswdet (R) Sync Word Detected.
        When a sync word is detected this bit will be set to 1.

6       ipreaval (R) Valid Preamble Detected.
        When a preamble is detected this bit will be set to 1.

5       ipreainval (R) Invalid Preamble Detected.
        When the preamble is not found within a period of time after the RX is 
        enabled, this bit will be set to 1.

4       irssi (R) RSSI.
        When RSSI level exceeds the programmed threshold this bit will be set 7
        to 1.

3       iwut (R) Wake-Up-Timer.
        On the expiration of programmed wake-up timer this bit will be set to 1.

2       ilbd (R) Low Battery Detect.
        When a low battery event is been detected this bit will be set to 1. 
        This interrupt event is saved even if it is not enabled by the mask 
        register bit and causes an interrupt after it is enabled.

1       ichiprdy (R) Chip Ready (XTAL).
        When a chip ready event has been detected this bit will be set to 1.

0       ipor (R) Power-on-Reset (POR).
        When the chip detects a Power on Reset above the desired setting this 
        bit will be set to 1.
*/
uint8_t SI4432::getInterruptStatus2(){
        return spiRead(0x04);
}


/*
BIT     FUNCTION:
7       enfferr (R/W) Enable FIFO Underflow/Overflow.
        When set to 1 the FIFO Underflow/Overflow interrupt will be enabled.

6       entxffafull (R/W) Enable TX FIFO Almost Full.
        When set to 1 the TX FIFO Almost Full interrupt will be enabled.

5       entxffaem (R/W) Enable TX FIFO Almost Empty.
        When set to 1 the TX FIFO Almost Empty interrupt will be enabled.

4       enrxffafull (R/W) Enable RX FIFO Almost Full.
        When set to 1 the RX FIFO Almost Full interrupt will be enabled.

3       enext (R/W) Enable External Interrupt.
        When set to 1 the External Interrupt will be enabled.

2       enpksent (R/W) Enable Packet Sent.
        When ipksent =1 the Packet Sense Interrupt will be enabled.

1       enpkvalid (R/W) Enable Valid Packet Received.
        When ipkvalid = 1 the Valid Packet Received Interrupt will be enabled.

0       encrcerror (R/W) Enable CRC Error.
        When set to 1 the CRC Error interrupt will be enabled.
*/
uint8_t SI4432::getInterruptEnable1(){
        return spiRead(0x05);
}

//look at the functions above for the BIT documentation
void SI4432::setInterruptEnable1(uint8_t data){
        spiWrite(0x05, data);
}

/*

7       enswdet (R) Enable Sync Word Detected.
        When mpreadet =1 the Preamble Detected Interrupt will be enabled.

6       enpreaval (R) Enable Valid Preamble Detected.
        When mpreadet =1 the Valid Preamble Detected Interrupt will be enabled.

5       enpreainval (R) Enable Invalid Preamble Detected.
        When mpreadet =1 the Invalid Preamble Detected Interrupt will be enabled.

4       enrssi (R) Enable RSSI.
        When set to 1 the RSSI Interrupt will be enabled.

3       enwut (R/W) Enable Wake-Up Timer.
        When set to 1 the Wake-Up Timer interrupt will be enabled.

2       enlbd (R/W) Enable Low Battery Detect.
        When set to 1 the Low Battery Detect interrupt will be enabled.

1       enchiprdy (R/W) Enable Chip Ready (XTAL).
        When set to 1 the Chip Ready interrupt will be enabled.

0       enpor (R/W) Enable POR.
        When set to 1 the POR interrupt will be enabled.
*/
uint8_t SI4432::getInterruptEnable2(){
        return spiRead(0x06);
}

//look at the functions above for the BIT documentation
void SI4432::setInterruptEnable2(uint8_t data){
        spiWrite(0x06, data);
}

