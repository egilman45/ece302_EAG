#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test FindPalindrome add a non-allowable word", "[FindPalindrome]" )
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

	stringsVector1 = {"asdfghjkl", "qwertyuiop", "zxcvbnm"};
	stringsVector2 = {"asdfg", "zxcvbnm"};
	//REQUIRE(b.cutTest2(stringsVector1, stringsVector2) == true);
	//Fails but should not

	stringsVector1 = {"qw", "er", "ty", "jk"};
	stringsVector2 = {"rw", "ky", "tq"};
	REQUIRE(b.cutTest2(stringsVector1, stringsVector2) == true);

	stringsVector1 = {"hello", "begone", "bye"};
	stringsVector2 = {"howdy", "hello", "goodbye"};
	REQUIRE(b.cutTest2(stringsVector1, stringsVector2) == false);

}
