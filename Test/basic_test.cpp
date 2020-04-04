#include <Language.h>
#include "Light_language.h"
#include "morphem_parser.h"
#include "basic_util.h"


using namespace std;

constexpr bool enable_all_word_variations = true;


string russian_filename = R"(D:\Projects\Language\res\dictionary.txt)";
string test_filename = R"(D:\Projects\Language\res\little_test_data.txt)";


void word_construct_test()
{
	string test_string = "он      мест сущ ед муж им      46361";
	string easy_test_string = "он      мест     ед муж им      46361";

	word this_word(test_string);
	this_word.print_data();

	word easy_word(easy_test_string);
	easy_word.print_data();
}


void file_word_exist_test()
{
	vector<string> test_words = { "нельзя", "сопутствуемый", "несмотря" };
	string data_from_file = readFile(russian_filename);
	cout << "In file: " << std::boolalpha << endl;

	for (auto& w : test_words) {
		auto fnd = data_from_file.find("\n" + w + "\t");
		cout << w << " : " << (fnd != string::npos) << endl;
		if ((fnd != string::npos)) cout << data_from_file[fnd] << ";" << Slice(data_from_file, fnd, fnd + 100) << endl;
	}

	light_language lang(russian_filename);
	cout << endl << "From language: " << endl;
	for (auto& w : test_words) {
		vector<word*>* response = lang.get_word_variations(w);
		bool fnd = response && (!(*response).empty());
		cout << w << " : " << fnd << endl;
	}
}

void multiword_string_test()
{
	light_language lang(russian_filename);

	vector<string> ambiguous;

	for (auto& p : lang.variation_getter)
	{
		if (split_words(p.first).size() > 1) {
			ambiguous.push_back(join(" ", split_words(p.first)));
		}
	}
	// sort(ambiguous.begin(), ambiguous.end());
	word_tree w;
	w.add_data(ambiguous);
}


void multiword_string_tests()
{
	vector<string> test1 = {
		"",
		"тоже"
	};

	vector<string> test2 = {
		"тоже",
		""
	};


	vector<string> test3 = {
		"и тоже",
		"и тоже ещё",
		"тоже",
		""
	};

	word_tree t(word_tree_node_types::unifying);
	t.add_data(test3);

	auto m1 = split_by_first_word(test1);
	auto m2 = split_by_first_word(test2);
	auto m3 = split_by_first_word(test3);

	cout << m1 << endl << m2 << endl << m3;
}


void language_test()
{
	light_language l(russian_filename);
	// light_language l(test_filename);
	string user_string;
	while (true) {

		cin >> user_string;
		if constexpr (!enable_all_word_variations) {
			word* w = l.get_main_form(user_string);
			if (!w) cout << "Try again!" << endl;
			else { w->print_data(); cout << endl; }
		}
		else {
			auto words = l.get_word_variations(user_string);
			if (!words) cout << "Can`t find this word :(\n";
			else {
				cout << "These " << (*words).size() << " words found:\n";
				for (auto& word : *words) {
					word->print_data();
					cout << "\n";
				}
			}
		}
		cout << "_________________________________________________\n";
	}
}

void morph_test(){
	morphem_parser::load();
	morphem_parser::store_in_human_file(R"(D:\Projects\Language\res\output\morph_freq.txt)", 1000);
	/*
	string to_decay = "а'встр/о/-ита'л/о/-франц/у'з/ск/ий";
	string atom = "австро-итало-французский";
	cout << *extract_word_decay(to_decay, atom) << endl;
	*/
}

void morph_decay_test()
{
	morphem_splitter::load_prestfixes();
	morphem_splitter::print_loaded_prestfixes();
}


void tree_construct_test()
{
	vector<string> example_data = {
		"в него",
		"в его лицо",
		"в его рожу",
		"а ну",
		"а ну тебя",
		"а то",
		"а то что же",
		"а то что ж"
	};
	word_tree tr(word_tree_node_types::unifying);
	tr.add_data(example_data);
}

void test_word_filtering()
{
	string test_phrase = "а ну тебя, а то! В его лицо... Они взяли и кинули камень.";
	vector<string> parsed_phrase = {
		"а",
		"ну",
		"тебя",
		"а",
		"то",
		"в",
		"его",
		"лицо",
		"они",
		"взяли",
		"и",
		"бросили",
		"камень",
	};

	vector<string> example_data = {
		"в него",
		"в его лицо",
		"в его рожу",
		"а ну",
		"а ну тебя",
		"а то",
		"а то что же",
		"а то что ж"
	};
	word_tree tr;
	tr.add_data(example_data);
	
	cout << compound_collocations(parsed_phrase, tr) << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	// language_test();
	// word_construct_test();

	// file_word_exist_test();

	// multiword_string_test();

	// tree_construct_test();

	test_word_filtering();
	
	return 0;
}
