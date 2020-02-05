#include "SPIc.h"

/*
Missing implementation (not nessasary at the moment): 
setHwCs(); setFrequency(); setClockDivider(); 
getClockDivider(); setDataMode(); setBitOrder();

Missing implementation (should be implemented and functionality documented)
transferBits();  writePixels();  writePattern();
INFO: transferBits is kind of broken (test signal before implementing (always 8 useless clk cycles))
for HAL implementation of the spi look at:
https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-spi.c
*/

/*
Mostly a warpper class, used to easily implement special functions
heavely based on:
https://github.com/espressif/arduino-esp32/blob/master/libraries/SPI/src/SPI.cpp
*/

SPIClass SPIcSPI(HSPI);

//uses hspi 
#define SPIc_SPI_CLK 14
#define SPIc_SPI_MISO 12
#define SPIc_SPI_MOSI 13

#define SPIc_SPI_SS_1 15

void SPIc::setup(){
    SPIcSPI.begin(SPIc_SPI_CLK, SPIc_SPI_MISO, SPIc_SPI_MOSI, -1);
}

void SPIc::close(){
    SPIcSPI.end();
}

void SPIc::beginTransaction(uint32_t maxSpeed, uint8_t bitOrder, uint8_t spiMode){
    SPIcSPI.beginTransaction(SPISettings(maxSpeed, bitOrder, spiMode));
}

void SPIc::beginTransaction(SPISettings settings){
    SPIcSPI.beginTransaction(settings);
}

void SPIc::endTransaction(){
    SPIcSPI.endTransaction();
}


//for writing (sending data to the slave)
void SPIc::write8(uint8_t data){
    SPIcSPI.write(data);
}

void SPIc::write16(uint16_t data){
    SPIcSPI.write16(data);
}

void SPIc::write32(uint32_t data){
    SPIcSPI.write32(data);
}

//for writing array 
//do not forget to delete the data array (mem leak)
void SPIc::writeArray8(uint8_t * data, uint32_t size){
    SPIcSPI.writeBytes(data, size);
}

//for read writing (sending data to the slave and receiving a response)
uint8_t SPIc::transfer8(uint8_t data){
    return SPIcSPI.transfer(data);
}

uint16_t SPIc::transfer16(uint16_t data){
    return SPIcSPI.transfer16(data);
}

uint32_t SPIc::transfer32(uint32_t data){
    return SPIcSPI.transfer32(data);
}

//for read and writing arrays 
//do not forget to delete the arrays (data + result) otherwise there will
//be a mem leak
uint8_t * SPIc::transferArray8(uint8_t * data, uint32_t size){
    uint8_t * result = nullptr;
    SPIcSPI.transferBytes(data, result, size);
    return result;
}
