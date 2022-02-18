#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method


TEST_CASE( "Test FindPalindrome add a non-allowable word")
{
	INFO("Hint: add a single non-allowable word");
	FindPalindrome b;
	//Test special characters get rejected
	REQUIRE(!b.add("kayak1"));
	REQUIRE(b.add("$0 COOL")==false);
	std::vector<std::string> strings = {"he110", "c00l", "hello"};
	REQUIRE(b.add(strings)==false);
}

TEST_CASE("Testing adding valid word to vector") {

	FindPalindrome b;
	REQUIRE(b.add("hello"));
	REQUIRE(b.add("abba"));
	std::vector<std::string> strings = {"he11o", "hey there", "bye"};
	REQUIRE(b.add(strings)==false);
	
}



TEST_CASE("Cut-Test 1") {
	FindPalindrome b;
	std::vector<std::string> stringsVector = {"haha", "baba", "bae"};
	REQUIRE(b.cutTest1(stringsVector) == false);

	stringsVector = {"haha", "baba", "bahe"};
	REQUIRE(b.cutTest1(stringsVector) == false);

	stringsVector = {"haha", "haha", "haha"};
	REQUIRE(b.cutTest1(stringsVector) == true);

	stringsVector = {"race", "car", "race" "car"};
	REQUIRE(b.cutTest1(stringsVector) == true);

	stringsVector = {"banana", "banana", "banana"};
	REQUIRE(b.cutTest1(stringsVector) == false);

	stringsVector = {"bannab"};
	REQUIRE(b.cutTest1(stringsVector) == true);

	stringsVector = {"hey", "there", "whatsup"};
	REQUIRE(b.cutTest1(stringsVector) == false);
}



TEST_CASE("Cut-Test 2") {
	FindPalindrome b;
	std::vector<std::string> stringsVector1 = {"race", "car", "race"};
	std::vector<std::string> stringsVector2 = {"car"};
	REQUIRE(b.cutTest2(stringsVector1, stringsVector2) == true);

	stringsVector1 = {"anna", "banna", "anna"};
	stringsVector2 = {"anna", "anna"};
	REQUIRE(b.cutTest2(stringsVector1, stringsVector2) == true);

	stringsVector1 = {"fdsa", "kjhg", "rewq"};
	stringsVector2 = {"kjhg", "rewq"};
	REQUIRE(b.cutTest2(stringsVector1, stringsVector2) == false);

	stringsVector1 = {"qw", "er", "ty", "jk"};
	stringsVector2 = {"rw", "ky", "tq"};
	REQUIRE(b.cutTest2(stringsVector1, stringsVector2) == false);

	stringsVector1 = {"hello", "begone", "bye"};
	stringsVector2 = {"howdy", "hello", "goodbye"};
	REQUIRE(b.cutTest2(stringsVector1, stringsVector2) == false);

}


TEST_CASE("Test Clear Funciton") {

	FindPalindrome b;
	std::vector<std::string> vectorWords = {"hannah"};
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==1);
	b.clear();
	REQUIRE(b.number()==0);

	vectorWords = {"Was", "it", "acar", "or", "a", "cat", "I", "saw"};
	REQUIRE(b.cutTest1(vectorWords));
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==2);
	b.clear();
	REQUIRE(b.number()==0);

}


TEST_CASE("Test Add String Function") {

	FindPalindrome b;
	std::vector<std::string> vectorWords = {"h", "e", "h"};
	REQUIRE(b.add(vectorWords)==false);
	vectorWords = {"be", "eb", "pp"};
	REQUIRE(b.cutTest1(vectorWords));
	REQUIRE(b.add(vectorWords));
	REQUIRE((b.number())==2);
	b.clear();
	vectorWords = {"race", "car"};
	REQUIRE(b.cutTest1(vectorWords));
	REQUIRE(b.add(vectorWords));
	REQUIRE((b.number())==1);
	vectorWords = {"race", "car", };
	REQUIRE(b.add(vectorWords)==false);


}

TEST_CASE("Test Add Vector Function") {

	FindPalindrome b;
	std::vector<std::string> vectorWords = {"hannah", "hannah"};
	REQUIRE(b.add(vectorWords)==false);

	vectorWords = {"a", "AA", "AaA"};
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==6);
	b.clear();

	vectorWords = {"A", "nut", "for", "a", "jar", "of", "tuna"};
	REQUIRE(b.cutTest1(vectorWords));
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==4);
	b.clear();

	vectorWords = {"Murder", "for", "a", "jar", "of"};
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==0);
	vectorWords = {"red", "rum"};
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==2);
	b.clear();

}

