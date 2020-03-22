/*
Lib for creating and managing pocsag messages
*/

#ifndef SPIc_h
#define SPIc_h


#include "ArrayList.h"
#include "SPI.h"
#include "Arduino.h"


class SPIc{

    

    public:
        static bool spiExists(uint8_t spi_bus);
        static SPIc* getSPI(uint8_t spi_bus);
        static SPIc* setupSPI(uint8_t spi_bus, int8_t sck, int8_t miso, int8_t mosi);
        static bool closeSPI(SPIc * spi);

        void setLock(bool state);
        bool getLock();
        uint8_t getSpiBusCode();
        SPIClass* getSpiClass();
        bool isInitialized();
        bool isTransmitting();
        bool setChipSelectPin(uint8_t CSpin);
        bool selectChip(uint8_t CSpin);
        bool deselectChip(uint8_t CSpin);
        bool beginTransaction(uint32_t maxSpeed, uint8_t bitOrder, uint8_t spiMode);
        bool beginTransaction(SPISettings settings);
        bool endTransaction();
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
        SPIc(uint8_t spi_bus);
        void setup(int8_t sck, int8_t miso, int8_t mosi);
        bool initialized = false;
        //to keep track whether the spi is initialized or not
        bool transmitting = false;
        SPIClass* SPIcSPI = nullptr;
        //TODO smart pointer
        static ArrayList<SPIc*> ListOfSPIs;
        int8_t SCK = -1;
        int8_t MISO = -1;
        int8_t MOSI = -1;
        uint8_t spiBusCode = -1;

        //to lock the spi for every other instance 
        //is used by SD because it access the SpiClass and not the SPIcClass
        bool lock = false;

};


#endif