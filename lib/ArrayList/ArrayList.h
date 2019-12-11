/*
Lib for creating dynamic arrays
*/

#ifndef ArrayList_H
#define ArrayList_H

template <class T> class ArrayList{

    public:
        ArrayList(T * pointer, int count);

    private:
        struct ArrayListStruct {T * pointer; int count;};
        ArrayListStruct dataStruct;
         
};


#endif