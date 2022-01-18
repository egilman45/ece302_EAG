#include "bitset.hpp"

Bitset::Bitset() {
//Default construction of valid bitset with size 8
//All bits set to 0

    std::bitset<8> bitsetData;
    bitsetData.reset();
    validBitset = true;
}

Bitset::Bitset(intmax_t size) {
//Construction of a valid bitset of size N, which is intmax_t
//All bits set to 0, bitset invalid if N is zero or less

    if (size < 1) {
        validBitset = false;
    } else {
        std::bitset<size> bitsetData;
        bitsetData.reset();
        validBitset = true;    
    }

}

Bitset::Bitset(const std::string & value) {
//Construction of valid bitset set to 00010000
//If string contains charater other than 0 or 1, it is invalid

    std::bitset<8> bitsetData (std::string("00010000"));
    validBitset = true;

    strcpy(std::arrayValue<char,value.length()>, value.c_str());

    for (int i = 0, i < value.length(), i++) {
        if (arrayValue[i] != "0" || arrayValue[i] != "1") {
            validBitset = false;
        }
    } 

}

Bitset::~Bitset() {
    return false;
}

Bitset::Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;) {

    return false;
}

Bitset::intmax_t size() const {
//Return the size of the bitset

    return bitsetData.size();

}

Bitset::bool good() const {
//Determine if the bitset if valid

    return validBitset;
}

Bitset::void set(intmax_t index) {
//Set nth bit to 1
//If n is not in range then bitset is invalid

    bitsetData.set(index, 1);

}

Bitset::void reset(intmax_t index) {
//Reset the nth bit to 0
//If n is not in range then bitset is invalid

    bitsetData.reset(index);

}

Bitset::void toggle(intmax_t index) {
//Toggle the nth bit from current state
//If n is not in range then bitset is invalid

    bitsetData.flip(index);

}

Bitset::bool test(intmax_t index) {
//Check if the nth bit is set to 1
//Return true if 1, return false if 0
//If n is not in range then bitset is invalid

    return bitsetData.test(index);

}

Bitset::std::string asString() const {
//Return the bitset as a string of 0s and 1s
//Most significant bit first

    std::string bitsetString = bitsetData.to_string<char,
    std::string::traits_type,std::string::allocator_type>();

    return bitsetString;
}