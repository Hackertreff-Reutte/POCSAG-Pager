#include "SI4432.h"

/*
REGISTERNAME: Device Type Code (DT)
REGISTER: 0x00 / 00h

data is not constistent through the datasheets so it is not possible
to say whats in this register
register address: 0x00
*/
uint8_t SI4432::getDeviceTypeCode(){
    return spiRead(0x00);
}


/*
REGISTERNAME: Version Code (VC)
REGISTER: 0x01 / 01h

returns the version code of the chip (bits 4:0) 
(7:5 are reservered and not used)
Rev X4 = 01      Rev V2: 02     Rev A0:  03
*/
uint8_t SI4432::getVersionCode(){
    return spiRead(0x01);
}


/*
REGISTERNAME: Device Status
REGISTER: 0x02 / 02h

returns the satus of the device (errors and so on)

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
REGISTERNAME: Interrupt/Status 1
REGISTER: 0x03 / 03h

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
REGISTERNAME: Interrupt/Status 2
REGISTER: 0x04 / 04h

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
REGISTERNAME: Interrupt Enable 1
REGISTER: 0x05 / 05h

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
REGISTERNAME: Interrupt Enable 2
REGISTER: 0x06 / 06h

BIT     FUNCTION:
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


/*
REGISTERNAME: Operating Mode and Function Control 1
REGISTER: 0x07 / 07h

BIT     FUNCTION:
7       swres (R/W) Software Register Reset Bit.
        This bit may be used to reset all registers simultaneously to a 
        DEFAULT state, without the need for sequentially writing to each 
        individual register. The RESET is accomplished by setting swres = 1. 
        This bit will be automatically cleared.

6       enlbd (R/W) Enable Low Battery Detect.
        When this bit is set to 1 the Low Battery Detector circuit and threshold 
        comparison will be enabled.

5       enwt (R/W) Enable Wake-Up-Timer.
        Enabled when enwt = 1. If the Wake-up-Timer function is enabled it will 
        operate in any mode and notify the microcontroller through the GPIO 
        interrupt when the timer expires.

4       x32ksel (R/W) 32,768 kHz Crystal Oscillator Select.
                0: RC oscillator
                1: 32 kHz crystal

3       txon (R/W) TX on in Manual Transmit Mode.
        Automatically cleared in FIFO mode once the packet is sent. 
        Transmission can be aborted during packet transmission, however, when 
        no data has been sent yet, transmission can only be aborted after the 
        device is programmed to “unmodulated carrier” 
        ("Register 71h. Modulation Mode Control 2").

2       rxon (R/W) RX on in Manual Receiver Mode.
        Automatically cleared if Multiple Packets config. is disabled and a 
        valid packet received.

1       pllon (R/W) TUNE Mode (PLL is ON).
        When pllon = 1 the PLL will remain enabled in Idle State. This will for 
        faster turn-around time at the cost of increased current consumption in 
        Idle State.

0       xton (R/W) READY Mode (Xtal is ON).
*/
uint8_t SI4432::getOperationModeAndFunctionControl1(){
        return spiRead(0x07);
}

//look at the functions above for the BIT documentation
void SI4432::setOperationModeAndFunctionControl1(uint8_t data){
        spiWrite(0x07, data);
}


