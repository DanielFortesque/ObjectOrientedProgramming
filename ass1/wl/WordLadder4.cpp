
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

#include <algorithm> // i added this

Lexicon wordList("EnglishWords.dat");
vector<string> finalLadder;
  

// find all possible next words, by changing 1 letter
// EXTEND WORD FUNCTION
void extendWord (vector<string> words, queue<vector<string>>& queue) {
  string nextWord;
///  cout << "nextWords: " << endl;
  for (unsigned int i = 0; i < words.back().length(); i++) {
    nextWord = words.back(); // reset nextWord
    for (char c = 'a'; c <= 'z'; c++) {
      nextWord[i] = c;
      // nextWord must be in lexicon AND must not be expanded word
      if (wordList.containsWord(nextWord) && nextWord.compare(words.back()) != 0) {
///        cout << nextWord << endl;
        vector<string> newLadder = words;
        newLadder.push_back(nextWord);
        queue.push(newLadder); 
      }
    }
///    cout << endl;
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

void printLadders (vector<vector<string>> ladders) {

  cout << "Found ladder: ";
  for (auto vi = ladders.begin(); vi != ladders.end(); ++vi) {
    vector<string> l = *vi;
    for (auto vi2 = l.begin(); vi2 != l.end(); ++vi2) {    
      //string word = *vi;
      cout << *vi2 << " ";
    }
    cout << endl;
  }
  //cout << endl;
}

int main() {

  // Read in start, end words
  
  

  cout << "Enter start word (RETURN to quit): ";
  string startWord;
  //cin >> startWord;
  getline(cin, startWord);
  if (startWord.empty()) {
    return 0;
  }

  cout << "Enter destination word: ";
  string endWord;
  //cin >> endWord;
  getline(cin, endWord);

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

  queue<vector<string>> wordLadders;

  vector<vector<string>> allLadders;

  // extend startWord, enqueueing expansions to wordLadder
  extendWord(finalLadder, wordLadders);

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

  unsigned int maxLength = finalLadder.max_size(); // arbitrary number
  //cout << "maxLength: " << maxLength << endl;

  // Go through wordLadder queue  
  while (!wordLadders.empty() && wordLadders.front().size() <= maxLength) {
    if ( wordLadders.front().back().compare(endWord) == 0 ) {
      maxLength = wordLadders.front().size();
      //wordLadder.front().push_back(endWord); // add endWord to end
///      printLadder(wordLadders.front());

      allLadders.push_back(wordLadders.front());
            

/// cout << "Found ladder: " << startWord << " " << endWord << endl;
      wordLadders.pop();
////break; 
    }
    else {
      // extend this word and enqueue its expansions
      // also dequeue/pop current word
      extendWord(wordLadders.front(), wordLadders);
///      cout << "Popped: " << wordLadders.front().back() << endl;
      wordLadders.pop();
    }
  
  }


  // SORT VECTOR OF VECTORS
  sort (allLadders.begin(), allLadders.end(), less<vector<string>>());
  printLadders(allLadders);

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






