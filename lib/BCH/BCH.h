/*
Lib for creating BCH codes and checking BCH codes
*/

#ifndef BCH_h
#define BCH_h

class BCH{

    public:
        bool checkBCH(long MessagePolynom, int messageLength, long generatorPolynom);
        long generateCode(long data, int dataLength, long generator);
        long generatePOCSAGCode(long data);
        bool hasCodeErrors(long code, int codeLength, long generator);
        bool hasPOCSAGCodeErrors(long code);
        long codeCorrection(long code, int codeLength, long generator, bool twoBitCodeCorrection);
        long POCSAGCodeCorrection(long code, bool twoBitCodeCorrection);

    private:
        long calculatePolynomialRemainder(long shiftedData, int fullLengthOfCode, long generator);
        int getBinaryLength(long number);
        int getBinaryLength(int number);
        long singleBitCorrection(long code, int codeLength, long generator);
        long twoBitCorrection(long code, int codeLength, long generator);

};


#endif