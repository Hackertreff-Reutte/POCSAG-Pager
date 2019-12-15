# ArrayList LIB

## Info
This lib is used to create ArrayLists (dynamic arrays in c++)


## Structure
 - ArrayList.h -> Headerfile contains all the function definitions of the lib
 - ArrayList.tpp -> contains all related template definition of the functions.


## Dependencies 
none


## Functions

### ArrayList()
```
     ArrayList();
```
Constructor of the object initializes a ArrayList with zero entries.

<br>

### add()
```
void add(T data);
```
This function will add an element to the ArrayList

#### Arguments: 
>__T data__ = the data that is going to be added

<br>

### appendWithArrayList()
```
void appendWithArrayList(ArrayList<T> * arrayList);
```
With this function it is possible to append an existing ArrayList with another ArrayList.

#### Arguments: 
>__ArrayList<T> * arrayList__ = the ArrayList that will be appended

<br>

### remove()
```
void remove(int index);
```
This function will remove an entries of the array at the position index

#### Arguments: 
>__int index__ = the index that defines which element will be removed 

<br>

### setNewArrayList()
```
void setNewArrayList(ArrayList<T> * arrayList);
```
This function will replace the current ArrayList with the given ArrayList.
The other array (old array) will be deleted 

#### Arguments: 
>__ArrayList<T> * arrayList__ = the ArrayList which should be the new ArrayList after this operation

<br>

### getArray()

```
T * getArray();
```
returns the current array of the ArrayList

#### Return value: 
>__T *__ = returns the pointer to the current Array of the ArrayList (T = type of the array)

<br>

### getSize()

```
int getSize();
```
This will return an integer with the current size of the array stored in the ArrayList

#### Return value: 
>__int__ = retuns the current size of the array inside the ArrayList (number of entries in the array)

<br>

### removeDoubleEntries()

```
void removeDoubleEntries();
```
This function will remove all double entries inside the array and only store the unique ones.
This is usefull if you only want unique entries and safe a memory (heap memory).

<br>

### deleteObject()

```
void deleteObject();
```
This function will free the memory of the stored array and also free the memory that was allocated at the creation of the ArrayList object.
This function is imported otherwise memory leaks can occour. 