/*
Lib for creating and managing pocsag messages
*/

#ifndef POCSAG_h
#define POCSAG_h

class POCSAG{

    public:
        bool hasCodeErrors(unsigned long code);
        unsigned long generateCodeWithBCH(unsigned long data);
        unsigned long tryCodeErrorCorrection(unsigned long code, bool twoBitCodeCorrectionEnable);
        unsigned long tryUnsecureCodeErrorCorrection(unsigned long code, int numberOfErrors);
        unsigned long tryUnsecureCodeErrorCorrection(unsigned long code, int numberOfErrors, bool withParityCheck);

    private:
        unsigned long calculateAndAddParity(unsigned long code);
        BCH bch;

};


#endif