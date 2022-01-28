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
    Bitset a(-1);
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

    //Test Invalid Case
    b.set(-1);
    REQUIRE(b.good()==false);

}

TEST_CASE( "Reset Method", "[bitset]") {

    //Set up Bitset with Default
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
    REQUIRE(b.good());
    REQUIRE(b.size()==8);
    REQUIRE(b.test(1)==false);
    REQUIRE(b.test(3)==false);
    REQUIRE(b.test(4)==false);

    //Test Invalid Case
    b.reset(-1);
    REQUIRE(b.good()==false);

    //Set up Bitset with Different Size
    Bitset a(4);
    a.set(1);
    a.set(3);
    REQUIRE(a.good());

    //Test for 1s and 0s
    REQUIRE(a.test(1));
    REQUIRE(a.test(2)==false);
    REQUIRE(a.test(3));

    //Reset and test again
    a.reset(1);
    a.reset(3);
    REQUIRE(a.good());
    REQUIRE(a.size()==4);
    REQUIRE(a.test(1)==false);
    REQUIRE(a.test(2)==false);
    REQUIRE(a.test(3)==false);

    //Test Invalid Case
    a.reset(-1);
    REQUIRE(a.good()==false);

    //Set up Bitset with String Constructor
    Bitset c("0101");
    c.set(0);
    c.set(2);
    REQUIRE(c.good());

    //Test for 1s
    REQUIRE(c.test(0));
    REQUIRE(c.test(1));
    REQUIRE(c.test(2));
    REQUIRE(c.test(3));

    //Reset and test again
    c.reset(1);
    c.reset(3);
    REQUIRE(c.good());
    REQUIRE(c.size()==4);
    REQUIRE(c.test(0)==true);
    REQUIRE(c.test(1)==false);
    REQUIRE(c.test(2)==true);
    REQUIRE(c.test(3)==false);

    //Test Invalid Case
    c.reset(-1);
    REQUIRE(a.good()==false);
    
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

    //Test Invalid Case
    b.toggle(-1);
    REQUIRE(b.good()==false);

    //Set up Bitset with Different Size
    Bitset a(10);
    a.set(7);
    a.set(8);
    REQUIRE(a.good());

    //Test for 1s and 0s
    REQUIRE(a.test(7));
    REQUIRE(a.test(6)==false);
    REQUIRE(a.test(8));

    //Toggle and test again
    a.toggle(6);
    a.toggle(7);
    a.toggle(8);
    REQUIRE(a.size()==10);
    REQUIRE(a.test(7)==false);
    REQUIRE(a.test(6)==true);
    REQUIRE(a.test(8)==false);

    //Test Invalid Case
    a.toggle(-1);
    REQUIRE(a.good()==false);

    //Set up Bitset with String Constructor
    Bitset c("00001");
    c.toggle(0);
    c.toggle(1);
    REQUIRE(c.good());

    //Test for 1s and 0s
    REQUIRE(c.test(0));
    REQUIRE(c.test(1));
    REQUIRE(c.test(4));

    //Toggle and test again
    c.toggle(0);
    c.toggle(1);
    c.toggle(2);
    c.toggle(4);
    REQUIRE(c.good());
    REQUIRE(c.size()==5);
    REQUIRE(c.test(0)==false);
    REQUIRE(c.test(1)==false);
    REQUIRE(c.test(2)==true);
    REQUIRE(c.test(4)==false);

    //Test Invalid Case
    c.toggle(-1);
    REQUIRE(c.good()==false);
    
}

TEST_CASE( "asString Method", "[bitset]") {

    //Test Default String
    Bitset b;
    REQUIRE(b.good());
    REQUIRE(b.asString()=="00000000");

    //Test Different Size Strings
    Bitset a(3);
    REQUIRE(a.asString()=="000");
    REQUIRE(a.good());
    a.set(2);
    REQUIRE(a.asString()=="001");

    //Test Changing String
    Bitset c("01110111");
    c.set(0);
    REQUIRE(c.good());
    REQUIRE(c.asString()=="11110111");
    c.toggle(4);
    REQUIRE(c.good());
    REQUIRE(c.asString()=="11111111");
    c.toggle(6);
    REQUIRE(c.good());
    REQUIRE(c.asString()=="11111101");
}





