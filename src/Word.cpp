#include "pch.h"
#include "Word.h"
#include "word_util.h"
#include "word_checker.h"




word::word(const vector<string>& vec)
{
	if (vec.empty()) return;
	bool space_flag = false;
	for (auto& el : vec) if (find_first_of(el.begin(), el.end(), begin(space_string), end(space_string)) == el.end()) { space_flag = true; break; }
	if (!space_flag) return;

	int type_index = -1;
	for (uint i = 1; i < vec.size(); i++) {
		bool found_type = in(string_to_word_type_converter, vec[i]);
		if (found_type)
		{
			type_index = i;
			break;
		}
		/*for (const auto& prop : string_to_word_type_converter) {
			if (prop.first == vec[i]) {
				type_index = i;

				break;
			}
		}*/
	}
	if (type_index == -1) {
		if constexpr (WORD_DEBUG_LEVEL >= 1) { cout << "Unknown word type here: " << join(" ", vec) << endl; raw_data = join(" ", vec); } return;
	}

	data = Join(" ", Slice(vec, 0, type_index)); 
	
	// raw_properties = Slice(vec, 1 + type_index, vec.size());
	word_type = string_to_word_type_converter[vec.at(type_index)];

	bool has_number = false;
	if (!vec.empty() && is_digital(vec.back())) {
		index = stoll(vec.back());
		has_number = true;
	}

	auto for_props = Slice(vec, static_cast<size_t>(type_index) + 1, (has_number) ? (vec.size() - 1) : (vec.size()));
	
	if (is_nameive(word_type)) {
		if constexpr (WORD_DEBUG_LEVEL >= 3) cout << "Word " << data << " is nameive!" << endl;
		unknown_properties = make_nameive_properties(*this, for_props);
	}
	else if (is_verbal(word_type)) {
		if constexpr (WORD_DEBUG_LEVEL >= 3) cout << "Word " << data << " is verbal!" << endl;
		unknown_properties = make_verbal_properties(*this, for_props);
	}
	has_semantic = has_semantic_cond(word_type);

	/* 
	switch (word_type) {
	case word_types::noun:
		// this->properties = new noun_properties();
		has_semantic = true;
		break;
	case word_types::adjective:
		// this->properties = new adjective_properties();
		has_semantic = true;
		break;
	case word_types::verb:
		// this->properties = new verb_properties();
		has_semantic = true;
		break;

	case word_types::particle:
		has_semantic = false;

	case word_types::conjunction:
		has_semantic = false;

	case word_types::interjection:
		has_semantic = false;
		
	case word_types::introduce:
		has_semantic = false;
		
	case word_types::preposition:
		has_semantic = false;
		
	case word_types::pronoun:
		has_semantic = false;
		break;

	default:
		// this->properties = new word_properties();
		// has_implemented_type = false;
		has_semantic = true;
		break;
	}
	*/

	/*
	if constexpr (WORD_DEBUG_LEVEL >= 3) cout << data << " " << std::boolalpha << has_semantic << " " << has_implemented_type << " " << word_type_to_string_converter[word_type] << endl;

	if (has_implemented_type) {
		auto for_props = Slice(vec, static_cast<size_t>(type_index) + 1, (has_number) ? (vec.size() - 1) : (vec.size()));
		unknown_properties = properties->make_properties(for_props);
	}
	else {
		unknown_properties = Slice(vec, static_cast<size_t>(type_index) + 1, has_number ? vec.size() - 1 : vec.size());
	}
	*/
}



