#include "Arduino.h"
#include "BCH.h"
#include "POCSAG.h"

BCH bch;
POCSAG poc;

void setup() {

  Serial.begin(115200);
  
  //read the free heap memory and store it in heapBeforCreation
  size_t heapBeforCreation = heap_caps_get_free_size(MALLOC_CAP_8BIT);

  //run the error correction and store the pointer to the result in pocsagcodeunsecure
  ArrayList<unsigned long> * pocsagcodeunsecure = poc.tryUnsecureCodeErrorCorrection(0b01111010100010011100000110010001, 4);

  //get the size of the corrected array (number of corrected codes found) and store it in size
  int size = pocsagcodeunsecure->getSize();

  //read the free heap memory after the error correction and store it in heapAfterCreation
  size_t heapAfterCreation = heap_caps_get_free_size(MALLOC_CAP_8BIT);


  //free the memory of the array and the object
  pocsagcodeunsecure->deleteObject();

  //read the free heap memory after the object is deleted and store it in heapAfterDeletion
  size_t heapAfterDeletion = heap_caps_get_free_size(MALLOC_CAP_8BIT);


  //calculate the heap memory that was allocated and print it
  size_t allocatedHeapMemory = heapBeforCreation - heapAfterCreation;
  Serial.print("Allocated memory after object creation = ");
  Serial.println(allocatedHeapMemory);

  //calculate the heap memory that was freed and print it
  size_t heapMemoryFreedAfterDeletion = heapAfterDeletion - heapAfterCreation;
  Serial.print("Heap memory freed after deltion of the object = ");
  Serial.println(heapMemoryFreedAfterDeletion);

  //calculate the leaked memory (free heap memory before the creation minus the free heap memory after the deletion) and print in
  size_t heapDifferenz = heapBeforCreation - heapAfterDeletion;
  Serial.print("Heap size difference bevor object creation and after object deletion (lost / leaked memory) = ");
  Serial.println(heapDifferenz);

  //print the size of the ArrayList (number of the corrected codes found)
  Serial.print("Size of the array: ");
  Serial.println(size);


}

void loop() {
  // put your main code here, to run repeatedly:

}