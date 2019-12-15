/*
Lib for creating dynamic arrays
*/


#ifndef ARRAYLIST_H
#define ARRAYLIST_H


template <typename T> class ArrayList{


    public:
        ArrayList();
        void add(T data);
        void appendWithArrayList(ArrayList<T> * arrayList);
        void remove(int index);
        void setNewArrayList(ArrayList<T> * arrayList);
        T * getArray();
        int getSize();
        void removeDoubleEntries();
        void deleteObject();
        
    private:    
        typedef struct ArrayListStruct {T * arrayPointer; int size;} ArrayListStruct;
        ArrayListStruct dataStruct;
        
         
};

//include the rest of the template
#include "ArrayList.tpp"

#endif