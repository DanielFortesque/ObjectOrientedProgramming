/**
 * Provides the implementation of the Production class, which
 * is simply a wrapper for the sequence of items (where items are terminals
 * or nonterminals).  It also completes the implementation of the ifstream
 * constructor, which was really the only thing missing from the .h
 */

#include "production.h"

/**
 * Constructor Implementation: Production
 * --------------------------------------
 * Constructor that initializes the Production based
 * on the content of a file.
 */

Production::Production(ifstream& infile)
{
  
  string currentLine;
   
  while (infile >> currentLine) {

    char lastChar = currentLine.back();

    if (lastChar == ';') {
      break;
    }
    else if (lastChar == '}') {
      phrases.push_back (currentLine); // push invalid character
      break;
    }
    else {
      phrases.push_back (currentLine);
    }   
  }
}
