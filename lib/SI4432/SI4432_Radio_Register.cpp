#include "SI4432.h"

/*
REGISTERNAME: IF Filter Bandwidth
REGISTER: 0x1C / 1Ch

BIT     FUNCTION:
7       dwn3_bypass (R/W) Bypass Decimator by 3 (if set).

6:4     ndec_exp[2:0] (R/W) IF Filter Decimation Rates.

3:0     filset[3:0] (R/W) IF Filter Coefficient Sets.
        Defaults are for Rb = 40 kbps and Fd = 20 kHz so Bw = 80 kHz.
*/
inline uint8_t SI4432::getIFFilterBandwidth(){
        return spiRead(0x1C);
}

//look at the functions above for the BIT documentation
inline void SI4432::setIFFilterBandwidth(uint8_t data){
        spiWrite(0x1C, data);
}


/*
REGISTERNAME: AFC Loop Gearshift Override
REGISTER: 0x1D / 1Dh

BIT     FUNCTION:
7       afcbd (R/W) If set, the tolerated AFC frequency error will be halved.

6       enafc (R/W) AFC Enable.

5:3     afcgearh[2:0] (R/W) AFC High Gear Setting.

2:0     afcgearl[2:0] (R/W) AFC Low Gear Setting
*/
inline uint8_t SI4432::getAFCLoopGearshiftOverride(){
        return spiRead(0x1D);
}

//look at the functions above for the BIT documentation
inline void SI4432::setAFCLoopGearshiftOverride(uint8_t data){
        spiWrite(0x1D, data);
}


/*
REGISTERNAME: AFC Timing Control
REGISTER: 0x1E / 1Eh

BIT     FUNCTION:
7:6     Reserved (R) Reserved.

5:3     shwait[2:0] (R/W) Short Wait Periods after AFC Correction.
        Used before preamble is detected. Short wait = (RegValue + 1) x 2Tb. 
        If set to 0 then no AFC correction will occur before preamble detect, 
        i.e. AFC will be disabled.

2:0     lgwait[2:0] (R/W) Long Wait Periods after Correction.
        Used after preamble detected. Long wait = (RegValue + 1) x 2Tb. If set 
        to 0 then no AFC correction will occur after the preamble detect.
*/
inline uint8_t SI4432::getAFCTimingControl(){
        return spiRead(0x1E);
}

//look at the functions above for the BIT documentation
inline void SI4432::setAFCTimingControl(uint8_t data){
        spiWrite(0x1E, data);
}


/*
REGISTERNAME: Clock Recovery Gearshift Override
REGISTER: 0x1F / 1Fh

BIT     FUNCTION:
7       Reserved (R/W) Reserved.

6       rxready (R/W) Improves Receiver Noise Immunity when in Direct Mode.
        It is recommended to set this bit after preamble is detected. 
        When in FIFO mode this bit should be set to “0” since noise immunity is 
        controlled automatically.

5:3     crfast[2:0] (R/W) Clock Recovery Fast Gearshift Value.

2:0     crslow[2:0] (R/W) Clock Recovery Slow Gearshift Value.
*/
inline uint8_t SI4432::getClockRecoveryGearshiftOverride(){
        return spiRead(0x1F);
}

//look at the functions above for the BIT documentation
inline void SI4432::setClockRecoveryGearshiftOverride(uint8_t data){
        spiWrite(0x1F, data);
}


/*
REGISTERNAME: Clock Recovery Oversampling Rate
REGISTER: 0x20 / 20h

BIT     FUNCTION:
7:0     rxosr[7:0] (R/W) Oversampling Rate.
        3 LSBs are the fraction, default = 0110 0100 = 12.5 clock cycles per 
        data bit

note    look in the datasheet for the formular 
*/
inline uint8_t SI4432::getClockRecoveryOversamplingRate(){
        return spiRead(0x20);
}

//look at the functions above for the BIT documentation
inline void SI4432::setClockRecoveryOversamplingRate(uint8_t data){
        spiWrite(0x20, data);
}


