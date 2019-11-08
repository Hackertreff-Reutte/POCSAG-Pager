/*
Lib for creating BCH codes and checking BCH codes
*/

#ifndef BCH_h
#define BCH_h

class BCH{

    public:
        bool checkBCH(long MessagePolynom, int messageLength, long generatorPolynom);
        int getBinaryLength(int number);
        

    private:
        long polynomialDivision();
        int getBinaryLength(long number);
};


#endif