/*
REGISTERNAME: Operating Mode and Function Control 2
REGISTER: 0x08 / 08h

BIT     FUNCTION:
7:5     antdiv[2:0] (R/W) Enable Antenna Diversity.
        The GPIO must be configured for Antenna Diversity for the algorithm to 
        work properly. 
                RX/TX state     non RX/TX state
                GPIO Ant1       GPIO Ant2       GPIO Ant1       GPIO Ant2
        000:    0               1               0               0
        001:    1               0               0               0
        010:    0               1               1               1
        011:    1               0               1               1
        100:    antenna diversity algorithm     0               0
        101:    antenna diversity algorithm     1               1
        110:    ant. div. algorithm 
                in beacon mode                  0               0
        111:    ant. div. algorithm 
                in beacon mode                  1               1

4       rxmpk (R/W) RX Multi Packet.
        When the chip is selected to use FIFO Mode (dtmod[1:0]) and RX Packet 
        Handling (enpacrx) then it will fill up the FIFO with multiple valid 
        packets if this bit is set, otherwise the transceiver will automatically
        leave the RX State after the first valid packet has been received.

3       autotx (R/W) Automatic Transmission.
        When autotx = 1 the transceiver will enter automatically TX State when 
        the FIFO is almost full. When the FIFO is empty it will automatically 
        return to the Idle State.

2       enldm (R/W) Enable Low Duty Cycle Mode.
        If this bit is set to 1 then the chip turns on the RX regularly. 
        The frequency should be set in the Wake-Up Timer Period register, 
        while the minimum ON time should be set in the Low-Duty Cycle Mode 
        Duration register. The FIFO mode should be enabled also.

1       ffclrrx (R/W) RX FIFO Reset/Clear.
        This has to be a two writes operation: Setting ffclrrx =1 followed by 
        ffclrrx = 0 will clear the contents of the RX FIFO.

0       ffclrtx (R/W) TX FIFO Reset/Clear.
        This has to be a two writes operation: Setting ffclrtx =1 followed by 
        ffclrtx = 0 will clear the contents of the TX FIFO.
*/
uint8_t SI4432::getOperationModeAndFunctionControl2(){
        return spiRead(0x08);
}

//look at the functions above for the BIT documentation
void SI4432::setOperationModeAndFunctionControl2(uint8_t data){
        spiWrite(0x08, data);
}


/*
REGISTERNAME: 30 MHz Crystal Oscillator Load Capacitance
REGISTER: 0x09 / 09h

for more info look at the point "5.8. Crystal Oscillator"

BIT     FUNCTION:
7       xtalshft (R/W) Direct Control to Analog.
6:0     xlc[6:0] (R/W) Tuning Capacitance for the 30 MHz XTAL
*/
uint8_t SI4432::get30MHzCrystalOscillatorLoadCapacitance(){
        return spiRead(0x09);
}

//look at the functions above for the BIT documentation
void SI4432::set30MHzCrystalOscillatorLoadCapacitance(uint8_t data){
        spiWrite(0x09, data);
}


/*
REGISTERNAME: Microcontroller Output Clock
REGISTER: 0x0A / 0Ah

BIT     FUNCTION:
7:6     Reserved (R) Reserved.

5:4     clkt[1:0] (R/W) Clock Tail.
        If enlfc = 0 then it can be useful to provide a few extra cycles for 
        the microcontroller to complete its operation. Setting the clkt[1:0] 
        register will provide the addition cycles of the clock before it shuts 
        off.
                00:       0 cycle
                01:     128 cycles
                10:     256 cycles
                11:     512 cycles

3       enlfc (R/W) Enable Low Frequency Clock.
        When enlfc = 1 and the chip is in Sleep mode then the 32.768 kHz clock 
        will be provided to the microcontroller no matter what the selection of 
        mclk[2:0] is. For example if mclk[2:0] = ‘000’, 30 MHz will be available
        through the GPIO to output to the microcontroller in all Idle, TX, or RX 
        states. When the chip is commanded to Sleep mode the 30 MHz clock will 
        become 32.768 kHz.

2:0     mclk[2:0] (R/W) Microcontroller Clock.
        Different clock frequencies may be selected for configurable GPIO clock 
        output. All clock frequencies are created by dividing the XTAL except 
        for the 32 kHz clock which comes directly from the 32 kHz RC Oscillator.
        The mclk[2:0] setting is only valid when xton = 1 except the 111.
                000:    30 MHz
                001:    15 MHz
                010:    10 MHz
                011:     4 MHz
                100:     3 MHz
                101:     2 MHz
                110:     1 MHz
                111:    32.768 kHz
*/
uint8_t SI4432::getMicrocontrollerOutputClock(){
        return spiRead(0x0A);
}

//look at the functions above for the BIT documentation
void SI4432::setMicrocontrollerOutputClock(uint8_t data){
        spiWrite(0x0A, data);
}

