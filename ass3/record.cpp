#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdlib>	// for exit()
#include <cstring>	// for strncmp()
#include <string>
using namespace std;

#include "fraction.h"
#include "utility.h"
#include "record.h"


int main() {
/*
  Record<string> r1; 
  cin >> r1;
  cout << r1;
*/
  //cout << "matchesQuery: " << r1.matchesQuery("name",Equal,"carl") << endl;
 // cout << "matchesQuery: " << r1.matchesQuery("name",Equal,"carlos") << endl;
  //cout << "matchesQuery: " << r1.matchesQuery("name",NotEqual,"carlos") << endl;
 // cout << "matchesQuery: " << r1.matchesQuery("*",NotEqual,"carl") << endl;

/*
  Record<int> r2; 
  cout << r2;
  cout << "matchesQuery: " << r2.matchesQuery("*",GreaterThan,16) << endl;
  cout << "matchesQuery: " << r2.matchesQuery("*",LessThan,101) << endl;
  cout << "matchesQuery: " << r2.matchesQuery("*",GreaterThan,150) << endl;
  cout << "matchesQuery: " << r2.matchesQuery("*",LessThan,50) << endl;
*/

  Record<Fraction> r3;
  cin >> r3;
  cout << r3;

/*
  Record<string> r1; 
  cout << "isSelected: " << r1.isSelected() << endl;
  r1.setSelected(true);  
  cout << "isSelected: " << r1.isSelected() << endl;
*/
/*
  cout << "isSelected: " << r1.isSelected() << endl;
  cout << "r1 created" << endl;
  cout << "pairs_(0): " << endl;
  cout << r1.pairs_.at(0).first << " = " << r1.pairs_.at(0).second << endl;
  cout << "pairs_(1): " << endl;
  cout << r1.pairs_.at(1).first << " = " << r1.pairs_.at(1).second << endl;
  cout << "pairs_(2): " << endl;
  cout << r1.pairs_.at(2).first << " = " << r1.pairs_.at(2).second << endl;
*/
  return 0;
}

