#include "linked_list.hpp"
#include "Node.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  headPtr = nullptr;
  numItems = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{

}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
  //TODO
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  //TODO
  return *this;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  return (numItems == 0);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const
{
  return numItems;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  //Can you index past something not created yet??
  if(position > getLength()+1) {
    return false;
  }

  Node<int>* currentPtr = headPtr;

  //Traverse to the desired node index in list
  for(int i = 0; i < position; i++) {
    //Get to the node that is position - 1

    while(currentPtr->getNext() != nullptr) {
    //Make sure not at the end

      //Set current pointer to the next pointer
      currentPtr = currentPtr->getNext();
    }
  }

  //Create new pointer to where new node is
  Node<int>* newNodePtr = new Node<T>();
  newNodePtr->setItem(item);

  if(getLength() == 0) {

    //If no other elements set pointer to the head pointer
    headPtr = newNodePtr;

  } else {

    //Create pointer to previous index orginal next
    Node<int>* orgIndexNext = currentPtr->getNext();

    //Set new node next to the previous index orginal next
    newNodePtr->setNext(orgIndexNext);

    //Set previous index next to new node pointer
    currentPtr->setNext(newNodePtr);


    numItems++; //Add to element counter
  }

  return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  //Can you index past something not created yet??
  if(position > getLength()) {
    return false;
  }

  Node<int>* currentPtr = headPtr;

  //Traverse to the desired node index in list
  for(int i = 0; i < position; i++) {
    //Get to the node that is position - 1

    while(currentPtr->getNext() != nullptr) {
    //Make sure not at the end

      //Set current pointer to the next pointer
      currentPtr = currentPtr->getNext();
    }
  }

  if(getLength() == 0) {

    //If no other elements set pointer to the head pointer
    headPtr = nullptr;

  } else {

    //Create pointer to index orginal next
    Node<int>* orgIndexNext = currentPtr->getNext();

    //Set new pointer to next of the index that should be removed
    Node<int>* removeNextPtr = orgIndexNext->getNext();;

    //Set orginal next to skip over 
    currentPtr->setNext(removeNextPtr);

    numItems++; //Add to element counter
  }

  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  //create pointer to clear
  Node<int>* deletePtr = headPtr;

  while(headPtr != nullptr) {
  //Make sure not at end

    //Set head pointer to next
    headPtr = headPtr->getNext();
    //Return to previous and de-link
    deletePtr->setNext(nullptr);
    //Delete pointer used to de-link
    delete deletePtr;
    //Repeat with next position
    deletePtr = headPtr;
  }
  numItems = 0;
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  if(position > getLength()+1) {
    return NULL;
  }

  Node<int>* currentPtr = headPtr;

  //Traverse to the desired node index in list
  for(int i = 0; i <= position; i++) {
    //Get to the node that is position

    while(currentPtr->getNext() != nullptr) {
    //Make sure not at the end

      //Set current pointer to the next pointer
      currentPtr = currentPtr->getNext();
    }
  }
  return currentPtr->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //Does not like this:
  //if(position > getLength()+1) {
  //  return 0;
  //}

  Node<int>* currentPtr = headPtr;

  //Traverse to the desired node index in list
  for(int i = 0; i <= position; i++) {
    //Get to the node that is position

    while(currentPtr->getNext() != nullptr) {
    //Make sure not at the end

      //Set current pointer to the next pointer
      currentPtr = currentPtr->getNext();
    }
  }

  currentPtr->setItem(newValue);
}
