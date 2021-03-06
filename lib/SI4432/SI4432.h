/*
Lib for controlling and managing the si4432
*/

#ifndef SI4432_h
#define SI4432_h

#include "SI4432.h"
#include "SPIc.h"
#include "Arduino.h"

class SI4432{

    
    public:
        //device managment register functions 
        //(you can use those but only if you know what your are doing)
        //those functions will write directly to the register without checking
        inline uint8_t getDeviceTypeCode();
        inline uint8_t getVersionCode();
        inline uint8_t getDeviceStatus();
        inline uint8_t getInterruptStatus1();
        inline uint8_t getInterruptStatus2();
        inline uint8_t getInterruptEnable1();
        inline void setInterruptEnable1(uint8_t data);
        inline uint8_t getInterruptEnable2();
        inline void setInterruptEnable2(uint8_t data);
        inline uint8_t getOperationModeAndFunctionControl1();
        inline void setOperationModeAndFunctionControl1(uint8_t data);
        inline uint8_t getOperationModeAndFunctionControl2();
        inline void setOperationModeAndFunctionControl2(uint8_t data);
        inline uint8_t get30MHzCrystalOscillatorLoadCapacitance();
        inline void set30MHzCrystalOscillatorLoadCapacitance(uint8_t data);
        inline uint8_t getMicrocontrollerOutputClock();
        inline void setMicrocontrollerOutputClock(uint8_t data);
        inline uint8_t getGPIOConfiguration0();
        inline void setGPIOConfiguration0(uint8_t data);
        inline uint8_t getGPIOConfiguration1();
        inline void setGPIOConfiguration1(uint8_t data);
        inline uint8_t getGPIOConfiguration2();
        inline void setGPIOConfiguration2(uint8_t data);
        inline uint8_t getIOPortConfiguration();
        inline void setIOPortConfiguration(uint8_t data);
        inline uint8_t getADCConfiguration();
        inline void setADCConfiguration(uint8_t data);
        inline uint8_t getADCSensorAmplifierOffset();
        inline void setADCSensorAmplifierOffset(uint8_t data);
        inline uint8_t getADCValue();
        inline uint8_t getTemperatureSensorCalibration();
        inline void setTemperatureSensorCalibration(uint8_t data);
        inline uint8_t getTemperatureValueOffset();
        inline void setTemperatureValueOffset(uint8_t data);
        inline uint8_t getWakeUpTimerPeriod1();
        inline void setWakeUpTimerPeriod1(uint8_t data);
        inline uint8_t getWakeUpTimerPeriod2();
        inline void setWakeUpTimerPeriod2(uint8_t data);
        inline uint8_t getWakeUpTimerPeriod3();
        inline void setWakeUpTimerPeriod3(uint8_t data);
        inline uint8_t getWakeUpTimerValue1();
        inline uint8_t getWakeUpTimerValue2();
        inline uint8_t getLowDutyCycleModeDuration();
        inline void setLowDutyCycleModeDuration(uint8_t data);
        inline uint8_t getLowBatteryDetectorThreshold();
        inline void setLowBatteryDetectorThreshold(uint8_t data);
        inline uint8_t getBatteryVoltageLevel();
        inline uint8_t getAnalogTestBusSelect();
        inline void setAnalogTestBusSelect(uint8_t data);

