
#include "BCH.h"
#include "POCSAG.h"
#include "stdbool.h"


//0b11101101001 = generator polynom used by pocsag: x^10 + x^9 + x^8 + x^6 + x^5 + x^3 + 1
#define POCSAG_GENERATOR_POLYNOM 0b11101101001
#define POCSAG_DATA_LENGTH 21
#define POCSAG_CODE_LENGTH 31



//same as hasCodeErrors but only for pocsag
bool POCSAG::hasCodeErrors(long code){
    return bch.hasCodeErrors(code, POCSAG_CODE_LENGTH, POCSAG_GENERATOR_POLYNOM);
}



//same as generateCode but used spesific for pocsag code
long POCSAG::generateCodeWithBCH(long data){
    //POCSAG_GENERATOR = generator polynom: x^10 + x^9 + x^8 + x^6 + x^5 + x^3 + 1
    //POCSAG_DATA_LENGTH = 21 = length of the data
    return bch.generateCode(data, POCSAG_DATA_LENGTH, POCSAG_GENERATOR_POLYNOM);
}

//this function can be used to correct more than 2 error but beware the hamming distance of the pocsag code is only 6 (2 Bit error correction)
//so there is a good chance that you will get a wrong code back 
long POCSAG::tryUnsecureCodeErrorCorrection(long code, int numberOfErrors){
    return bch.codeCorrection(code, POCSAG_CODE_LENGTH, POCSAG_GENERATOR_POLYNOM, numberOfErrors);
}


long POCSAG::tryCodeErrorCorrection(long code, bool twoBitCodeCorrectionEnable){

    int numberOfErrors = 1;

    if(twoBitCodeCorrectionEnable == true){
        numberOfErrors = 2;
    }

    return bch.codeCorrection(code, POCSAG_CODE_LENGTH, POCSAG_GENERATOR_POLYNOM, numberOfErrors);
}