# POCSAG LIB

## Info
This lib  is used to handle pocsag messages

## Dependencies 
This lib requires the BCH Lib (created by the HTR)

## Functions

### hasCodeErrors()

```
bool hasCodeErrors(long code);
```
Checks if the 32 (without parity bit) bit POCSAG message has errors.
If it has errors it returns 1 (true), if the message has no errors it returns 0 (false)

#### Arguments: 
>__long code__ = the 32 (with parity bit) bit pocsag code that was received (message bits + bch bits + parity bit).


#### Return value: 
>__return bool__ = returns 1 (true) if the code has errors, if not it returns 0 (false)

<br>

### generateCodeWithBCH()

```
long generateCodeWithBCH(long data);
```
With this function you can generate the pocsag message (32 bit (with parity bit) = 21 message bits + 10 bch bits + parity bit)

#### Arguments: 
>__long data__ = the 21 bits of data you want to "encode"

#### Return value: 
>__return long__ = returns the code (message bits (12) + bch bit (10) + parity bit (1))

<br>

### tryCodeErrorCorrection()

```
long tryCodeErrorCorrection(long code, bool twoBitCodeCorrectionEnable);
```
This is the save methode to correct a bch code. It will try to correct 1 or 2 errors (hammingdistance = 6) and return the result.
Result = corrected code or 0 if the correction fails

#### Arguments: 
>__long code__ = the 32 (with parity bit) bit pocsag code that was received (message bits + bch bits + parity bit).

>__bool twoBitCodeCorrectionEnable__ = 1 (true) to use two and one bit error correction or 0 (false) to only use one bit error correction

#### Return value: 
>__return long__ = if the error correction is successful it will return the corrected code (data + bch bits + parity bit) if not it will return 0

<br>

### tryUnsecureCodeErrorCorrection()

```
long tryUnsecureCodeErrorCorrection(long code, int numberOfErrors);
long tryUnsecureCodeErrorCorrection(long code, int numberOfErrors, bool withParityCheck);
```
This is the unsecure methode to correct a pocsag code. You can choose how many errors you want to correct. but that doesn't mean you will get the correct code back. you will get a possible code back.

#### Arguments: 
>__long code__ = the 32 (with parity bit) bit pocsag code that was received (message bits + bch bits+ parity bit).

>__int numberOfErrors__ = the number of errors you want to correct. Ex: if numberOfErrors is set to 3 it will first try to correct 1 error then 2 errors and then 3 errors. That means that you don't need to call it for 1, 2, 3 errors. it is sufficient to call it for 3. 

>__long withParityCheck__ = set this to true if you want to only accept codes when the parity is okay. (if you set this the is a better chance to correct 3 Bit errors correctly) [optional]

#### Return value: 
>__return long__ = if the error correction is successful it will return the corrected code (data + bch bits + parity bit) if not it will return 0