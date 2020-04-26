# SPIc LIB

## Info
This lib is mostly a wrapper lib and just adds some more funtions and better functions names to the existing SPI functions


## Structure
 - SPIc.h -> Headerfile contains all the function definitions of the lib
 - SPIc.cpp -> contains all the functions for managing the SD cards and the files (rename, move, mkdir ...)

## Dependencies 
 - Arduino.h
 - SPI.h


## Functions

<!-- 
Here start the SPI STATIC FUNCTIONS
-->


### spiExists()

```
static bool spiExists(uint8_t spi_bus);
```
Checks if the SPI exists / is initalized.

#### Arguments: 
>__uint8_t spi_bus__ = the spi bus code (eg: HSPI or VSPI (ESP32))

#### Return value: 
>__return bool__ = returns true (1) if the SPI exists / is initalized and false (0) if not.

<br>

### getSPI()
```
static SPIc * getSPI(uint8_t spi_bus);
```
Returns a pointer to the initalised SPI instance if it exits, otherwise it will return a nullptr

#### Arguments: 
>__uint8_t spi_bus__ = the spi bus code (eg: HSPI or VSPI (ESP32))

#### Return value: 
>__return SPIc *__ = returns a pointer to the SPIc instance

<br>

### setupSPI()
```
static SPIc * setupSPI(uint8_t spi_bus, int8_t sck, int8_t miso, int8_t mosi);
```
This function is just to setup a SPI instance if it is not already initialized. If the instance already exists the functions will return a nullptr. With this function it is also set which pins the SPI will use.

#### Arguments: 
>__uint8_t spi_bus__ = the spi bus code (eg: HSPI or VSPI (ESP32))

>__int8_t sck__ = the pin of the clocksignal (SPI CLOCK)

>__int8_t miso__ = the pin of the miso signal (master in slave out) (SPI MISO)

>__int8_t mosi__ = the pin of the mosi signal (master out slave in) (SPI MOSI)

#### Return value: 
>__return SPIc *__ = returns a pointer to the SPIc instance

<br>

### closeSPI()
```
static bool closeSPI(SPIc * spi);
```
closes the SPI instance and return whether the closing procedure was successful.

#### Arguments: 
>__SPIc * spi__ = a pointer to the SPI instance that should be closed

#### Return value: 
>__return bool__ = returns wheter it was successful (1) true or not (0) false

<br>


<!-- 
Here start the SPI BASIC FUNCTIONS
-->

### setLock()
```
void setLock(bool state);
```
sets the lock of the SPI instance. If the lock is set the instance cannot be used. (Transfer, Write, Read). This may only be used when you pass the SPIClass object to another program. For example when you use the SD lib.

#### Arguments: 
>__bool state__ = true (1) == locked    false (0) == unlocked

<br>

### getLock()
```
bool getLock();
```
Returns the current state of the lock status. If it returns true (1) the spi instance is locked if it returns false (0) it is unlocked.

#### Return value: 
>__return bool__ = returns wheter it was successful (1) true or not (0) false

<br>

### getSpiBusCode()
```
uint8_t getSpiBusCode();
```
returns the code of the spi bus. (example esp32: VSPI HSPI)

#### Return value: 
>__return bool__ = the spi bus code (eg: HSPI or VSPI (ESP32))

<br>

### getSpiClass()
```
SPIClass * getSpiClass();
```
returns the pointer that points to the stored spiClass object. This function should only be used if there is no other way. For example when using the SD lib. Do not forget to lock the SPI instance if you pass the spiClass object to another lib.

#### Return value: 
>__return SPIClass *__ = returns a pointer to the stored spiClass object (Arduino SPI (SPI.h))

<br>

### bool isInitialized()
```
bool isInitialized();
```
return the status of the spi object true (1) = the object is initalized and false (0) = the object is not or no longer initialized

#### Return value: 
>__return bool__ = returns the status of the spi true (1) or false (0)

<br>

