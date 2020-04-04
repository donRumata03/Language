#include "pch.h"

/*
#include "file_walker.h"
#include <filesystem>
#include <iostream>

vector<std::string> recursive_lsdir(const string& string_path)
{
	vector<string> res;
	vector<fs::path> subdirs;
	const fs::path path = string_path;

	fs::recursive_directory_iterator start(string_path);
	fs::recursive_directory_iterator _end;

	copy_if(start, _end, back_inserter(subdirs), [](const fs::path & p) {
		return fs::is_directory(p);
		});

	for (auto& p : subdirs)
	{
		res.push_back(p.string());
	}

	return res;
}

vector<std::string> lsdir(const string& string_path)
{
	vector<string> res;
	vector<fs::path> subdirs;
	const fs::path path = string_path;


	fs::directory_iterator start(string_path);
	fs::directory_iterator _end;

	copy_if(start, _end, back_inserter(subdirs), [](const fs::path & p) {
		return fs::is_directory(p);
		});

	res.reserve(subdirs.size());
	for (auto& p : subdirs)
	{
		res.push_back(p.string());
	}

	return res;
}

vector<string> find_files(const string& string_path, string&& extension)
{
	vector<string> res;
	vector<fs::path> subdirs;
	const fs::path path = string_path;

	fs::recursive_directory_iterator start(string_path);
	fs::recursive_directory_iterator _end;

	copy_if(start, _end, back_inserter(subdirs), [&](const fs::path & p) {
		return (fs::is_regular_file(p)) && (extension.empty() || get_extension(*new string(p.string())) == extension);
		});

	for (auto& p : subdirs)
	{
		res.push_back(p.string());
	}

	return res;
}

string get_extension(string& filename)
{
	string res;
	auto it = filename.c_str() + filename.size() - 1;
	while (it != filename.data()) {
		res.push_back(*it);
		if (*it == '.') break;
		--it;
	}
	reverse(res.begin(), res.end());
	return res;
}

*/