/*
 * File: WordLadder.cpp
 * --------------------
 * Name: Daniel Musso
 * This file is the starter project for the word ladder problem on Assignment #1.
 */

#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <vector>
#include <iostream>


int main() {

  // does stuff for ONE-LETTER-TRANSFORMATIONS

  // Read in start, end words
  // put start word in Word Ladder vector
  // for each letter that can be changed to form new word,
  // enqueue this word into a NEW queue
  

  cout << "Enter start word (RETURN to quit): ";
  string startWord;
  cin >> startWord;

  cout << "Enter destination word: ";
  string endWord;
  cin >> endWord;

/*
  vector<string> wordLadder;

  wordLadder.push_back(startWord);
  wordLadder.push_back(endWord);
*/

  //cout << endl;

/*
  cout << "startWord: " << startWord << endl; 
  cout << "endWord: " << endWord << endl; 

  cout << "First Word in Vector: " << wordLadder.front() << endl;
  cout << "Last Word in Vector: " << wordLadder.back() << endl;

  cout << "Found ladder: " << startWord << " " << endWord << endl;
*/

  Lexicon wordList("EnglishWords.dat");

  //cout << "wordList has size: " << wordList.size() << endl;
  
/*
  if (wordList.containsWord(startWlord)) {
    cout << "wordList contains: " << startWord << endl;
  }
*/

  /*
  cout << "Characters of " << startWord << endl;
  
  for(auto it = startWord.begin(); it != startWord.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
*/

  queue<string> wordLadder;

  // find all possible next words, by changing 1 letter
  string nextWord;
  cout << "nextWords: " << endl;
  for (unsigned int i = 0; i < startWord.length(); i++) {
    nextWord = startWord; // reset nextWord
    for (char c = 'a'; c <= 'z'; c++) {
      nextWord[i] = c;
      if (wordList.containsWord(nextWord)) {
        cout << nextWord << endl;
        wordLadder.push(nextWord); 
      }
    }
    cout << endl;
  }

  // Go through wordLadder queue  
  while (true) {
    if ( wordLadder.front().compare(endWord) == 0 ) {
      cout << "Found ladder: " << startWord << " " << endWord << endl;
      break; 
    }
    else {
      cout << "Popped: " << wordLadder.front() << endl;
      wordLadder.pop();
    }
  
  }



  /*
  // PRINT ALL 2-LETTER WORDS
  string word = "xx";
  for (char c0 = 'a'; c0 <= 'z'; c0++) {
  
    word[0] = c0;
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
      word[1] = c1;
      if (wordList.containsWord(word)) {
        cout << word << endl;
      }
    }
  }
  */



	return 0;
}