### bool isTransmitting()
```
bool isTransmitting();
```
returns if the spi is currently transmitting data (in use). only one transaction at a time is allowed per spi bus

#### Return value: 
>__return bool__ = returns true (1) if the spi is transmitting or false (0) if not

<br>

### bool setChipSelectPin()
```
bool setChipSelectPin(uint8_t CSpin);
```
This function defines and sets a pin as an output pin. This pin can than be used to select / enable a spi slave

#### Arguments: 
>__uint8_t CSpin__ = the number of the pin that should be setup (look at the documentation of the microcontroller of those numbers)

#### Return value: 
>__return bool__ = returns true (1) if the setup of the pin was successful or false (0) if not

<br>

### bool selectChip()
```
bool selectChip(uint8_t CSpin);
```
This function will select a slave device if nothing prevents it.

#### Arguments: 
>__uint8_t CSpin__ = the number of the pin where the slave device is attached to and which should be enabled / activated (listen to data over spi)

#### Return value: 
>__return bool__ = returns true (1) if the chip was selected (chip select pin = HIGH) or false (0) if not (possible reasons for failure: already initialised or locked)

<br>

### bool deselectChip()
```
bool deselectChip(uint8_t CSpin);
```
This function will deselect a slave device if nothing prevents it. So that it doesn't listen to the signals of the spi bus.

#### Arguments: 
>__uint8_t CSpin__ = the number of the pin where the slave device is attached to and which should be deselected (set device to standby)

#### Return value: 
>__return bool__ = returns true (1) if the chip was deselected (chip select pin = LOW) or false (0) if not (possible reasons for failure: not initialised or locked)

<br>

### bool beginTransaction()
```
bool beginTransaction(uint32_t maxSpeed, uint8_t bitOrder, uint8_t spiMode);
bool beginTransaction(SPISettings settings);
```
This function will initialize a spi transaction with the given parameters.
For more information regarding the parameters it could be a good idea to visit the following wikipedia page:
https://en.wikipedia.org/wiki/Serial_Peripheral_Interface

#### Arguments: 
>__uint32_t maxSpeed__ = The Speed of the SPI clock signal in Hz (eg. 1Mhz = 1000000; 100kHz = 100000)

>__uint8_t bitOrder__ = sets the bit order of the signal MSBFIRST (most significant bit first) or LSBFIRST (least significant bit first)

>__uint8_t spiMode__ = this sets the mode (SPI_MODE1, SPI_MODE1, SPI_MODE1, SPI_MODE1)

>__SPISettings settings__ = this a object that contains all the settings and can also be used to setup a transaction. For more information regarding this option consider visiting: https://www.arduino.cc/en/Reference/SPISettings

#### Return value: 
>__return bool__ = returns true (1) if a transaction was startet (spi is ready for transfers / sending data) or false (0) if not (reasons for failure include but not limited to: locked spi)

<br>

### bool endTransaction()
```
bool endTransaction()
```
This function will end a transaction.

#### Return value: 
>__return bool__ = returns true (1) if the transaction was stopped or false (0) if it could not be stopped (reasons for failure include but not limited to: no running transaction)

<br>

<!-- 
Here start the SPI WRITE FUNCTIONS
-->

### write8()

```
void write8(uint8_t data);
```
Sends 8 bit of data out the MOSI pin.

#### Arguments: 
>__uint8_t data__ = the 8 bit of data that will be sent.

<br>

### write16()

```
void write16(uint16_t data);
```
Sends 16 bit of data out the MOSI pin.

#### Arguments: 
>__uint16_t data__ = the 16 bit of data that will be sent.

<br>

### write32()

```
void write32(uint32_t data);
```
Sends 32 bit of data out the MOSI pin.

#### Arguments: 
>__uint32_t data__ = the 32 bit of data that will be sent.

<br>

### writeArray8()

