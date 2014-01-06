#include "SMatrix.h"
#include <algorithm>

#include <cstring>
#include <sstream>

using namespace std;

/* CONSTRUCTORS */

// Default Constructor
SMatrix::SMatrix(size_type size) : SMatrix::SMatrix(size,size) {
////  cout << "size: " << size << endl;
  //SMatrix SMatrix(size,size);
}

// Constructor
SMatrix::SMatrix(size_type r, size_type c) {
////  cout << "SMatrix();" << endl;
  numRows_ = r;
  numCols_ = c;
  numVals_ = 0;

////  cout << "numRows_: " << rows() << endl;
////  cout << "numCols_: " << cols() << endl;

  // initialise vals and cols arrays
  int size = min(int(ceil((r*c)/5.0)), 1000);
////  cout << "size: " << size << endl;
  vals_ = new int[size];

  if (!vals_) {
    cerr << "Out of memory" << endl;
    exit(1);
  }

  cidx_ = new SMatrix::size_type[size];

  if (!cidx_) {
    cerr << "Out of memory" << endl;
    exit(1);
  }

//// keep track of initial size of these arrays
//// when adding elements check if numVals == size of vals_ AND cidx_

  valsLen_ = size; // same as colsLen
  
////  cout << "valsLen_: " << valsLen_ << endl; 

}

// Constructor
SMatrix::SMatrix(std::istream& stream) {

  string line;
  bool setval = false;
  while (getline (stream,line)) {

    istringstream iss(line);
    string s;
    while (iss >> s) {
      //cout << "s: " << s << endl;
  
      int start = s.find_first_of("(");
      s.erase(start,1);
     /// cout << "s: " << s << endl;
      int end = s.find_first_of(")");
      s.erase(end,1);

      ///cout << "s: " << s << endl;

      std::string::size_type sz;   

      size_type firstNum = std::stoi (s,&sz);
      string t = s.substr(sz);
      t.erase(0,1);
      size_type secondNum = std::stoi (t,&sz);
      //cout << "s: " << s << endl;
      //cout << "s1: " << s << endl;
      string u = t.substr(sz);
      u.erase(0,1);
      //cout << "u: " << u << endl;
      ///t.erase(0,2);
      size_type thirdNum = std::stoi (u,&sz);
      //size_type thirdNum = 15;
      //cout << "thirdNum: " << thirdNum << endl;
      //cout << "s2: " << s << endl;
      //size_type thirdNum = std::stoi (t,&sz);
      ///SMatrix(firstNum,secondNum);

      if (setval == true) {
        setVal(firstNum,secondNum,thirdNum);

      }
      else {
        numRows_ = firstNum;
        numCols_ = secondNum;
        numVals_ = 0;
        //numVals_ = thirdNum;

      ////  cout << "numRows_: " << rows() << endl;
      ////  cout << "numCols_: " << cols() << endl;

        // initialise vals and cols arrays
        int size = min(int(ceil((firstNum*secondNum)/5.0)), 1000);
      ////  cout << "size: " << size << endl;
        vals_ = new int[size];
        cidx_ = new SMatrix::size_type[size];

      //// keep track of initial size of these arrays
      //// when adding elements check if numVals == size of vals_ AND cidx_

        valsLen_ = size; // same as colsLen
        setval = true;
      }

      
    ////  cout << "valsLen_: " << valsLen_ << endl; 
    }
  }
}
/*
// Copy Constructor
SMatrix::SMatrix(const SMatrix &m) :
  numRows_(m.numRows_),
  numCols_(m.numCols_),
  numVals_(m.numVals_),
  vals_(m.vals_),
  cidx_(m.cidx_),
  valsLen_(m.valsLen_),
  ridx_(m.ridx_)
  { } 
*/

// Copy Constructor
SMatrix::SMatrix(const SMatrix &m) {
  
  numRows_ = m.numRows_;
  numCols_ = m.numCols_;
  numVals_ = m.numVals_;

  // initialise vals and cols arrays
  vals_ = new int[m.valsLen_];
  if (!vals_) {
    cerr << "Out of memory" << endl;
    exit(1);
  }

  memcpy(vals_, m.vals_, sizeof(int) * m.valsLen_);

  cidx_ = new SMatrix::size_type[m.valsLen_];
  if (!cidx_) {
    cerr << "Out of memory" << endl;
    exit(1);
  }

  memcpy(cidx_, m.cidx_, sizeof(size_type) * m.valsLen_);

  //vals_ = m.vals_;
  //cidx_ = m.cidx_;

  valsLen_ = m.valsLen_;
  ridx_ = m.ridx_;
}


