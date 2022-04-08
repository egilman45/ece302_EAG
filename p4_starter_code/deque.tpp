//#include "deque.hpp"

// TODO
template <typename T> 
Deque<T>::Deque() {
    linklist.count = 0;
}

template <typename T> 
Deque<T>::~Deque() {
    linklist->clear();
    linklist.count = 0;
}

template <typename T> 
Deque<T>::Deque(const Deque<T>& x) {
    linklist(x);
}
  /** Returns true if the deque is empty, else false
   */
template <typename T> 
bool Deque<T>::isEmpty() const noexcept {
    return (linklist->isEmpty());
};

  /** Add item to the front of the deque
   * may throw std::bad_alloc
   */
template <typename T> 
void Deque<T>::pushFront(const T & item) {
    linklist.insert(1,item);
};

  /** Remove the item at the front of the deque
   * throws std::runtime_error if the deque is empty
   */
template <typename T> 
void Deque<T>::popFront() {
    if(linklist.count == 0) {
        throw(std::runtime_error);
    } else {
        return linklist.remove(0);
    }
};

  /** Returns the item at the front of the deque
   * throws std::runtime_error if the deque is empty
   */
template <typename T> 
T Deque<T>::front() const {
    return linklist.getEntry(0)*;
};

  /** Add item to the back of the deque
   * may throw std::bad_alloc
   */
template <typename T> 
void Deque<T>::pushBack(const T & item) {
    linklist.insert(count, item);
};

  /** Remove the item at the back of the deque
   * throws std::runtime_error if the deque is empty
   */
template <typename T> 
void Deque<T>::popBack() {
    if(linklist.count == 0) {
        throw(std::runtime_error);
    } else {
        linklist.remove(linklist.count);
    }
};

  /** Returns the item at the back of the deque
   * throws std::runtime_error if the deque is empty
   */
template <typename T> 
T Deque<T>::back() const {
    if(linklist.count == 0) {
        throw(std::runtime_error);
    } else {
        return linklist.getEntry(linklist.count);
    }
};
