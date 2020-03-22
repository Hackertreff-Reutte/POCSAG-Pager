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


//some common spi pins 

//hspi 
#define HSPI_CLK 14
#define HSPI_MISO 12
#define HSPI_MOSI 13

//vspi
#define VSPI_CLK 18
#define VSPI_MISO 19
#define VSPI_MOSI 23




//------------------------------------------------------------------------------


//list of spis
ArrayList<SPIc*> SPIc::ListOfSPIs;

//static 
//check whether a spi exists or not (init)
bool SPIc::spiExists(uint8_t spi_bus){
    for(int i = 0; i < ListOfSPIs.getSize(); i++){
        if(ListOfSPIs.getArray()[i]->getSpiBusCode() == spi_bus){
            return true;
        }
    }
    return false;
}

//static function that returns the spi if it exists
SPIc* SPIc::getSPI(uint8_t spi_bus){
    for(int i = 0; i < ListOfSPIs.getSize(); i++){
        if(ListOfSPIs.getArray()[i]->getSpiBusCode() == spi_bus){
            return ListOfSPIs.getArray()[i];
        }
    }
    return nullptr;
}

//static creates a new instance of the spi bus
SPIc* SPIc::setupSPI(uint8_t spi_bus, int8_t sck, int8_t miso, int8_t mosi){
    
    //the spi should not exist
    if(spiExists(spi_bus) == true){
        return nullptr;
    }

    //create new spiBus
    SPIc* newSPI = new SPIc(spi_bus);

    //inits the spi
    newSPI->setup(sck, miso, mosi);

    //set the spi buscode
    newSPI->spiBusCode = spi_bus;

    ListOfSPIs.add(newSPI);

    return newSPI;
}

//returns the bus code
uint8_t SPIc::getSpiBusCode(){
    return spiBusCode;
}

//private constructor for kind of singleton usage 
SPIc::SPIc(uint8_t spi_bus){
    SPIcSPI = new SPIClass(spi_bus);
}

//returns the SpiClass instance should only really be used if you need it
//example: for the SD lib
SPIClass* SPIc::getSpiClass(){
    if(lock == false){
        return SPIcSPI;
    }

    return nullptr;
}


//setsup and spi controller
void SPIc::setup(int8_t sck, int8_t miso, int8_t mosi){
    MOSI = mosi;
    MISO = miso;
    SCK = sck;

    SPIcSPI->begin(sck, miso, mosi, -1);
    
    initialized = true;
}

bool SPIc::closeSPI(SPIc * spi){
    if(spi->initialized && spi->lock == false){
        spi->SPIcSPI->end();
        spi->initialized = false;

        //remove the SPIc from the SPI list;
        //IMPORTANT the user should delete the SPIc object
        for(int i = 0; i < ListOfSPIs.getSize(); i++){
            if(ListOfSPIs.getArray()[i]->getSpiBusCode() == spi->spiBusCode){
                ListOfSPIs.remove(i);
                delete[] spi->SPIcSPI;
            }
        }

        delete[] spi;

        return true;
    }

    return false;
}

//sets the state of the lock
void SPIc::setLock(bool state){
    lock = state;
}

//returns the state of the lock
bool SPIc::getLock(){
    return lock;
}

//get the init status of the chip
bool SPIc::isInitialized(){
    return initialized;
}

//get the transmitting status
bool SPIc::isTransmitting(){
    return transmitting;
}

//------------------------------------------------------------------------------


//changes a pin to an output pin 
bool SPIc::setChipSelectPin(uint8_t CSpin){

    if(initialized == true && lock == false){

        pinMode(CSpin, OUTPUT);
        digitalWrite(CSpin, HIGH);

        return true;
    }

    return false;
}


bool SPIc::selectChip(uint8_t CSpin){

    if(initialized == true && lock == false){
    
        digitalWrite(CSpin, LOW);
        
        //wait for 2 instructions (20ns setup time)
        //should normaly not be needed and is just here to be sure
        __asm("nop");
        __asm("nop");

        return true;

    }

    return false;
}

    
bool SPIc::deselectChip(uint8_t CSpin){

    if(initialized == true && lock == false){
    
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

        return true;

    }

    return false;
}

//overloaded function (will call the other one)
bool SPIc::beginTransaction(uint32_t maxSpeed, uint8_t bitOrder, uint8_t spiMode){
    
    //check if the SPI controller is initialised or locked or the spi is transmitting
    if(initialized == false || lock == true || transmitting == true){
        return false;
    }

    return beginTransaction(SPISettings(maxSpeed, bitOrder, spiMode));

}

bool SPIc::beginTransaction(SPISettings settings){

    //check if the SPI controller is initialised or locked  or the spi is transmitting
    if(initialized == false || lock == true  || transmitting == true){
        return false;
    }

    transmitting = true;
    SPIcSPI->beginTransaction(settings);

    return true;
}

bool SPIc::endTransaction(){

    //check if the SPI controller is initialised or locked or the spi is not transmitting
    if(initialized == false || lock == true || transmitting == false){
        return false;
    }

    SPIcSPI->endTransaction();
    transmitting = false;

    return true;
}


//for read writing (sending data to the slave and receiving a response)
uint8_t SPIc::transfer8(uint8_t data){

    //check if the SPI controller is initialised or locked
    if(initialized == false || lock == true || transmitting == false){
        return 0;
    }

    //needs to be volatile so that the compiler does optimize the read 
    //operation of the read register away
    volatile uint8_t result = SPIcSPI->transfer(data);
    return result;
}

uint16_t SPIc::transfer16(uint16_t data){

    //check if the SPI controller is initialised or locked
    if(initialized == false || lock == true || transmitting == false){
        return 0;
    }

    //needs to be volatile so that the compiler does optimize the read 
    //operation of the read register away
    volatile uint16_t result = SPIcSPI->transfer16(data);
    return result;
}

uint32_t SPIc::transfer32(uint32_t data){

    //check if the SPI controller is initialised or locked
    if(initialized == false || lock == true || transmitting == false){
        return 0;
    }

    //needs to be volatile so that the compiler does optimize the read 
    //operation of the read register away
    volatile uint32_t result = SPIcSPI->transfer32(data);
    return result;
}

//for read and writing arrays 
//do not forget to delete the arrays (data + result) otherwise there will
//be a mem leak
uint8_t * SPIc::transferArray8(uint8_t * data, uint32_t size){

    //check if the SPI controller is initialised or locked
    if(initialized == false || lock == true || transmitting == false){
        return nullptr;
    }

    uint8_t * result = new uint8_t[size];
    SPIcSPI->transferBytes(data, result, size);
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