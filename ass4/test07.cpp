#include <algorithm>
#include <iostream>
#include <iterator>

#include "btree.h"

//g++ -std=c++11 -Wall -Werror -O2 -o test04 test04.cpp

using namespace std;

int main(void) {
  btree<int> b(2);

  b.insert(10);
  b.insert(19);
  b.insert(4);
  b.insert(7);
  b.insert(13);
  b.insert(16);
  b.insert(22);
  b.insert(25);
  b.insert(2);
  b.insert(3);
  b.insert(5);
  b.insert(6);
  b.insert(8);
  b.insert(9);
  b.insert(11);
  b.insert(12);
  b.insert(14);
  b.insert(15);
  b.insert(17);
  b.insert(18);
  b.insert(20);
  b.insert(21);
  b.insert(23);
  b.insert(24);
  b.insert(26);
  b.insert(27);

  std::cout << "OUTPUT OPERATOR << (top to bottom print): " << std::endl;
  std::cout << b << std::endl;
  std::cout << std::endl;

  std::cout << std::endl << "PRINT BEGIN TO END" << std::endl;
  for(btree<int>::iterator iter = b.rbegin(); iter != b.rend(); --iter) {
    //btree<int>::iterator iter = b.rbegin();
    //(*iter)++;
    std::cout << *iter;// << std::endl;
    
  }
  std::cout << std::endl;
  


/*
  std::cout << std::endl << "PRINT BEGIN TO END" << std::endl;
  for(btree<int>::iterator iter = b.begin(); iter != b.cend(); --iter) {
    //btree<int>::iterator iter = b.begin();
    //(*iter)++;
    std::cout << *iter;// << std::endl;
    
  }
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "OUTPUT OPERATOR << (top to bottom print): " << std::endl;
  std::cout << b << std::endl;
*/


/*
  b.insert(6);
  b.insert(2);  
  b.insert(4);
  b.insert(8);
  b.insert(0);
  b.insert(1);
  b.insert(9);
*/

/*
  b.insert(10);
  b.insert(20);
  b.insert(30);
  b.insert(40);

  b.insert(1);
  b.insert(2);
  b.insert(3);
  b.insert(4);

  b.insert(11);
  b.insert(12);
  b.insert(13);
  b.insert(14);

  b.insert(21);
  b.insert(22);
  b.insert(23);
  b.insert(24);

  b.insert(31);
  b.insert(32);
  b.insert(33);
  b.insert(34);

  b.insert(41);
  b.insert(42);
  b.insert(43);
  b.insert(44);
*/
/*
  std::cout << "PRINT BEGIN TO END" << std::endl;
  for(btree<int>::iterator iter = b.begin(); iter != b.end(); ++iter)
    //btree<int>::iterator iter = b.begin();
    std::cout << *iter;// << std::endl;
  std::cout << std::endl;

  std::cout << "OUTPUT OPERATOR << (top to bottom print): " << std::endl;
  std::cout << b << std::endl;

  const btree<int>& bCopy = b;

  std::cout << std::endl << std::endl << std::endl << std::endl;
  std::cout << "PRINT BEGIN TO END" << std::endl;
  for(btree<int>::const_iterator iter = bCopy.cbegin(); iter != bCopy.cend(); ++iter)
    //btree<int>::iterator iter = b.begin();
    std::cout << *iter;// << std::endl;
  std::cout << std::endl;

  std::cout << "OUTPUT OPERATOR << (top to bottom print): " << std::endl;
  std::cout << bCopy << std::endl;
*/
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
