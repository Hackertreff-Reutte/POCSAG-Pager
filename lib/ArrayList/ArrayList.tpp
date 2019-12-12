//#include "ArrayList.h"

template <typename T> ArrayList<T>::ArrayList(T * arrayPointer, int size){
   this->dataStruct.arrayPointer = arrayPointer;
   this->dataStruct.size = size;
}

template <typename T> void ArrayList<T>::add(T data){

   //create a new buffer array
   T * buffer = new T [this->dataStruct.size + 1];
   
   //fill the new array with the existing data
   for(int i = 0; i < this->dataStruct.size; i++){
      buffer[i] = this->dataStruct.arrayPointer[i];
   }

   buffer[this->dataStruct.size] = data;
   delete[] this->dataStruct.arrayPointer;
   this->dataStruct.arrayPointer = buffer;
   this->dataStruct.size++;

}


template <typename T> void ArrayList<T>::appendWithArray(ArrayList<T> arrayList){

   T * buffer = new T [this->dataStruct.size + arrayList.getSize()];;  
 
   //copy the first array in the new buffer array
   for(int i = 0; i < this->dataStruct.size; i++){
      buffer[i] = this->dataStruct.arrayPointer[i];
   }

   //copy the content of the second array
   for(int i = 0; i < arrayList.dataStruct.size; i++){
      buffer[this->dataStruct.size + i] = arrayList.getArray()[i];
   }

   //delete the old arrays
   delete[] this->dataStruct.arrayPointer;
   delete[] arrayList.getArray();

   //asign the new array and the new size
   this->dataStruct.arrayPointer = buffer;
   this->dataStruct.size = this->dataStruct.size + arrayList.getSize();

}


template <typename T> void ArrayList<T>::remove(int index){

   //used to remove element from the array
   T * buffer = new T [this->dataStruct.size - 1];

   //add all the elements bevor the index
   for(int i = 0; i < index; i++){
      buffer[i] = this->dataStruct.arrayPointer[i];
   }

   //add all the elements after the index
   for(int i = index; i + 1 < this->dataStruct.size; i++){
      buffer[i] = this->dataStruct.arrayPointer[i+1];
   }

   //delete the old array, add the new array and decrement the size
   delete[] this->dataStruct.arrayPointer;
   this->dataStruct.size--;
   this->dataStruct.arrayPointer = buffer;
}



template <typename T> void ArrayList<T>::setNewArrayList(ArrayList<T> arrayList){
   delete[] this->dataStruct.arrayPointer;
   this->dataStruct.arrayPointer = arrayList.getArray();
   this->dataStruct.size = arrayList.getSize();

   //delete the old object
   delete[] arrayList.dataStruct.arrayPointer;
}

//returns the pointer to the array of the arraylist
template <typename T> T * ArrayList<T>::getArray(){
   return this->dataStruct.arrayPointer;
}

template <typename T> int ArrayList<T>::getSize(){
   return this->dataStruct.size;
}




}