// Move Constructor
SMatrix::SMatrix(SMatrix &&m) {

  numRows_ = m.numRows_;
  m.numRows_ = 0;

  numCols_ = m.numCols_;
  m.numCols_ = 0;

  numVals_ = m.numVals_;
  m.numVals_ = 0;

  vals_ = m.vals_;
  m.vals_ = nullptr;

  cidx_ = m.cidx_;
  m.cidx_ = nullptr;

  valsLen_ = m.valsLen_;
  m.valsLen_ = 0;

  ridx_ = m.ridx_;
  m.ridx_.clear();

}
/* DESTRUCTOR */

// Destructor
SMatrix::~SMatrix() { 

  delete [] vals_;
  delete [] cidx_;

////  cout << "~SMatrix()" << endl;

}

SMatrix SMatrix::identity(size_type n) {

  SMatrix m(n,n);
  for (unsigned int i = 0; i < n; ++i) {
    m.setVal(i,i,1);
  }

  return m;
}


// Your fantastic implementation goes here!
// You should test it extensively to ensure that it behaves exactly 
// as required by the specification, it does not leak memory and is
// optimised for performance!

/* OPERATORS */

// Print Operator
std::ostream& operator<<(std::ostream &os, const SMatrix &m) {

  // this operator will be used as the primary testing mechanism
  // make sure that it sbehaves ***EXACTLY*** as specified

  if (m.numRows_ == 0 && m.numCols_ == 0) {


  }
  else {
    ///os << "Printing: m" << endl;
    os << "(" << m.numRows_ << "," << m.numCols_ << "," 
       << m.numVals_ << ")";

    int val = 99;
    bool valFound = true;
    SMatrix::size_type j = 0;

    for (SMatrix::size_type i = 0; i < m.numRows_; ++i) {
      // if map at i exists
      if (m.ridx_.find(i) != m.ridx_.end()) {
        while (j < (m.ridx_.at(i).first + m.ridx_.at(i).second)) {
         // val = m.ridx_.at(i).second;
          val = m.vals_[j];
          if (valFound) {
            os << endl;
            valFound = false;
          }
          os << "(" << i << "," << m.cidx_[j] << "," << val << ")";
              
          if (j != (m.ridx_.at(i).first + m.ridx_.at(i).second) - 1) {
            os << " ";
          } 
          j++;
        }
        if (static_cast<int>(j) != m.numVals_) {
          cout << endl;
        }
      }
    }
  }
  return os;
}

// == equals operator
bool operator==(const SMatrix &a, const SMatrix &b) {
  bool equal = true;
  if (a.rows() != b.rows() || a.cols() != b.cols()) {
    equal = false;
  }
  else {
    b.begin();
    for (a.begin(); !a.end(); a.next()) {
      if (a.value() != b.value()) {
        equal = false;
        break;
      }
      b.next();
    }
  }
  return equal;
}

// != not equals operator
bool operator!=(const SMatrix &a, const SMatrix &b) {
  bool notEqual = false;
  if (a.rows() != b.rows() || a.cols() != b.cols()) {
    notEqual = true;
  }
  else {
    b.begin();
    for (a.begin(); !a.end(); a.next()) {
      if (a.value() != b.value()) {
        notEqual = true;
        break;
      }
      b.next();
    }
  }
  return notEqual;
}

// + operator
SMatrix operator+(const SMatrix &a, const SMatrix &b) throw(MatrixError) {
  if (a.rows() != b.rows() || a.cols() != b.cols()) {
    throw MatrixError("Matrix size error");
  }

  ///SMatrix c = a;
  SMatrix c(a.rows(),a.cols());

  SMatrix::size_type count = 1;
  SMatrix::size_type row = 0;
  SMatrix::size_type col = 0;

  a.begin();
  for (b.begin(); !b.end(); b.next()) {
    if (a.value() == 0 && b.value() == 0) {
      ///c.setVal(row,col,c(row,col) + b.value());
      
    }
    else {
      c.setVal(row,col,a.value() + b.value());
    }
    if (count % b.cols() == 0) {
      col = 0;
      ++row;
    }
    else {
      ++col;
    }
    ++count;
    a.next();
  }
  return c;
}

