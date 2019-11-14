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
Checks if the 31 (without parity bit) bit POCSAG message has errors.
If it has errors it returns 1 (true), if the message has no errors it returns 0 (false)

__long code__ = the 31 (without parity bit) bit pocsag code that was received (message bits + bch bits).

__return bool__ = returns 1 (true) if the code has errors, if not it returns 0 (false)

<br>

### generateCodeWithBCH()

```
long generateCodeWithBCH(long data);
```
With this function you can generate the pocsag message (31 bit (without parity bit) = 21 message bits + 10 bch bits)

__long data__ = the 21 bits of data you want to "encode"

<br>

### tryCodeErrorCorrection()

```
long tryCodeErrorCorrection(long code, bool twoBitCodeCorrectionEnable);
```
This is the save methode to correct a bch code. It will try to correct 1 or 2 errors (hammingdistance = 6) and return the result.
Result = corrected code or 0 if the correction fails

__long code__ = the 31 (without parity bit) bit pocsag code that was received (message bits + bch bits).

__bool twoBitCodeCorrectionEnable__ = 1 (true) to use two and one bit error correction or 0 (false) to only use one bit error correction

<br>

### tryUnsecureCodeErrorCorrection()

```
long tryUnsecureCodeErrorCorrection(long code, int numberOfErrors);
```
This is the unsecure methode to correct a pocsag code. You can choose how many errors you want to correct. but that doesn't mean you will get the correct code back. you will get a possible code back.

__long code__ = the 31 (without parity bit) bit pocsag code that was received (message bits + bch bits).

__int numberOfErrors__ = the number of errors you want to correct. Ex: if numberOfErrors is set to 3 it will first try to correct 1 error then 2 errors and then 3 errors. That means that you don't need to call it for 1, 2, 3 errors. it is sufficient to call it for 3. 