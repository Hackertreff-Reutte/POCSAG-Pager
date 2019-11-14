/*
Lib for creating BCH codes and checking BCH codes
*/

#ifndef BCH_h
#define BCH_h

class BCH{

    public:
        unsigned long generateCode(unsigned long data, int dataLength, unsigned long generator);
        bool hasCodeErrors(unsigned long code, int codeLength, unsigned long generator);
        unsigned long codeCorrection(unsigned long code, int codeLength, unsigned long generator, int numberOfErrors);
        unsigned long codeCorrection(unsigned long code, int codeLength, unsigned long generator, int numberOfErrors, bool parity);

    private:
        unsigned long calculatePolynomialRemainder(unsigned long shiftedData, int fullLengthOfCode, unsigned long generator);
        int getBinaryLength(unsigned long number);
        int getBinaryLength(int number);
        unsigned long singleBitErrorCorrection(unsigned long code, int codeLength, unsigned long generator);
        unsigned long errorCorrectionRecursion(unsigned long code, int codeLength, unsigned long generator, int depth, bool enableParityCheck, bool parity);

};


#endif