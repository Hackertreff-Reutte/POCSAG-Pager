//ignore error ArrayList is no template it would normaly belong in the 
//header file but i want it sperated


template <typename T> ArrayList<T>::ArrayList(){
   this->dataStruct.arrayPointer = new T[0];
   this->dataStruct.size = 0;
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


template <typename T> void ArrayList<T>::appendWithArrayList(ArrayList<T> * arrayList){

   T * buffer = new T [this->dataStruct.size + arrayList->getSize()];  
 
   //copy the first array in the new buffer array
   for(int i = 0; i < this->dataStruct.size; i++){
      buffer[i] = this->dataStruct.arrayPointer[i];
   }

   //copy the content of the second array
   for(int i = 0; i < arrayList->getSize(); i++){
      buffer[this->dataStruct.size + i] = arrayList->getArray()[i];
   }

   //delete the old array of the current object
   delete[] this->dataStruct.arrayPointer;

   
   //asign the new array and the new size
   this->dataStruct.arrayPointer = buffer;
   this->dataStruct.size = this->dataStruct.size + arrayList->getSize();

   //delete the object that was given as a parameter
   arrayList->deleteObject();

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



template <typename T> void ArrayList<T>::setNewArrayList(ArrayList<T> * arrayList){

   delete[] this->dataStruct.arrayPointer;
   
   this->dataStruct.arrayPointer = arrayList->getArray();
   this->dataStruct.size = arrayList->getSize();

   //delete the old object
   arrayList->deleteObject();
}

//returns the pointer to the array of the arraylist
template <typename T> T * ArrayList<T>::getArray(){
   return this->dataStruct.arrayPointer;
}

template <typename T> int ArrayList<T>::getSize(){
   return this->dataStruct.size;
}




//remove all the double entries from the array
template <typename T> void ArrayList<T>::removeDoubleEntries(){

   T * tagArray = new T [this->dataStruct.size];

   //init tagArray with -1
   for(int i = 0; i < this->dataStruct.size; i++){
      tagArray[i] = -1;
   }

   //check from back to front for each element check if it exist before (infront)
   //if it exists write the current i (index of the outer loop) in the array
   for(int i = this->dataStruct.size - 1; i >= 0; i--){
      for(int j = 0; j < i; j++){
         if(this->dataStruct.arrayPointer[i] == this->dataStruct.arrayPointer[j]){
            tagArray[i] = i;
         }
      }
   }

   //from back to front remove all the flaged double entries
   for(int i = this->dataStruct.size - 1; i >= 0; i--){
      if(tagArray[i] != -1){
         this->remove(i);
      }
   }

   //some cleanup
   delete[] tagArray;

}

//free the memory and delete the object
template <typename T> void ArrayList<T>::deleteObject(){
   delete[] this->getArray();
   delete this;
}