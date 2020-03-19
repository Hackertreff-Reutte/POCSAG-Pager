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