/*
Lib for creating BCH codes and checking BCH codes
*/

#ifndef BCH_h
#define BCH_h

class BCH{

    public:
        long generateCode(long data, int dataLength, long generator);
        bool hasCodeErrors(long code, int codeLength, long generator);
        long codeCorrection(long code, int codeLength, long generator, int numberOfErrors);
        long codeCorrection(long code, int codeLength, long generator, int numberOfErrors, bool parity);

    private:
        long calculatePolynomialRemainder(long shiftedData, int fullLengthOfCode, long generator);
        int getBinaryLength(long number);
        int getBinaryLength(int number);
        long singleBitErrorCorrection(long code, int codeLength, long generator);
        long errorCorrectionRecursion(long code, int codeLength, long generator, int depth, bool enableParityCheck, bool parity);

};


#endif