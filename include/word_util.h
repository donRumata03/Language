#pragma once

#include "pch.h"

extern initializer_list<char> word_dividers;
extern initializer_list<char> spacieves;
extern initializer_list<char> sentence_dividers;
extern string space_string;

inline bool is_big(const char c) {return (c >= 'A' && c <= 'Z') || ((c >= 'À') && (c <= 'ß')) || c == '¨'; }
inline bool is_word_divider(const char c) { return !(is_russian(c) || is_english(c) || is_digit(c)); }


bool is_russian(const string& word);
bool is_english(const string& word);
bool is_digital(const string& word);
