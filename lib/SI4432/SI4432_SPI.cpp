#include "SI4432.h"

//for more infos on the chip and the spi look at the datasheet
//https://www.silabs.com/documents/public/data-sheets/Si4430-31-32.pdf



//the cip select pin (nSEL)
#define CSpin 15

static const uint32_t spiMaxSpeed = 100000; // 1Mhz = 1000000; 100kHz = 100000 (for testing purpose ozi)
static const uint8_t spiBitOrder = MSBFIRST;
static const uint8_t spiMode = SPI_MODE0; //should be MODE 0 but should be checked again

bool SI4432::spiInitialized = false;
static bool si4432Transaction = false;

//setup spi
void SI4432::spiSetup(){
    if(!spiInitialized){
        spi.setup(CSpin);
        //check wether the spi initialization worked
        if(spi.isInitialized()){
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
    
    //enable / select the chip
    spi.selectChip(CSpin);

    if(si4432Transaction){
        //if the begin is already executed then just send the data
        spi.write16(spiData);
    }else{
        //begin and end transaction if nothing is initalized
        beginTransaction();
        spi.write16(spiData);
        endTransaction();

    }

    //disable / deselect the chip
    spi.deselectChip(CSpin);

}



uint8_t SI4432::spiRead(uint8_t address){
    //check if adress is out of range
    if(address > 127){
        return 0;
    }

    uint8_t spiData = address;

    uint8_t spiResponse;

    //enable / select the chip
    spi.selectChip(CSpin);

    if(si4432Transaction){
        //if the begin is already executed then just send the data
        spi.write8(spiData);
        spiResponse = spi.transfer8(0); //the type and value of the data that is transfered is irrelevant
    }else{
        //begin and end transaction if nothing is initalized
        beginTransaction();
        spi.write8(spiData);
        spiResponse = spi.transfer8(0); //the type and value of the data that is transfered is irrelevant
        endTransaction();

    }

    //disable / deselect the chip
    spi.deselectChip(CSpin);

    return spiResponse;
}


void SI4432::spiBurstWrite(uint8_t address, uint8_t * data, uint32_t size){
     
    //check if adress is out of range
    if(address > 127){
        return;
    }

    //first block of data 
    uint8_t spiData = 0b10000000;
    spiData = spiData ^ address;

    //enable / select the chip
    spi.selectChip(CSpin);

    if(si4432Transaction){
        //if the begin is already executed then just send the data
        spi.write8(spiData);
        spi.writeArray8(data, size);
    }else{
        //begin and end transaction if nothing is initalized
        beginTransaction();
        spi.write8(spiData);
        spi.writeArray8(data, size);
        endTransaction();

    }

    //disable / deselect the chip
    spi.deselectChip(CSpin);

}


//don't foget to delete the pointer / array (mem leak)
uint8_t * SI4432::spiBurstRead(uint8_t address, uint32_t size){
    
    //check if adress is out of range
    if(address > 127){
        return nullptr;
    }

    uint8_t spiData = address;


    uint8_t * spiResponse = nullptr;
    uint8_t * placeholder = new uint8_t[size];

    
    //can be removed if it is too slow 
    //is just here so that the signal looks pretty 
    for(int i = 0; i < size; i++){
        placeholder[i] = 0;
    }

    //enable / select the chip
    spi.selectChip(CSpin);

    if(si4432Transaction){
        //if the begin is already executed then just send the data
        spi.write8(spiData);
        spiResponse = spi.transferArray8(placeholder, size); //the type and value of the data that is transfered is irrelevant
    }else{
        //begin and end transaction if nothing is initalized
        beginTransaction();
        spi.write8(spiData);
        spiResponse = spi.transferArray8(placeholder, size); //the type and value of the data that is transfered is irrelevant
        endTransaction();
    }

    //disable / deselect the chip
    spi.deselectChip(CSpin);

    //delete otherwise memory leak 
    delete[] placeholder;

    return spiResponse;
}