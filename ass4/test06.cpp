#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

#include "btree.h"

//g++ -std=c++11 -Wall -Werror -O2 -o test04 test04.cpp

//using namespace std;

int main(void) {
  btree<std::string> b;

  b.insert("comp3000");
  b.insert("comp3171");
  b.insert("comp2000");
  b.insert("comp1000");


  std::cout << "PRINT BEGIN TO END" << std::endl;
  for(btree<string>::iterator iter = b.begin(); iter != b.end(); ++iter)
    //btree<int>::iterator iter = b.begin();
    std::cout << *iter;// << std::endl;
  std::cout << std::endl;

  std::cout << "OUTPUT OPERATOR << (top to bottom print): " << std::endl;
  std::cout << b << std::endl;
/*
  b.insert(6);
  
  btree<int>::iterator iter = b.begin();
  std::cout << "*iter: " << *iter << std::endl;

  b.insert(9);
  std::cout << "*iter: " << *iter << std::endl;
  ++iter;
  std::cout << "*iter: " << *iter << std::endl;
  //std::cout << "maxNodeElems_: " << b.maxNodeElems_ << std::endl;


  std::cout << "Tree: " << b << std::endl;
*/
  //b.insert(99);

  return 0;
}
