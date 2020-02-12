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


<!-- 
Here start the SPI TRANSFER FUNCTIONS
-->


<!-- 
Here start the SPI READ FUNCTIONS
-->