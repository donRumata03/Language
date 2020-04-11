#pragma once
#include  "pch.h"
#include "Basic_language.h"
#include <optional>
#include "word_tree.h"

class light_language : public basic_language
{
public:
	// Data storage:
	vector<vector<word>> blocks;
	bool has_word_variations;
	
	// To get pointer to word object:
	unordered_map<string, vector<word*>> variation_getter;

	// To get word properties if there are no variations
	unordered_map<string, word*> word_getter;
	unordered_map<string, word*> main_form_getter;
	unordered_map<string, vector<word>*> block_getter;
	
public:
	explicit light_language(const string& filename, bool enable_multithreading = true, bool enable_word_variations = true);

	void print_words() const { for (auto& block : blocks) { for (auto& word : block) { word.print_data(); } cout << "\n\n"; } }

	[[nodiscard]] word* get_word(const string& string_word) const;
	
	[[nodiscard]] string* get_string_main_form( const string& string_word) const;
	[[nodiscard]] word* get_main_form( const string& string_word) const;
	
	[[nodiscard]] optional<vector<word>*> get_block( const string& string_word, size_t block_index = 0) const;

	[[nodiscard]] vector<word*>* get_word_variations(const string& string_word);
	friend struct add_word_blocks;
};