// - operator
SMatrix operator-(const SMatrix &a, const SMatrix&b) throw(MatrixError) {
  if (a.rows() != b.rows() || a.cols() != b.cols()) {
    throw MatrixError("Matrix size error");
  }

  ///SMatrix c = a;
  SMatrix c(a.rows(),a.cols());

  SMatrix::size_type count = 1;
  SMatrix::size_type row = 0;
  SMatrix::size_type col = 0;

  a.begin();
  for (b.begin(); !b.end(); b.next()) {
    if (a.value() == 0 && b.value() == 0) {
    }
    else {
      c.setVal(row,col,a.value() - b.value());
    }
    if (count % b.cols() == 0) {
      col = 0;
      ++row;
    }
    else {
      ++col;
    }
    ++count;
    a.next();
  }
  return c;
}

// * operator
SMatrix operator*(const SMatrix &a, const SMatrix &b) throw(MatrixError) {
 
  if (a.cols() != b.rows() ) {
    throw MatrixError("Matrix size error");
  }

  ///SMatrix c = a;
  SMatrix c(a.rows(),b.cols());

  //SMatrix::size_type count = 1;
  SMatrix::size_type cRow = 0;
  SMatrix::size_type cCol = 0;

  SMatrix::size_type aCol = 0;
  SMatrix::size_type aRow = cRow; // remains constant at ROW
  SMatrix::size_type bCol = cCol; // remains constant at COL
  SMatrix::size_type bRow = 0;

  int value;


  for (auto it = a.ridx_.cbegin(); it != a.ridx_.cend(); ++it) {

    cRow = (*it).first;
    aRow = cRow;
    

    // for each value in c row
    for (unsigned int j = 0; j < a.cols(); ++j) {
      aCol = 0;
      bRow = 0;
      bCol = cCol;
      value = 0;

      // sum up all multiplications
      for (unsigned int k = 0; k < a.cols(); ++k) {
        ////cout << "a(" << aRow << ", " <<  aCol << ") * (" << bRow << ", " << bCol << ")" << endl;
        value += a(aRow, aCol) * b(bRow, bCol);
        aCol++;
        bRow++;
      }

      ///cout << "NOW cRow: " << cRow << " cCol: " << cCol << "value: " << value << endl;
      c.setVal(cRow,cCol,value);
      ++cCol;
    }
    cCol = 0;
  }

/**************************
  for (unsigned int i = 0; i < (a.rows()*b.cols()); ++i) {
    ///cout << "c.cols(): " << c.cols() << endl;
////    cout << "cRow: " << cRow << " cCol: " << cCol << endl;
    
    ///c.setVal(cRow,cCol,7); // change to result of a double for loop

    aCol = 0;
    aRow = cRow; // remains constant at ROW
    bCol = cCol; // remains constant at COL
    bRow = 0;
    int value = 0;

    // if a's row is all zeroes, skip row in c
    if (a.ridx_.count(cRow) == 0) {  // if row i not in map
      
      //cout << "BLAH cRow: " << cRow << endl;
      // go to next line of c
      cCol = 0;
      ++cRow;
      count = 1; // reset count
      i += b.cols()-1; // skip entire row
    }
    else {
      for (unsigned int j = 0; j < a.cols(); ++j) {
        
 ////       cout << "aCol: " << aCol << " bRow: " << bRow << endl;
        value += a(aRow, aCol) * b(bRow, bCol);
        aCol++;
        bRow++;
      }

      ///cout << "NOW cRow: " << cRow << " cCol: " << cCol << "value: " << value << endl;
      c.setVal(cRow,cCol,value);
    
    
    if (count % c.cols() == 0) {
      cCol = 0;
      ++cRow;
    }
    else {
      ++cCol;
    }
    ++count;
    ///cout << "count: " << count << endl;
    }
  }

***********************/
  return c;
}

// transpose(a)
SMatrix transpose(const SMatrix &a) {

  SMatrix m = a;

  SMatrix::size_type aRow = 0;
  SMatrix::size_type aCol = 0;

  for (unsigned int i = 0; i < a.rows(); ++i) {
    for (unsigned int j = 0; j < a.cols(); ++j) {
      m.setVal(i,j,a(aRow,aCol));
      aRow++;
    }
    aRow = 0;
    aCol++;
  } 

  return m;
}

