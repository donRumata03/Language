#pragma once

#include "pch.h"

struct word_dividing_struct
{
	vector<string> prefixes;
	vector<string> roots;
	vector<string> root_splitters;
	vector<string> postfixes;
	string ending;

	void print() const
	{
		if (roots.empty())
		{
			cout << "We have no ideas about this word...\n";
			return;
		}
		cout << "I suppose, the root(s) is(are): " << roots << endl;

		if (!root_splitters.empty()) cout << "The root splitters are: " << root_splitters << endl;

		if (!postfixes.empty()) {
			cout << "Postfixes: ";
			for (auto& p : postfixes)
			{
				cout << p << " ";
			}
			cout << endl;
		}

		if (!prefixes.empty()) {
			cout << "Prefixes: ";
			for (auto& p : prefixes)
			{
				cout << p << " ";
			}
			cout << endl;
		}

		if (!ending.empty())
		{
			cout << "Ending: " << ending;
		}
	}
};



namespace morphem_splitter
{
	// Functions:
	map<string, vector<string>> extract(string& s);
	
	void load_prestfixes();
	void print_loaded_prestfixes();
	word_dividing_struct decay_word(const string& word_string);

	// Data:
	inline map<string, vector<string>> prefixes;
	inline map<string, vector<string>> postfixes;
	inline map<string, vector<string>> endings;
	
}
