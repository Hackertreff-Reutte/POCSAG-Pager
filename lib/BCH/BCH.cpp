
#include "BCH.h"




//get the binary length of an number from type int
int BCH::getBinaryLength(int number){
    //uses the long function
    return getBinaryLength((unsigned long) number);
}

//get the binary length of an number from type long
int BCH::getBinaryLength(unsigned long number){

    //special case 0 -> would otherwise return -2147483648
    if(number == 0){
        return 0;
    }
    return (unsigned int) (floor(log2(number)) + 1);
}


//used to calculate the polynomial remainder of a given data binary code and a generator binary code
unsigned long BCH::calculatePolynomialRemainder(unsigned long shiftedData, int fullLengthOfCode, unsigned long generator){

    int generatorLength = getBinaryLength(generator);
    unsigned long remainder =  shiftedData >> (fullLengthOfCode - generatorLength + 1);

    for(int i = fullLengthOfCode - generatorLength + 1; i > 0; i--){

        //append the remainder with the next bit of data from shiftedData
        remainder = (remainder << 1)^((shiftedData >> (i-1))&1);

        //checks if the MSB of the remainder has the same location as the MSB of the generator
        if((remainder >> (generatorLength - 1)&1) == 1){
            //if yes -> XOR them
            remainder = remainder^generator;
        }

    }
    return remainder;
}

//check if the bch code has error 
bool BCH::hasCodeErrors(unsigned long code, int codeLength, unsigned long generator){
    unsigned long remainder = calculatePolynomialRemainder(code, codeLength, generator);

    //if the remainder is zero return false (no errors)
    return remainder != 0;
}




//generate the bch code and add it to the code
unsigned long BCH::generateCode(unsigned long data, int dataLength, unsigned long generator){

    //polynomDegree is the highest polynom in the polynom  (Ex:  x^4 + x^2 + 1 -> polynomDegree = 4)
    int polynomDegree = getBinaryLength(generator) - 1; 

    //the length of the code at the end
    int fullLength = dataLength + polynomDegree;

    unsigned long shiftedData = data << (polynomDegree);

    unsigned long remainder = calculatePolynomialRemainder(shiftedData, fullLength, generator);

    //return the generated code
    return shiftedData^remainder;
}


ArrayList<unsigned long> * BCH::singleBitErrorCorrection(unsigned long code, int codeLength, unsigned long generator){
    unsigned long correctedCode = 0;
    
    //init array List
    ArrayList<unsigned long> * correctedCodeArrayList = new ArrayList<unsigned long>();


    for(int i = -1; i < codeLength; i++){

        correctedCode = code^(1<<i);

        //to check if errors in the code even exists
        if(i == -1){
            correctedCode = code;
        }

        unsigned long remainder = calculatePolynomialRemainder(correctedCode, codeLength, generator);

        if(remainder == 0){
            //add the new found code
            correctedCodeArrayList->add(correctedCode);
        }
    }

    //return the corrected code array if no code is found the array has a length of zero; 
    return correctedCodeArrayList;
}

ArrayList<unsigned long> * BCH::errorCorrectionRecursion(unsigned long code, int codeLength, unsigned long generator, int depth, bool enableParityCheck, int numberOfErrors,  bool parity){

    //init array List 
    ArrayList<unsigned long> * correctedCodeArrayList = new ArrayList<unsigned long>();

    //if zero just to catch some error if someone tries to set the iterations to zero
    if(depth <= 0){
        return correctedCodeArrayList;
    }else if(depth == 1){
        //calculate the single bit error correction
        ArrayList<unsigned long> * singleBitErrorCorrectedCodeArrayList = singleBitErrorCorrection(code, codeLength, generator);

        if(enableParityCheck){
            //make a parity check for each array element
            unsigned long singleBitErrorCorrectedCode;
            unsigned long * buffer = new unsigned long[singleBitErrorCorrectedCodeArrayList->getSize()];

            for(int i = 0; i < singleBitErrorCorrectedCodeArrayList->getSize(); i++){
                singleBitErrorCorrectedCode = singleBitErrorCorrectedCodeArrayList->getArray()[i];

                if(singleBitErrorCorrectedCode % 2 != parity){
                    //same parity (code == okay)
                    //set to 1
                    buffer[i] = 1;
                }else{
                    //wrong parity = wrong corrected code = set 0
                    buffer[i] = 0;
                }
            }
                
            //needs to work from the back to the fronnt otherwise it will fail (array shrinks)
            for(int i = singleBitErrorCorrectedCodeArrayList->getSize() -1; i >= 0; i++){
                //check if buffer array is zero
                if(buffer == 0){
                    //remove the entry
                    singleBitErrorCorrectedCodeArrayList->remove(i);
                }
            }
                
            //delete the buffer array;
            delete[] buffer;
            
            return singleBitErrorCorrectedCodeArrayList;
        }else{
            //return singleBitErrorCorrectedCode without parity check
            return singleBitErrorCorrectedCodeArrayList;
        }

    }else{
        for(int i = -1; i < codeLength; i++){
            unsigned long tempCode = code ^ (1 << i);
            if(i == -1){
                tempCode = code;
            }
            //call the function again and go on iteration deeper and add the conent to the array list
            correctedCodeArrayList->appendWithArray(errorCorrectionRecursion(tempCode, codeLength, generator, depth - 1, enableParityCheck, numberOfErrors, parity));

            //remove the double enties so that it doesn't allocated to much ram otherwise the code will failt (out of memory)
            correctedCodeArrayList.removeDoubleEntries();
        }

        //return the correctedCodeArray
        return correctedCodeArrayList;
    }

    //return ArrayList with count -1 if something goes horribly wrong (should be unreachable code)
    return correctedCodeArrayList;

}


//with this function you can correct up to 2 bit errors. 
ArrayList<unsigned long> * BCH::codeCorrection(unsigned long code, int codeLength, unsigned long generator, int numberOfErrors){
    //numberOfErros = the number of errors you want to try to correct (1 == 1 Bit error correction)
    bool enableParityCheck = false;

    //get the corrected codes
    ArrayList<unsigned long> * resultCorrectedCodeArrayList = errorCorrectionRecursion(code, codeLength, generator, numberOfErrors, enableParityCheck, numberOfErrors, 0);

    //remove all double entries
    resultCorrectedCodeArrayList->removeDoubleEntries();

    //return the code without double entries
    return resultCorrectedCodeArrayList;
}

ArrayList<unsigned long> * BCH::codeCorrection(unsigned long code, int codeLength, unsigned long generator, int numberOfErrors, bool parity){
    //numberOfErros = the number of errors you want to try to correct (1 == 1 Bit error correction)
    bool enableParityCheck = true;

    //get the coorected codes
    ArrayList<unsigned long> * resultCorrectedCodeArrayList = errorCorrectionRecursion(code, codeLength, generator, numberOfErrors, enableParityCheck, numberOfErrors, parity);

    //remove all double entries
    resultCorrectedCodeArrayList->removeDoubleEntries();

    //return the code without double entries
    return resultCorrectedCodeArrayList;
}
