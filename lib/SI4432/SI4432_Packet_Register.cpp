#include "SI4432.h"

/*
REGISTERNAME: Data Access Control
REGISTER: 0x30 / 30h

BIT     FUNCTION:
7       enpacrx (R/W) Enable Packet RX Handling.
        If FIFO Mode (dtmod = 10) is being used automatic packet handling may be 
        enabled. Setting enpacrx = 1 will enable automatic packet handling in 
        the RX path. Register 30–4D allow for various configurations of the 
        packet structure. Setting enpacrx = 0 will not do any packet handling in 
        the RX path. It will only receive everything after the sync word and 
        fill up the RX FIFO.

6       lsbfrst (R/W) LSB First Enable.
        The LSB of the data will be transmitted/received first if this bit is set.

5       crcdonly (R/W) CRC Data Only Enable.
        When this bit is set to 1 the CRC is calculated on and checked against 
        the packet data fields only.

4       Reserved (R/W) Reserved.

3       enpactx (R/W) Enable Packet TX Handling.
        If FIFO Mode (dtmod = 10) is being used automatic packet handling may be 
        enabled. Setting enpactx = 1 will enable automatic packet handling in 
        the TX path. Register 30–4D allow for various configurations of the 
        packet structure. Setting enpactx = 0 will not do any packet handling in 
        the TX path. It will only transmit what is loaded to the FIFO.

2       encrc (R/W) CRC Enable.
        Cyclic Redundancy Check generation is enabled if this bit is set.
                1:0 crc[1:0] CRC Polynomial Selection.
                00: CCITT
                01: CRC-16 (IBM)
                10: IEC-16
                11: Biacheva
*/
inline uint8_t SI4432::getDataAccessControl(){
        return spiRead(0x30);
}

//look at the functions above for the BIT documentation
inline void SI4432::setDataAccessControl(uint8_t data){
        spiWrite(0x30, data);
}


/*
REGISTERNAME: EZMAC Status
REGISTER: 0x31 / 31h

BIT     FUNCTION:
7       Reserved (R) Reserved.

6       rxcrc1 (R) If high, it indicates the last CRC received is all one’s.
        May indicated Transmitter underflow in case of CRC error.

5       pksrch (R) Packet Searching.
        When pksrch = 1 the radio is searching for a valid packet.

4       pkrx (R) Packet Receiving.
        When pkrx = 1 the radio is currently receiving a valid packet.

3       pkvalid (R) Valid Packet Received.
        When a pkvalid = 1 a valid packet has been received by the receiver. 
        (Same bit as in register 03, but reading it does not reset the IRQ)

2       crcerror (R) CRC Error.
        When crcerror = 1 a Cyclic Redundancy Check error has been detected. 
        (Same bit as in register 03, but reading it does not reset the IRQ)

1       pktx (R) Packet Transmitting.
        When pktx = 1 the radio is currently transmitting a packet.

0       pksent (R) Packet Sent.
        A pksent = 1 a packet has been sent by the radio. (Same bit as in 
        register 03, but reading it does not reset the IRQ)
*/
inline uint8_t SI4432::getEZMACStatus(){
        return spiRead(0x31);
}


/*
REGISTERNAME: Header Control 1
REGISTER: 0x32 / 32h

BIT     FUNCTION:
7:4     bcen[3:0] (R/W) Broadcast Address (FFh) Check Enable.
        If it is enabled together with Header Byte Check then the header check 
        is OK if the incoming header byte equals with the appropriate check 
        byte or FFh). One hot encoding.
            0000: No broadcast address enable.
            0001: Broadcast address enable for header byte 0.
            0010: Broadcast address enable for header byte 1.
            0011: Broadcast address enable for header bytes 0 & 1.
            0100: …

3:0     hdch[3:0] (R/W) Received Header Bytes to be Checked Against the Check 
        Header Bytes.
        One hot encoding. The receiver will use hdch[2:0] to know the position 
        of the Header Bytes.
            0000: No Received Header check
            0001: Received Header check for byte 0.
            0010: Received Header check for bytes 1.
            0011: Received header check for bytes 0 & 1.
            0100: …
*/
inline uint8_t SI4432::getHeaderControl1(){
        return spiRead(0x32);
}

//look at the functions above for the BIT documentation
inline void SI4432::setHeaderControl1(uint8_t data){
        spiWrite(0x32, data);
}


