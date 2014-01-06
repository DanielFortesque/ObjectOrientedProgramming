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

Lexicon wordList("EnglishWords.dat");
vector<string> finalLadder;
  

// find all possible next words, by changing 1 letter
// EXTEND WORD FUNCTION
void extendWord (string word, queue<vector<string>>& queue) {
  string nextWord;
  cout << "nextWords: " << endl;
  for (unsigned int i = 0; i < word.length(); i++) {
    nextWord = word; // reset nextWord
    for (char c = 'a'; c <= 'z'; c++) {
      nextWord[i] = c;
      if (wordList.containsWord(nextWord) && nextWord.compare(word) != 0) {
        cout << nextWord << endl;
        vector<string> newLadder = finalLadder;
        newLadder.push_back(nextWord);
        queue.push(newLadder); 
      }
    }
    cout << endl;
  }
}

void printLadder (vector<string> ladder) {

  cout << "Found ladder: ";
  for (auto vi = ladder.begin(); vi != ladder.end(); ++vi) {
    //string word = *vi;
    cout << *vi << " ";
  }
  cout << endl;
}

int main() {

  // Read in start, end words
  
  

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

////  Lexicon wordList("EnglishWords.dat");

  //cout << "wordList has size: " << wordList.size() << endl;
  
/*
  if (wordList.containsWord(startWord)) {
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



  finalLadder.push_back(startWord);

  queue<vector<string>> wordLadder;

  // extend startWord, enqueueing expansions to wordLadder
  extendWord(startWord, wordLadder);

/*
  // find all possible next words, by changing 1 letter
  // EXTEND WORD FUNCTION
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
*/

  // Go through wordLadder queue  
  while (!wordLadder.empty()) {
    if ( wordLadder.front().back().compare(endWord) == 0 ) {
      //wordLadder.front().push_back(endWord); // add endWord to end
      printLadder(wordLadder.front());
/// cout << "Found ladder: " << startWord << " " << endWord << endl;
      wordLadder.pop();
      break; 
    }
    else {
      // extend this word and enqueue its expansions
      // also dequeue/pop current word
      extendWord(wordLadder.front().back(), wordLadder);
      cout << "Popped: " << wordLadder.front().back() << endl;
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






