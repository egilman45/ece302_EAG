#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}
}

static void removeSpaces(string & value) {
	for (int i = 0; i < value.size(); i ++) {
		if(value[i] == ' ') {
			value.erase(value.begin()+i);
		}
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
	// TODO need to implement this recursive function!
	if(cutTest1(const vector<string> & stringVector) != true) {
		//Does not pass cut test 1

	}
	
	return;
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	removeSpaces(currentString);


	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	possiblePalindromes = 0;

}

FindPalindrome::~FindPalindrome()
{
	// TODO need to implement this...
}

int FindPalindrome::number() const
{
	// TODO need to implement this...
	return 10;
}

void FindPalindrome::clear()
{
	vectorPalidromes.clear();
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	int oddCounter = 0;
	int counter = 0;
	std::string newString;

	for(int i = 0; i < stringVector.size(); i++){
		newString = newString + stringVector[i];
	}
	
	for(int j = 0; j < newString.size(); j++) {
		char checkChar = newString[j];
		counter = 0;
		for(int k = 0; k < newString.size(); k++) {
			if (checkChar == newString[k]) {
				counter++;
			}
		}
		if(counter % 2 != 0) {
			oddCounter++;
		}

		if(oddCounter > 1) {
			return false;
		}
	}
	
	return true;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{

	std::vector<std::string> biggerVector;
	std::vector<std::string> smallerVector;
	std::string smallerVectorString;
	std::string biggerVectorString;
	int counter = 0;

	if(stringVector1.size()>stringVector2.size()) {
		biggerVector = stringVector1;
		smallerVector = stringVector2;
	} else {
		biggerVector = stringVector2;
		smallerVector = stringVector1;
	}

	

	for(int y = 0; y < smallerVector.size(); y++){
		smallerVectorString = smallerVectorString + smallerVector[y];
	}

	for(int z = 0; z < smallerVector.size(); z++){
		biggerVectorString = biggerVectorString + biggerVector[z];
	}

	for(int j = 0; j < smallerVectorString.size(); j++) {
		char checkChar = smallerVectorString[j];
		counter = 0;
		for(int k = 0; k < biggerVectorString.size(); k++) {
			if (checkChar == biggerVectorString[k]) {
				counter++;
			}
		}
		if(counter == 0) {
			return false;
		}
	}

	return true;
}

bool FindPalindrome::add(const string & value)
{
	for(int i = 0; i < value.size(); i++){
		if (value[i] >= 65 && value[i] <= 90) {
			containsCapitalLetter = true;
		} else if (value[i] >= 97 && value[i] <= 122) {
			containsLowerCase = true; 
		} else {
			return false;
		}
	}

	vectorPalidromes.push_back(value);
	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	bool returnSuccess = true;
	for(int i = 0; i < stringVector.size(); i++){

			bool success = add(stringVector[i]);

			if (success == false) {
				returnSuccess = false;
			}

	}

	return returnSuccess;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	// TODO need to implement this...
	vector<vector<string>> returnThingie;
	return returnThingie;
}

