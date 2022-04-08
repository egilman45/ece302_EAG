#include "image.h"
#include "deque.hpp"
#include <iostream>
#include <vector>

//Prototypes
bool inExplored(int, int);
bool checkEdge(int, Image<Pixel>);

std::vector<std::vector<int>> explored;

int main(int argc, char *argv[])
{
  // TODO

  //Read the file 
  try {

    //frontier = FIFO queue
    Deque<int> frontier;

    //explored = empty set
    std::vector<int> currentSet;
    std::vector<int> temp;
    

    //Create Initial Condition State
    std::vector<int> redLocation;
    int red_count = 0;
    
    //Read the input file pixel information
    Image<Pixel> input = readFromFile(argv[1]); 

    int state = 0;
    bool success = false;

    while (success != true){

      switch (state){
        
        case 0:
        //Initial State

          //Find the Red Pixel 
          for (size_t row = 0; row < input.height(); row++) {
            for (size_t col = 0; col <input.width(); col++){
              if(input(row,col) == RED) {
                red_count++;
                if(red_count > 1){
                  //ERROR more than one starting point
                  return EXIT_FAILURE;
                }
                redLocation.push_back(row);
                redLocation.push_back(col);
                std::cout << "Initial Position: " << row << " " << col << std::endl;
              }
            }
          } 

          //Add Coordinates to Frontier
          //frontier.pushFront(redLocation);
          //frontier.pushFront(redLocation[0]);

          //Send Intial to Goal and Check if Start is Already Finish
          //Change States to Check for Success
          state = 1;

        case 1:
        //Checking for Success

        //If Frontier is Empty Return Failure
        if(frontier.isEmpty() == true) {
           return EXIT_FAILURE;
        }
        
        //Find the New Coordinates From The Frontier
        //Pop coordinates off frontier
        //currentSet = frontier.front();
        frontier.popFront();
        //currentSet[1] = frontier.front();
        //frontier.popFront();

        //Add Coordinates to Explored
        //explored.push_back(currentSet[0]);
        explored.push_back(currentSet);

        //Use currentSet coordinates to see if the Coordinates are Solutions
        if((checkEdge(currentSet[0], input)==true) && (checkEdge(currentSet[1], input)==true)) {
          state = 3;
        } else {
          state = 2;
        }

        case 2:
        //Unsuccessful Try, Assign Next Pixel
        
        if((input(currentSet[0]-1, currentSet[1])==WHITE) && 
          (inExplored(currentSet[0]-1, currentSet[1])==false)){
        //Check Previous Row for Black/White Space 
          temp.push_back(currentSet[0]-1);
          temp.push_back(currentSet[1]); 
          //frontier.pushFront(temp);
        } else if (input(currentSet[0]+1, currentSet[1])==WHITE) {
        //Check Next Row for Black/White Space
          temp.push_back(currentSet[0]+1);
          temp.push_back(currentSet[1]); 
          //frontier.pushFront(temp);
        } else if (input(currentSet[0], currentSet[1]-1)==WHITE) {
        //Check Previous Column for Black/White Space
          temp.push_back(currentSet[0]);
          temp.push_back(currentSet[1]-1); 
          //frontier.pushFront(temp);
        } else if (input(currentSet[0], currentSet[1]+1)==WHITE) {
          //Check New Column for Black/White Space
          temp.push_back(currentSet[0]);
          temp.push_back(currentSet[1]+1); 
          //frontier.pushFront(temp);
        } else{
          return EXIT_FAILURE;
        }

        state = 1;

        case 3:

        //Successful Solution Found
        success = true;

        //Change the coordinates of solution to green
        std::cout << "Change To Green" << std::endl;
        input(currentSet[0], currentSet[1]) = GREEN;

        //Goal Met Create and Write to Output File
        writeToFile(input, argv[2]);

      }
      
    }

  } catch (std::exception &ex) {
    std::cout << "No Solution Found";
    std::cerr << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  std::cout << "Solution Found";
  return EXIT_SUCCESS;

}

bool inExplored(int input1, int input2){

  bool one = false;
  bool two = false;

  for(int i = 0; i < explored.size(); i++) {
    if(input1 == explored[i][0]){
      one = true;
    }
    if(input2 == explored[i][1]) {
      two == false;
    }

    if(one == true && two == true){
      return true;
    }
  }

  return false;
  
}

bool checkEdge(int input1, Image<Pixel> input) {
  if(input1 == 0) {
    return true;
  } else if (input1 == input.height()) {
    return true;
  } else if (input1 == input.width()) {
    return true;
  } else {
    return false;
  }
}