/*
REGISTERNAME: GPIO Configuration 0
REGISTER: 0x0B / 0Bh

BIT     FUNCTION:
7:6     gpiodrv0[1:0] (R/W) GPIO Driving Capability Setting.

5       pup0 (R/W) Pullup Resistor Enable on GPIO0.
        When set to 1 the a 200 kohm resistor is connected internally between VDD 
        and the pin if the GPIO is configured as a digital input.

4:0     gpio0[4:0] (R/W) GPIO0 pin Function Select.
                00000: Power-On-Reset (output)
                00001: Wake-Up Timer: 1 when WUT has expired (output)
                00010: Low Battery Detect: 1 when battery is below threshold setting (output)
                00011: Direct Digital Input
                00100: External Interrupt, falling edge (input)
                00101: External Interrupt, rising edge (input)
                00110: External Interrupt, state change (input)
                00111: ADC Analog Input
                01000: Reserved (Analog Test N Input)
                01001: Reserved (Analog Test P Input)
                01010: Direct Digital Output
                01011: Reserved (Digital Test Output)
                01100: Reserved (Analog Test N Output)
                01101: Reserved (Analog Test P Output)
                01110: Reference Voltage (output)
                01111: TX/RX Data CLK output to be used in conjunction with TX/RX Data pin (output)
                10000: TX Data input for direct modulation (input)
                10001: External Retransmission Request (input)
                10010: TX State (output)
                10011: TX FIFO Almost Full (output)
                10100: RX Data (output)
                10101: RX State (output)
                10110: RX FIFO Almost Full (output)
                10111: Antenna 1 Switch used for antenna diversity (output)
                11000: Antenna 2 Switch used for antenna diversity (output)
                11001: Valid Preamble Detected (output)
                11010: Invalid Preamble Detected (output)
                11011: Sync Word Detected (output)
                11100: Clear Channel Assessment (output)
                11101: VDD
                else : GND
*/
uint8_t SI4432::getGPIOConfiguration0(){
        return spiRead(0x0B);
}

//look at the functions above for the BIT documentation
void SI4432::setGPIOConfiguration0(uint8_t data){
        spiWrite(0x0B, data);
}


/*
REGISTERNAME: GPIO Configuration 1
REGISTER: 0x0C / 0Ch

BIT     FUNCTION:
7:6     gpiodrv1[1:0] (R/W) GPIO Driving Capability Setting.

5       pup1 (R/W) Pullup Resistor Enable on GPIO1.
        When set to 1 the a 200 kohm resistor is connected internally between VDD 
        and the pin if the GPIO is configured as a digital input.

4:0     gpio1[4:0] (R/W) GPIO1 pin Function Select.
                00000: Power-On-Reset (output)
                00001: Wake-Up Timer: 1 when WUT has expired (output)
                00010: Low Battery Detect: 1 when battery is below threshold setting (output)
                00011: Direct Digital Input
                00100: External Interrupt, falling edge (input)
                00101: External Interrupt, rising edge (input)
                00110: External Interrupt, state change (input)
                00111: ADC Analog Input
                01000: Reserved (Analog Test N Input)
                01001: Reserved (Analog Test P Input)
                01010: Direct Digital Output
                01011: Reserved (Digital Test Output)
                01100: Reserved (Analog Test N Output)
                01101: Reserved (Analog Test P Output)
                01110: Reference Voltage (output)
                01111: TX/RX Data CLK output to be used in conjunction with TX/RX Data pin (output)
                10000: TX Data input for direct modulation (input)
                10001: External Retransmission Request (input)
                10010: TX State (output)
                10011: TX FIFO Almost Full (output)
                10100: RX Data (output)
                10101: RX State (output)
                10110: RX FIFO Almost Full (output)
                10111: Antenna 1 Switch used for antenna diversity (output)
                11000: Antenna 2 Switch used for antenna diversity (output)
                11001: Valid Preamble Detected (output)
                11010: Invalid Preamble Detected (output)
                11011: Sync Word Detected (output)
                11100: Clear Channel Assessment (output)
                11101: VDD
                else : GND
*/
uint8_t SI4432::getGPIOConfiguration1(){
        return spiRead(0x0C);
}

//look at the functions above for the BIT documentation
void SI4432::setGPIOConfiguration1(uint8_t data){
        spiWrite(0x0C, data);
}


