#pragma once

#include "pch.h"
#include <optional>

constexpr bool debug_morph = true;

optional<vector<string>> extract_word_decay(string& to_decay, string& atomic_word);

namespace morphem_parser
{
	inline unordered_map<string, vector<string>> parsed_data;

	inline vector<pair<string, size_t>> m_prefix_freq, m_ending_freq;

	inline vector<string> prefixes;
	inline vector<string> postfixes;
	inline vector<string> endings;
	inline vector<string> roots;
	
	
	void load(const string& filename = R"(D:\Projects\Language\res\morphem.txt)");
	void load_and_parse_data(const string& filename);
	void parse_word_parts();

	void store_in_human_file(string&& filename, size_t amount);
	void store_in_machine_files(const string& filename);
};