// a = b (copy assignment)
SMatrix& SMatrix::operator=(const SMatrix& m) {
  if (this != &m) {
    numRows_ = m.numRows_;
    numCols_ = m.numCols_;
    numVals_ = m.numVals_;

    // initialise vals and cols arrays
    vals_ = new int[m.valsLen_];
    if (!vals_) {
      cerr << "Out of memory" << endl;
      exit(1);
    }

    memcpy(vals_, m.vals_, sizeof(int) * m.valsLen_);

    cidx_ = new SMatrix::size_type[m.valsLen_];
    if (!cidx_) {
      cerr << "Out of memory" << endl;
      exit(1);
    }
    memcpy(cidx_, m.cidx_, sizeof(size_type) * m.valsLen_);

    //vals_ = m.vals_;
    //cidx_ = m.cidx_;
    valsLen_ = m.valsLen_;
    ridx_ = m.ridx_;
  }
  return *this;
}

// a = b (move assignment)
SMatrix& SMatrix::operator=(SMatrix &&m) {
  if (this != &m) {
    numRows_ = m.numRows_;
    m.numRows_ = 0;

    numCols_ = m.numCols_;
    m.numCols_ = 0;

    numVals_ = m.numVals_;
    m.numVals_ = 0;

    delete [] vals_;
    vals_ = m.vals_;
    m.vals_ = nullptr;

    delete [] cidx_;
    cidx_ = m.cidx_;
    m.cidx_ = nullptr;

    valsLen_ = m.valsLen_;
    m.valsLen_ = 0;

    ridx_.clear();
    ridx_ = m.ridx_;
    m.ridx_.clear();
  }
  return *this;
}

// a += b a is replaced with the sum of a and b
SMatrix& SMatrix::operator+=(const SMatrix &b) throw(MatrixError) {

  if (rows() != b.rows() || cols() != b.cols()) {
    throw MatrixError("Matrix size error");
  }

  if (this != &b) { // if a != b

    SMatrix::size_type count = 1;
    SMatrix::size_type row = 0;
    SMatrix::size_type col = 0;

    begin();
    for (b.begin(); !b.end(); b.next()) {
      if (value() == 0 && b.value() == 0) {
      }
      else {
        setVal(row,col,value() + b.value());
      }
      if (count % b.cols() == 0) {
        col = 0;
        ++row;
      }
      else {
        ++col;
      }
      ++count;
      next();
    }
  }
  return *this;
}

// a -= b a is replaced with the difference of a and b
SMatrix& SMatrix::operator-=(const SMatrix &b) throw(MatrixError) {

  if (rows() != b.rows() || cols() != b.cols()) {
    throw MatrixError("Matrix size error");
  }

  if (this != &b) { // if a != b

    SMatrix::size_type count = 1;
    SMatrix::size_type row = 0;
    SMatrix::size_type col = 0;

    begin();
    for (b.begin(); !b.end(); b.next()) {
      if (value() == 0 && b.value() == 0) {
      }
      else {
        setVal(row,col,value() - b.value());
      }
      if (count % b.cols() == 0) {
        col = 0;
        ++row;
      }
      else {
        ++col;
      }
      ++count;
      next();
    }
  }
  return *this;
}

// a *= b a is replaced with the product of a and b
SMatrix& SMatrix::operator*=(const SMatrix &b) throw(MatrixError) {

  if (cols() != b.rows() ) {
    throw MatrixError("Matrix size error");
  }

  SMatrix a(rows(),b.cols());
  a = *this;

  SMatrix c(rows(),b.cols());
  
  SMatrix::size_type count = 1;
  SMatrix::size_type cRow = 0;
  SMatrix::size_type cCol = 0;

  SMatrix::size_type aCol = 0;
  SMatrix::size_type aRow = cRow; // remains constant at ROW
  SMatrix::size_type bCol = cCol; // remains constant at COL
  SMatrix::size_type bRow = 0;

  for (unsigned int i = 0; i < (a.rows()*b.cols()); ++i) {
    ///cout << "c.cols(): " << c.cols() << endl;
////    cout << "cRow: " << cRow << " cCol: " << cCol << endl;
    
    ///c.setVal(cRow,cCol,7); // change to result of a double for loop

    aCol = 0;
    aRow = cRow; // remains constant at ROW
    bCol = cCol; // remains constant at COL
    bRow = 0;
    int value = 0;

    for (unsigned int j = 0; j < a.cols(); ++j) {
      ///cout << "aCol: " << aCol << " bRow: " << bRow << endl;
      value += a(aRow, aCol) * b(bRow, bCol);
      aCol++;
      bRow++;
    }

    ///cout << "NOW cRow: " << cRow << " cCol: " << cCol << "value: " << value << endl;
    c.setVal(cRow,cCol,value);

    if (count % c.cols() == 0) {
      cCol = 0;
      ++cRow;
    }
    else {
      ++cCol;
    }
    ++count;
  }


  *this = c;
  return *this;
  
}

