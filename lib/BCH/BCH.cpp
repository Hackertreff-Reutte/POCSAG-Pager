
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


unsigned long * BCH::singleBitErrorCorrection(unsigned long code, int codeLength, unsigned long generator){
    unsigned long correctedCode = 0;
    unsigned long* correctedCodeArray = new unsigned long[0];

    for(int i = -1; i < codeLength; i++){

        correctedCode = code^(1<<i);

        //to check if errors in the code even exists
        if(i == -1){
            correctedCode = code;
        }

        unsigned long remainder = calculatePolynomialRemainder(correctedCode, codeLength, generator);

        if(remainder == 0){
            //create a by 1 bigger array
            unsigned long* bufferArray = new unsigned long[sizeof(correctedCodeArray) + 1];
            //copy the data from the "old" array to the buffer array
            for(int j = 0; j < sizeof(correctedCodeArray); j++){
                bufferArray[j] = correctedCodeArray[j];
            }
            //add the new entry to the buffer array
            bufferArray[sizeof(correctedCodeArray)] = correctedCode;
            //delelte the old array
            delete[] correctedCodeArray;
            //change the old array address to the new array
            correctedCodeArray = bufferArray;
        }
    }

    //return the corrected code array if no code is found the array has a length of zero; 
    return correctedCodeArray;
}

unsigned long * BCH::errorCorrectionRecursion(unsigned long code, int codeLength, unsigned long generator, int depth, bool enableParityCheck, bool parity){

    //define the correctedCodeArray globaly so that it can be retuned later on;
    unsigned long * correctedCodeArray = nullptr;

    //if zero just to catch some error if someone tries to set the iterations to zero
    if(depth <= 0){
        return nullptr;
    }else if(depth == 1){
        //calculate the single bit error correction
        unsigned long* singleBitErrorCorrectedCodeArray = singleBitErrorCorrection(code, codeLength, generator);

        if(enableParityCheck){
            //make a parity check for each array element
            unsigned long singleBitErrorCorrectedCode;
            int sizeOfNewArray = 0;
            for(int i = 0; i < sizeof(singleBitErrorCorrectedCodeArray); i++){
                singleBitErrorCorrectedCode = singleBitErrorCorrectedCodeArray[i];

                if(singleBitErrorCorrectedCode % 2 == parity){
                    //same parity (code == okay)
                    //increase the counter for the size of the new array
                    sizeOfNewArray++;
                }else{
                    //wrong parity = wrong corrected code = set 0
                    singleBitErrorCorrectedCodeArray[i] = 0;
                }

                //build a new array with only the accepted codes
                unsigned long* bufferArray = new unsigned long[sizeOfNewArray];
                //fill the new array
                int indexCounter = 0;
                for(int j = 0; j < sizeof(singleBitErrorCorrectedCodeArray); j++){
                    if(singleBitErrorCorrectedCodeArray[j] != 0){
                        bufferArray[indexCounter] = singleBitErrorCorrectedCodeArray[j];
                        indexCounter++;
                    }
                }
                
                //delete the old array
                delete[] singleBitErrorCorrectedCodeArray;
                //change the old array address to the new array
                singleBitErrorCorrectedCodeArray = bufferArray;
            }
            return singleBitErrorCorrectedCodeArray;
        }else{
            //return singleBitErrorCorrectedCode without parity check
            return singleBitErrorCorrectedCodeArray;
        }

    }else{
        for(int i = -1; i < codeLength; i++){
            unsigned long tempCode = code ^ (1 << i);
            if(i == -1){
                tempCode = code;
            }
            //call the function again and go on iteration deeper
            correctedCodeArray = errorCorrectionRecursion(tempCode, codeLength, generator, depth - 1, enableParityCheck, parity);
        }

        //return the correctedCodeArray
        return correctedCodeArray;
    }

    //return nullptr if something goes horribly wrong (should be unreachable code)
    return nullptr;    

}


//with this function you can correct up to 2 bit errors. 
unsigned long * BCH::codeCorrection(unsigned long code, int codeLength, unsigned long generator, int numberOfErrors){
    //numberOfErros = the number of errors you want to try to correct (1 == 1 Bit error correction)
    bool enableParityCheck = false;
    return errorCorrectionRecursion(code, codeLength, generator, numberOfErrors, enableParityCheck, 0);
}

unsigned long * BCH::codeCorrection(unsigned long code, int codeLength, unsigned long generator, int numberOfErrors, bool parity){
    //numberOfErros = the number of errors you want to try to correct (1 == 1 Bit error correction)
    bool enableParityCheck = true;
    return errorCorrectionRecursion(code, codeLength, generator, numberOfErrors, enableParityCheck, parity);
}
