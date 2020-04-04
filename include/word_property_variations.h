#pragma once

/*
#define WORD_VARIATIONS
#include <Word.h>

struct name_properties : word_properties {
	word_case word_case = word_case::unknown;
	gender word_gender = gender::unknown;
	quantity word_quantity = quantity::unknown;
	soulness word_soulness = soulness::unknown;

	explicit name_properties(vector<string>& properties)
	{
		for (string prop : properties) {
			if (string_to_case_converter.find(prop) != string_to_case_converter.end()) {

				this->word_case = string_to_case_converter[prop];
			}
			else if (string_to_gender_converter.find(prop) != string_to_gender_converter.end()) {
				this->word_gender = string_to_gender_converter[prop];
			}
			else if (string_to_soulness_converter.find(prop) != string_to_soulness_converter.end()) {
				this->word_soulness = string_to_soulness_converter[prop];
			}
			else if (string_to_quantity_converter.find(prop) != string_to_quantity_converter.end()) {
				this->word_quantity = string_to_quantity_converter[prop];
			}
		}
	}
	name_properties() = default;

	
};

struct noun_properties : word_properties {
	word_case word_case = word_case::unknown;
	gender word_gender = gender::unknown;
	quantity word_quantity = quantity::unknown;
	soulness word_soulness = soulness::unknown;

	noun_properties(vector<string>& properties);
	noun_properties() = default;
	vector<string> make_properties(vector<string>& properties) override;

	void print_data() override
	{
		cout << "(Noun properties): \n";

		print(map<string, string> {
			{ "Gender", gender_to_string_converter[word_gender]},
			{ "Soulness", soulness_to_string_converter[word_soulness] },
			{ "Quantity", quantity_to_string_converter[word_quantity] },
			{ "Case", case_to_string_converter[word_case] },
		});
	}
};


struct adjective_properties : word_properties {
public:
	word_case word_case = word_case::unknown;
	gender word_gender = gender::unknown;
	quantity word_quantity = quantity::unknown;
	soulness word_soulness = soulness::unknown;

	adjective_properties(vector<string>& properties);
	adjective_properties() = default;
	vector<string> make_properties(vector<string>& properties) override;

	void print_data() override {
		cout << "(Adjective properties): \n";

		print(map<string, string> {
			{ "Gender", gender_to_string_converter[word_gender]},
			{ "Soulness", soulness_to_string_converter[word_soulness] },
			{ "Quantity", quantity_to_string_converter[word_quantity] },
			{ "Case", case_to_string_converter[word_case] },
		});
	}
};


struct verb_properties : public word_properties {
	tence word_tence = tence::unknown;

	verb_properties(vector<string>& properties);
	verb_properties() = default;

	vector<string> make_properties(vector<string>& properties) override;

	void print_data() override
	{
		cout << "(Verb properties): \n";
		cout << map<string, string> { {"Tence", tence_to_string_converter[word_tence] } } << endl;
	}
};

*/
