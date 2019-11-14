
#include "stdbool.h"
#include "math.h"
#include "BCH.h"


//get the binary length of an number from type int
int BCH::getBinaryLength(int number){
    //uses the long function
    return getBinaryLength((unsigned long) number);
}

//get the binary length of an number from type long
int BCH::getBinaryLength(unsigned long number){

    //special case 0 -> would otherwise return -2147483648
    if(number == 0){
        return 0;
    }
    return (unsigned int) (floor(log2(number)) + 1);
}


//used to calculate the polynomial remainder of a given data binary code and a generator binary code
unsigned long BCH::calculatePolynomialRemainder(unsigned long shiftedData, int fullLengthOfCode, unsigned long generator){

    int generatorLength = getBinaryLength(generator);
    unsigned long remainder =  shiftedData >> (fullLengthOfCode - generatorLength + 1);

    for(int i = fullLengthOfCode - generatorLength + 1; i > 0; i--){

        //append the remainder with the next bit of data from shiftedData
        remainder = (remainder << 1)^((shiftedData >> (i-1))&1);

        //checks if the MSB of the remainder has the same location as the MSB of the generator
        if((remainder >> (generatorLength - 1)&1) == 1){
            //if yes -> XOR them
            remainder = remainder^generator;
        }

    }
    return remainder;
}

//check if the bch code has error 
bool BCH::hasCodeErrors(unsigned long code, int codeLength, unsigned long generator){
    unsigned long remainder = calculatePolynomialRemainder(code, codeLength, generator);

    //if the remainder is zero return false (no errors)
    return remainder != 0;
}




//generate the bch code and add it to the code
unsigned long BCH::generateCode(unsigned long data, int dataLength, unsigned long generator){

    //polynomDegree is the highest polynom in the polynom  (Ex:  x^4 + x^2 + 1 -> polynomDegree = 4)
    int polynomDegree = getBinaryLength(generator) - 1; 

    //the length of the code at the end
    int fullLength = dataLength + polynomDegree;

    unsigned long shiftedData = data << (polynomDegree);

    unsigned long remainder = calculatePolynomialRemainder(shiftedData, fullLength, generator);

    //return the generated code
    return shiftedData^remainder;
}


unsigned long BCH::singleBitErrorCorrection(unsigned long code, int codeLength, unsigned long generator){
    unsigned long correctedCode = 0;

    for(int i = -1; i < codeLength; i++){

        correctedCode = code^(1<<i);

        //to check if errors in the code even exists
        if(i == -1){
            correctedCode = code;
        }

        unsigned long remainder = calculatePolynomialRemainder(correctedCode, codeLength, generator);

        if(remainder == 0){
            return correctedCode;
        }
    }

    //error correction failed
    return 0;
}

unsigned long BCH::errorCorrectionRecursion(unsigned long code, int codeLength, unsigned long generator, int depth, bool enableParityCheck, bool parity){
    //if zero just to catch some error if someone tries to set the iterations to zero
    if(depth <= 0){
        return 0;
    }else if(depth == 1){
        //calculate the single bit error correction
        unsigned long singleBitErrorCorrectedCode = singleBitErrorCorrection(code, codeLength, generator);

        if(enableParityCheck){
            //make a parity check
            if(singleBitErrorCorrectedCode % 2 == parity){
                //same parity
                return singleBitErrorCorrectedCode;
            }else{
                //wrong parity = wrong corrected code = return 0
                return 0;
            }
        }else{
            //return singleBitErrorCorrectedCode without parity check
            return singleBitErrorCorrectedCode;
        }

    }else{
        for(int i = -1; i < codeLength; i++){
            unsigned long tempCode = code ^ (1 << i);
            if(i == -1){
                tempCode = code;
            }
            //call the function again and go on iteration deeper
            unsigned long correctedCode = errorCorrectionRecursion(tempCode, codeLength, generator, depth - 1, enableParityCheck, parity);

            if(correctedCode != 0){

                if(enableParityCheck){
                    //make parity check
                    if(correctedCode % 2 == parity){
                        //return correctedCode because parity is okay
                        return correctedCode;
                    }else{
                        //return 0 because of wrong parity
                        return 0;
                    }
                }else{
                    //return correctedCode without parity check
                    return correctedCode;
                }
            }
        }
    }

    //return 0 if everything fails (no error correction possible)
    return 0;

}


//with this function you can correct up to 2 bit errors. 
unsigned long BCH::codeCorrection(unsigned long code, int codeLength, unsigned long generator, int numberOfErrors){
    //numberOfErros = the number of errors you want to try to correct (1 == 1 Bit error correction)
    bool enableParityCheck = false;
    return errorCorrectionRecursion(code, codeLength, generator, numberOfErrors, enableParityCheck, 0);
}

unsigned long BCH::codeCorrection(unsigned long code, int codeLength, unsigned long generator, int numberOfErrors, bool parity){
    //numberOfErros = the number of errors you want to try to correct (1 == 1 Bit error correction)
    bool enableParityCheck = true;
    return errorCorrectionRecursion(code, codeLength, generator, numberOfErrors, enableParityCheck, parity);
}
