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

	// TESTING
	// for ( int i = 0; i < candidateStringVector.size(); i++ ) { std::cout << candidateStringVector[i] << " "; }
	// std::cout << " | "; 
	// for ( int i = 0; i < currentStringVector.size(); i++ ) { std::cout << currentStringVector[i] << " "; }
	// std::cout << std::endl;

	//Testing if at end of current string at base case 
	if (currentStringVector.size() == 0) {

		//Convert candidate vector to string
		
		
		std::string stringCandidate = "";
		for(int i = 0; i < candidateStringVector.size(); i++){
			stringCandidate = stringCandidate + candidateStringVector[i];
			
		}

		
		//Call function to check if palindrome
		bool isPalindromeBool = isPalindrome(stringCandidate);

		
		//If palindrome add to vector of know palindromes
		
		if (isPalindromeBool == true) {
			//Increment palindrom counter
			possiblePalindromes++;
			
			//Put string into known palindrome
			vectorKnownPalindromes.push_back(stringCandidate);
			
			//Add vector to known palindrome vectors
			vectorVectorPalidromes.push_back(candidateStringVector);
			

		} 

		return;

	}

	//Check for Cut Test 2

	//Define new vectors to split current into
	std::vector<std::string> currentFirstHalf;
	std::vector<std::string> currentLastHalf;

	for (int k = 0; k < (candidateStringVector.size()/2); k++) {
		currentFirstHalf.push_back(candidateStringVector[k]);
	}
	for (int h = (candidateStringVector.size()/2); h < candidateStringVector.size(); h++) {
		currentLastHalf.push_back(candidateStringVector[h]);
	}
	if (cutTest2(currentFirstHalf, currentLastHalf) != true) {
		//Does not pass cut test 2
		return;
	}


	//Start adding words to the candidate vector and begin recursive calls
	for(int j = 0; j < currentStringVector.size(); j++) {
		
		
		//Push first word in current string to candidate string
		candidateStringVector.push_back(currentStringVector[j]);

		//Erase word from current string
		currentStringVector.erase(currentStringVector.begin()+j);

		//Now with new candidate vector do recursive call
		recursiveFindPalindromes(candidateStringVector, currentStringVector);

		//Put moved word back in order in the current string
		currentStringVector.insert(currentStringVector.begin() + j, candidateStringVector[candidateStringVector.size()-1]);

		//Pop back
		candidateStringVector.pop_back();
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
	clear();
}

int FindPalindrome::number() const
{
	return possiblePalindromes;
}

void FindPalindrome::clear()
{
	possiblePalindromes = 0;
	vectorKnownPalindromes.clear();
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

	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	bool returnSuccess = true;
	for(int i = 0; i < stringVector.size(); i++){

			bool success = true;
			std::string value = stringVector[i];

			for(int i = 0; i < value.size(); i++){
				if (value[i] >= 65 && value[i] <= 90) {
					containsCapitalLetter = true;
				} else if (value[i] >= 97 && value[i] <= 122) {
					containsLowerCase = true; 
				} else {
					success = false;
				}
			}

			if (success == false) {
				returnSuccess = false;
			}

	}


	//Check if vector has potential to be palindrome
	if(cutTest1(stringVector) != true) {
		//Does not pass cut test 1, no reason to keep going
		return false;

	}

	//Call recursive function
	std::vector<std::string> candidateStringVector;
	recursiveFindPalindromes(candidateStringVector, stringVector);
	

	return returnSuccess;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return vectorVectorPalidromes;
}

