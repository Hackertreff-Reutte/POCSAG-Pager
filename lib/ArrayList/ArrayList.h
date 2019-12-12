/*
Lib for creating dynamic arrays
*/


#ifndef ARRAYLIST_H
#define ARRAYLIST_H


template <typename T> class ArrayList{


    public:
        ArrayList(T * arrayPointer, int size);
        void add(T data);
        void appendWithArray(ArrayList<T> arrayList);
        void remove(int index);
        void setNewArrayList(ArrayList<T> arrayList);
        T * getArray();
        int getSize();
        void removeDoubleEntries();
        
    private:    
        struct ArrayListStruct {T * arrayPointer; int size;};
        ArrayListStruct dataStruct;
        
         
};

#include "ArrayList.tpp"

#endif