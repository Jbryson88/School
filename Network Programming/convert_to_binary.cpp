// John Bryson
// CS 3013 - Network Programming
// Project 1
// Due Sep. 12, 2022
#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
using namespace std;

int
main ()
{
  int nums[256];
  for (int i = 0; i < 256; i++)	// Iterates through the array for value of i, incrementing through
    {
      cout << bitset < 8 > (i) << " " << hex << " " << i << " " << nums[i] << endl;	// Prints out the location of i in binary, then the value of i in hex
    }

  return 0;
}
