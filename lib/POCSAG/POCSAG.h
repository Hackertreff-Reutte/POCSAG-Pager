/*
Lib for creating and managing pocsag messages
*/

#ifndef POCSAG_h
#define POCSAG_h

class POCSAG{

    public:
    bool hasCodeErrors(long code);
    long generateCodeWithBCH(long data);
    long tryCodeErrorCorrection(long code, bool twoBitCodeCorrectionEnable);
    long tryUnsecureCodeErrorCorrection(long code, int numberOfErrors);

    private:
        

};


#endif