#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method


TEST_CASE( "Test FindPalindrome add a non-allowable word")
{
	FindPalindrome b;

	//Test special characters get rejected
	REQUIRE(!b.add("kayak1"));
	REQUIRE(b.add("$0 COOL")==false);
	std::vector<std::string> strings = {"he110", "c00l", "hello"};
	REQUIRE(b.add(strings)==false);
	REQUIRE(b.add("yeah yeah")==false);

}

TEST_CASE("Testing adding valid word to vector") {

	FindPalindrome b;

	INFO("Test successful strings and vector");
	REQUIRE(b.add("hello"));
	REQUIRE(b.add("abba"));
	std::vector<std::string> strings = {"hi", "hey there", "bye"};
	REQUIRE(b.add(strings)==false);
	strings = {"hi", "heythere", "bye"};
	REQUIRE(b.add(strings));
	b.clear();
	
	INFO("Check duplicate string in first add");
	REQUIRE(b.add("pillow"));
	REQUIRE(b.add("pillow")==false);
	REQUIRE(b.add("blanket"));
	REQUIRE(b.add("blanket")==false);
	REQUIRE(b.add("Pillow")==false);
	REQUIRE(b.add("blankeT")==false);
	b.clear();

	INFO("Check duplicate string in second add");
	strings = {"fork", "knife", "spoon"};
	REQUIRE(b.add(strings));
	strings = {"bowl", "plate"};
	REQUIRE(b.add(strings));
	strings = {"fork", "Bowl", "spooN"};
	REQUIRE(b.add(strings)==false);
	strings = {"dish", "Plate", "napkin"};
	REQUIRE(b.add(strings)==false);
	strings = {"see", "sea", "see"};
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
	b.clear();

	vectorWords = {"UFO", "tofu"};
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==1);
	b.clear();

	vectorWords = {"b", "BB", "BbB", "BBbb"};
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==24);
	b.clear();

	vectorWords = {"a", "AA", "AaA"};
	REQUIRE(b.cutTest1(vectorWords));
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==6);
	b.clear();

	vectorWords = {"draWo", "c", "oward", "be", "eb"};
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==8);
	b.clear();

	vectorWords = {"A", "nut", "fora", "jar", "of", "tuna"};
	REQUIRE(b.cutTest1(vectorWords));
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==2);
	b.clear();

	vectorWords = {"Murder", "for", "a", "jar", "of"};
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==0);
	vectorWords = {"red", "rum"};
	REQUIRE(b.add(vectorWords));
	REQUIRE(b.number()==2);
	b.clear();

}



