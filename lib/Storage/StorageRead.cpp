#include "Storage.h"

/*
In this class only the most important functions are implemented,
that means that some are missing and will be implemented on the 
fly. -> if you miss some important function please let us know
*/


//read the current line from the stream and go to the next
String Storage::readLine(File file){

    if(!file.available()){
        return "";
    }

    return file.readStringUntil('\n');
}


//read a specific line (0 - x) (first line is line zero)
String Storage::readLine(String path, size_t line){

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


byte * Storage::readBytes(File file, size_t length){

    if(!file.available()){
        return nullptr;
    }

    byte * buffer = new byte[length];
    file.read(buffer, length);
    return  buffer;
}


//start is given in bytes, so it will start reading after 8 * start bits
byte * Storage::readBytes(String path, size_t start, size_t length){
    
    File file = getFile(path, FILE_READ);
    if(!file.available()){
        return nullptr;
    }
    
    byte * buffer;

    for(int i = 0; i < start; i++){
        buffer = readBytes(file, 1);
        delete[] buffer;
    }

    return readBytes(file, length);
}


