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
        void spiWrite(uint8_t address, uint8_t data);
        uint8_t spiRead(uint8_t address);
    private:
        //spi instance
        SPIc spi;
        //to keep track if the spi for the chip is initialized
        static bool spiInitialized;
        void spiSetup();
        void beginTransaction();
        void endTransaction();
        

};


#endif