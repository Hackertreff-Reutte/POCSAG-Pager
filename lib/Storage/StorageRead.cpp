#include "Storage.h"


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