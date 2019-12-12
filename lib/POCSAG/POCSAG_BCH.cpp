
#include "BCH.h"
#include "POCSAG.h"
#include "stdbool.h"

//0b11101101001 = generator polynom used by pocsag: x^10 + x^9 + x^8 + x^6 + x^5 + x^3 + 1
#define POCSAG_GENERATOR_POLYNOM 0b11101101001
#define POCSAG_DATA_LENGTH 21
#define POCSAG_CODE_LENGTH 31


unsigned long POCSAG::calculateAndAddParity(unsigned long code){
    bool parity = code % 2;

    //shift and add parity
    code = (code << 1)^parity;
    return code;
}


//same as hasCodeErrors but only for pocsag
bool POCSAG::hasCodeErrors(unsigned long code){

    //remove parity bit from code
    code = code >> 1;

    return bch.hasCodeErrors(code, POCSAG_CODE_LENGTH, POCSAG_GENERATOR_POLYNOM);
}



//same as generateCode but used spesific for pocsag code
unsigned long POCSAG::generateCodeWithBCH(unsigned long data){
    //POCSAG_GENERATOR = generator polynom: x^10 + x^9 + x^8 + x^6 + x^5 + x^3 + 1
    //POCSAG_DATA_LENGTH = 21 = length of the data
    unsigned long newCode = bch.generateCode(data, POCSAG_DATA_LENGTH, POCSAG_GENERATOR_POLYNOM);

    //Add parity bit and return
    return calculateAndAddParity(newCode);
}

//this function can be used to correct more than 2 error but beware the hamming distance of the pocsag code is only 6 (2 Bit error correction)
//so there is a good chance that you will get a wrong code back 
unsigned long POCSAG::tryUnsecureCodeErrorCorrection(unsigned long code, int numberOfErrors){

    //1 bit shift to remove parity bit
    code = code >> 1;

    unsigned long correctedCode = bch.codeCorrection(code, POCSAG_CODE_LENGTH, POCSAG_GENERATOR_POLYNOM, numberOfErrors);
    
    //Add parity bit and return
    return calculateAndAddParity(correctedCode);
}

unsigned long POCSAG::tryUnsecureCodeErrorCorrection(unsigned long code, int numberOfErrors, bool withParityCheck){
    //get parity bit
    bool parity = code & 0b1;

    //1 bit shift to remove parity bit
    code = code >> 1;

    unsigned long correctedCode = bch.codeCorrection(code, POCSAG_CODE_LENGTH, POCSAG_GENERATOR_POLYNOM, numberOfErrors, parity);

    //Add parity bit and return
    return calculateAndAddParity(correctedCode);
}


unsigned long POCSAG::tryCodeErrorCorrection(unsigned long code, bool twoBitCodeCorrectionEnable){

    //1 bit shift to remove parity bit
    code = code >> 1;

    int numberOfErrors = 1;

    if(twoBitCodeCorrectionEnable == true){
        numberOfErrors = 2;
    }

    unsigned long correctedCode = bch.codeCorrection(code, POCSAG_CODE_LENGTH, POCSAG_GENERATOR_POLYNOM, numberOfErrors);

    //Add parity bit and return
    return calculateAndAddParity(correctedCode);
}