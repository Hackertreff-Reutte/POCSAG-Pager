
#include "stdbool.h"
#include "math.h"
#include "BCH.h"


//get the binary length of an number from type long
int BCH::getBinaryLength(int number){
    return floor(log2(number)) + 1;
}

//get the binary length of an number from type long
int BCH::getBinaryLength(long number){
    return (int) (floor(log2(number)) + 1);
}


long BCH::polynomialDivision(){

    return 0;
}

bool BCH::checkBCH(long MessagePolynom, int messageLength, long generatorPolynom){

    //return just a placeholder for now
    return true;
}