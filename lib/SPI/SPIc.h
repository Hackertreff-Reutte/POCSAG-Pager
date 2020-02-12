/*
Lib for creating and managing pocsag messages
*/

#ifndef SPIc_h
#define SPIc_h

#include "SPI.h"
#include "Arduino.h"

class SPIc{

    

    public:
       static bool transmitting;
       void setup(uint8_t CSpin);
       bool isInitialized();
       void close();
       void selectChip(uint8_t CSpin);
       void deselectChip(uint8_t CSpin);
       void beginTransaction(uint32_t maxSpeed, uint8_t bitOrder, uint8_t spiMode);
       void beginTransaction(SPISettings settings);
       void endTransaction();
       //write
       void write8(uint8_t data);
       void write16(uint16_t data);
       void write32(uint32_t data);
       void writeArray8(uint8_t * data, uint32_t size);
       //transfer (write read)
       uint8_t transfer8(uint8_t data);
       uint16_t transfer16(uint16_t data);
       uint32_t transfer32(uint32_t data);
       uint8_t * transferArray8(uint8_t * data, uint32_t size);
       //read functions
       uint8_t read8();
       uint16_t read16();
       uint32_t read32();
       uint8_t * readArray8(uint32_t size);

    private:
        //to keep track whether the spi is initialized of not
        static bool initialized;
        
};


#endif