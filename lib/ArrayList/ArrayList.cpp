#include "ArrayList.h"


template <typename T> ArrayList<T>::ArrayList(T * pointer, int count){
   this->dataStruct.pointer = pointer;
   this->dataStruct.count = count;
}