        inline uint8_t getIFFilterBandwidth();
        inline void setIFFilterBandwidth(uint8_t data);
        inline uint8_t getAFCLoopGearshiftOverride();
        inline void setAFCLoopGearshiftOverride(uint8_t data);
        inline uint8_t getAFCTimingControl();
        inline void setAFCTimingControl(uint8_t data);
        inline uint8_t getClockRecoveryGearshiftOverride();
        inline void setClockRecoveryGearshiftOverride(uint8_t data);
        inline uint8_t getClockRecoveryOversamplingRate();
        inline void setClockRecoveryOversamplingRate(uint8_t data);
        inline uint8_t getClockRecoveryOffset2();
        inline void setClockRecoveryOffset2(uint8_t data);
        inline uint8_t getClockRecoveryOffset1();
        inline void setClockRecoveryOffset1(uint8_t data);
        inline uint8_t getClockRecoveryOffset0();
        inline void setClockRecoveryOffset0(uint8_t data);
        inline uint8_t getClockRecoveryTimingLoopGain1();
        inline void setClockRecoveryTimingLoopGain1(uint8_t data);
        inline uint8_t getClockRecoveryTimingLoopGain0();
        inline void setClockRecoveryTimingLoopGain0(uint8_t data);
        inline uint8_t getReceivedSignalStrengthIndicator();
        inline uint8_t getRSSIThresholdforClearChannelIndicator();
        inline void setRSSIThresholdforClearChannelIndicator(uint8_t data);
        inline uint8_t getAntennaDiversity1();
        inline uint8_t getAntennaDiversity2();

        inline uint8_t getDataAccessControl();
        inline void setDataAccessControl(uint8_t data);
        inline uint8_t getEZMACStatus();
        inline uint8_t getHeaderControl1();
        inline void setHeaderControl1(uint8_t data);
        inline uint8_t getHeaderControl2();
        inline void setHeaderControl2(uint8_t data);
        inline uint8_t getPreambleLength();
        inline void setPreambleLength(uint8_t data);
        inline uint8_t getPreambleDetectionControl1();
        inline void setPreambleDetectionControl1(uint8_t data);
        inline uint8_t getSynchronizationWord3();
        inline void setSynchronizationWord3(uint8_t data);
        inline uint8_t getSynchronizationWord2();
        inline void setSynchronizationWord2(uint8_t data);
        inline uint8_t getSynchronizationWord1();
        inline void setSynchronizationWord1(uint8_t data);
        inline uint8_t getSynchronizationWord0();
        inline void setSynchronizationWord0(uint8_t data);
        inline uint8_t getTransmitHeader3();
        inline void setTransmitHeader3(uint8_t data);
        inline uint8_t getTransmitHeader2();
        inline void setTransmitHeader2(uint8_t data);
        inline uint8_t getTransmitHeader1();
        inline void setTransmitHeader1(uint8_t data);
        inline uint8_t getTransmitHeader0();
        inline void setTransmitHeader0(uint8_t data);
        inline uint8_t getPacketLength();
        inline void setPacketLength(uint8_t data);
        inline uint8_t getCheckHeader3();
        inline void setCheckHeader3(uint8_t data);
        inline uint8_t getCheckHeader2();
        inline void setCheckHeader2(uint8_t data);
        inline uint8_t getCheckHeader1();
        inline void setCheckHeader1(uint8_t data);
        inline uint8_t getCheckHeader0();
        inline void setCheckHeader0(uint8_t data);
        inline uint8_t getHeaderEnable3();
        inline void setHeaderEnable3(uint8_t data);
        inline uint8_t getHeaderEnable2();
        inline void setHeaderEnable2(uint8_t data);
        inline uint8_t getHeaderEnable1();
        inline void setHeaderEnable1(uint8_t data);
        inline uint8_t getHeaderEnable0();
        inline void setHeaderEnable0(uint8_t data);
        inline uint8_t getReceivedHeader3();
        inline uint8_t getReceivedHeader2();
        inline uint8_t getReceivedHeader1();
        inline uint8_t getReceivedHeader0();
        inline uint8_t getReceivedPacketLength();
        
    private:
        SPIc* spi;
        //to keep track if the spi for the chip is initialized
        bool spiSetup(uint8_t spi_bus, uint8_t cspin);
        bool spiSetup(uint8_t spi_bus, int8_t sck, int8_t miso, int8_t mosi, uint8_t cspin);
        uint8_t CSpin = 15; //just an example pin will be changed during setup
        void spiWrite(uint8_t address, uint8_t data);
        uint8_t spiRead(uint8_t address);
        void spiBurstWrite(uint8_t address, uint8_t * data, uint32_t size);
        uint8_t * spiBurstRead(uint8_t address, uint32_t size);
        bool beginTransaction();
        bool endTransaction();

};


#endif