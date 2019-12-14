#include <Arduino.h>
#include <BCH.h>
#include "POCSAG.h"

BCH bch;
POCSAG poc;

void setup() {

  Serial.begin(115200);
  
  size_t heapBeforCreation = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  ArrayList<unsigned long> * pocsagcodeunsecure = poc.tryUnsecureCodeErrorCorrection(0b01111010100010011100000110010001, 5);

  int size = pocsagcodeunsecure->getSize();

  size_t heapAfterCreation = heap_caps_get_free_size(MALLOC_CAP_8BIT);


  //free the memory of the array and the object
  pocsagcodeunsecure->deleteObject();

  size_t heapafterdel = heap_caps_get_free_size(MALLOC_CAP_8BIT);


  size_t allocatedHeapMemory = heapBeforCreation - heapAfterCreation;
  Serial.print("Allocated memory after object creation = ");
  Serial.println(allocatedHeapMemory);

  size_t heapMemoryFreedAfterDeletion = heapafterdel - heapAfterCreation;
  Serial.print("Heap memory freed after deltion of the object = ");
  Serial.println(heapMemoryFreedAfterDeletion);

  size_t heapDifferenz = heapBeforCreation - heapafterdel;
  Serial.print("Heap size difference bevor object creation and after object deletion (lost / leaked memory) = ");
  Serial.println(heapDifferenz);

  Serial.print("Size of the array: ");
  Serial.println(size);


}

void loop() {
  // put your main code here, to run repeatedly:

}