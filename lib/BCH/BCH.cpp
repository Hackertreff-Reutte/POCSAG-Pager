
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


long BCH::polynomialDivision(){

    return 0;
}

bool BCH::checkBCH(long MessagePolynom, int messageLength, long generatorPolynom){

    //return just a placeholder for now
    return true;
}