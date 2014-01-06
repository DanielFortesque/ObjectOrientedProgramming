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
#include <algorithm>

Lexicon wordList("EnglishWords.dat");
vector<string> finalLadder;
unsigned int maxLength = finalLadder.max_size(); // arbitrary number
string endWord;

// distanceFromGoal - calculates number of letters in word that do not match to goal word
// Used to stop expanding partial ladders that would get too long
unsigned int distanceFromGoal(string word, string goal) {
  int count = 0;
  for (unsigned int i = 0; i < word.size(); i++) {
    if (word[i] != goal[i]) {
      count++;
    }
  }
  return count;
}

// wordUsed -  Takes in vector and a word and returns true if word is in the vector
bool wordUsed (vector<string> words, string word) {
  bool used = false;
  for (auto vi = words.begin(); vi != words.end(); ++vi) {
    string currentWord = *vi;
    if (currentWord == word) {  
      used = true;
      break;
    }
  }
  return used;
}

/* extendWord - find all possible next words, by changing 1 letter
*  words - partial word ladder
*  wordLadders - queue of partial word ladders
*/
void extendWord (vector<string> words, queue<vector<string>>* wordLadders) {
  string nextWord;
  for (unsigned int i = 0; i < words.back().length(); i++) {
    nextWord = words.back(); // reset nextWord
    for (char c = 'a'; c <= 'z'; c++) {
      nextWord[i] = c;

      // nextWord must be in lexicon AND must not be expanded word
      if (wordList.containsWord(nextWord) && nextWord.compare(words.back()) != 0 && !wordUsed(words, nextWord) ) {
        vector<string> newLadder = words;
        newLadder.push_back(nextWord);
        if (nextWord == endWord) { // if final word found, save maxLength
          maxLength = newLadder.size();
          
        }
        wordLadders->push(newLadder); 
      }
    }
  }
}

void printLadders (vector<vector<string>> ladders) {

  if (ladders.empty()) {
    cout << "No ladder found." << endl;
  }
  else {
    cout << "Found ladder: ";
    for (auto vi = ladders.begin(); vi != ladders.end(); ++vi) {
      vector<string> l = *vi;
      for (auto vi2 = l.begin(); vi2 != l.end(); ++vi2) {    
        cout << *vi2 << " ";
      }
      cout << endl;
    }
  }
}

int main() {

  // Read in start, end words
  
  cout << "Enter start word (RETURN to quit): ";
  string startWord;
  getline(cin, startWord);
  if (startWord.empty()) {
    return 0;
  }

  cout << "Enter destination word: ";
  getline(cin, endWord);

  finalLadder.push_back(startWord);

  queue<vector<string>> *wordLadders = new queue<vector<string>>;

  vector<vector<string>> allLadders;

  // extend startWord, enqueueing expansions to wordLadder
  extendWord(finalLadder, wordLadders);

  // Go through wordLadder queue  
  while (!wordLadders->empty() && wordLadders->front().size() <= maxLength) {
    if ( wordLadders->front().back().compare(endWord) == 0 ) { // If ladder found
      maxLength = wordLadders->front().size();

      allLadders.push_back(wordLadders->front());
            
      wordLadders->pop();
    }
    else if (wordLadders->front().size() < maxLength) { // dont want to expand vectors already at the max length
      // extend this word and enqueue its expansions
      // also dequeue/pop current word

      // extend word if distance from endword to goalword is <= (maxLength-size)
      if ( distanceFromGoal(wordLadders->front().back() , endWord) <= (maxLength - wordLadders->front().size()) ) {
        
        extendWord(wordLadders->front(), wordLadders);
        wordLadders->pop();

      }
      else {
        wordLadders->pop();
      }
    }
    else {
      wordLadders->pop();    
    }
  }

  // Sort vector of vectors
  sort (allLadders.begin(), allLadders.end(), less<vector<string>>());
  printLadders(allLadders);

	return 0;
}
