/*
Lib for creating and managing pocsag messages
*/

#ifndef Storage_h
#define Storage_h

#include "FS.h"
#include "SD.h"
#include "SPIc.h"
#include "SPI.h"
#include "string.h"
#include "ArrayList.h"

class Storage{

    public:
        bool setup(uint8_t spi_bus, int8_t sck, int8_t miso, int8_t mosi, uint8_t cspin);
        void close();
        ArrayList<String> * listDir(String path);
        bool mkDir(String path);
        bool rmDir(String path);
        bool rmFile(String path);
        bool rename(String path, String newPath);
        bool move(String path, String newPath);
        File getFile(String path, const char* mode);
        bool exists(String path);
        //READ
        String readLine(File file);
        String readLine(String path, size_t line);
        byte * readBytes(File file, size_t length);
        byte * readBytes(String path, size_t start, size_t length);
    private:
        

};


#endif