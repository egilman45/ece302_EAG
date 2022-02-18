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
    REQUIRE(l.insert(1,45));
    REQUIRE(l.getLength()==1);
    REQUIRE(l.getEntry(1)==45);
    REQUIRE(l.insert(2,33));
    REQUIRE(l.getEntry(2)==33);
    REQUIRE(l.getLength()==2);
}

TEST_CASE("Testing Remove") {
    LinkedList<int> l;
    REQUIRE(l.insert(1,45));
    REQUIRE(l.insert(2,33));
    REQUIRE(l.insert(3,12));
    REQUIRE(l.getLength()==3);
    REQUIRE(l.remove(2));
    REQUIRE(l.getLength()==2);
    REQUIRE(l.getEntry(1)==45);
    REQUIRE(l.getEntry(2)==12);
}

TEST_CASE("Testing Clear") {
    LinkedList<int> l;
    REQUIRE(l.insert(1,45));
    REQUIRE(l.insert(2,33));
    REQUIRE(l.insert(3,12));
    REQUIRE(l.getLength()==3);
    l.clear();
    REQUIRE(l.getLength()==0);
}
