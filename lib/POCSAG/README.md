# POCSAG LIB

## Info
This lib  is used to handle pocsag messages


## Structure
 - POCSAG.h -> Headerfile contains all the function definitions of the lib
 - POCSAG_BCH.cpp -> contains all related to generation, checking and correction codes.


## Dependencies 
This lib requires the BCH lib (created by the HTR) and the ArrayList lib (created by the HTR)


## Functions

### hasCodeErrors()

```
bool hasCodeErrors(unsigned long code);
```
Checks if the 32 (without parity bit) bit POCSAG message has errors.
If it has errors it returns 1 (true), if the message has no errors it returns 0 (false)

#### Arguments: 
>__unsigned long code__ = the 32 (with parity bit) bit pocsag code that was received (message bits + bch bits + parity bit).


#### Return value: 
>__return bool__ = returns 1 (true) if the code has errors, if not it returns 0 (false)

<br>

### generateCodeWithBCH()

```
unsigned long generateCodeWithBCH(unsigned long data);
```
With this function you can generate the pocsag message (32 bit (with parity bit) = 21 message bits + 10 bch bits + parity bit)

#### Arguments: 
>__unsigned long data__ = the 21 bits of data you want to "encode"

#### Return value: 
>__return unsigned long__ = returns the code (message bits (12) + bch bit (10) + parity bit (1))

<br>

### tryCodeErrorCorrection()

```
unsigned long tryCodeErrorCorrection(unsigned long code, bool twoBitCodeCorrectionEnable);
```
This is the save methode to correct a bch code. It will try to correct 1 or 2 errors (hammingdistance = 6) and return the result.
Result = corrected code or 0 if the correction fails

#### Arguments: 
>__unsigned long code__ = the 32 (with parity bit) bit pocsag code that was received (message bits + bch bits + parity bit).

>__bool twoBitCodeCorrectionEnable__ = 1 (true) to use two and one bit error correction or 0 (false) to only use one bit error correction

#### Return value: 
>__ArrayList<unsigned long> *__ = if the error correction is successful it will return a ArrayList Pointer with the corrected codes (data + bch bits + parity bit) if not it will return a ArrayList with no entries

<br>

### tryUnsecureCodeErrorCorrection()

```
unsigned long tryUnsecureCodeErrorCorrection(unsigned long code, int numberOfErrors);
unsigned long tryUnsecureCodeErrorCorrection(unsigned long code, int numberOfErrors, bool withParityCheck);
```
This is the unsecure methode to correct a pocsag code. You can choose how many errors you want to correct. but that doesn't mean you will get the correct code back. you will get a possible code back.

#### Arguments: 
>__unsigned long code__ = the 32 (with parity bit) bit pocsag code that was received (message bits + bch bits+ parity bit).

>__int numberOfErrors__ = the number of errors you want to correct. Ex: if numberOfErrors is set to 3 it will first try to correct 1 error then 2 errors and then 3 errors. That means that you don't need to call it for 1, 2, 3 errors. it is sufficient to call it for 3. 

>__bool withParityCheck__ = set this to 1 (true) if you want to only accept codes when the parity is okay. (if you set this the is a better chance to correct 3 Bit errors correctly) [optional]

#### Return value: 
>__ArrayList<unsigned long> *__ = if the error correction is successful it will return a ArrayList Pointer with the corrected codes (data + bch bits + parity bit) if not it will return a ArrayList with no entries