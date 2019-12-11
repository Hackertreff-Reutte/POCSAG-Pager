/*
Lib for creating dynamic arrays
*/


#ifndef ArrayList_H
#define ArrayList_H

//include the file for the return types
template <class T> class ArrayList{


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


#endif