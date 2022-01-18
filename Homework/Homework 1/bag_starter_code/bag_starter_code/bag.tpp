#include "bag.hpp"
                                                                                                    

template <typename T> Bag<T>::Bag() {

        //Define Vector
        std::vector<int> dataVector;
        
        
}

template <typename T> Bag<T>::~Bag() {}

template <typename T> std::size_t Bag<T>::getCurrentSize() const { 

    //Use vector class function to determine size
    return dataVector.size(); 

}

template <typename T> bool Bag<T>::isEmpty() const { 
    
    //Use vector class function to determine if empty
    return dataVector.empty();
}

template <typename T> bool Bag<T>::add(const T& entry) { 
//Add instance of entry to bag

    int intLength = getCurrentSize();

    dataVector.push_back(entry);

    if (intLength < getCurrentSize()) {
        return true;
    } else {
        return false;
    }
}

template <typename T> bool Bag<T>::remove(const T& entry) { 
//Remove one occurance of the particular entry from bag
    
    int intLength = getCurrentSize();

    for (int i = 0; i < getCurrentSize(); i++) {
       
        if (dataVector[i] == entry){
            dataVector.erase(dataVector.begin() + i);

            if (intLength == getCurrentSize()) {
                return false;
            } else {
                return true;
            }
        }
        
    }

    return false;
}

template <typename T> void Bag<T>::clear() {
    
    //use vector class function to clear all elements
    dataVector.clear();

}

template <typename T> std::size_t Bag<T>::getFrequencyOf(const T& entry) const { 
    
    int counter = 0;

    for (int i = 0; i < getCurrentSize(); i++) {
       
        if (dataVector[i] == entry){
            
            counter++;            
        }
        
    }

    return counter; 
}

template <typename T> bool Bag<T>::contains(const T& entry) const { 
   
   for (int i = 0; i <= getCurrentSize(); i++) {
       
        if (dataVector[i] == entry){
            
            return true;
        }
        
    }

    return false;
   
}

