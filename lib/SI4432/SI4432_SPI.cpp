#include "SI4432.h"


//for more infos on the chip and the spi look at the datasheet
//https://www.silabs.com/documents/public/data-sheets/Si4430-31-32.pdf



//the cip select pin (nSEL)
#define CSpin 15

static const uint32_t spiMaxSpeed = 1000000; // 1Mhz = 1000000;
static const uint8_t spiBitOrder = MSBFIRST;
static const uint8_t spiMode = SPI_MODE0; //should be MODE 0 but should be checked again

bool SI4432::spiInitialized = false;
static bool si4432Transaction = false;

//setup spi
void SI4432::spiSetup(){
    if(!spiInitialized){
        spi.setup();
        //check wether the spi initialization worked
        if(spi.isInitialized()){
            //enable the CHIP select pins es output and set it high
            pinMode(CSpin, OUTPUT);
            digitalWrite(CSpin, HIGH);
            spiInitialized = true;
        }
    }
}


void SI4432::beginTransaction(){
    if(!si4432Transaction){
        spi.beginTransaction(spiMaxSpeed, spiBitOrder, spiMode);
        si4432Transaction = true;
    }
}



void SI4432::endTransaction(){
    if(si4432Transaction){
        spi.endTransaction();
        si4432Transaction = false;
    }
}


void SI4432::spiWrite(uint8_t address, uint8_t data){
    
    //check if adress is out of range
    if(address > 127){
        return;
    }

    //init the data with the first bit as 1 for write operation
    uint16_t spiData = 0b1000000000000000;

    //shift the adress and add it to the spiData
    spiData = spiData ^ (address << 8);

    //add the data
    spiData = spiData ^ data;
    

    digitalWrite(CSpin, LOW);
    
    //wait for 2 instructions (20ns setup time)
    __asm("nop");
    __asm("nop");

    if(si4432Transaction){
        //if the begin is already executed then just send the data
        spi.write16(spiData);
    }else{
        //begin and end transaction if nothing is initalized
        beginTransaction();
        spi.write16(spiData);
        endTransaction();

    }

    digitalWrite(CSpin, HIGH);

    //8 nops so that the program will have the min high time of
    //the slave select ping (80ns)
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
}



uint8_t SI4432::spiRead(uint8_t address){
    //check if adress is out of range
    if(address > 127){
        return 0;
    }

    uint8_t spiData = address;


    digitalWrite(CSpin, LOW);
    
    //wait for 2 instructions (20ns setup time)
    __asm("nop");
    __asm("nop");

    uint8_t spiResponse;

    if(si4432Transaction){
        //if the begin is already executed then just send the data
        spiResponse = spi.transfer8(spiData);
    }else{
        //begin and end transaction if nothing is initalized
        beginTransaction();
        spiResponse = spi.transfer8(spiData);
        endTransaction();

    }

    digitalWrite(CSpin, HIGH);

    //8 nops so that the program will have the min high time of
    //the slave select ping (80ns)
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");

    return spiResponse;
}


