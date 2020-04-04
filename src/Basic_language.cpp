#include "pch.h"
#include "Basic_language.h"
#include <mylibs.hpp>

basic_language::basic_language(const string& filename, bool enable_multithreading)
{
	// TODO: Fix bugs : too much blocks!!!
	
	Timer file_loading;
	string raw_data = readFile(filename);
	if constexpr (BASIC_LANG_DEBUG_LEVEL >= 1) cout << "Language file loaded: Time taken: " << file_loading.get_time() << " ms\n";

	if constexpr (BASIC_LANG_DEBUG_LEVEL >= 2) cout << "Raw data: " << raw_data << endl << endl;

	Timer block_parsing;
	size_t char_index = 0;
	bool in_line = false, in_block = false;
	size_t last_new_lines = 0;
	string this_word;
	for (char c : raw_data) {

		if (c == '\n') {
			if (in_line) {
				raw_blocks.back().emplace_back(split(this_word));
				string().swap(this_word);
			}
			in_line = false;
			
			last_new_lines++;
			if (last_new_lines >= 2) { in_block = false; last_new_lines = 0; }
			else {
				
			}
		}
		else if (c != '\r') {
			last_new_lines = 0;
			if (!in_block) raw_blocks.emplace_back();
			this_word.push_back(c);
			
			in_line = true;
			in_block = true;
		}
		
		char_index++;
	}

	if (raw_data[raw_data.size() - 1] != '\n') raw_blocks.back().push_back(split(this_word));


	if constexpr (BASIC_LANG_DEBUG_LEVEL >= 1) cout << "Blocks are parsed! Time: " << block_parsing.get_time() << " ms" << endl;
	
	if constexpr (BASIC_LANG_DEBUG_LEVEL >= 2) {
		for (const auto& v : raw_blocks) {
			print(v);
			cout << "\n" << endl;
		}
	}
}
