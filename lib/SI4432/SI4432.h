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
        uint8_t getDeviceTypeCode();
        uint8_t getVersionCode();
        uint8_t getDeviceStatus();
        uint8_t getInterruptStatus1();
        uint8_t getInterruptStatus2();
        uint8_t getInterruptEnable1();
        void setInterruptEnable1(uint8_t data);
        uint8_t getInterruptEnable2();
        void setInterruptEnable2(uint8_t data);
        uint8_t getOperationModeAndFunctionControl1();
        void setOperationModeAndFunctionControl1(uint8_t data);
        uint8_t getOperationModeAndFunctionControl2();
        void setOperationModeAndFunctionControl2(uint8_t data);
        uint8_t get30MHzCrystalOscillatorLoadCapacitance();
        void set30MHzCrystalOscillatorLoadCapacitance(uint8_t data);
        uint8_t getMicrocontrollerOutputClock();
        void setMicrocontrollerOutputClock(uint8_t data);
        uint8_t getGPIOConfiguration0();
        void setGPIOConfiguration0(uint8_t data);
        uint8_t getGPIOConfiguration1();
        void setGPIOConfiguration1(uint8_t data);
        uint8_t getGPIOConfiguration2();
        void setGPIOConfiguration2(uint8_t data);
        uint8_t getIOPortConfiguration();
        void setIOPortConfiguration(uint8_t data);
        uint8_t getADCConfiguration();
        void setADCConfiguration(uint8_t data);
        uint8_t getADCSensorAmplifierOffset();
        void setADCSensorAmplifierOffset(uint8_t data);
        uint8_t getADCValue();
        uint8_t getTemperatureSensorCalibration();
        void setTemperatureSensorCalibration(uint8_t data);
        uint8_t getTemperatureValueOffset();
        void setTemperatureValueOffset(uint8_t data);
        uint8_t getWakeUpTimerPeriod1();
        void setWakeUpTimerPeriod1(uint8_t data);
        uint8_t getWakeUpTimerPeriod2();
        void setWakeUpTimerPeriod2(uint8_t data);
        uint8_t getWakeUpTimerPeriod3();
        void setWakeUpTimerPeriod3(uint8_t data);

        
    private:
        //spi instance
        SPIc spi;
        //to keep track if the spi for the chip is initialized
        static bool spiInitialized;
        void spiSetup();
        void spiWrite(uint8_t address, uint8_t data);
        uint8_t spiRead(uint8_t address);
        void spiBurstWrite(uint8_t address, uint8_t * data, uint32_t size);
        uint8_t * spiBurstRead(uint8_t address, uint32_t size);
        void beginTransaction();
        void endTransaction();

};


#endif