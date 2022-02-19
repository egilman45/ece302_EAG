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
	//std::cout << "Enter Recursive." << std::endl;

	std::string stringCandidate = "";
	for(int i = 0; i < candidateStringVector.size(); i++){
		stringCandidate = stringCandidate + candidateStringVector[i];
		
	}

	// TESTING
	/*
	 std::cout << "Candidate: " << std::endl;
	 for ( int i = 0; i < candidateStringVector.size(); i++ ) { std::cout << candidateStringVector[i] << " "; }
	 std::cout << " | "; 
	 std::cout << "Current: " << std::endl;
	 for ( int i = 0; i < currentStringVector.size(); i++ ) { std::cout << currentStringVector[i] << " "; }
	 std::cout << std::endl;
	*/

	//Testing if at end of current string at base case 
	if (currentStringVector.size() == 0) {

		//std::cout << "ENTER BASE CASE" << std::endl;
	
		//Call function to check if palindrome
		bool isPalindromeBool = isPalindrome(stringCandidate);

		
		//If palindrome add to vector of know palindromes
		
		if (isPalindromeBool == true) {
		
			//Put string into known palindrome
			vectorKnownPalindromes.push_back(stringCandidate);
			
			//Add vector to known palindrome vectors
			vectorVectorPalidromes.push_back(candidateStringVector);

			//Set size
			possiblePalindromes = vectorKnownPalindromes.size();
			

		} 

		//std::cout << "EXIT BASE AND RETURN" << std::endl;

		return;

	}

	//Check for Cut Test 2

	//Define new vectors to split current into
	std::vector<std::string> currentFirstHalf;
	std::vector<std::string> currentLastHalf;

	//std::cout << "IN CUT TEST 2" << std::endl;


	for (int k = 0; k < (candidateStringVector.size()/2); k++) {
		currentFirstHalf.push_back(candidateStringVector[k]);
		//std::cout << candidateStringVector[k];
	}
	for (int h = (candidateStringVector.size()/2); h < candidateStringVector.size(); h++) {
		currentLastHalf.push_back(candidateStringVector[h]);
		//std::cout << candidateStringVector[h] << std::endl;
	}
	if (cutTest2(currentFirstHalf, currentLastHalf) != true) {
		//Does not pass cut test 2
		//std::cout << "FAILS CUT TEST 2" << std::endl;
		//return;
	} 

	//std::cout << "PASSES CUT TEST 2" << std::endl;


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
	
	/*
		std::cout << "CANDIDATE: ";
		for (int k = 0; k < candidateStringVector.size(); k++) {
			std::cout << candidateStringVector[k]; 
		}

		std::cout <<  std::endl << "CURRENT: ";
		for (int h = 0; h < currentStringVector.size(); h++){
			std::cout << currentStringVector[h];
		} 
		std::cout << endl;
	*/

	return;
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	
	//std::cout << "CHECK STRING: " << currentString << std::endl;
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			//std::cout << "RETURN FALSE" << std::endl;
			return false;
		}
	}
	//std::cout << "RETURN TRUE" << std::endl;
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
	return vectorKnownPalindromes.size();
}

