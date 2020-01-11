/*
Lib for creating and managing pocsag messages
*/

#ifndef POCSAG_h
#define POCSAG_h



#include "ArrayList.h"
#include "BCH.h"
#include "stdbool.h"

class POCSAG{

    

    public:
        bool hasCodeErrors(unsigned long code);
        unsigned long generateCodeWithBCH(unsigned long data);
        ArrayList<unsigned long> * tryCodeErrorCorrection(unsigned long code, bool twoBitCodeCorrectionEnable);
        ArrayList<unsigned long> * tryCodeErrorCorrection(unsigned long code, bool twoBitCodeCorrectionEnable, bool withParityCheck);
        ArrayList<unsigned long> * tryUnsecureCodeErrorCorrection(unsigned long code, int numberOfErrors);
        ArrayList<unsigned long> * tryUnsecureCodeErrorCorrection(unsigned long code, int numberOfErrors, bool withParityCheck);

    private:
        unsigned long calculateAndAddParity(unsigned long code);
        ArrayList<unsigned long> * calculateAndAddParityToArray(ArrayList<unsigned long> * codeArrayList);
        BCH bch;

};


#endif