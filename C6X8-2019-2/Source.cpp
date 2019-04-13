// C6-X6-2019.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
Exercise 6 Chapter 6 from
"Software - Principles and Practice using C++" by Bjarne Stroustrup
EXERCISE: Write a program that checks if a sentence is correct accoring to the
English grammar in Section6.4.1 (plus the 'the' modification). Assume that every
sentence is terminated by a full stop (.) surrounded by whitespace.

For each sentence entered, the program should simply repsond "OK" or "Not OK"

Hint - don't bother with tokens, just read into a string using >>.
*/

#include "pch.h"
#include "C:\Users\mark.alexieff\source\repos\std_lib_facilities.h"


//------------------------------------------------------------------------------

/*	This version of get_sentence takes a reference to a vector of strings and
	gets input from cin.  Adds each string to the vector.  Stops when it gets to
	a newline character.

	Continues to ask for sentences until  "XXX" is entered as first word of sentence
*/

vector<string> conjunctions;			// vectors to hold the vocab/parts of speech
vector<string> nouns;					// they get initialized later on
vector<string> verbs;
vector<string> articles;

bool copy_sentence(vector<string>& s1, int pos, vector<string>& s2);


bool get_sentence(vector<string>& s) {
	string temp{ "poop" };
	char ch{ NULL };
	bool more_to_read{ true };

	if (s.size() > 0) s.clear();				// This is intended to clear the 
												// vector from a previous run
												// not sure it is the right function
												// Seem to be the righ one

	while (more_to_read) {					// Loop to read strings until newline
		cin.get(ch);
		if (!iswspace(ch)) {
			cin.putback(ch);
			cin >> temp;
			s.push_back(temp);
		}
		else if (ch == '\n') more_to_read = false;			//  added to handle sentences with whitespace at the end
		if (temp == "XXX" && s.size() == 1) return false;	// false on return means we are tired of playing

	}
	return true;							// no real meaning currently
}

/*	sentence as currently written just outputs the sentence to cout
	Need to change this to be my output fucntion	*/

bool output_sentence(vector<string>& s) {
	for (int i = 0; i < s.size(); i++) {
		cout << s[i];
		cout << ' ';
	}
	cout << '\n';
	return true;
}

// Set of functions to check grammar type of string
// we pass a reference to the vector containing the elements and check to see if s is in them

bool is_noun(vector<string>& n, string s);
bool is_verb(vector<string>& v, string s);
bool is_conjunction(vector<string>& c, string s);
bool is_article(vector<string>& a, string s);
bool is_full_stop(string s);
bool is_sentence(vector<string>& s);

int main()

try
{
	// Variables// 
	vector<string> sentence_to_test;
	bool ret_value{ true };
	bool keep_going{ true };

	// Initialize vectors

	conjunctions.push_back("and");				// Initialize the vectors of parts of speech
	conjunctions.push_back("or");				// likely there is a better way to do this
	conjunctions.push_back("but");

	nouns.push_back("birds");
	nouns.push_back("fish");
	nouns.push_back("C++");

	verbs.push_back("rules");
	verbs.push_back("fly");
	verbs.push_back("swim");

	articles.push_back("the");

	cout << "Welcome to the English Grammar Checker V1.0\n";

	// While Keep Going is True has not been entered //

	while (keep_going) {
		cout << "Please enter a sentence to test - end sentence with newline.\n";
		cout << "Enter 'XXX' to terminate program.\n\n > ";
		keep_going = get_sentence(sentence_to_test);
		ret_value = output_sentence(sentence_to_test);

		cout << "\nTesting part of grammar checking fucntions\n\n";

		/*
		note the cooler way of iterating though a vector using iterator
		rather the indexes - point to note is that an iterator is a pointer
		*/


		for (auto it = begin(sentence_to_test); it != end(sentence_to_test); ++it) {
			cout << *it << "\t\tis ";
			if (is_noun(nouns, *it)) cout << "a noun!\n";
			else if (is_verb(verbs, *it)) cout << "a verb!\n";
			else if (is_conjunction(conjunctions, *it)) cout << "a conjunction!\n";
			else if (is_article(articles, *it)) cout << "an article!\n";
			else if (is_full_stop(*it)) cout << "a full stop!\n";
			else cout << "not in the Grammar!\n\n";
		}

		ret_value = is_sentence(sentence_to_test);  // call to the function that does all the work

		output_sentence(sentence_to_test);
		cout << " ---- ";
		if (ret_value) cout << "is a sentence!\n\n";
		else cout << "is NOT a sentence!\n\n";

	}

	keep_window_open();
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}

/* stupid function to copy a vector from postion pos onwards */
bool copy_sentence(vector<string>& s1, int pos, vector<string>& s2)
{
	int i{ 0 };
	s2.clear();
	for (auto it = begin(s1); it != end(s1); ++it) {
		if (i++ <= pos) continue;
		s2.push_back(*it);
	}
	return true;
}

bool is_noun(vector<string>& n, string s) {
	for (auto it = begin(n); it != end(n); ++it) {
		if (*it == s) return true;
	}
	return false;
}

bool is_verb(vector<string>& n, string s) {
	for (auto it = begin(n); it != end(n); ++it) {
		if (*it == s) return true;
	}
	return false;
}

bool is_conjunction(vector<string>& n, string s) {
	for (auto it = begin(n); it != end(n); ++it) {
		if (*it == s) return true;
	}
	return false;
}

bool is_article(vector<string>& n, string s)
{
	for (auto it = begin(n); it != end(n); ++it) {
		if (*it == s) return true;
	}
	return false;
}

bool is_full_stop(string s) {
	if (s == ".") return true;
	else return false;
}

bool is_sentence(vector<string>& temp_sentence)
{
	vector<string> temp_sentence2;  // apparently you don't have to initialize a vector to have storage allocated - 
									// meaning you can pass as a reference


	int cur_position{ 0 };
	bool ret_value{ true };

	//check to see if ends in full stop
	if (!is_full_stop(temp_sentence.back())) return false;

	//check to see if starts with a noun (but need to check if starts with article first)
	if (is_article(articles, temp_sentence[cur_position])) {
		cur_position++;														// look at next word
		if (!is_noun(nouns, temp_sentence[cur_position])) return false;  //initial article not follow by a noun
	}
	else if (!is_noun(nouns, temp_sentence[cur_position])) return false;  // first word is not a noun

	cur_position++;  // first word is a noun or article plus noun, look at next word

	if (!is_verb(verbs, temp_sentence[cur_position])) return false;  //noun not followed by a verb

	cur_position++;  // have noun or article+noun followed by verb, look at next word.

	/* next bit checks to see if we are at the last word in the sentence - has to be a full stop*/

	if (cur_position + 1 == temp_sentence.size() && is_full_stop(temp_sentence[cur_position])) return true;

	/* otherwise it has to be a conjunction or it is not a sentence */

	if (is_conjunction(conjunctions, temp_sentence[cur_position])) {
		ret_value = copy_sentence(temp_sentence, cur_position, temp_sentence2);
		if (!is_sentence(temp_sentence2)) return false;
		else return true;
	}
	/* if we get to here then we have something other than a conjunction following a verb */
	return false;

}
