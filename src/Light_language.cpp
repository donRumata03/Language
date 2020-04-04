#include "pch.h"
#include "Light_language.h"
#include <thread>
#include <optional>


struct add_word_blocks {
	vector<vector<word>>& destination;
	size_t start_idx, end_idx;
	vector<vector<vector<string>>>& src;
	add_word_blocks(vector<vector<vector<string>>>& _src, vector<vector<word>>& _destination, const size_t _start_idx,
	                const size_t _end_idx) :
					destination(_destination), start_idx(_start_idx),
					end_idx(_end_idx), src(_src) {}
	void operator() ()
	{
		/*
		 * For thread
		 * End isn`t included
		 */
		for (size_t block_index = start_idx; block_index < end_idx; block_index++) {
			destination[block_index].reserve(src[block_index].size());
			for (auto& for_word : src[block_index]) {
				destination[block_index].emplace_back(for_word);
			}
		}
	}
};


light_language::light_language(const string& filename, const bool enable_multithreading, const bool enable_word_variations) :
				basic_language(filename, enable_multithreading), has_word_variations(enable_word_variations)
{
	// TODO: Make special split function! (for string / strings, but not chars)

	Timer wording;

	blocks.reserve(raw_blocks.size());
	if (!enable_multithreading) {
		for (auto& for_block : raw_blocks) {
			blocks.emplace_back();
			blocks.back().reserve(for_block.size());

			for (auto& for_word : for_block) {
				blocks.back().emplace_back(for_word); // Construct word from vector<string>
				block_getter[blocks.back().back().data] = &blocks.back(); // Add it to block getter
				word_getter[blocks.back().back().data] = &blocks.back().back();
				main_form_getter[blocks.back().back().data] = &blocks.back()[0];

				if (enable_word_variations) {
					auto it = variation_getter.find(blocks.back().back().data);
					if (it == variation_getter.end()) {
						variation_getter.insert({ blocks.back().back().data, {&blocks.back().back()} });
					}
					else {
						it->second.push_back(&blocks.back().back());
					}
				}
			}
		}
	}
	else {
		// Copy geometry:
		for (int i = 0; i < raw_blocks.size(); i++) {
			blocks.emplace_back();
		}
		// Start threads:
		// Tasks example = { { 1, 100 /* Block indexes */ }, { 100, 200 }, { 200, 300 } };
		auto tasks = distribute_task_ranges(raw_blocks.size(), 12);

		vector<thread> threads;
		for (auto& task : tasks) {
			add_word_blocks this_worker(raw_blocks, blocks, task.first, task.second);
			threads.emplace_back(this_worker);
		}
		for(auto& this_thread : threads) {
			this_thread.join();
		}

		// Add everything to the unordered maps:
		
		for(auto& block : blocks) {
			for(auto& this_word : block) {
				
				if (enable_word_variations) {
					this_word.parent_block = &block;
					auto it = variation_getter.find(this_word.data);
					if (it == variation_getter.end()) {
						variation_getter.insert({ this_word.data, {&this_word} });
					}
					else {
						it->second.push_back(&this_word);
					}
				}
				else {
					word_getter[this_word.data] = &this_word;
					block_getter[this_word.data] = &block; // Add it to block getter
					main_form_getter[this_word.data] = &block[0];
				}
			}
		}
	}
	if constexpr (BASIC_LANG_DEBUG_LEVEL >= 1) cout << "Word structuring done! It took: " << wording.get_time() << " ms\n" \
													<< "_____________________________________________\n";
	
	vector<vector<vector<string>>>().swap(raw_blocks);
}

word* light_language::get_word(const string& string_word)
{
	assert(!has_word_variations);
	auto founded = word_getter.find(string_word);
	if (founded != word_getter.end()) return founded->second;
	return nullptr;
}

word* light_language::get_main_form(const string& string_word)
{
	assert(!has_word_variations);
	auto block = get_block(string_word);
	if (block) return &(*block)->front();
	return nullptr;
}



string* light_language::get_string_main_form(const string& string_word)
{
	assert(!has_word_variations);
	auto founded = block_getter.find(string_word);
	if (founded != block_getter.end()) return &founded->second->front().data;
	return nullptr;
}


optional<vector<word>*> light_language::get_block(const string& string_word, const size_t block_index)
{
	if (!has_word_variations) {
		auto f = block_getter.find(string_word);
		if (f != block_getter.end()) {
			return f->second;
		}
		return nullopt;
	}
	auto f = variation_getter.find(string_word);
	if (f == variation_getter.end()) return nullopt;
	return f->second[block_index]->parent_block;
}

vector<word*>* light_language::get_word_variations(const string& string_word)
{
	assert(has_word_variations);
	auto f = variation_getter.find(string_word);
	if (f != variation_getter.end()) return &f->second;
	return nullptr;
}


/*
pair<bool, string> light_language::get_string_main_form(const string& word)
{
	auto got = get_string_block(word);
	if (got && !got->empty()) return {true, (*got)[0]};
	return { false, nullptr };
}

word* light_language::get_main_form(const string& word)
{
	auto got = get_string_block(word);
	if (got && !got->empty()) return get_word((*got)[0]);
	return nullptr;
}


vector<string>* light_language::get_string_block(const string& word)
{
	auto founded = block_getter.find(word);
	if (founded != block_getter.end()) return founded->second->data;
	return nullptr;
}
*/
