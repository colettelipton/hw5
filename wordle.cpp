#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(set<string>& words, const set<string>& dict, string in, string floating, unsigned idx, unsigned d);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in, // how many letters the word is, 5 = ----- or --t--
    const std::string& floating, // a string of letters that have already been guessed that are in the word somewhere
    const std::set<std::string>& dict) // a dictionary
{
    // Add your code here
		// you're given some sort of string with dashes, recurse through
		// string until find -, then loop through every single possibility
		// in floating. try those out (put them into the string). your own 
		// temporary string you can modify. substitute that in for a dash. 
		// run through all the floatings. then run through all the chars in the 
		// alphabet and do the same thing. then base case is if the length 
		// of the word is the length of the original word. just check if it'same
		// in the dictionary
		set<string> words;
		unsigned dashes = 0;

		// counts number of dashes// count number of dashes
		for(unsigned i = 0; i < in.size(); i++){
			if(in[i] == '-') dashes++;
		}

		helper(words, dict, in, floating, 0, dashes);

		return words;

}

// Define any helper functions here
void helper(set<string>& words, const set<string>& dict, string in, string floating, unsigned idx, unsigned d){
	string temp;

	// stops when reaches end of length
	if(idx == in.length()){
		// check if it's in the dictionary
		if(dict.find(in) != dict.end()){
			words.insert(in);
		}
		return;
	}

	// if less dashes than floating
	if(d < floating.size()){
		return;
	}

	// recurse if not a -
	if(in[idx] != '-'){
		helper(words, dict, in, floating, idx + 1, d);
	}

	// loop through every single possibility in floating
	for(unsigned i = 0; i < floating.size(); i++){
		temp = in;
		temp[idx] = floating[i];
		string newfloating = floating.substr(0,i) + floating.substr(i + 1, floating.size() - i - 1);
		helper(words, dict, temp, newfloating, idx + 1, d - 1);
	}

	if(d > floating.size()){
		// loop through every single possibility in the alphabet
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		for(unsigned i = 0; i < 26; i++){
			temp = in;
			temp[idx] = alphabet[i];
			helper(words, dict, temp, floating, idx + 1, d - 1);
		}
	}
}
