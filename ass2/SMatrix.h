#ifndef SMATRIX_H
#define SMATRIX_H

#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <utility>

#include <cstddef>


// matrix error class
class MatrixError : public std::exception {
 public:
  MatrixError(const std::string& what_arg) : _what(what_arg) { }
  virtual const char* what() const throw() { return _what.c_str (); }
  virtual ~MatrixError() throw() { }
 private:
  std::string _what;
};


// sparse matrix class
class SMatrix {
 public:
  // public interface
  // *** YOU SHOULD NOT MODIFY THE PUBLIC INTERFACE IN ANY WAY! ***

  // types
  typedef size_t size_type;

  // friends
  friend bool operator==(const SMatrix&, const SMatrix&);
  friend bool operator!=(const SMatrix&, const SMatrix&);
  friend SMatrix operator+(const SMatrix&, const SMatrix&) throw(MatrixError); 
  friend SMatrix operator-(const SMatrix&, const SMatrix&) throw(MatrixError); 
  friend SMatrix operator*(const SMatrix&, const SMatrix&) throw(MatrixError); 
  friend SMatrix transpose(const SMatrix&);
  friend std::ostream& operator<<(std::ostream&, const SMatrix&);
  
  // constructors
  SMatrix(size_type size = 1); // the default constructor
  SMatrix(size_type, size_type);
  SMatrix(std::istream&);
  SMatrix(const SMatrix&);   // copy
  SMatrix(SMatrix&&);        // move

  // operators  
  SMatrix& operator=(const SMatrix&);  // copy 
  SMatrix& operator=(SMatrix&&);       // move
  SMatrix& operator+=(const SMatrix&) throw(MatrixError);
  SMatrix& operator-=(const SMatrix&) throw(MatrixError);
  SMatrix& operator*=(const SMatrix&) throw(MatrixError);
  int operator()(size_type, size_type) const throw(MatrixError);
  
  // operations
  inline size_type rows() const { return numRows_; };
  inline size_type cols() const { return numCols_; };
  bool setVal(size_type, size_type, int) throw(MatrixError);

  // `iterator' operations
  void begin() const;
  bool end() const;
  void next() const;
  int value() const;

  // destructor
  ~SMatrix();
  
  // static members  
  static SMatrix identity(size_type);

 private:
  // private data members
  size_type numRows_;
  size_type numCols_;
  int numVals_;

  int *vals_;
  size_type *cidx_;

  int valsLen_;

  std::map< size_type, std::pair<size_t, unsigned int> > ridx_;

  mutable size_type matrixPointerRow_;
  mutable size_type matrixPointerCol_;

  int getVal(size_type i, size_type j) const throw(MatrixError);
  void doubleSize();
  int findPos (int startPos, int endPos, int valPos);
  void insertVal(int pos, int val, size_type row, size_type col);

  // you may/should augment the private interface as required by your implementation



};

#endif
