/**
 * Provides the implementation of the full RSG application, which
 * relies on the services of the built-in string, ifstream, vector,
 * and map classes as well as the custom Production and Definition
 * classes provided with the assignment.
 */
 
#include <map>
#include <fstream>
#include <cstdlib>
#include "definition.h"
#include "production.h"

using namespace std;

/**
 * Takes a reference to a legitimate infile (one that's been set up
 * to layer over a file) and populates the grammar map with the
 * collection of definitions that are spelled out in the referenced
 * file. 
 *
 * @param infile a valid reference to a flat text file storing the grammar.
 * @param grammar a reference to the STL map, which maps nonterminal strings
 *                to their definitions.
 */

static void readGrammar(ifstream& infile, map<string, Definition>& grammar)
{
 
  string currentLine;
   
  while (!infile.eof()) {

    getline(infile,currentLine);
      
    char lastChar = currentLine.back();

    if (lastChar == '{') {
    
      Definition definition (infile);

      // Now put Definition in grammar map

      grammar.insert ( pair<string, Definition>(definition.getNonterminal(),definition) );
    }
  }
  infile.close();
}

static void printProduction( const map<string, Definition>& grammar, vector<string> sentence)
{

  bool nonterminalExpanded = false;
  vector<string> nextSentence;

  // Generate next sentence, expanding at most 1 nonterminal
  for (auto vi = sentence.begin(); vi != sentence.end(); ++vi) {
    string word = *vi;
    
    if (word.front() == '<' && !nonterminalExpanded) { //if 1st nonterminal
      map<string,Definition>::const_iterator it;
      it = grammar.find(word);

      // if expansion is in grammar
      if (it != grammar.end()) {
        const Production nextProduction = it->second.getRandomProduction();
        for (auto pi = nextProduction.begin(); pi != nextProduction.end(); ++pi) {
          nextSentence.push_back(*pi);
        }
        nonterminalExpanded = true;
      }  
      // else expansion references an undefined non-terminal, exit program
      else {
        cerr << "Could not find \"" << word << "\" in the grammar file." << endl;
        exit(0);
      }
       
    }
    else if (nonterminalExpanded) {
      nextSentence.push_back(word);
    }
    else {
      nextSentence.push_back(word);
    }
  }

  // If nonterminals were expanded we print next Sentence
  if (nonterminalExpanded == true) {
    printProduction(grammar, nextSentence);
  }
  else {
    for (auto vi = nextSentence.begin(); vi != nextSentence.end(); ++vi) {
      vi++;
      if (vi != nextSentence.end()) {
        string nextWord = *vi;
        vi--;
        if (nextWord.compare(",") == 0 || nextWord.compare(".") == 0 ||
            nextWord.compare("?") == 0 || nextWord.compare("!") == 0 ||
            nextWord.compare(":") == 0) {
          cout << *vi;
        } 
        else {
          cout << *vi << " ";
        }
      }
      else {
        vi--;
        cout << *vi << " ";
      }
    }
  }
}

/**
 * Takes a const reference to a grammar stored in a map and prints
 * sentences produced by applying the grammar rules. The number of
 * sentences should be as specified by the second parameter.
 *
 * @param grammar a reference to the STL map, which maps nonterminal strings
 *                to their definitions.
 * @param numSentencesNeeded number of sentences to be produced
 */
 
static void generateRandomSentences(const map<string, Definition>& grammar, 
				    int numSentencesNeeded)
{
   
  for (int i = 0; i < numSentencesNeeded; i++) {
    map<string,Definition>::const_iterator it;
    it = grammar.find("<start>");
    
    const Production startProduction = it->second.getRandomProduction();

    vector<string> sentence;
    // Copy startProduction into a vector
    for (auto pi = startProduction.begin(); pi != startProduction.end(); ++pi) {
      string word = *pi;
      sentence.push_back(word);
    }
    
    printProduction (grammar, sentence);
  }
  cout << endl;

}


 
/**
 * Performs the rudimentary error checking needed to confirm that
 * the client provided a grammar file.  It then continues to
 * open the file, read the grammar into a map<string, Definition>,
 * and then print out the total number of Definitions that were read in.
 *
 * @param argc the number of tokens making up the command that invoked
 *             the RSG executable.  There must be at least two arguments,
 *             and only the first two are used.
 * @param argv the sequence of tokens making up the command, where each
 *             token is represented as a '\0'-terminated C string.
 */

int main(int argc, char *argv[])
{
  if (argc == 1) {
    cerr << "You need to specify the name of a grammar file." << endl;
    cerr << "Usage: rsg <path to grammar text file>" << endl;
    return EXIT_FAILURE;
  }
  
  ifstream grammarFile(argv[1]);
  if (grammarFile.fail()) {
    cerr << "Failed to open the file named \"" << argv[1] << "\". "
            "Check to ensure the file exists." << endl;
    return EXIT_FAILURE;
  }
  
  // things are looking good...
  map<string, Definition> grammar;
  readGrammar(grammarFile, grammar);
  generateRandomSentences(grammar, 3);

  return EXIT_SUCCESS;
}
