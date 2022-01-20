#include "bitset.hpp"
#include <array>
#include <string>
#include <new>
#include <stdlib.h>

Bitset::Bitset() {

    length = 8;

    bitsetData = new int [8];
    for (int i = 0; i < 8; i++) {
        bitsetData[i] = 0;
    }
    validBitset = true;
}

Bitset::Bitset(intmax_t size) {

    length = size;

    bitsetData = new int [length];

    for (int i = 0; i < length; i++) {
        bitsetData[i] = 0;
    }

    if (size < 1) {
        validBitset = false;
    } else {
        validBitset = true;    
    }

}

Bitset::Bitset(const std::string & value) { 
    
    length = value.length();

    bitsetData = new int [length];

    validBitset = true;

    for (int i = 0; i < length; i++) {

        stringData = value[i];

        int intValue = std::stoi(stringData);

        if (intValue != 0 && intValue != 1) {
            validBitset = false;
        }

        bitsetData[i] = intValue;
    }
}

Bitset::~Bitset() {}


intmax_t Bitset::size() const {

    return length;

}

bool Bitset::good() const {

    return validBitset;
}

void Bitset::set(intmax_t index) {

    if (index < 0 || index > size()-1) {
        validBitset = false;
    }

    bitsetData[index] = 1;

}

void Bitset::reset(intmax_t index) {

    if (index < 0 || index > size()-1) {
        validBitset = false;
    }

    bitsetData[index] = 0;

}

void Bitset::toggle(intmax_t index) {

    if (index < 0 || index > size()-1) {
        validBitset = false;
    }
    
    if (bitsetData[index] == 1) {
        bitsetData[index] = 0;
    } else if (bitsetData[index] == 0){
        bitsetData[index] = 1;
    } else {
        validBitset = false;
    }

}

bool Bitset::test(intmax_t index) {

    if (index < 0 || index > size()-1) {
        validBitset = false;
    }

    return (bitsetData[index]==1);

}

std::string Bitset::asString() const {


    std::string bitsetString = "";

    for (int i = 0; i < size(); i++) {

        bitsetString = bitsetString + std::to_string(bitsetData[i]); }

    return bitsetString;
}