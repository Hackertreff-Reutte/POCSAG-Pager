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
        void close();
        ArrayList<String> * listDir(String dirName);
        bool mkDir(String path);
        bool rmDir(String path);
        bool rmFile(String path);
        bool rename(String path, String newPath);
        bool move(String path, String newPath);
        File getFile(String path, const char* mode);
        bool exists(String path);
        //READ
        String readLine(File file);
        String readLine(String path, int line);
    private:
        

};


#endif