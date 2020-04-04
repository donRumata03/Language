#include "pch.h"
#include "word_util.h"


initializer_list<char> word_dividers  = {' ', '\n', ',', '.', '!', '-', '/', ';', '?', ':', '\\', '#', '"', '\'', '$', '%', '(', ')', '<', '>', '=', '+', '*', '@', '[', ']', '^', '_', '\t', '^'}; //  \n,.-!?:;/\"��#$%&'()�*+<=>@[]\\^_`{|}~\t\v\f\r
initializer_list<char> sentence_dividers = { '.', '\n', '?', '!' };
initializer_list<char> spacieves = { ' ', '\n', '\t', '\r', '\v', '\a', '\f', '\b' };
string space_string = " \n\r\t\v\f\a\b";

bool is_russian(const string& word) {
	for (char c : word) {
		if (!is_russian(c)) {
			return false;
		}
	}
	return true;
}

bool is_english(const string& word) {
	for (char c : word) {
		if (!is_english(c)) {
			return false;
		}
	}
	return true;
}

bool is_digital(const string& word) {
	for (char c : word) {
		if (!is_digit(c)) {
			return false;
		}
	}
	return true;
}