// a(i,j)
int SMatrix::operator()(size_type i, size_type j) const throw(MatrixError) {
 
  int val = 0;
////////take off smatrix::///////////////////////////////////////////////////////////////////
  if (i >= numRows_ || j >= numCols_) {
    throw MatrixError("Matrix bound error");
  }
  else if (ridx_.count(i) == 0) {
    
  }
  else {

    int startPos = 0;
    int endPos = ridx_.at(i).second;
    int midPoint;


    while ((endPos - startPos) > 1) {
      midPoint = (startPos + endPos ) / 2;

      if (cidx_[ridx_.at(i).first + midPoint] == j) {               // if at column  j
        val = vals_[ridx_.at(i).first + midPoint];
        return val;
      }
      else if (cidx_[ridx_.at(i).first + midPoint] < j) {
        startPos = midPoint;
      }
      else {

        endPos = midPoint;
      }
    }

    if (cidx_[ridx_.at(i).first + startPos] == j) {  
      val = vals_[ridx_.at(i).first + startPos];
      
    }
    else if (cidx_[ridx_.at(i).first + endPos] == j) {
      val = vals_[ridx_.at(i).first + endPos];
    }

/*////
    for (unsigned int k = 0; k < ridx_.at(i).second; ++k) {  // go through all vals in row i
      if (cidx_[ridx_.at(i).first + k] == j) {               // if at column  j
        val = vals_[ridx_.at(i).first + k];
////        cout << "val: " << val << endl;
        //return val;
      }
    }  
*/////
  }
  return val;  
}

/* FUNCTIONS */

int SMatrix::findPos (int startPos, int endPos, int valPos) {

  int goalPos;
  int midpoint;

  if (startPos == endPos) {
    if (valPos < static_cast<int>(cidx_[startPos])) {
      goalPos = startPos;
    }
    else {
      goalPos = startPos+1;
    }
  }
  else {

    while ((endPos - startPos) > 1) {
      midpoint = (startPos + endPos ) / 2;
      if (valPos < static_cast<int>(cidx_[midpoint])) {
        endPos = midpoint;
      }
      else {
        startPos = midpoint;
      }
    }
    if (valPos < static_cast<int>(cidx_[startPos])) {
      goalPos = startPos;
    }
    else if (valPos > static_cast<int>(cidx_[endPos])) {
      goalPos = endPos+1;
    }
    else {
      goalPos = endPos;
    }
  }

////  cout << "goalPos: " << goalPos << endl;
  return goalPos;
}

void SMatrix::insertVal (int pos, int val, size_type row, size_type col) {

////  cout << "insertVal" << endl;
  if (vals_[pos-1] == val) {
////    cout << "vals[pos] was already " << val << endl;

  }

  bool done = false;
  if (ridx_.count(row) == 0) { // if row i not in map dont worry about
                               // checking for existing value at (row,col)
  }
  else {
    int startPos = ridx_.at(row).first;
    int endPos = startPos + (ridx_.at(row).second);
    
    while (startPos < endPos) {
      // if nonzero already in same matrix position
      if (cidx_[startPos] == col) { 
        vals_[startPos] = val;
        done = true;
        break;
      }
      startPos++;
    }
  }

  if (!done) {

  


  //////DO STUFF FOR VAL = 0

  //////IF CHANGING EXISTING VALUE TO A 0 OR NONZERO {

    // Update vals array
   // int tmpVal = vals_[pos];
    //vals_[pos] = val;

    // Update cols array
   // size_type tmpCol = cidx_[pos];
    //cidx_[pos] = col;

    // shift vals_ AND cidx_[pos+1....numVals_]
    // eg cidx_[pos+1] = tmp;

    // Update vals and cidx arrays
    for (int i = numVals_; i > pos; i--) {
      vals_[i] = vals_[i-1];
      cidx_[i] = cidx_[i-1];
    }
    vals_[pos] = val;
    cidx_[pos] = col;

    // Update ridx_ map
   // ridx_.insert(make_pair(row, make_pair(0,1))); 

    // updates ridx_ for 1 value
    if (ridx_.count(row) == 0) {
      ridx_.insert(make_pair(row, make_pair(pos,1)));
    }
    else {
      unsigned int prevNum = ridx_.at(row).second++;
////      cout << "prevNum: " << prevNum << endl;
      unsigned int prevPos = ridx_.at(row).first;
      ridx_.insert(make_pair(row, make_pair(prevPos,prevNum)));
    }
    
    for (auto it = ridx_.find(row); it != ridx_.cend(); ++it) {
      if (it != ridx_.find(row)) {
        (*it).second.first++;
      }
    }

    // increment total number of vals
    numVals_++;
  }
}

