#pragma once

#include "pch.h"


using namespace std;


constexpr auto WORD_DEBUG_LEVEL = 0;


enum class free_properties : int // Независимые свойства слова
{
	unknown = -1,
	modal,
	predicate
};


enum class word_types : int {	// Части речи:
	unknown = -1,
	noun,							// Существительное
	verb,							// Глагол
	adjective,						// Прилагательное
	adverb,							// Наречие
	preposition,					// Предлог
	particle,						// Частича
	interjection,					// Междометие
	conjunction,					// Союз
	communion,						// Причастие
	verb_communion,					// Деепричастие
	count,							// Числительное
	pronoun,						// Местоимение
	introduce,						// Вводное слово
	predicative						// Предикатив
};


enum class word_case : int { // Падеж:
	unknown = -1,
	nominative,						// Именительный
	parent,							// Родительный
	accusative,						// Винительный
	dative,							// Дательный
	ablative,						// Творитльный
	prepositional					// Предложный
};


enum class gender : int { // Род:
	unknown = -1,
	male = 0,							// Мужкой род
	female,								// Женский род
	neuter								// Средний род
};


enum class quantity : int {				// Число:
	unknown = -1,
	single,								// Единственное число
	multiple							// Множественное число
};


enum class soulness : int { // Одушевлённость:
	unknown = -1,
	ensouled,				// Одушевлённое
	non_ensouled			// Неодушевлённое
};

enum class tence : int { // Время:
	unknown = -1,
	past,		// Прошедшее
	present,	// Настоящее
	future		// Будущее
};

enum class word_personality : int {
	unknown = -1,
	first,
	second,
	third
};



extern map<string, free_properties> string_to_free_properties_converter;
extern map<string, word_types> string_to_word_type_converter;
extern map<string, gender> string_to_gender_converter;
extern map<string, quantity> string_to_quantity_converter;
extern map<string, soulness> string_to_soulness_converter;
extern map<string, tence> string_to_tence_converter;
extern map<string, word_case> string_to_case_converter;
extern map<string, word_personality> string_to_personality_converter;

extern map<word_types, string> word_type_to_string_converter;
extern map<free_properties, string> free_properties_to_string_converter;
extern map<gender, string> gender_to_string_converter;
extern map<quantity, string> quantity_to_string_converter;
extern map<soulness, string> soulness_to_string_converter;
extern map<tence, string> tence_to_string_converter;
extern map<word_case, string> case_to_string_converter;
extern map<word_personality, string> personality_to_string_converter;

extern map<word_types, bool> has_semantic_checker;

/*
struct word_properties {
	virtual void print_data() { cout << "Property of unknown type..." << endl; }
	virtual vector<string> make_properties(vector<string>& properties) { cout << "ERROR" << endl; return vector<string>(); }
};
*/

void print_word_free_property(const free_properties& free_property, ostream& out = cout);
void print_word_type(const word_types& word_type, ostream& out = cout);
void print_word_gender(const gender& gender, ostream& out = cout);
void print_word_quantity(const quantity& quantity, ostream& out = cout);
void print_word_soulness(const soulness& soulness, ostream& out = cout);
void print_word_case(const word_case& word_case, ostream& out = cout);
void print_word_tence(const tence& tence, ostream& out = cout);




struct word {
	// Raw data:
	vector<string> unknown_properties;
	string data;
	string raw_data;

	// Word properties:
	word_types word_type = word_types::unknown;
	
	word_case word_case = word_case::unknown;
	tence word_tence = tence::unknown;
	soulness soulness = soulness::unknown;
	quantity quantity = quantity::unknown;
	gender gender = gender::unknown;
	word_personality personality = word_personality::unknown;

	// Other stuff:

	// Deprecated: word_properties* properties = nullptr;
	vector<word>* parent_block;
	long long index = -1;
	free_properties free_property = free_properties::unknown;
	bool has_semantic = false;

	word() = default;
	explicit word(const string& s) : word(split(s)) {}
	explicit word(const vector<string>& vec);
	
	void print_data();
	
	[[nodiscard]] string get_type() const {
		return word_type_to_string_converter[word_type];
	}
};


vector<string> make_nameive_properties(word& target_word, vector<string>& properties);
vector<string> make_verbal_properties(word& word, vector<string>& properties);



#ifndef WORD_VARIATIONS

#include "word_property_variations.h"

#endif