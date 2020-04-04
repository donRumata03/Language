#pragma once
#include "pch.h"
#include "Word.h"

using namespace std;


constexpr auto BASIC_LANG_DEBUG_LEVEL = 1; // 0 For no debug; 1 for time benchmarking; 2 for printing all data;


class basic_language
{
public:
	vector<vector<vector<string>>> raw_blocks;
	
	explicit basic_language(const string& filename, bool enable_multithreading = true);
};

