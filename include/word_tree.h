#pragma once
#include <utility>


#include "pch.h"

enum class word_tree_node_types
{
	unifying,
	simple,
	end
};

unordered_map<string, vector<string>> split_by_first_word(const vector<string>& strings);

struct word_tree
{
	vector<word_tree> word_trees;
	word_tree_node_types type = word_tree_node_types::end;
	string m_string;
	string total_string;

	explicit word_tree(const word_tree_node_types& type = word_tree_node_types::unifying, string str = "", string total_string = "") : type (type),
				m_string(std::move(str)),
					total_string(std::move(total_string)) {}

	/**
	 * \brief 
	 * \param data : ёxample: m_string = "а", data = {"", "ну", "ну тебя", "то", "то что же", "то что ж" }
	 */
	void add_data(const vector<string>& data)
	{
		
		vector<pair<string, vector<string>>> to_construct = get_sorted_elements(split_by_first_word(data));

		/*
		if (is_in("", data)) {
			to_construct.push_back({ "" , {} });
			// word_trees.ёmplace_back("", word_tree_node_types::end);
		}
		sort(data.begin(), data.end());

		vector<string> for_this_word;
		string last_word;
		bool begin_flag = true;
		for (size_t el_index = 0; el_index < data.size(); el_index++)
		{
			auto& expr = data[el_index];
			if (expr.empty()) {
				begin_flag = false;
				continue;
			}
			auto splitted = split(expr);
			string first_word = splitted[0];
			
			
			if (((el_index == data.size() - 1) || 
				(first_word != last_word)) && !begin_flag)
			{
				if (data.size() - 1 == el_index)
				{
					for_this_word.push_back(join(" ", Slice(splitted, 1)));
					last_word = first_word;
				}
				// auto& constructed_word = word_trees.emplace_back(last_word, word_tree_node_types::simple);
				// constructed_word.add_data(for_this_word);
				to_construct.emplace_back(last_word, for_this_word);
				for_this_word.clear();
			}

			for_this_word.push_back(join(" ", Slice(splitted, 1)));


			last_word = first_word;
			begin_flag = false;
		}
		*/

		// cout << split_by_first_word(data) << endl;
	
		word_trees.reserve(to_construct.size());
		for (auto& p : to_construct)
		{
			if (p.first.empty())
			{
				word_trees.emplace_back(word_tree_node_types::end);
			}
			else {
				auto& this_tree = word_trees.emplace_back(word_tree_node_types::simple, p.first, total_string + " " + p.first);
				this_tree.add_data(p.second);
			}
		}

	}
};


inline vector<string> compound_collocations(const vector<string>& words, word_tree& t)
{
	word_tree* this_node = &t;
	vector<string> res;

	for(size_t w_index = 0; w_index < words.size(); w_index++)
	{
		const string& w = words[w_index];
		bool found = false;

		vector<string> this_colloc;
		
		if (this_node->word_trees.empty()) {
			res.push_back(this_node.total_string);
			this_node = t;
		}
		
		for (auto& next_node : this_node.word_trees)
		{
			if (next_node.m_string == w)
			{
				this_node = next_node;
				found = true;
				break;
			}
		}

		if (!found) {
			this_node = t;
			w_index--;
		}
		
	}

	return res;
}


inline unordered_map<string, vector<string>> split_by_first_word(const vector<string>& strings)
{
	unordered_map<string, vector<string>> res;
	for (auto& str : strings)
	{
		if (str.empty()) {
			res[""] = {};
			continue;
		}


		auto splitted = split(str);
		string first_word = splitted[0];
		string other_words = join(" ", Slice(splitted, 1));
		
		auto fnd = res.find(first_word);
		if (fnd == res.end()) {
			res.insert({first_word, { other_words }});
		}
		else
		{
			fnd->second.push_back(other_words);
		}
	}

	return res;
}
