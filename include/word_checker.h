#pragma once

#include "Word.h"

constexpr bool debug_word_checker = false;

// Nameive checking:

inline bool is_word_type_nameive(word_types word_type)
{
	/*
	 * If it`t noun or adjective or pronoun
	 */
	vector<word_types> good_types = {
		word_types::pronoun,
		word_types::adjective,
		word_types::noun
	};
	return is_in(word_type, good_types);
}

inline bool is_string_word_type_nameive(string& for_word)
{
	auto f = string_to_word_type_converter.find(for_word);
	if (f == string_to_word_type_converter.end()) {
		return false;
	}
	else {
		return is_word_type_nameive((*f).second);
	}
}

inline bool is_word_nameive(word* word)
{
	/*
	 * If it`t noun or adjective or pronoun
	 */

	auto t = word->word_type;
	return is_word_type_nameive(t);
}

inline bool is_nameive(word* word)
{
	return is_word_nameive(word);
}

inline bool is_nameive(string& s)
{
	return is_string_word_type_nameive(s);
}

inline bool is_nameive(word_types word_type)
{
	return is_word_type_nameive(word_type);
}



// Verbal checking:

inline bool is_word_type_verbal(const word_types word_type)
{
	/*
	 * If it`t verb or communion or verb_communion
	 */
	vector<word_types> good_types = {
		word_types::communion,
		word_types::verb,
		word_types::verb_communion
	};
	return is_in(word_type, good_types);
}

inline bool is_string_word_type_verbal(string& for_word)
{
	auto f = string_to_word_type_converter.find(for_word);
	if (f == string_to_word_type_converter.end()) {
		return false;
	}
	return is_word_type_verbal((*f).second);
}

inline bool is_word_verbal(word* word)
{
	auto t = word->word_type;
	return is_word_type_verbal(t);
}


// Useful, comfortable

inline bool is_verbal(word* word)
{
	return is_word_verbal(word);
}

inline bool is_verbal(string& s)
{
	return is_string_word_type_verbal(s);
}

inline bool is_verbal(word_types word_type)
{
	return is_word_type_verbal(word_type);
}



// Has semantics:

inline bool has_semantic_cond(word* word)
{
	return in(has_semantic_checker, word->word_type);
}

inline bool has_semantic_cond(string& for_type)
{
	return in(has_semantic_checker, string_to_word_type_converter[for_type]);
}

inline bool has_semantic_cond(const word_types word_type)
{
	if constexpr (debug_word_checker) if (!in(has_semantic_checker, word_type))
	{
		cout << "What`s about the type ";
		print_word_type(word_type);
	}
	return has_semantic_checker[word_type];
}
