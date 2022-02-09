#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList() {
  sizeArray = 0;
  dynamicArray = new int[sizeArray];
}

template <typename T>
ArrayList<T>::~ArrayList() {
  delete [] dynamicArray;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList & rhs){}

template <typename T>
ArrayList<T> & ArrayList<T>::operator=(const ArrayList & rhs){
  return *this;
}

template <typename T>
bool ArrayList<T>::isEmpty() const{
  return (getLength()==false);
}

template <typename T>
std::size_t ArrayList<T>::getLength() const{
  return sizeArray;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){

  //Store the current values of the dynamic array in temporary array
  int temp[sizeArray];
  for (int k = 0; k  = sizeArray; k++) {
    temp[k] = dynamicArray[k];
  }

  //Delete the allocated memory and data in array
  delete [] dynamicArray;

  //Increase the size of array
  sizeArray = sizeArray + 1;

  //Allocate new memory for new sized array
  dynamicArray = new int[sizeArray];


  //Iterate through and put all the values before the index back
  for (int i = 0; i < position; i++) {
      dynamicArray[i] = temp[i]; 
  }

  //Set desired index to desired value
  dynamicArray[position] = item;

  //Set the rest of array to remaining values in orginal array
  for (int j = position+1; j < sizeArray; j++) {
    dynamicArray[j] = temp[j-1];
  }

  return true;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position){
  
  //Store the current values of the dynamic array in temporary array
  int temp[sizeArray];
  for (int k = 0; k  = sizeArray; k++) {
    temp[k] = dynamicArray[k];
  }
  

  //Delete the allocated memory and data in array
  delete [] dynamicArray;

  //Decrease the size of array
  sizeArray = sizeArray - 1;

  //Allocate new memory for new sized array
  dynamicArray = new int[sizeArray];


  //Iterate through and put all the values before the index back
  for (int i = 0; i < position; i++) {
      dynamicArray[i] = temp[i]; 
  }

  //Jump the value at position that should be deleted
  for (int j = position; j < sizeArray; j++) {
      dynamicArray[j] = temp[j+1];
  }
  
  return true;
}

template <typename T>
void ArrayList<T>::clear() {

  //Delete memory allocation for array
  delete [] dynamicArray;
  sizeArray = 0;

}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
  return dynamicArray[position];
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
  dynamicArray[position] = newValue;
}
