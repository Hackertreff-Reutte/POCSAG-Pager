
#include "stdbool.h"
#include "math.h"
#include "BCH.h"



//get the binary length of an number from type int
int BCH::getBinaryLength(int number){
    //uses the long function
    return getBinaryLength((long) number);
}

//get the binary length of an number from type long
int BCH::getBinaryLength(long number){

    //special case 0 -> would otherwise return -2147483648
    if(number == 0){
        return 0;
    }
    return (int) (floor(log2(number)) + 1);
}


//used to calculate the polynomial remainder of a given data binary code and a generator binary code
long BCH::calculatePolynomialRemainder(long shiftedData, int fullLengthOfCode, long generator){

    long remainder = 0;
    int generatorLength = getBinaryLength(generator);

    //TODO change endpoint for more efficency
    for(int i = fullLengthOfCode; i > 0; i--){

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
bool BCH::hasCodeErrors(long code, int codeLength, long generator){
    long remainder = calculatePolynomialRemainder(code, codeLength, generator);

    //if the remainder is zero return false (no errors)
    return remainder != 0;
}




//generate the bch code and add it to the code
long BCH::generateCode(long data, int dataLength, long generator){

    //polynomDegree is the highest polynom in the polynom  (Ex:  x^4 + x^2 + 1 -> polynomDegree = 4)
    int polynomDegree = getBinaryLength(generator) - 1; 

    //the length of the code at the end
    int fullLength = dataLength + polynomDegree;

    long shiftedData = data << (polynomDegree);

    long remainder = calculatePolynomialRemainder(shiftedData, fullLength, generator);

    //return the generated code
    return shiftedData^remainder;
}


long BCH::singleBitCodeCorrection(long code, int codeLength, long generator){
    long correctedCode = 0;

    for(int i = -1; i < codeLength; i++){

        correctedCode = code^(1<<i);

        //to check if errors in the code even exists
        if(i == -1){
            correctedCode = code;
        }

        long remainder = calculatePolynomialRemainder(correctedCode, codeLength, generator);

        if(remainder == 0){
            return correctedCode;
        }
    }

    //error correction failed
    return 0;
}

long BCH::twoBitCodeCorrection(long code, int codeLength, long generator){
    long correctedCode = 0;
    long helperCode = 0; //needed for bit shifting

    for(int x = 0; x < codeLength; x++) {
        helperCode = code ^ (1 << x);
        for (int i = -1; i < codeLength; i++) {
            correctedCode = helperCode ^ (1 << i);

            //used for -1 shift
            if (i == -1) {
                correctedCode = helperCode;
            }

            long remainder = calculatePolynomialRemainder(correctedCode, codeLength, generator);
            if (remainder == 0) {
                return correctedCode;
            }
        }
    }
      
    //error corection failed
    return 0;
}


//with this function you can correct up to 2 bit errors. 
long BCH::codeCorrection(long code, int codeLength, long generator, bool twoBitCodeCorrectionEnable){
    long correctedCode = singleBitCodeCorrection(code, codeLength, generator);

    if(twoBitCodeCorrectionEnable == true && correctedCode != code){
        correctedCode = twoBitCodeCorrection(code, codeLength, generator);
    }

    return correctedCode;
}


bool BCH::checkBCH(long MessagePolynom, int messageLength, long generatorPolynom){

    //return just a placeholder for now
    return true;
}