#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE( "Test creation of array" ) {

  ArrayList<int> a;
  REQUIRE(a.getLength()==0);
  REQUIRE(a.isEmpty());

}

TEST_CASE( "Test insert element" ) {

  ArrayList<int> a;
  REQUIRE(a.isEmpty());
  REQUIRE(a.insert(1,10));
  REQUIRE(a.isEmpty()==false);
  REQUIRE(a.getLength()==1);
  REQUIRE(a.insert(2,20)); 
  REQUIRE(a.getLength()==2);
  REQUIRE(a.getEntry(1)==10);
  REQUIRE(a.getEntry(2)==20);

}
