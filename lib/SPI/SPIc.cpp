#include "SPIc.h"

/*
Missing implementation (not nessasary at the moment): 
setHwCs(); setFrequency(); setClockDivider(); 
getClockDivider(); setDataMode(); setBitOrder();

Missing implementation (should be implemented and functionality documented)
transferBits();  writePixels();  writePattern();
INFO: transferBits is kind of broken (test signal before implementing 
(always 8 useless clk cycles))
Github ISSUE: https://github.com/espressif/arduino-esp32/issues/3714
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

//ignored at the moment
#define SPIc_SPI_SS_1 15

bool SPIc::initialized = false;
bool SPIc::transmitting = false;

void SPIc::setup(uint8_t CSpin){

    pinMode(CSpin, OUTPUT);
    digitalWrite(CSpin, HIGH);

    //if not initialized do the setup
    if(!initialized){
        SPIcSPI.begin(SPIc_SPI_CLK, SPIc_SPI_MISO, SPIc_SPI_MOSI, -1);
        initialized = true;
    }
}

bool SPIc::isInitialized(){
    return initialized;
}

void SPIc::close(){
    if(initialized){
        SPIcSPI.end();
        initialized = false;
    }
}

void SPIc::selectChip(uint8_t CSpin){
    
    digitalWrite(CSpin, LOW);
    
    //wait for 2 instructions (20ns setup time)
    //should normaly not be needed and is just here to be sure
    __asm("nop");
    __asm("nop");
}

    
void SPIc::deselectChip(uint8_t CSpin){
    
    digitalWrite(CSpin, HIGH);

    //8 nops so that the program will have the min high time of
    //the slave select ping (80ns)
    //should normaly not be needed and is just here to be sure
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
}

//overloaded function (will call the other one)
void SPIc::beginTransaction(uint32_t maxSpeed, uint8_t bitOrder, uint8_t spiMode){
    beginTransaction(SPISettings(maxSpeed, bitOrder, spiMode));
}

void SPIc::beginTransaction(SPISettings settings){
    transmitting = true;
    SPIcSPI.beginTransaction(settings);
}

void SPIc::endTransaction(){
    SPIcSPI.endTransaction();
    transmitting = false;
}


//for read writing (sending data to the slave and receiving a response)
uint8_t SPIc::transfer8(uint8_t data){
    //needs to be volatile so that the compiler does optimize the read 
    //operation of the read register away
    volatile uint8_t result = SPIcSPI.transfer(data);
    return result;
}

uint16_t SPIc::transfer16(uint16_t data){
    //needs to be volatile so that the compiler does optimize the read 
    //operation of the read register away
    volatile uint16_t result = SPIcSPI.transfer16(data);
    return result;
}

uint32_t SPIc::transfer32(uint32_t data){
    //needs to be volatile so that the compiler does optimize the read 
    //operation of the read register away
    volatile uint32_t result = SPIcSPI.transfer32(data);
    return result;
}

//for read and writing arrays 
//do not forget to delete the arrays (data + result) otherwise there will
//be a mem leak
uint8_t * SPIc::transferArray8(uint8_t * data, uint32_t size){
    uint8_t * result = new uint8_t[size];
    SPIcSPI.transferBytes(data, result, size);
    return result;
}


//for writing (sending data to the slave)
void SPIc::write8(uint8_t data){
    transfer8(data);
}

void SPIc::write16(uint16_t data){
    transfer16(data);
}

void SPIc::write32(uint32_t data){
    transfer32(data);
}

//for writing array 
//do not forget to delete the data array (mem leak)
void SPIc::writeArray8(uint8_t * data, uint32_t size){
    uint8_t * result = transferArray8(data, size);
    delete[] result;
}



//for reading 
uint8_t SPIc::read8(){
    //transfers a zero signal (MOSI)
    return transfer8(0);
}

uint16_t SPIc::read16(){
    //transfers a zero signal (MOSI)
    return transfer16(0);
}

uint32_t SPIc::read32(){
    //transfers a zero signal (MOSI)
    return transfer32(0);
}

//for read arrays 
//do not forget to delete the array (result) otherwise there will
//be a mem leak
uint8_t * SPIc::readArray8(uint32_t size){

    uint8_t * result = nullptr;
    uint8_t * data = new uint8_t[size];

    //is used so that the MOSI data is constantly zero 
    //(pretty signal and less confusing)
    //maybe removed if speed is an issue but should only have a minimum effect
    for(int i = 0; i < size; i++){
        data[i] = 0;
    }

    result = transferArray8(data, size);
    
    delete[] data;
    return result;
}