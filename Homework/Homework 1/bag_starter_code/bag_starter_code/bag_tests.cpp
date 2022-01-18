#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "bag.hpp"

// force template expansion
template class Bag<int>;

TEST_CASE("Empty Test", "[Bag]"){
  Bag<int> bag;
  REQUIRE(bag.isEmpty());
}

TEST_CASE("Get Current Size", "[Bag]"){
  Bag<int> bag;
  bag.clear();
  REQUIRE(bag.add(1)==true);
  REQUIRE(bag.add(2)==true);
  REQUIRE(bag.add(3)==true);
  REQUIRE(bag.getCurrentSize()==3);
  bag.clear();
}

TEST_CASE("Add Test", "[Bag]"){
  Bag<int> bag;
  int length = bag.getCurrentSize();
  REQUIRE(bag.add(8)==true);
  REQUIRE(bag.getCurrentSize() > length);
  bag.clear();
}

TEST_CASE("Remove Test", "[Bag]"){
  Bag<int> bag;
  bag.clear();
  REQUIRE(bag.add(1)==true);
  REQUIRE(bag.add(1)==true);
  REQUIRE(bag.add(2)==true);
  REQUIRE(bag.getCurrentSize()==3);
  
  //Test occurance is removed
  REQUIRE(bag.remove(2)==true);
  REQUIRE(bag.getCurrentSize()==2);
  REQUIRE(bag.getFrequencyOf(2)==0);
  
  //Test only one occurance is removed
  REQUIRE(bag.remove(1)==true);
  REQUIRE(bag.getFrequencyOf(1)==1);
  REQUIRE(bag.getCurrentSize()==1);
  bag.clear();
}

TEST_CASE("Clear Test", "[Bag]"){
  Bag<int> bag;
  REQUIRE(bag.add(1)==true);
  REQUIRE(bag.add(2)==true);
  REQUIRE(bag.add(3)==true);
  bag.clear();
  REQUIRE(bag.isEmpty()==true);
}

TEST_CASE("Frequency Test", "[Bag]"){
  Bag<int> bag;
  bag.clear();
  REQUIRE(bag.add(4)==true);
  REQUIRE(bag.add(4)==true);
  REQUIRE(bag.add(4)==true);
  REQUIRE(bag.getFrequencyOf(4)==3);
  bag.clear();
}

TEST_CASE("Contain Test", "[Bag]"){
  Bag<int> bag;
  bag.clear();
  REQUIRE(bag.add(1)==true);
  REQUIRE(bag.contains(1)==true);
  REQUIRE(bag.contains(2)==false);
}