/* OPERATIONS */

bool SMatrix::setVal(size_type i, size_type j, int v) throw(MatrixError) {

  if (i >= numRows_ || j >= numCols_) {
    throw MatrixError("Matrix bound error");
  }

  bool moreMemory = false;



  if (v != 0) {
///// IF CAN SWAP EXISTING NUMBER, RETURN TRUE
    

////does this work or no arrow needed
//if this->(1,1) == 0 { then need to insert

/*
    cout << "numVals_: " << numVals_ << endl;
    // Update vals array
    vals_[numVals_] = v;

    // Update cols array
    cidx_[numVals_] = j;
    //cout << "cidx_[numVals_] = j: " << numVals_ << "] = " << j << endl;

    // increment total number of vals
    numVals_++;
*/

    // check array capacity
    if (numVals_ == valsLen_) {
      doubleSize();
      moreMemory = true;
    }

    //size_type a = 0;
    //unsigned int b = 1;
    if (ridx_.empty()) {
     // cout << "ridx was empty" << endl;
      vals_[numVals_] = v; // temp
      cidx_[numVals_] = j; // temp
      numVals_++;           // temp
      ridx_.insert(make_pair(i, make_pair(0,1))); 

    }
    else if (ridx_.count(i) == 0) {  // if row i not in map
      if (i > 0) {              // if inserting numbers into rows 1, 2, ...
        
        unsigned int rowBefore = i -1;
        while (ridx_.count(rowBefore) == 0) {
          rowBefore--;
        }
////        cout << "rowBefore is: " << rowBefore << endl; 
        unsigned int num = ridx_.at(rowBefore).first + ridx_.at(rowBefore).second;  
        ridx_.insert(make_pair(i, make_pair(num,1)));

//ridx_.insert(make_pair(i, make_pair(numVals_,1)));
        vals_[numVals_] = v; // temp
        cidx_[numVals_] = j; // temp
        numVals_++;           // temp
        for (auto it = ridx_.find(i); it != ridx_.cend(); ++it) { // temp
          if (it != ridx_.find(i)) {
            (*it).second.first++;
          }
        }
        //unsigned int num = ridx_.at(i-1).second;
        //ridx_.insert(make_pair(i, make_pair(num,1)));
      }
      else { 
        insertVal(0, v, i, j);
        //ridx_.insert(make_pair(i, make_pair(0,1))); 
      }
    }
    else { // row is in map
      int startPos = ridx_.at(i).first;
      int endPos = startPos + (ridx_.at(i).second - 1); // position of the last value in the row
      int goalPos = findPos (startPos, endPos, j);
      insertVal(goalPos, v, i, j); // goalPos is cidx index
    }

/*
      unsigned int prevNum = ridx_.at(i).second++;
      cout << "prevNum: " << prevNum << endl;
      unsigned int pos = ridx_.at(i).first;
      ridx_.insert(make_pair(i, make_pair(pos,prevNum)));
    }
*/

  // Setting a value to 0 
  } else {
    if (ridx_.empty()) {
      // do nothing
    }
    else if (ridx_.count(i) == 0) {
      // do nothing
    }
    else {
      // check if nonzero will become 0
      int startPos = ridx_.at(i).first;
      int endPos = startPos + (ridx_.at(i).second);

      while (startPos < endPos) {
        // if nonzero already in same matrix position
        if (cidx_[startPos] == j) { 
          //vals_[startPos] = v;
          
          //int goalPos = findPos (startPos, endPos, j);
          // Update vals and cidx arrays
          for (int k = startPos; k < numVals_; k++) {
            vals_[k] = vals_[k+1];
            cidx_[k] = cidx_[k+1];
          }
          //vals_[k]
          //cidx_[k]
  
          // Update ridx_ map
          ridx_.at(i).second--;
          
          for (auto it = ridx_.find(i); it != ridx_.cend(); ++it) {
            if (it != ridx_.find(i)) {
              (*it).second.first--;
            }
          }

          // delete row from map if no more values in row
          if (ridx_.at(i).second == 0) {
            ridx_.erase (i);
          }

          // decrement total number of vals
          numVals_--;

          break;
        }
        startPos++;
      }
    } 
  }

////
/*
  for (size_type i = 0; i < numCols_; ++i) {
    if (ridx_.count(i) != 0) { 
      cout << "ridx[" << i << "] -> " << ridx_.at(i).first << "," << ridx_.at(i).second << endl;
    }
  }
*/

/*
  if (ridx_.count(0) != 0) { 
    cout << "ridx[0] -> " << ridx_.at(0).first << "," << ridx_.at(0).second << endl;
  }
  if (ridx_.count(1) != 0) { 
    cout << "ridx[1] -> " << ridx_.at(1).first << "," << ridx_.at(1).second << endl; 
  }    
*/
  //ridx_.insert(pair<size_type, pair<size_t, unsigned int>>(i, (0,1)));

  //pair<size_type, std::pair<size_t, unsigned int>>   
 
////
/*
  for (int i = 0; i < numVals_; i++) {
    cout << "vals_[" << i << "] = " << vals_[i] << endl;
  }

  for (int i = 0; i < numVals_; i++) {
    cout << "cidx_[" << i << "] = " << cidx_[i] << endl;
  }
*/


  return moreMemory;
}