```
void writeArray8(uint8_t * data, uint32_t size);
```
Sends an 8 bit array (byte array) out of the MOSI pin. This functions is used when a lot of bits need to be sent. You can only send a multiple of 8 bit of data with this functions (bytes)

#### Arguments: 
>__uint8_t * data__ = a pointer to an array that contains the data that should be sent

>__uint32_t size__ = the size of the array or the amout that should be sent. (Should not be bigger than the amount of entries in the array itself) (eg. size = 4 sends 4 bytes (4 * 8 bits))

<br>

<!-- 
Here start the SPI TRANSFER FUNCTIONS
-->

### transfer8()

```
uint8_t transfer8(uint8_t data);
```
This functions transfers 8 bit of data through the MOSI pin and reads at the same moment 8 bit from the MISO and returns them. (Both operations are executet at the same time)

#### Arguments: 
>__uint8_t data__ = the data that will be sent (8 bit)

#### Return value: 
>__return uint8_t__ = the data that was read from the MISO pin (8 bit)

<br>

### transfer16()

```
uint16_t transfer16(uint16_t data);
```
This functions transfers 16 bit of data through the MOSI pin and reads at the same moment 16 bit from the MISO and returns them. (Both operations are executet at the same time)

#### Arguments: 
>__uint16_t data__ = the data that will be sent (16 bit)

#### Return value: 
>__return uint16_t__ = the data that was read from the MISO pin (16 bit)

<br>

### transfer32()

```
uint32_t transfer32(uint32_t data);
```
This functions transfers 32 bit of data through the MOSI pin and reads at the same moment 32 bit from the MISO and returns them. (Both operations are executet at the same time)

#### Arguments: 
>__uint32_t data__ = the data that will be sent (32 bit)

#### Return value: 
>__return uint32_t__ = the data that was read from the MISO pin (32 bit)

<br>

### transferArray8()

```
uint8_t * transftransferArray8er32(uint8_t * data, uint32_t size);
```
This function sends an byte array through the MSOI pin. The amount of bytes being sent is defined by the size var. The data that will be sent is located at the data pointer. The size variable must not exceed the size of the array (data). While the data is sent the SPI controller will read all incoming bits on the MISO pin and store them in an array with the size of the size variable. The function will return a pointer to the received data. (Both operations (send and receive) are executet at the same time)

#### Arguments: 
>__uint8_t * data__ = a pointer to the array which contains the data that will be sent

>__uint32_t size__ = the size of the array or the amount of data that should be sent in bytes (3 bytes = 3 * 8 bits)

#### Return value: 
>__return uint8_t *__ = returns an pointer to an array which contains the data that was received (MISO) simultaneously to the sent data. The size of that array is the same as the value of the variable size

<br>

<!-- 
Here start the SPI READ FUNCTIONS
-->

### read8()

```
uint8_t read8();
```
This function will read 8 bits from the MISO pin and return it. The MOSI pin will be 0 the entire time.

#### Return value: 
>__return uint8_t__ = returns the data (8 bit) that was read be the SPI on the MISO pin

<br>

### read16()

```
uint16_t read16();
```
This function will read 16 bits from the MISO pin and return it. The MOSI pin will be 0 the entire time.

#### Return value: 
>__return uint16_t__ = returns the data (16 bit) that was read be the SPI on the MISO pin

<br>

### read32()

```
uint32_t read32();
```
This function will read 32 bits from the MISO pin and return it. The MOSI pin will be 0 the entire time.

#### Return value: 
>__return uint32_t__ = returns the data (32 bit) that was read be the SPI on the MISO pin

<br>

### readArray8()

```
uint8_t * readArray8(uint32_t size);
```
This functions will read the amount given by size bytes (1 byte = 8 bit) from the MISO pin. The MOSI pin will be zero the entire time.

#### Arguments: 
>__uint32_t size__ = the amount of bytes that should be read

#### Return value: 
>__return uint8_t *__ = returns the pointer to an array which contains the read bytes. The array has the same size as the given variable size

<br>