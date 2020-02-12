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
Here start the SPI BASIC FUNCTIONS
-->


### setup()

```
void setup(uint8_t CSpin);
```
Initializes the SPI bis with the pre defined pins (ESP32 HSPI). It also sets the given pin as an output pin and to an HIGH state

#### Arguments: 
>__uint8_t CSpin__ = the pin number of the pin that should be used as the slave select pin for controlling the slave device.

<br>

### isInitialized()

```
bool isInitialized();
```
returns the initialization state of the SPI bus.

#### Return value: 
>__return bool__ = returns 1 (true) if the spi bus is initialized and 0 (false) if not

<br>

### close()

```
void close();
```
Ends / closees the SPI bus

<br>

### selectChip()

```
void selectChip(uint8_t CSpin);
```
Selects the slave that is connected to the given CSpin (pulls the CSpin low) (makes the slave ready for receiving data)

#### Arguments: 
>__uint8_t CSpin__ = the pin number of the slave device that should be selected

<br>

### deselectChip()

```
void deselectChip(uint8_t CSpin);
```
Deselects the slave that is connected to the given CSpin (pulls the CSpin HIGH) (disables the slave / slave does not listen to the data on the spi bus until it is selected again)

#### Arguments: 
>__uint8_t CSpin__ = the pin number of the slave device that should be deselected

<br>

### beginTransaction()

```
void beginTransaction(uint32_t maxSpeed, uint8_t bitOrder, uint8_t spiMode);
void beginTransaction(SPISettings settings);

```
Begins a SPI transmission with the given parameters. Don't forget to end it, otherwise you can't start a new one. Only one active transmission / transaction per spi interface / controller at the time.

#### Arguments: 
>__uint32_t maxSpeed__ = the maximum Speed of the SPI bus (SPI clock) in Hz (eg. 1000000 = 1Mhz) [Option 1]

>__uint8_t bitOrder__ = gives the bit order in which the bits are transfered (MSB to LSB or LSB to MSB). The defines for that field are "MSBFIRST" (1) and "LSBFIRST" (0) [Option 1]

>__uint8_t spiMode__ = sets the mode of the SPI. There are 4 diffrent modes: "SPI_MODE0" (0), "SPI_MODE1" (1), "SPI_MODE2" (2), "SPI_MODE3" (3). For more information on the SPI modes look at the following link: https://en.wikipedia.org/wiki/Serial_Peripheral_Interface [Option 1]

>__SPISettings settings__ = is an object that contains the settings from option 1 (eg. SPISettings(maxSpeed, bitOrder, spiMode)). For more inforamtion on this object you can look at the SPI.h file [Option 2]. This settings object is good if you have a lot of diffrent settings that must be switched all the time.

<br>

### endTransaction()

```
void endTransaction();
```
Ends an transmission that was started by the function beginTransaction(). The current transmission / transaction must be stoped / ended before a new on can start. Only one transaction per SPI interface can be active

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