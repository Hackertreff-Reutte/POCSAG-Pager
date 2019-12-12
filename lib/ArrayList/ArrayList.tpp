//#include "ArrayList.h"


template <typename T> ArrayList<T>::ArrayList(T * pointer, int count){
   this->dataStruct.pointer = pointer;
   this->dataStruct.count = count;
}

template <typename T> void ArrayList<T>::add(T data){

   //create a new buffer array
   T * buffer = new T [this->dataStruct.count + 1];
   
   //fill the new array with the existing data
   for(int i = 0; i < this->dataStruct.count; i++){
      buffer[i] = this->dataStruct.pointer[i];
   }

   buffer[this->dataStruct.count] = data;
   delete[] this->dataStruct.pointer;
   this->dataStruct.pointer = buffer;
   this->dataStruct.count++;

}


template <typename T> void ArrayList<T>::appendWithArray(ArrayList<T> arrayList){

   T * buffer = new T [this->dataStruct.count + arrayList.dataStruct.count];

   //copy the first array in the new buffer array
   for(int i = 0; i < this->dataStruct.count; i++){
      buffer[i] = this->dataStruct.pointer[i];
   }

   //copy the content of the second array
   for(int i = 0; i < arrayList.dataStruct.count; i++){
      buffer[this->dataStruct.count + i] = arrayList.dataStruct.pointer[i];
   }

   //delete the old arrays
   delete[] &arrayList;
   delete[] this->dataStruct.pointer;

   //asign the new array
   this->dataStruct.pointer = buffer;

}


template <typename T> void ArrayList<T>::remove(int index){
   //TODO check this function

   //used to remove element from the array
   T * buffer = new T [this->dataStruct.count - 1];

   //add all the elements bevor the index
   for(int i = 0; i < index; i++){
      buffer[i] = this->dataStruct.pointer[i];
   }

   //add all the elements after the index
   for(int i = index; i + 1 < this->dataStruct.count; i++){
      buffer[i] = this->dataStruct.pointer[i+1];
   }

   //delete the old array, add the new array and decrement the counter
   delete[] this->dataStruct.pointer;
   this->dataStruct.count--;
   this->dataStruct.pointer = buffer;
}


template <typename T> void ArrayList<T>::setNewArrayList(ArrayList<T> arrayList){
   delete[] this->dataStruct.pointer;
   this->dataStruct.pointer = arrayList.dataStruct.pointer;
   this->dataStruct.count = arrayList.dataStruct.count;

   //delete the old object
   delete &arrayList;
}

