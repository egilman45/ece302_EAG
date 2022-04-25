#include "frontier_queue.hpp"
#include <math.h>
#include <iostream>

// TODO implement the member functions here

//Traversing Notes:
// 2 * level --> child
// level / 2 --> parent
// level * 2 + 1 --> left child
// level * 2 + 2 --> right child
// height log2(n)

template <typename T>
State<T> frontier_queue<T>::pop() {

  //TODO

  //Remove Root
  State<T> lowestCost = queue.front();

  //Replace with Last Node
  queue[0] = queue.front();

  //Delete Last Node Moved to the Root
  queue.pop_back();


  //Exchange Nodes with largest child as much as possible
  
  //Define relative parent and child locations
  int parent_loc = 0;
  int left_child_loc = 1;
  int right_child_loc = 2;
  
  for (int i = 0; i < queue.size()-1; i++) {
    
    if(queue[parent_loc].getFCost() > queue[right_child_loc].getFCost()){
      State<T> temp = queue[right_child_loc];
      queue[right_child_loc] = queue[parent_loc];
      queue[parent_loc] = temp;
    }
    parent_loc = parent_loc + 1;
    left_child_loc = left_child_loc + 1;
    right_child_loc = right_child_loc + 1;

  }

  // needs return statement
  return lowestCost;

}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {

  //TODO
  //Create new state from inputs
  State<T> pushState(p, cost, heur);

  //Add the node to the next empty spot in the structure
  queue.push_back(pushState);

  //Bubble up exchanging with parent if it is larger than the parent
  int parent_loc = 0;
  int left_child_loc = 1;
  int right_child_loc = 2;

  for (int i = 0; i < queue.size()-1; i++) {
    
    if(queue[parent_loc].getFCost() > queue[right_child_loc].getFCost()){
      State<T> temp = queue[right_child_loc];
      queue[right_child_loc] = queue[parent_loc];
      queue[parent_loc] = temp;
    }
    parent_loc = parent_loc + 1;
    left_child_loc = left_child_loc + 1;
    right_child_loc = right_child_loc + 1;

  }

}

template <typename T>
bool frontier_queue<T>::empty() {

  if(queue.size() == 0){
    return true;
  } else {
    return false;
  }

}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) {

  for(int i = 0; i < queue.size()-1; i++){
    if(queue[i].getValue()== p){
      return true;
    }
  }

  return false; 

}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {

  for(int i = 0; i < queue.size() - 1; i++){ 
    //if p is the same as any value, compare cost
    if(p == queue[i].getValue()) {
      //Check and update the cost of p if needed
      if(queue[i].getFCost() > cost){
        queue[i].updatePathCost(cost);
      }
    }
    
  }

}