void FindPalindrome::clear()
{
	possiblePalindromes = 0;
	currentVector.clear();
	vectorKnownPalindromes.clear();
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	//Define needed variables
	int oddCounter = 0;
	int counter = 0;
	std::string newString;

	//Create string of new vector
	for(int i = 0; i < stringVector.size(); i++){
		newString = newString + stringVector[i];
	}

	convertToLowerCase(newString);

	//std::cout << "Cut Test 1 Testing: " << newString << std::endl;
	
	//Go through all the characters
	for(int j = 0; j < newString.size(); j++) {
		
		//Define char to check each iteration
		char checkChar = newString[j];
		//std::cout << "Checking: " << checkChar << std::endl;

		//Reset counter to zero
		counter = 0;

		//Go through all the characters again and check for repetition
		for(int k = 0; k < newString.size(); k++) {
			//std::cout << k;
			if (checkChar == newString[k]) {
				//std::cout << "Check Against: " << newString[k] << std::endl;
				
				counter++;
				
				//std::cout << "Counter: " << counter << std::endl;
			}
		}

		//If appears odd number of times
		if(counter % 2 != 0) {
			oddCounter++;
		}

		if(oddCounter > 1) {
			//std::cout << "Cut Test 1 Return False" << std::endl;
			return false;
		}
	}

	//std::cout << "Cut Test 1 Return True" << std::endl;
	
	return true;
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{

	//Declare needed variables
	std::vector<std::string> biggerVector;
	std::vector<std::string> smallerVector;
	std::string smallerVectorString;
	std::string biggerVectorString;

	int counter = 0;

	//Determine which of the enteries is bigger
	if(stringVector1.size()>stringVector2.size()) {
		biggerVector = stringVector1;
		smallerVector = stringVector2;
	} else {
		biggerVector = stringVector2;
		smallerVector = stringVector1;
	}

	
	//Create String of Smaller Vector
	for(int y = 0; y < smallerVector.size(); y++){
		smallerVectorString = smallerVectorString + smallerVector[y];
	}

	convertToLowerCase(smallerVectorString);

	//Create String of Larger Vector
	for(int z = 0; z < biggerVector.size(); z++){
		biggerVectorString = biggerVectorString + biggerVector[z];
	}

	convertToLowerCase(biggerVectorString);

	//std::cout << "Cut Test 2 Testing: " << smallerVectorString << biggerVectorString << std::endl;

	int hold = 0;

	//Go through all the characters in the smaller string
	for(int j = 0; j < smallerVectorString.size(); j++) {
		
		//Create char varaible of the smaller string to check
		char checkChar = smallerVectorString[j];

		//Counter to see if any chars aren't found
		//should not be zero to pass test
		counter = 0;

		//Go through the bigger string and see if the char
		//in the small is found in the bigger one
		for(int k = 0; k < biggerVectorString.size(); k++) {
			if (checkChar == biggerVectorString[k]) {
				hold = k;
				counter++;
			}
		}

		//Erase the found letter, for duplicates must find another
		biggerVectorString.erase(hold);

		//If counter is still zero, char was not found so fails
		if(counter == 0) {
			return false;
		}
	}

	return true;
}

bool FindPalindrome::add(const string & value)
{
	std::string temp;
	std::string valueTemp = value;
	convertToLowerCase(valueTemp);

	possiblePalindromes = 0;
	for(int i = 0; i < value.size(); i++){
		if (value[i] >= 65 && value[i] <= 90) {
			containsCapitalLetter = true;
		} else if (value[i] >= 97 && value[i] <= 122) {
			containsLowerCase = true; 
		} else {
			return false;
		}
	}

	//Check for duplicates in the vector
	for(int k = 0; k < currentVector.size(); k++){
		temp = currentVector[k];
		convertToLowerCase(temp);
		if(valueTemp == temp){
			return false;
		}
	}

	//std::cout << "Add value " << value << " to current." << std::endl;
	currentVector.push_back(value);

	//for(int i = 0; i < currentVector.size(); i++) {
	//	std::cout << currentVector[i];
	//}
	//std::cout << std::endl;

	//Check if vector has potential to be palindrome
	if(cutTest1(currentVector) == true) {
		//std::cout << "Pass Cut Test 1." << std::endl;
		//Does not pass cut test 1, no reason to keep going
		possiblePalindromes = 0;
		vectorVectorPalidromes.clear();
		vectorKnownPalindromes.clear();

		//Call recursive function
		//std::cout << "Call Recursive." << std::endl;
		std::vector<std::string> candidateStringVector;
		recursiveFindPalindromes(candidateStringVector, currentVector);

			/*std::cout << "KNOWN PALINDROMES: ";
			for(int f = 0; f < vectorKnownPalindromes.size(); f++){
				std::cout << vectorKnownPalindromes[f] << " ";
			}
			std::cout << std::endl;*/

	} else {
		//std::cout << "Cut Test 1 Failed." << std::endl;
	}
	

	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	possiblePalindromes = 0;
	int repCounter = 0;
	std::string temp;

	for(int i = 0; i < stringVector.size(); i++){

			bool success = true;
			std::string value = stringVector[i];
			convertToLowerCase(value);

			//Check for duplicates in the current vector
			for(int k = 0; k < currentVector.size(); k++){
				//std::cout << "Value: " << value << std::endl;
				//std::cout << "Check Against: " << currentVector[k] << std::endl;
				
				if(value == currentVector[k]){
					//std::cout << "Return False." << std::endl;
					return false;
				}
			}
			
			repCounter = 0;

			//Check for duplicates in the given vector
			for(int q = 0; q < stringVector.size(); q++){
				temp = stringVector[q];
				convertToLowerCase(temp);
				if(q != i) {
					//std::cout << "Value: " << value << std::endl;
					//std::cout << "Check Against: " << temp << std::endl;
					if(value == temp){
						repCounter++;
					}
				}
			}
			if(repCounter > 0) {
				//std::cout << "DUPLICATE" << std::endl;
				return false;
			}

			for(int i = 0; i < value.size(); i++){
				if (value[i] >= 65 && value[i] <= 90) {
					containsCapitalLetter = true;
				} else if (value[i] >= 97 && value[i] <= 122) {
					containsLowerCase = true; 
				} else {
					return false;
				}
			}

	}

	for(int i = 0; i < stringVector.size(); i++) {
		//std::cout << "Add value " << stringVector[i] << " to current." << std::endl;
		currentVector.push_back(stringVector[i]);
	}

	//Check if vector has potential to be palindrome
	if(cutTest1(currentVector) == true) {
		//std::cout << "Pass Cut Test 1." << std::endl;
		//Does not pass cut test 1, no reason to keep going
		possiblePalindromes = 0;
		vectorVectorPalidromes.clear();
		vectorKnownPalindromes.clear();

		//Call recursive function
		//std::cout << "Call Recursive." << std::endl;
		std::vector<std::string> candidateStringVector;
		recursiveFindPalindromes(candidateStringVector, currentVector);

		/*std::cout << "KNOWN PALINDROMES: ";
			for(int f = 0; f < vectorKnownPalindromes.size(); f++){
				std::cout << vectorKnownPalindromes[f] << " ";
			}
		std::cout << std::endl; */

	} else {
		//std::cout << "Cut Test 1 Failed." << std::endl;
	}
	
	/*std::cout << "KNOWN PALINDROMES: ";
	for(int f = 0; f < vectorKnownPalindromes.size(); f++){
		std::cout << vectorKnownPalindromes[f] << " ";
	}
	std::cout << std::endl; */

	return true;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return vectorVectorPalidromes;
}

