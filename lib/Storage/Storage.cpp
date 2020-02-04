#include "Storage.h"

//use the VSPI
SPIClass SDSPI(VSPI);

#define Storage_SPI_CLK 18
#define Storage_SPI_MISO 19
#define Storage_SPI_MOSI 22
#define Storage_SPI_SS 5

static bool cardIsMounted = false;

bool Storage::setup(){
    SDSPI.begin(Storage_SPI_CLK, Storage_SPI_MISO, Storage_SPI_MOSI, -1);
    cardIsMounted = SD.begin(Storage_SPI_SS, SDSPI);
    return cardIsMounted;
}

//normaly you shouldn't use this function (know your directories)
ArrayList<String> * Storage::listDir(String dirName){

    //check if card is mounted
    if(!cardIsMounted){
        return nullptr;
    }
    
    File root = SD.open(dirName);
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

    //remove director
    return SD.remove(path);
}


/* 
 *  Modes: FILE_WRITE, FILE_READ, FILE_APPEND 
 */
File Storage::getFile(String path, const char* mode){
    //check if card is mounted
    File f;
    if(!cardIsMounted){
        return f;
    }

    //open file
    f = SD.open(path, mode);
    return f;
}

//read the current line from the stream and go to the next
String Storage::readLine(File file){
    if(!file.available()){
        return "";
    }

    return file.readStringUntil('\n');
}


//read a specific line (0 - x) (first line is line zero)
String Storage::readLine(String path, int line){

    File file = getFile(path, FILE_READ);
    if(!file.available()){
        return "";
    }

    for(int i = 0; i < line; i++){
        if(!file.available()){
            return "";
        }
        readLine(file);
    }

    String s = readLine(file);

    file.close();

    return s;
}