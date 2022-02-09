#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE( "testing constructor and length initilized" ) {

    LinkedList<int> l;
    REQUIRE(l.isEmpty() == true);
    REQUIRE(l.getLength() == 0);
  
}

TEST_CASE("Testing Insert") {
    LinkedList<int> l;
    REQUIRE(l.insert(3,45)==false);
    REQUIRE(l.getLength()==0);
    //Getting segmentation error
    REQUIRE(l.insert(1,45));
    REQUIRE(l.getLength()==1);
}
