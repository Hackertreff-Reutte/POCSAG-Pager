/*
Lib for creating and managing pocsag messages
*/

#ifndef Storage_h
#define Storage_h

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "string.h"
#include "ArrayList.h"

class Storage{

    public:
        bool setup();
        ArrayList<String> * listDir(String dirName);
        bool mkDir(String path);
        bool rmDir(String path);
        File getFile(String path, const char* mode);
        String readLine(File file);
        String readLine(String path, int line);
    private:
        

};


#endif