void word::print_data() {
	if (word_type == word_types::unknown) { cout << "This is unknown word with raw text = " << raw_data << endl; return; }
	cout << "Word: " << data << "; ";
	cout << "Type: " << this->get_type() << "; ";
	
	if (this->free_property != free_properties::unknown) cout << "Has special properties!!! : " << free_properties_to_string_converter[this->free_property] << endl;
	
	cout << "Index: " << this->index << ";\n";

	/*
	if (properties) {
		cout << "Known properties ";
		properties->print_data();
	}
	*/

	cout << "Known properties:" << endl;
	map<string, string> to_print = {
		{ "Word type", word_type_to_string_converter[this->word_type] },
		{ "Word gender", gender_to_string_converter[this->gender] },
		{ "Word quantity", quantity_to_string_converter[this->quantity] },
		{ "Word case", case_to_string_converter[this->word_case] },
		{ "Word personality", personality_to_string_converter[this->personality] },
		{ "Word soulness", soulness_to_string_converter[this->soulness] },
		{ "Word tence", tence_to_string_converter[this->word_tence] },
	};
	cout << to_print << endl;
	
	cout << "Unknown properties: ";
	print(unknown_properties);

	cout << "\n";
	cout << "Has semantic meaning: " << std::boolalpha << has_semantic;
	cout << "\n\n";
}

vector<string> make_nameive_properties(word& target_word, vector<string>& properties)
{
	vector<string> unknowns;
	for (string& for_prop : properties) {
		bool is_known = false;
		// Case
		if (string_to_case_converter.find(for_prop) != string_to_case_converter.end()) {
			target_word.word_case = string_to_case_converter[for_prop];
			is_known = true;
		}
		
		// Gender
		else if (string_to_gender_converter.find(for_prop) != string_to_gender_converter.end()) {
			target_word.gender = string_to_gender_converter[for_prop];
			is_known = true;

		}

		// Quantity
		else if (string_to_quantity_converter.find(for_prop) != string_to_quantity_converter.end()) {
			target_word.quantity = string_to_quantity_converter[for_prop];
			is_known = true;

		}

		// Soulness: noun personal:
		else if (target_word.word_type == word_types::noun) {
			if (string_to_soulness_converter.find(for_prop) != string_to_soulness_converter.end()) {
				target_word.soulness = string_to_soulness_converter[for_prop];
				is_known = true;
			}
		}

		if (!is_known) unknowns.push_back(for_prop);
	}
	return unknowns;
}

vector<string> make_verbal_properties(word& word, vector<string>& properties)
{
	/*
	 * Returns unknown properties
	 */
	vector<string> unknowns;
	for (auto& for_prop : properties) {
		bool is_known = false;
		// Common:

		// Tence:
		if (in(string_to_tence_converter, for_prop)) {
			word.word_tence = string_to_tence_converter[for_prop];
			is_known = true;
		}

		// Quantity:
		if (in(string_to_quantity_converter, for_prop)) {
			word.quantity = string_to_quantity_converter[for_prop];
			is_known = true;
		}

		// Gender:
		if (in(string_to_gender_converter, for_prop)) {
			word.gender = string_to_gender_converter[for_prop];
			is_known = true;
		}

		// Verb personal:
		if (word.word_type == word_types::verb) {
			if (in(string_to_personality_converter, for_prop)) {
				word.personality = string_to_personality_converter[for_prop];
				is_known = true;
			}
		}

		// Communion personal:
		if (word.word_type == word_types::communion) {
			if (in(string_to_case_converter, for_prop)) {
				word.word_case = string_to_case_converter[for_prop];
				is_known = true;
			}
		}
		
		if (!is_known) unknowns.push_back(for_prop);
	}
	return unknowns;
}

/* 
verb_properties::verb_properties(vector<string> & properties) {
	for (string prop : properties) {
		if (string_to_tence_converter.find(prop) != string_to_tence_converter.end()) {
			this->word_tence = string_to_tence_converter[prop];
		}
	}
}

adjective_properties::adjective_properties(vector<string> & properties) {
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



noun_properties::noun_properties(vector<string> & properties) {
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

vector<string> noun_properties::make_properties(vector<string> & properties) {
	vector<string> res;
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
		else {
			res.push_back(prop);
		}
	}
	return res;
}

vector<string> adjective_properties::make_properties(vector<string> & properties) {
	vector<string> res;
	for (string &prop : properties) {
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
		else {
			res.push_back(prop);
		}
	}
	return res;
}

vector<string> verb_properties::make_properties(vector<string> & properties) {
	vector<string> res;
	for (string &prop : properties) {
		if (string_to_tence_converter.find(prop) != string_to_tence_converter.end()) {
			this->word_tence = string_to_tence_converter[prop];
		}
	}
	return res;
}

*/
