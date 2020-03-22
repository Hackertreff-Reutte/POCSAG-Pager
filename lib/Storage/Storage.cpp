#include "Storage.h"

/*
All the important functions where implemented,
there are some functions missing and will be 
implemented if needed.
Functions: cardSize(); cardType(); totalBytes(); usedBytes();
*/

//use the VSPI normaly
//#define VSPI_CLK 18
//#define VSPI_MISO 19
//#define VSPI_MOSI 23
//#define Storage_SPI_SS 5

static bool cardIsMounted = false;

SPIc* spi = nullptr;

//starts the storage and mounts the sd card
bool Storage::setup(uint8_t spi_bus, int8_t sck, int8_t miso, int8_t mosi, uint8_t cspin){

    if(SPIc::spiExists(spi_bus)){
        //spi is already active
        spi = SPIc::getSPI(spi_bus);
    }else{
        spi = SPIc::setupSPI(spi_bus, sck, miso, mosi);
    }

    //setup did not work or spi is already locked!
    if(spi == nullptr || spi->getLock()){
        return false;
    }


    cardIsMounted = SD.begin(cspin, *spi->getSpiClass());

    //lock the spi so that nothing can use it (this spi will only work uver the spiclass)
    spi->setLock(true);

    return cardIsMounted;
}

//stops the storage and unmounts the sd card
void Storage::close(){
    SD.end();
    spi->setLock(false);
    SPIc::closeSPI(spi);
    spi = nullptr;
}

//normaly you shouldn't use this function (know your directories)
ArrayList<String> * Storage::listDir(String path){

    //check if card is mounted
    if(!cardIsMounted){
        return nullptr;
    }
    
    File root = SD.open(path);
    //check if directory can be opened
    if(!root){
        return nullptr;
    }

    //check if it is a directory
    if(!root.isDirectory()){
        return nullptr;
    }

    ArrayList<String> * dirList = new ArrayList<String>();

    File file = root.openNextFile();
    while(file){
        //check if file is dir
        if(file.isDirectory()){

            //get the dir name and add it to the ArrayList
            String s = file.name();
            s += "/";
            dirList->add(s);
            
        } else {
            //get the file name and add to the ArrayList
            String s = file.name();
            dirList->add(s);
        }
        file = root.openNextFile();
    }

    //returns the ArrayList
    return dirList;
}

//you must give this function the absolute path (eg: /test  or  /test/foo (test must exist))
bool Storage::mkDir(String path){

    //check if card is mounted
    if(!cardIsMounted){
        return false;
    }

    //create directory
    return SD.mkdir(path);
}

bool Storage::rmDir(String path){
    //check if card is mounted
    if(!cardIsMounted){
        return false;
    }

    //check if directory exists
    if(!SD.exists(path)){
        return false;
    }

    //remove directory
    return SD.rmdir(path);
}


bool Storage::rmFile(String path){
    //check if card is mounted
    if(!cardIsMounted){
        return false;
    }

    //check if file exists
    if(!SD.exists(path)){
        return false;
    }

    //removes file
    return SD.remove(path);
}

//works for files and directories
bool Storage::rename(String path, String newPath){
    //check if card is mounted
    if(!cardIsMounted){
        return false;
    }

    //checks if the "to be moved" file exists and check that the move 
    //location is empty (no file exists at that path (no overwrite))
    if(!SD.exists(path) || SD.exists(newPath)){
        return false;
    }

    return SD.rename(path, newPath);
}


bool Storage::move(String path, String newPath){
    return rename(path, newPath);
}


/* 
 *  Modes: FILE_WRITE, FILE_READ, FILE_APPEND 
 */
File Storage::getFile(String path, const char * mode){
    //check if card is mounted
    File f;
    if(!cardIsMounted){
        return f;
    }

    //open file
    f = SD.open(path, mode);
    return f;
}

bool Storage::exists(String path){
    //check if card is mounted
    if(!cardIsMounted){
        return false;
    }

    return SD.exists(path);
}