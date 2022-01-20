#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "bitset.hpp"

TEST_CASE( "Test Bitset Construction", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "Different Size Constructor", "[bitset]" ) {

    //Test a valid bitset size
    Bitset b(4);  
    REQUIRE(b.size() == 4);
    REQUIRE(b.good());

    //Test an invalid bitset size
    Bitset a(0);
    REQUIRE(a.good()==false);
}

TEST_CASE( "String Constructor", "[bitset]" ) {

    //Test Custom String
    Bitset b("01010101"); 
    REQUIRE(b.asString()=="01010101"); 
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());  
    REQUIRE(b.test(1)==true);
    REQUIRE(b.test(0)==false);

    //Test Invalid Bitset
    Bitset c("0123");
    REQUIRE(c.good()==false);
}


TEST_CASE( "Set Method", "[bitset]") {

    //Set up Bitset
    Bitset b;
    b.set(1);
    b.set(4);
    REQUIRE(b.good());

    //Test for 1s and 0s
    REQUIRE(b.test(1));
    REQUIRE(b.test(3)==false);
    REQUIRE(b.test(4));

}

TEST_CASE( "Reset Method", "[bitset]") {

    //Set up Bitset
    Bitset b;
    b.set(1);
    b.set(4);
    REQUIRE(b.good());

    //Test for 1s and 0s
    REQUIRE(b.test(1));
    REQUIRE(b.test(3)==false);
    REQUIRE(b.test(4));

    //Reset and test again
    b.reset(1);
    b.reset(4);
    REQUIRE(b.size()==8);
    REQUIRE(b.test(1)==false);
    REQUIRE(b.test(3)==false);
    REQUIRE(b.test(4)==false);
    
}

TEST_CASE( "Toggle Method", "[bitset]") {

    //Set up Bitset
    Bitset b;
    b.set(1);
    b.set(4);
    REQUIRE(b.good());

    //Test for 1s and 0s
    REQUIRE(b.test(1));
    REQUIRE(b.test(3)==false);
    REQUIRE(b.test(4));

    //Reset and test again
    b.toggle(1);
    b.toggle(4);
    b.toggle(3);
    REQUIRE(b.size()==8);
    REQUIRE(b.test(1)==false);
    REQUIRE(b.test(3)==true);
    REQUIRE(b.test(4)==false);
    
}

TEST_CASE( "asString Method", "[bitset]") {

    //Test Default String
    Bitset b;
    REQUIRE(b.asString()=="00000000");

    //Test Different Size Strings
    Bitset a(3);
    REQUIRE(a.asString()=="000");

    //Test Changing String
    Bitset c("01110111");
    c.set(0);
    REQUIRE(c.asString()=="11110111");
    c.toggle(4);
    REQUIRE(c.asString()=="11111111");
    c.toggle(6);
    REQUIRE(c.asString()=="11111101");
}





