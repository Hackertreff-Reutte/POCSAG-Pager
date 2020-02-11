# Storage LIB

## Info
This lib  is used to read, write and manage and SD Card via the SPI interface


## Structure
 - Storage.h -> Headerfile contains all the function definitions of the lib
 - Storage.cpp -> contains all the functions for managing the SD cards and the files (rename, move, mkdir ...)
 - StorageRead.cpp -> contains all the functions for reading data from files that are stored on the SD-Card


## Dependencies 
 - ArrayList lib (created by HTR)
 - FS lib (Filesystem) (std Arduino lib)
 - SD lib (std Arduino lib)
 - SPI lib (std Arduino lib)
 - string lib (string.h) (cpp)


## Functions

<!-- 
Here start the STOARGE BASIC FUNCTIONS
-->

### setup()

```
bool setup();
```
Initializes the SPI for the SD-Card and the SD lib

#### Return value: 
>__return bool__ = returns 1 (true) if the card was mounted, if not it returns 0 (false)

<br>

### close()
```
void close();
```
This functions ends the the SD lib (SD-Card interface) and ends the SPI for the SD-Card (closes both)

<br>

### listDir()
```
ArrayList<String> * listDir(String path);
```
This function will return all the files and directories in the given path

#### Arguments: 
>__String path__ = the absolute path to the directory that should be returned
(eg. "/dir")

#### Return value: 
>__return ArrayList<String> *__ = returns an ArrayList with all the names of the files in this directory

<br>

### mkDir()
```
bool mkDir(String path);
```
This function will create a directory at the given path (path must be absolute)
(eg. path = /docs -> will create folder docs)

#### Arguments: 
>__String path__ = the absolute path to the directory that should be created

#### Return value: 
>__return bool__ = returns if the creation was successful 
1 (true) = successful  |  0 (false) = not successful

<br>

### rmDir()
```
bool rmDir(String path);
```
This function will remove a directory at the given path (path must be absolute)
(eg. path = /docs -> will remove folder docs)

#### Arguments: 
>__String path__ = the absolute path to the directory that should be removed

#### Return value: 
>__return bool__ = returns if the removal was successful 
1 (true) = successful  |  0 (false) = not successful

<br>

### rmFile()
```
bool rmFile(String path);
```
This function will remove a file at the given path (path must be absolute)
(eg. path = /docs/test.txt -> will remove file text.txt)

#### Arguments: 
>__String path__ = the absolute path to the file that should be removed

#### Return value: 
>__return bool__ = returns if the removal was successful 
1 (true) = successful  |  0 (false) = not successful

<br>

### rename()
```
bool rename(String path, String newPath);
```
This function is used to rename files. You must give this functions 2 absolute paths.
(eg. path = /test/file.txt    newPath = /test/newName.txt)

#### Arguments: 
>__String path__ = the absolute path to the file that should be renamed

>__String newPath__ = the absolute path to file + the file with the new name

#### Return value: 
>__return bool__ = returns if the renaming was successful 
1 (true) = successful  |  0 (false) = not successful

<br>

### move()
```
bool move(String path, String newPath);
```
This function is used to move files. You must give this functions 2 absolute paths.
(eg. path = /test/file.txt    newPath = /otherDir/file.txt)

#### Arguments: 
>__String path__ = the absolute path to the file that should be moved

>__String newPath__ = the absolute path to new location + the file 

#### Return value: 
>__return bool__ = returns if the moving was successful 
1 (true) = successful  |  0 (false) = not successful

<br>

### getFile()
```
File getFile(String path, const char * mode);
```
This function will open file in an selected mode (Read / Write / Append) and returns a file object that can be used to access the file.

#### Arguments: 
>__String path__ = the absolute path to the file that should be opened

>__const char * mode__ = the mode in which the file should be opened ((FILE_READ / "r"), (FILE_WRITE / "w"), (FILE_APPEND / "a"))

#### Return value: 
>__return File__ = returns the file

<br>

### exists()
```
bool exists(String path);
```
This functions checks if a file exists or not

#### Arguments: 
>__String path__ = the absolute path to the file that should be checked for existence 

#### Return value: 
>__return bool__ = returns true (1) if the file exists and false (0) if it doesn't.

<br>

<!-- 
Here start the STOARGE READ FUNCTIONS
-->


### readLine()
```
String readLine(File file);
String readLine(String path, size_t line)
```
This function will read the line from the current line pointer and put the line pointer to the next line. With this function it is possible to read the file line by line, you just need to call it x-times (x-times = amount of lines). It is also possible to read a spesific line of a file, for that the absolute path to the file must be given to the functions and the line number.
(Will alway read until the next "\n")

#### Arguments: 
>__File file__ = the file that should be read from (obtainable via the getFile() function) [Option 1]

>__String path__ = absolute path to the file that should be read from (eg. /testDir/file.txt) [Option 2]

>__size_t line__ = the line number that should be read from the selected file (path) [Option 2]

#### Return value: 
>__return String__ = return the line from the line pointer location of the currently read file or the line specified by (size_t line) 

<br>

### readBytes()
```
byte * readBytes(File file, size_t length);
byte * readBytes(String path, size_t start, size_t length);
```
This functions will read the number given by length bytes and returns them in an byte array. If the function is called more than one time (first functions) it will start reading where the last one left off. The other function will start reading given by length number bytes after it has read the number by start given bytes. So it will only read the number given by length bytes after the number by start given bytes offset (start is given in bytes  (start = 2 -> 2 bytes offset))

#### Arguments: 
>__File file__ = the file that should be read from [Option 1]

>__size_t length__ = the number of bytes that should be read [Option 1] [Option 2]

>__String path__ = the absolute path to the file that should be read from

>__size_t start__ = offset of bytes. the functions will only start reading after the by start defined bytes (start = read offset)


#### Return value: 
>__return byte *__ = returns an pointer to an byte array containing the read bytes from the file

<br>

<!-- 
Here start the STOARGE WRITE FUNCTIONS
-->