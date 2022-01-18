#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "bag.hpp"

// force template expansion
template class Bag<int>;

TEST_CASE("Empty Test", "[Bag]"){
  //When Bag is intialized, should be empty
  Bag<int> bag;
  REQUIRE(bag.isEmpty());
}

TEST_CASE("Get Current Size", "[Bag]"){
  //Create bag and make sure it is clear
  Bag<int> bag;
  bag.clear();

  //Successfully add elements 1,2,3 to bag
  REQUIRE(bag.add(1)==true);
  REQUIRE(bag.add(2)==true);
  REQUIRE(bag.add(3)==true);

  //Three elements added, so size should be 3
  REQUIRE(bag.getCurrentSize()==3);
  bag.clear();
}

TEST_CASE("Add Test", "[Bag]"){
  //Create bag and gather intial size
  Bag<int> bag;
  int length = bag.getCurrentSize();

  //Successfully add an element to bag
  REQUIRE(bag.add(8)==true);

  //Make sure length is greater after addition
  REQUIRE(bag.getCurrentSize() > length);
  bag.clear();
}

TEST_CASE("Remove Test", "[Bag]"){
  //Create bag and make sure elements are clear
  Bag<int> bag;
  bag.clear();

  //Successfully add elements 1,1,2 to bag
  REQUIRE(bag.add(1)==true);
  REQUIRE(bag.add(1)==true);
  REQUIRE(bag.add(2)==true);
  REQUIRE(bag.getCurrentSize()==3);
  
  //Test occurance is removed
  //Size should be smaller, frequency decreased
  REQUIRE(bag.remove(2)==true);
  REQUIRE(bag.getCurrentSize()==2);
  REQUIRE(bag.getFrequencyOf(2)==0);
  
  //Test only one occurance is removed
  //Size should be smaller, frequency decreased
  REQUIRE(bag.remove(1)==true);
  REQUIRE(bag.getFrequencyOf(1)==1);
  REQUIRE(bag.getCurrentSize()==1);
  bag.clear();
}

TEST_CASE("Clear Test", "[Bag]"){
  //Create bag
  Bag<int> bag;

  //Successfully add elements 1,2,3 to bag
  REQUIRE(bag.add(1)==true);
  REQUIRE(bag.add(2)==true);
  REQUIRE(bag.add(3)==true);

  //Clear the elements in bag
  bag.clear();

  //Ensure the bag is now empty with no elements
  REQUIRE(bag.isEmpty()==true);
}

TEST_CASE("Frequency Test", "[Bag]"){
  //Create bag and ensure elements are clear
  Bag<int> bag;
  bag.clear();

  //Successfully add multiple instances of 4 to bag
  REQUIRE(bag.add(4)==true);
  REQUIRE(bag.add(4)==true);
  REQUIRE(bag.add(4)==true);

  //Test freqency count is correct
  REQUIRE(bag.getFrequencyOf(4)==3);
  bag.clear();
}

TEST_CASE("Contain Test", "[Bag]"){
  //Create bag and ensure elements are cleared
  Bag<int> bag;
  bag.clear();

  //Successfully add element to bag
  REQUIRE(bag.add(1)==true);

  //Confirm element is in bag, not other values
  REQUIRE(bag.contains(1)==true);
  REQUIRE(bag.contains(2)==false);
  REQUIRE(bag.contains(3)==false);
}
