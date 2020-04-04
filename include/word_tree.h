#pragma once
#include <utility>


#include "pch.h"

enum class word_tree_node_types
{
	unifying,
	simple,
	end
};

struct word_tree
{
	vector<word_tree> word_trees;
	word_tree_node_types type = word_tree_node_types::end;
	string m_string;

	explicit word_tree(string str, const word_tree_node_types& type = word_tree_node_types::end) : type (type), m_string(std::move(str)) {}

	/**
	 * \brief 
	 * \param data : ёxample: m_string = "а", data = {"", "ну", "ну тебя", "то", "то что же", "то что ж" }
	 */
	void add_data(vector<string>& data)
	{
		
		vector<pair<string, vector<string>>> to_construct;

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
				(first_word != last_word)) && !begin_flag /*for_this_word.empty()*/)
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

		word_trees.reserve(to_construct.size());
		for (auto& p : to_construct)
		{
			if (p.first.empty())
			{
				word_trees.emplace_back("", word_tree_node_types::end);
			}
			else {
				auto& this_tree = word_trees.emplace_back(p.first, word_tree_node_types::simple);
				this_tree.add_data(p.second);
			}
		}

	}
};


inline void clear_multiwords(const vector<string>& words, const word_tree& t)
{
	word_tree this_node = t;
	vector<string> res;

	for(auto& w : words)
	{
		for (auto& next_node : this_node.word_trees)
		{
			if (1)
			{
				
			}
		}
	}
}

