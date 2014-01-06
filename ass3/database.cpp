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
#include "database.h"

//g++ -std=c++11 -Wall -Werror -O2 -o database database.cpp fraction.cpp


int main() {

  Database<string> db1;

  db1.read(cin);

  //cout << db1 << endl;
/*
  cout << "numSelected: " << db1.numSelected() << endl;
  db1.selectAll();
  cout << "numSelected: " << db1.numSelected() << endl;
  cout << "numRecords: " << db1.numRecords() << endl;
*/
  db1.write(cout,AllRecords);
  db1.deleteRecords(SelectedRecords);
  db1.write(cout,AllRecords);

  //db1.select(Remove, "name",Equal,"dan");
  db1.select(All, "name",Equal,"dan");
  cout << "Now print whats left" << endl;
  db1.write(cout,SelectedRecords);
 // db1.write(cout,SelectedRecords);
  return 0;
}

