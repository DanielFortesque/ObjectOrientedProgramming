/**
 * Provides the implementation of
 * the Definition class, which is really
 * nothing more than an ordered pair: a nonterminal
 * attached to a string.
 */ 
 
#include "definition.h"
#include "random.h"

/**
 * Constructor: Definition
 * -----------------------
 * Constructs an instance of a Definition object
 * based on the content of the specified file.
 */

Definition::Definition(ifstream& infile)
{

  string currentLine;
 
  while (!infile.eof()) {
    getline(infile,currentLine);
    
    while (currentLine.back() == ' ') {
      currentLine.pop_back();
    }
  
    char lastChar = currentLine.back();

    // if current line is the nonterminal
    if (lastChar == '>') {
      nonterminal = currentLine;
      Production production(infile);
      possibleExpansions.push_back (production);
      
      // when there are more productions in current definition
      // and previous production was valid

      auto pi = production.begin();
      string firstWord = *pi; // first Word of previous Production

      while ( firstWord.compare("}") != 0 ) {

        Production production(infile);

        possibleExpansions.push_back (production);
        pi = production.begin();
        firstWord = *pi;
      }

      // delete the '}' production
      possibleExpansions.pop_back ();

    }
    else if (currentLine.empty()) {
      break;
    }
  }
}

/**
 * Method: getRandomProduction
 * ---------------------------
 * Returns a const reference to one of the
 * embedded Productions.
 */

const Production& Definition::getRandomProduction() const
{
  
  int numProductions = possibleExpansions.size();

  // choose a random production, (int between 0 and numProductions-1)
  static RandomGenerator randomGenerator;
  int randomProduction = randomGenerator.getRandomInteger(0, numProductions-1);
  return possibleExpansions.at(randomProduction);
}




