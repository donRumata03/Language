#pragma once

#include "pch.h"
// #include <include/file_walker.h>


inline void congatanate_jsons(const string& dir_name)
{
	auto filenames = find_files(dir_name, ".json");
	cout << filenames;
	for(auto& path : filenames) {
		auto str = readFile(path);
		// cout << str << endl;
		auto this_json = json::parse(str, nullptr);
		cout << this_json;
	}
}

