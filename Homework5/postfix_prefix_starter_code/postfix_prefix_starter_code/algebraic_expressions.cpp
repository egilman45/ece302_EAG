#include <string>
using std::string;

#include <iostream>

#include <stack>

#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(string &postfix, string &prefix) {

  //Check if valid string for postfix before advancing
  if (isPost(postfix)==false) {
    return;
  }

  prefix = "";

  //Declare needed variables 
  std::string element1;
  std::string element2;
  std::string current;
  std::string temp;

  //Create stack to hold the values while sorting
  std::stack<char> theStack;

  for(int i = 0; i<postfix.size(); i++) {
    //std::cout << "Element: " << postfix[i] << std::endl;
   //For the length of the postfix go through loop

    if(isoperator(postfix[i])){
      
      //Check if character is operator
      //std::cout << "Operator Found" << std::endl;

      //Convert Operator to string
      std::string operatorString(1,postfix[i]);

      if(theStack.size()==0) {
       
        current = operatorString + current;

      } else if (theStack.size()==1) {
        
        element1 = theStack.top();
        theStack.pop();

        current = operatorString + current + element1;

      } else {

        //Get two most recent variables
        element1 = theStack.top();
        theStack.pop();
        element2 = theStack.top();
        theStack.pop();
        
        //Make new string with operator and two variables
        current =  current + operatorString + element2 + element1;

        if(theStack.empty()==false){
          for(int i = 0; i < theStack.size(); i++){
            temp = theStack.top();
            theStack.pop();
            current = temp + current;
          }
        }
        
      }
      
    } else {
      //std::cout << "Operand Found" << std::endl;
      theStack.push(postfix[i]);
    } 
    //std::cout << "The Stack: ";
    //for(int h = 0; h < theStack.size(); h++){
    //  std::cout << theStack[h];
    //}

    //std::cout << std::endl << "Prefix Stack: ";
    //for(int h = 0; h < prefixStack.size(); h++){
    //  std::cout << prefixStack[h];
    //}
  }

      prefix = current;

    return;
}