/*
REGISTERNAME: Header Control 2
REGISTER: 0x33 / 33h

BIT     FUNCTION:
7       Reserved (R) Reserved.

6:4     hdlen[2:0] (R/W) Header Length.
        Length of header used if packet handler is enabled for TX/RX (enpactx/rx). 
        Headers are transmitted/received in descending order.
            000: No TX/RX header
            001: Header 3
            010: Header 3 and 2
            011: Header 3 and 2 and 1
            100: Header 3 and 2 and 1 and 0

3       fixpklen (R/W) Fix Packet Length.
        When fixpklen = 1 the packet length (pklen[7:0]) is not included in the 
        header. When fixpklen = 0 the packet length is included in the header.

2:1     synclen[1:0] (R/W) Synchronization Word Length.
        The value in this register corresponds to the number of bytes used in 
        the Synchronization Word. The synchronization word bytes are transmitted 
        in descending order.
            00: Synchronization Word 3
            01: Synchronization Word 3 and 2
            10: Synchronization Word 3 and 2 and 1
            11: Synchronization Word 3 and 2 and 1 and 0

0       prealen[8] (R/W) MSB of Preamble Length.
        See register Preamble Length.
*/
inline uint8_t SI4432::getHeaderControl2(){
        return spiRead(0x33);
}

//look at the functions above for the BIT documentation
inline void SI4432::setHeaderControl2(uint8_t data){
        spiWrite(0x33, data);
}


/*
REGISTERNAME: Preamble Length
REGISTER: 0x34 / 34h

BIT     FUNCTION:
7:0     prealen[7:0] (R/W) Preamble Length.
        The value in the prealen[8:0] register corresponds to the number of 
        nibbles (4 bits) in the packet. For example prealen[8:0] = ‘000001000’ 
        corresponds to a preamble length of 32 bits (8 x 4bits) or 4 bytes. 
        The maximum preamble length is prealen[8:0] = 111111111 which 
        corresponds to a 255 bytes Preamble. Writing 0 will hav
*/
inline uint8_t SI4432::getPreambleLength(){
        return spiRead(0x34);
}

//look at the functions above for the BIT documentation
inline void SI4432::setPreambleLength(uint8_t data){
        spiWrite(0x34, data);
}


/*
REGISTERNAME: Preamble Detection Control 1
REGISTER: 0x35 / 35h

BIT     FUNCTION:
7:3     preath[4:0] (R/W) Number of nibbles processed during detection.

2:0     Reserved (R/W) Reserved.
*/
inline uint8_t SI4432::getPreambleDetectionControl1(){
        return spiRead(0x35);
}

//look at the functions above for the BIT documentation
inline void SI4432::setPreambleDetectionControl1(uint8_t data){
        spiWrite(0x35, data);
}


/*
REGISTERNAME: Synchronization Word 3
REGISTER: 0x36 / 36h

BIT     FUNCTION:
7:0     sync[31:24] (R/W) Synchronization Word 3.
        4th byte of the synchronization word
*/
inline uint8_t SI4432::getSynchronizationWord3(){
        return spiRead(0x36);
}

//look at the functions above for the BIT documentation
inline void SI4432::setSynchronizationWord3(uint8_t data){
        spiWrite(0x36, data);
}


/*
REGISTERNAME: Synchronization Word 2
REGISTER: 0x37 / 37h

BIT     FUNCTION:
7:0     sync[23:16] (R/W) Synchronization Word 2.
        3rd byte of the synchronization word.
*/
inline uint8_t SI4432::getSynchronizationWord2(){
        return spiRead(0x37);
}

//look at the functions above for the BIT documentation
inline void SI4432::setSynchronizationWord2(uint8_t data){
        spiWrite(0x37, data);
}


/*
REGISTERNAME: Synchronization Word 1
REGISTER: 0x38 / 38h

BIT     FUNCTION:
7:0     sync[15:8] (R/W) Synchronization Word 1.
        2nd byte of the synchronization word.
*/
inline uint8_t SI4432::getSynchronizationWord1(){
        return spiRead(0x38);
}

//look at the functions above for the BIT documentation
inline void SI4432::setSynchronizationWord1(uint8_t data){
        spiWrite(0x38, data);
}


/*
REGISTERNAME: Synchronization Word 1
REGISTER: 0x39 / 39h

BIT     FUNCTION:
7:0     sync[7:0] (R/W) Synchronization Word 0.
        1st byte of the synchronization word.
*/
inline uint8_t SI4432::getSynchronizationWord0(){
        return spiRead(0x39);
}

//look at the functions above for the BIT documentation
inline void SI4432::setSynchronizationWord0(uint8_t data){
        spiWrite(0x39, data);
}