/*
REGISTERNAME: GPIO Configuration 2
REGISTER: 0x0D / 0Dh

BIT     FUNCTION:
7:6     gpiodrv2[1:0] (R/W) GPIO Driving Capability Setting.

5       pup2 (R/W) Pullup Resistor Enable on GPIO2.
        When set to 1 the a 200 kohm resistor is connected internally between VDD 
        and the pin if the GPIO is configured as a digital input.

4:0     gpio2[4:0] (R/W) GPIO2 pin Function Select.
                00000: Power-On-Reset (output)
                00001: Wake-Up Timer: 1 when WUT has expired (output)
                00010: Low Battery Detect: 1 when battery is below threshold setting (output)
                00011: Direct Digital Input
                00100: External Interrupt, falling edge (input)
                00101: External Interrupt, rising edge (input)
                00110: External Interrupt, state change (input)
                00111: ADC Analog Input
                01000: Reserved (Analog Test N Input)
                01001: Reserved (Analog Test P Input)
                01010: Direct Digital Output
                01011: Reserved (Digital Test Output)
                01100: Reserved (Analog Test N Output)
                01101: Reserved (Analog Test P Output)
                01110: Reference Voltage (output)
                01111: TX/RX Data CLK output to be used in conjunction with TX/RX Data pin (output)
                10000: TX Data input for direct modulation (input)
                10001: External Retransmission Request (input)
                10010: TX State (output)
                10011: TX FIFO Almost Full (output)
                10100: RX Data (output)
                10101: RX State (output)
                10110: RX FIFO Almost Full (output)
                10111: Antenna 1 Switch used for antenna diversity (output)
                11000: Antenna 2 Switch used for antenna diversity (output)
                11001: Valid Preamble Detected (output)
                11010: Invalid Preamble Detected (output)
                11011: Sync Word Detected (output)
                11100: Clear Channel Assessment (output)
                11101: VDD
                else : GND
*/
uint8_t SI4432::getGPIOConfiguration2(){
        return spiRead(0x0D);
}

//look at the functions above for the BIT documentation
void SI4432::setGPIOConfiguration2(uint8_t data){
        spiWrite(0x0D, data);
}


/*
REGISTERNAME: I/O Port Configuration
REGISTER: 0x0E / 0Eh

BIT     FUNCTION:
7       Reserved (R) Reserved.

6       extitst[2] (R) External Interrupt Status.
        If the GPIO2 is programmed to be external interrupt sources then the 
        status can be read here.

5       extitst[1] (R) External Interrupt Status.
        If the GPIO1 is programmed to be external interrupt sources then the 
        status can be read here.

4       extitst[0] (R) External Interrupt Status.
        If the GPIO0 is programmed to be external interrupt sources then the 
        status can be read here.

3       itsdo (R/W) Interrupt Request Output on the SDO Pin.
        nIRQ output is present on the SDO pin if this bit is set and the nSEL 
        input is inactive (high).

2       dio2 (R/W) Direct I/O for GPIO2.
        If the GPIO2 is configured to be a direct output then the value on the 
        GPIO pin can be set here. If the GPIO2 is configured to be a direct 
        input then the value of the pin can be read here.

1       dio1 (R/W) Direct I/O for GPIO1.
        If the GPIO1 is configured to be a direct output then the value on the 
        GPIO pin can be set here. If the GPIO1 is configured to be a direct 
        input then the value of the pin can be read here.

0       dio0 (R/W) Direct I/O for GPIO0.
        If the GPIO0 is configured to be a direct output then the value on the 
        GPIO pin can be set here. If the GPIO0 is configured to be a direct 
        input then the value of the pin can be read here.
*/
uint8_t SI4432::getIOPortConfiguration(){
        return spiRead(0x0E);
}

//look at the functions above for the BIT documentation
void SI4432::setIOPortConfiguration(uint8_t data){
        spiWrite(0x0E, data);
}


/*
REGISTERNAME: ADC Configuration
REGISTER: 0x0F / 0Fh

BIT     FUNCTION:
7       adcstart/adcdone (R/W) ADC Measurement Start Bit.
        Reading this bit gives 1 if the ADC measurement cycle has been finished.

6:4     adcsel[2:0] (R/W) ADC Input Source Selection.
        The internal 8-bit ADC input source can be selected as follows:
                000: Internal Temperature Sensor
                001: GPIO0, single-ended
                010: GPIO1, single-ended
                011: GPIO2, single-ended
                100: GPIO0(+) – GPIO1(–), differential
                101: GPIO1(+) – GPIO2(–), differential
                110: GPIO0(+) – GPIO2(–), differential
                111: GND

3:2     adcref[1:0] (R/W) ADC Reference Voltage Selection.
        The reference voltage of the internal 8-bit ADC can be selected as follows:
                0X: bandgap voltage (1.2 V)
                10: VDD / 3
                11: VDD / 2

1:0     adcgain[1:0] (R/W) ADC Sensor Amplifier Gain Selection.
        The full scale range of the internal 8-bit ADC in differential mode 
        (see adcsel) can be set as follows:
                adcref[0] = 0: adcref[0] = 1:
                FS = 0.014 x (adcgain[1:0] + 1) x VDD FS = 0.021 x (adcgain[1:0] + 1) x VDD
*/
uint8_t SI4432::getADCConfiguration(){
        return spiRead(0x0F);
}

