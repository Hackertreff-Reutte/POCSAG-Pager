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

