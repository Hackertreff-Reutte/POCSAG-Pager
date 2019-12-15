# BCH LIB

## Info
This lib  is used to generate, check and correct messages that have bch codes


## Structure
 - BCH.h -> Headerfile contains all the function definitions of the lib
 - BCH.cpp -> contains all related to generation, checking and correction of BCH codes.


## Dependencies 
This lib requires the ArrayList lib (created by the HTR)


## Functions

### generateCode()
```
    unsigned long generateCode(unsigned long data, int dataLength, unsigned long generator);
```
This function is used to generate the message with the data and in the appendix the bch checkbits.

#### Arguments: 
>__unsigned long data__ = the data you want to sent,

>__int dataLength__ = the length of the data (number of bits)

>__unsigned long generator__ = the generator polynom in binary that should be used to generate the code

#### Return value: 
>__return unsigned long__ = returns the code with the message bits + bch bits (bch bits = appendix)

<br>

### hasCodeErrors()
```
bool hasCodeErrors(unsigned long code, int codeLength, unsigned long generator);
```
This function is used to check if the code has errors. It return 1 (true) is the code has errors and 0 (false) if the code doesn't have any errors

#### Arguments: 
>__unsigned long code__ = the code that was received (data + bch bits)

>__int codeLength__ = the full length of the code (length of the data bits + length of the bch bits)

>__unsigned long generator__ = the generator polynom in binary that was used to generate the code

#### Return value: 
>__return bool__ = returns 0 (false) if the code has no errors and 1 (true) if the code has errors.

<br>

### codeCorrection()
```
long codeCorrection(long code, int codeLength, long generator, int numberOfErrors);

unsigned long codeCorrection(long code, int codeLength, unsigned long generator, int numberOfErrors, bool parity);
```
With this function it is possible to correct _numberOfErrors_ Errors in the Code.
But be careful. You can only correct (Hammingdistance - 1) / 2.
It can work if you correct more but it can't be guaranteed that you will get the "right" code.

#### Arguments: 
>__unsigned long code__ = the code that was received (data + bch bits)

>__int codeLength__ = the full length of the code (length of the data bits + length of the bch bits)

>__unsigned long generator__ = the generator polynom in binary that was used to generate the code

>__int numberOfErrors__ = the number of errors you want to correct. Ex: if numberOfErrors is set to 3 it will first try to correct 1 error then 2 errors and then 3 errors. That means that you don't need to call it for 1, 2, 3 errors. it is sufficient to call it for 3. 

>__bool parity__ = here you can set the parity bit. if it is set it will be considered by the error correction and assumend to be correct. So if the correction has found an correct code it will only accept it if the parity of the new found code is the same as the parity bit set in the function (even parity)
this is optional if you don't want it don't write a number (0 is a number) [optional]

#### Return value: 
>__ArrayList<unsigned long> *__ = if the error correction is successful it will return an ArrayList<unsigned long> with all the corrected codes (data + bch bits) if not it will return an ArrayList with no entries