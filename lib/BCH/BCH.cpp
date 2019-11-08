
#include "stdbool.h"
#include "math.h"
#include "BCH.h"

//0b11101101001 = generator polynom used by pocsag: x^10 + x^9 + x^8 + x^6 + x^5 + x^3 + 1
#define POCSAG_GENERATOR_POLYNOM 0b11101101001
#define POCSAG_DATA_LENGTH 21
#define POCSAG_CODE_LENGTH 31

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

//same as generateCode but used spesific for pocsag code
long BCH::generatePOCSAGCode(long data){
    //POCSAG_GENERATOR = generator polynom: x^10 + x^9 + x^8 + x^6 + x^5 + x^3 + 1
    //POCSAG_DATA_LENGTH = 21 = length of the data
    return generateCode(data, POCSAG_DATA_LENGTH, POCSAG_GENERATOR_POLYNOM);
}

long BCH::codeCorrection(long code, int codeLength, long generator, bool doubleCodeCorrection){

}

bool BCH::checkBCH(long MessagePolynom, int messageLength, long generatorPolynom){

    //return just a placeholder for now
    return true;
}