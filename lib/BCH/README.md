# BCH LIB

## Info
This lib  is used to generate, check and correct messages that have bch codes


## Functions

### generateCode()
```
    long generateCode(long data, int dataLength, long generator);
```
This function is used to generate the message with the data and in the appendix the bch checkbits.

__long data__ = the data you want to sent,

__int dataLength__ = the length of the data (number of bits)

__long generator__ = the generator polynom in binary that should be used to generate the code

__return long__ = returns the code with the message bits + bch bits (bch bits = appendix)

<br>

### hasCodeErrors()
```
bool hasCodeErrors(long code, int codeLength, long generator);
```
This function is used to check if the code has errors. It return 1 (true) is the code has errors and 0 (false) if the code doesn't have any errors

__long code__ = the code that was received (data + bch bits)

__int codeLength__ = the full length of the code (length of the data bits + length of the bch bits)

__long generator__ = the generator polynom in binary that was used to generate the code

__return bool__ = returns 0 (false) if the code has no errors and 1 (true) if the code has errors.

<br>

### codeCorrection
```
long codeCorrection(long code, int codeLength, long generator, int numberOfErrors);
```
With this function it is possible to correct _numberOfErrors_ Errors in the Code.
But be careful. You can only correct (Hammingdistance - 1) / 2.
It can work if you correct more but it can't be guaranteed that you will get the "right" code.

__long code__ = the code that was received (data + bch bits)

__int codeLength__ = the full length of the code (length of the data bits + length of the bch bits)

__long generator__ = the generator polynom in binary that was used to generate the code

__int numberOfErrors__ = the number of errors you want to correct. Ex: if numberOfErrors is set to 3 it will first try to correct 1 error then 2 errors and then 3 errors. That means that you don't need to call it for 1, 2, 3 errors. it is sufficient to call it for 3. 

__return long__ = if the error correction is successful it will return the corrected code (data + bch bits) if not it will return 0