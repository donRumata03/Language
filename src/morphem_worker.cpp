#include "pch.h"

#include "morphem_worker.h"


map<string, vector<string>> morphem_splitter::extract(string& s)
{
	return my_lang_extract(s, [](auto & param) { return is_english(param); }, \
		[](auto & param) { return is_russian(param); });
}

void morphem_splitter::load_prestfixes()
{
		// File_paths:
		const char endings_path[] = R"(D:\Projects\Language\res\endings.txt)";
		const char postfixes_path[] = R"(D:\Projects\Language\res\postfixes.txt)";
		const char prefixes_path[] = R"(D:\Projects\Language\res\prefixes.txt)";

		string raw_endings_data = readFile(endings_path);
		string raw_postfixes_data = readFile(postfixes_path);
		string raw_prefixes_data = readFile(prefixes_path);

		endings = extract(raw_endings_data);
		postfixes = extract(raw_postfixes_data);
		prefixes = extract(raw_prefixes_data);
}

void morphem_splitter::print_loaded_prestfixes()
{
	cout << "Prefixes: {" << endl;
	cout << prefixes << endl;
	cout << "}" << endl;

	cout << "Postfixes: {" << endl;
	cout << postfixes << endl;
	cout << "}" << endl;


	cout << "Endings: {" << endl;
	cout << endings << endl;
	cout << "}" << endl;
}

word_dividing_struct morphem_splitter::decay_word(const string& word_string)
{
	word_dividing_struct res;

	// First of all, decay prefixes
	return {};
}
