/*
Lib for creating dynamic arrays
*/


#ifndef ARRAYLIST_H
#define ARRAYLIST_H


template <typename T> class ArrayList{


    public:
        ArrayList(T * pointer, int count);
        void add(T data);
        void appendWithArray(ArrayList<T> arrayList);
        void remove(int index);
        void setNewArrayList(ArrayList<T> arrayList);
        struct ArrayListStruct {T * pointer; int count;};
        ArrayListStruct dataStruct;

    private:
        
         
};

#include "ArrayList.tpp"

#endif