//look at the functions above for the BIT documentation
void SI4432::setADCConfiguration(uint8_t data){
        spiWrite(0x0F, data);
}


/*
REGISTERNAME: ADC Sensor Amplifier Offset
REGISTER: 0x10 / 10h

BIT     FUNCTION:
7:4     Reserved (R) Reserved.

3:0     adcoffs[3:0] (R/W) ADC Sensor Amplifier Offset.
        The offset can be calculated as Offset = adcoffs[2:0] x VDD / 1000; 
        MSB = adcoffs[3] = Sign bit.
*/
uint8_t SI4432::getADCSensorAmplifierOffset(){
        return spiRead(0x10);
}

//look at the functions above for the BIT documentation
void SI4432::setADCSensorAmplifierOffset(uint8_t data){
        spiWrite(0x10, data);
}


/*
REGISTERNAME: ADC Value
REGISTER: 0x11 / 11h

BIT     FUNCTION:
7:0     adc[7:0] (R) Internal 8 bit ADC Output Value.
*/
uint8_t SI4432::getADCValue(){
        return spiRead(0x11);
}


/*
REGISTERNAME: Temperature Sensor Calibration
REGISTER: 0x12 / 12h

BIT     FUNCTION:
7:6     tsrange[1:0] (R/W) Temperature Sensor Range Selection.
        (FS range is 0..1024 mV)
                00:     –40 °C .. 64 °C (full operating range), with 0.5 °C 
                        resolution (1 LSB in the 8-bit ADC)
                01:     –40 °C .. 85 °C, with 1 °C resolution 
                        (1 LSB in the 8-bit ADC)
                11:     0 °C .. 85 °C, with 0.5 °C resolution 
                        (1 LSB in the 8-bit ADC)
                10:     –40 °F .. 216 °F, with 1 °F resolution 
                        (1 LSB in the 8-bit ADC)

5       entsoffs (R/W) Temperature Sensor Offset to Convert from K to °C.

4       entstrim (R/W) Temperature Sensor Trim Enable.

3:0     tstrim[3:0] (R/W) Temperature Sensor Trim Value.
*/
uint8_t SI4432::getTemperatureSensorCalibration(){
        return spiRead(0x12);
}

//look at the functions above for the BIT documentation
void SI4432::setTemperatureSensorCalibration(uint8_t data){
        spiWrite(0x12, data);
}


/*
REGISTERNAME: Temperature Value Offset
REGISTER: 0x13 / 13h

BIT     FUNCTION:
7:0     tvoffs[7:0] (R/W) Temperature Value Offset.
        This value is added to the measured temperature value. 
        (MSB, tvoffs[8]: sign bit)
*/
uint8_t SI4432::getTemperatureValueOffset(){
        return spiRead(0x13);
}

//look at the functions above for the BIT documentation
void SI4432::setTemperatureValueOffset(uint8_t data){
        spiWrite(0x13, data);
}


/*
REGISTERNAME: Wake-Up Timer Period 1
REGISTER: 0x14 / 14h

BIT     FUNCTION:
7:6     Reserved (R/W) Reserved.

5:2     wtr[3:0] (R/W) Wake Up Timer Exponent (R) Value*.

1:0     wtd[3:0] (R/W) Wake Up Timer Exponent (D) Value*.

*Note: The period of the wake-up timer can be calculated as 
TWUT = (32 x M x 2R-D) / 32.768 ms.
*/
uint8_t SI4432::getWakeUpTimerPeriod1(){
        return spiRead(0x14);
}

//look at the functions above for the BIT documentation
void SI4432::setWakeUpTimerPeriod1(uint8_t data){
        spiWrite(0x14, data);
}