/*
REGISTERNAME: Clock Recovery Offset 2
REGISTER: 0x21 / 21h

BIT     FUNCTION:
7:5     rxosr[10:8] (R/W) Oversampling Rate.
        Upper bits.

4       stallctrl (R/W) Used for BCR Purposes.

3:0     ncoff[19:16] (R/W) NCO Offset.

note    look in the datasheet for the formular 
*/
inline uint8_t SI4432::getClockRecoveryOffset2(){
        return spiRead(0x21);
}

//look at the functions above for the BIT documentation
inline void SI4432::setClockRecoveryOffset2(uint8_t data){
        spiWrite(0x21, data);
}


/*
REGISTERNAME: Clock Recovery Offset 1
REGISTER: 0x22 / 22h

BIT     FUNCTION:
7:0     ncoff[15:8] (R/W) NCO Offset.

note    look in the datasheet for the formular 
*/
inline uint8_t SI4432::getClockRecoveryOffset1(){
        return spiRead(0x22);
}

//look at the functions above for the BIT documentation
inline void SI4432::setClockRecoveryOffset1(uint8_t data){
        spiWrite(0x22, data);
}


/*
REGISTERNAME: Clock Recovery Offset 0
REGISTER: 0x23 / 23h

BIT     FUNCTION:
7:0     ncoff[7:0] (R/W) NCO Offset. 

note    look in the datasheet for the formular 
*/
inline uint8_t SI4432::getClockRecoveryOffset0(){
        return spiRead(0x23);
}

//look at the functions above for the BIT documentation
inline void SI4432::setClockRecoveryOffset0(uint8_t data){
        spiWrite(0x23, data);
}


/*
REGISTERNAME: Clock Recovery Timing Loop Gain 1
REGISTER: 0x24 / 24h

BIT     FUNCTION:
7:3     Reserved (R/W) Reserved.

2:0     crgain[10:8] (R/W) Clock Recovery Timing Loop Gain.
*/
inline uint8_t SI4432::getClockRecoveryTimingLoopGain1(){
        return spiRead(0x24);
}

//look at the functions above for the BIT documentation
inline void SI4432::setClockRecoveryTimingLoopGain1(uint8_t data){
        spiWrite(0x24, data);
}


/*
REGISTERNAME: Clock Recovery Timing Loop Gain 0
REGISTER: 0x25 / 25h

BIT     FUNCTION:
7:0     crgain[7:0] (R/W) Clock Recovery Timing Loop Gain.
*/
inline uint8_t SI4432::getClockRecoveryTimingLoopGain0(){
        return spiRead(0x25);
}

//look at the functions above for the BIT documentation
inline void SI4432::setClockRecoveryTimingLoopGain0(uint8_t data){
        spiWrite(0x25, data);
}


/*
REGISTERNAME: Received Signal Strength Indicator
REGISTER: 0x26 / 26h

BIT     FUNCTION:
7:0     rssi[7:0] (R) Received Signal Strength Indicator Value.
*/
inline uint8_t SI4432::getReceivedSignalStrengthIndicator(){
        return spiRead(0x26);
}


/*
REGISTERNAME: RSSI Threshold for Clear Channel Indicator
REGISTER: 0x27 / 27h

BIT     FUNCTION:
7:0     rssith[7:0] (R/W) RSSI Threshold.
        Interrupt is set if the RSSI value is above this threshold
*/
inline uint8_t SI4432::getRSSIThresholdforClearChannelIndicator(){
        return spiRead(0x27);
}

//look at the functions above for the BIT documentation
inline void SI4432::setRSSIThresholdforClearChannelIndicator(uint8_t data){
        spiWrite(0x27, data);
}


/*
REGISTERNAME: Antenna Diversity 1
REGISTER: 0x28 / 28h

BIT     FUNCTION:
7:0     adrssi[7:0] (R) Measured RSSI Value on Antenna 1.
*/
inline uint8_t SI4432::getAntennaDiversity1(){
        return spiRead(0x28);
}


/*
REGISTERNAME: Antenna Diversity 2
REGISTER: 0x29 / 29h

BIT     FUNCTION:
7:0     adrssi2[7:0] (R) Measured RSSI Value on Antenna 2
*/
inline uint8_t SI4432::getAntennaDiversity2(){
        return spiRead(0x29);
}