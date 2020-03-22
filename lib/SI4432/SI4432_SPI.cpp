#include "SI4432.h"

//for more infos on the chip and the spi look at the datasheet
//https://www.silabs.com/documents/public/data-sheets/Si4430-31-32.pdf



//the cip select pin (nSEL)
//#define CSpin 15

//hspi 
//#define HSPI_CLK 14
//#define HSPI_MISO 12
//#define HSPI_MOSI 13

static const uint32_t spiMaxSpeed = 100000; // 1Mhz = 1000000; 100kHz = 100000 (for testing purpose ozi)
static const uint8_t spiBitOrder = MSBFIRST;
static const uint8_t spiMode = SPI_MODE0; //should be MODE 0 but should be checked again


static bool si4432Transaction = false;



bool SI4432::spiSetup(uint8_t spi_bus, uint8_t cspin){

    if(SPIc::spiExists(spi_bus)){
        //spi is already active
        spi = SPIc::getSPI(spi_bus);

        //spi is locked an cannot be used
        if(spi->getLock()){
            return false;
        }

        spi->setChipSelectPin(cspin);

        CSpin = cspin;
        return true;
    }

    //spi is not init or does not exists
    return false;
}


bool SI4432::spiSetup(uint8_t spi_bus, int8_t sck, int8_t miso, int8_t mosi, uint8_t cspin){

    if(SPIc::spiExists(spi_bus)){
        //spi is already active
        spi = SPIc::getSPI(spi_bus);

        //spi is locked an cannot be used
        if(spi->getLock()){
            return false;
        }

        spi->setChipSelectPin(cspin);
        CSpin = cspin;
        return true;
    }

    spi = SPIc::setupSPI(spi_bus, sck, miso, mosi);

    //setup failed
    if(spi == nullptr){
        return false;
    }

    spi->setChipSelectPin(cspin);
    CSpin = cspin;
    return true;
}


bool SI4432::beginTransaction(){
    if(!si4432Transaction){
        bool success = spi->beginTransaction(spiMaxSpeed, spiBitOrder, spiMode);
        si4432Transaction = true;
        return success;
    }
    return false;
}



bool SI4432::endTransaction(){
    if(si4432Transaction){
        bool success = spi->endTransaction();
        si4432Transaction = false;
        return success;
    }
    return false;
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
    

    if(si4432Transaction){
        //if the begin is already executed then just send the data

        //enable / select the chip
        spi->selectChip(CSpin);

        //send the address of the register you want to write to ( MSB - 1 until MSB - 8)
        //plus the data (last 8 bit) (MSB must be 1 (write operation))
        spi->write16(spiData);

        //disable / deselect the chip
        spi->deselectChip(CSpin);

    }else{
        //begin and end transaction if nothing is initalized
        if(beginTransaction()){

            //enable / select the chip
            spi->selectChip(CSpin);

            spi->write16(spiData);
            endTransaction();

            //disable / deselect the chip
            spi->deselectChip(CSpin);
        }

    }


}



uint8_t SI4432::spiRead(uint8_t address){
    //check if adress is out of range
    if(address > 127){
        return 0;
    }

    uint8_t spiData = address;

    uint8_t spiResponse = 0;

    if(si4432Transaction){
        //if the begin is already executed then just send the data

        //enable / select the chip
        spi->selectChip(CSpin);

        //send the address of the register you want to read from
        spi->write8(spiData);

        //get the response of the chip (contents of the register)
        spiResponse = spi->read8();

        //disable / deselect the chip
        spi->deselectChip(CSpin);

    }else{
        //begin and end transaction if nothing is initalized
        if(beginTransaction()){

            //enable / select the chip
            spi->selectChip(CSpin);

            //send the address of the register you want to read from
            spi->write8(spiData);

            //get the response of the chip (contents of the register)
            spiResponse = spi->read8();
            endTransaction();

            //disable / deselect the chip
            spi->deselectChip(CSpin);
        }

    }


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


    if(si4432Transaction){
        //if the begin is already executed then just send the data

        //enable / select the chip
        spi->selectChip(CSpin);

        //write the address (register you want to write to (start address))
        spi->write8(spiData);

        //write the data in the registers
        spi->writeArray8(data, size);

        //disable / deselect the chip
        spi->deselectChip(CSpin);

    }else{
        //begin and end transaction if nothing is initalized
        if(beginTransaction()){
            
            //enable / select the chip
            spi->selectChip(CSpin);

            //write the address (register you want to write to (start address))
            spi->write8(spiData); 

            //write the data registers
            spi->writeArray8(data, size);
            endTransaction();

            //disable / deselect the chip
            spi->deselectChip(CSpin);
        }

    }
}


//don't foget to delete the pointer / array (mem leak)
uint8_t * SI4432::spiBurstRead(uint8_t address, uint32_t size){
    
    //check if adress is out of range
    if(address > 127){
        return nullptr;
    }

    uint8_t spiData = address;


    uint8_t * spiResponse = nullptr;

    if(si4432Transaction){
        //if the begin is already executed then just send the data

        //enable / select the chip
        spi->selectChip(CSpin);

        //write the address (register you want to read from (start address))
        spi->write8(spiData);

        //the data that will be read from the registers
        spiResponse = spi->readArray8(size); //the type and value of the data that is transfered is irrelevant

        //disable / deselect the chip
        spi->deselectChip(CSpin);

    }else{
        //begin and end transaction if nothing is initalized
        if(beginTransaction()){

            //enable / select the chip
            spi->selectChip(CSpin);

            //write the address (register you want to read from (start address))
            spi->write8(spiData);

            //the data that will be read from the registers
            spiResponse = spi->readArray8(size); //the type and value of the data that is transfered is irrelevant
            endTransaction();

            //disable / deselect the chip
            spi->deselectChip(CSpin);
        }
    }


    return spiResponse;
}