/* ITERATOR OPERATIONS */
void SMatrix::begin() const {
  //matrixPointer_ = &(0,0);
  //cout << vals_[0] << endl;
///  matrixPointer_ = &vals_[0];
  matrixPointerRow_ = 0;
  matrixPointerCol_ = 0;
  //cout << *matrixPointer_ << endl;
}

bool SMatrix::end() const {
  bool atEnd = false;
  ///if (*matrixPointer_ == vals_[valsLen_]) {  
 /// }
  if (matrixPointerRow_ >= numRows_ || matrixPointerCol_ >= numCols_) {
    atEnd = true;
  }
  return atEnd;
}

void SMatrix::next() const {
  // if at last column
  if (matrixPointerCol_ == numCols_-1) {
    // go to next row, column 0
    matrixPointerCol_ = 0;
    matrixPointerRow_++;
  }
  else {
    matrixPointerCol_++;
  }
}

int SMatrix::value() const {
  ///return *matrixPointer_;
  return getVal(matrixPointerRow_, matrixPointerCol_);
}

int SMatrix::getVal(size_type i, size_type j) const throw(MatrixError) {
 
  //cout << "i: " << i << endl;
  //cout << "j: " << j << endl;
  int val = 0;

  if (i >= numRows_ || j >= numCols_) {
    throw MatrixError("Matrix bound error");
  }
  // if row has no non-zeroes, return 0
  else if (ridx_.count(i) == 0) {
    
  }
  else {
    // go through all vals in row i
    for (unsigned int k = 0; k < ridx_.at(i).second; ++k) {  
      if (cidx_[ridx_.at(i).first + k] == j) {  // if at column  j
        val = vals_[ridx_.at(i).first + k];
        ///cout << "val: " << val << endl;
        //return val;
      }
    }  

  }
  return val;  
}

void SMatrix::doubleSize() {

////  cout << "Doubling size of arrays" << endl;

  int *newVals = new int[valsLen_ * 2];

  if (!newVals) {
    cerr << "Out of memory" << endl;
    exit(1);
  }

  size_type *newCidx = new size_type[valsLen_ * 2];

  if (!newCidx) {
    cerr << "Out of memory" << endl;
    exit(1);
  }

  for (int i = 0; i < valsLen_; ++i) {
    newVals[i] = vals_[i];
    newCidx[i] = cidx_[i];
  }
  delete [] vals_;
  vals_ = newVals;
  delete [] cidx_;
  cidx_ = newCidx;
  valsLen_ *= 2;
////  cout << "valsLen_ now " << valsLen_ << endl; 

}




