#ifndef BITSET_HPP
#define BITSET_HPP
#include <string>
#include <bitset>

class Bitset{
public:

  //Default construction of valid bitset with size 8
  //All bits set to 0
  Bitset();

  //Construction of a valid bitset of size N, which is intmax_t
  //All bits set to 0, bitset invalid if N is zero or less
  Bitset(intmax_t size);

  //Construction of valid bitset set to 00010000
  //If string contains charater other than 0 or 1, it is invalid
  Bitset(const std::string & value);

  // Deconstructor for Bitset class
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  //Return the size of the bitset
  intmax_t size() const;

  //Determine if the bitset if valid
  bool good() const;

  //Set nth bit to 1
  //If n is not in range then bitset invalid
  void set(intmax_t index);

  //Reset the nth bit to 0
  //If n is not in range then bitset is invalid
  void reset(intmax_t index);

  //Toggle the nth bit from current state
  //If n is not in range then bitset is invalid
  void toggle(intmax_t index);

  //Check if the nth bit is set to 1
  //Return true if 1, return false if 0
  //If n is not in range then bitset is invalid

  bool test(intmax_t index);

  //Return the bitset as a string of 0s and 1s
  //Most significant bit first
  std::string asString() const;

private:

  //Holds length of Bitset
  intmax_t length;

  //Allocate memory for bitsetData
  int * bitsetData;

  //Determine if Bitset is valid
  bool validBitset;

  //Holds String of Bitset
  std::string stringData;
  

};

#endif
