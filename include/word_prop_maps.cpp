#include "pch.h"

#include <Word.h>
#include <word_util.h>



// Word to enums convertors:


// Free characteristics
map<string, free_properties> string_to_free_properties_converter{
	{"мод", free_properties::modal},
	{"предик", free_properties::predicate}
};

// Backwards converter
map<free_properties, string> free_properties_to_string_converter{
	{free_properties::predicate, "Предикативный"},
	{free_properties::modal, "Модальный"},
	{free_properties::unknown, "НЕОПОЗНАННЫЙ"}
};

void print_word_free_property(free_properties& free_property, ostream& out)
{
	out << free_properties_to_string_converter[free_property];
}

// Type:
map<string, word_types> string_to_word_type_converter{
	{"союз", word_types::conjunction},
	{"сущ", word_types::noun},
	{"част", word_types::particle},
	{"межд", word_types::interjection},
	{"прл", word_types::adjective},
	{"гл", word_types::verb},
	{"прч", word_types::communion},
	{"нар", word_types::adverb},
	{"сущ", word_types::noun},
	{"сущ", word_types::noun},
	{"дееп", word_types::verb_communion},
	{"числ", word_types::count},
	{"мест", word_types::pronoun},
	{"ввод", word_types::introduce},
	{"предл", word_types::preposition},
	{"предик" , word_types::predicative}
};

// Backward converter:
map<word_types, string> word_type_to_string_converter{
	{word_types::unknown, "НЕИЗВЕСТНАЯ ЧАСТЬ РЕЧИ"},
	{word_types::conjunction, "Союз"},
	{word_types::noun, "Существительное"},
	{word_types::particle, "Частица" },
	{word_types::interjection, "Междометие" },
	{word_types::adjective, "Прилагательное" },
	{word_types::verb, "Глагаол" },
	{word_types::communion, "Причастие" },
	{word_types::adverb, "Наречие" },
	{word_types::verb_communion, "Деепричастие"},
	{word_types::count, "Числительное"},
	{word_types::introduce, "Вводное слово"},
	{word_types::preposition, "Предлог"},
	{word_types::pronoun, "Местоимение"},
	{word_types::predicative, "Предикатив"}
};


void print_word_type(const word_types& word_type, ostream& out)
{
	out << word_type_to_string_converter[word_type];
}


// Gender
map<string, gender> string_to_gender_converter{
	{"жен", gender::male},
	{"муж", gender::female},
	{"ср", gender::neuter}
};

// Backward converter:
map<gender, string> gender_to_string_converter{
	{gender::male, "мужской" },
	{gender::female, "женский" },
	{gender::neuter, "средний" },
	{gender::unknown, "WARNING: НЕОПОЗНАННЫЙ ГЕНДЕР" }
};

void print_word_gender(const gender& gender, ostream& out)
{
	out << gender_to_string_converter[gender];
}

// Quantity
map<string, quantity> string_to_quantity_converter{
	{"ед", quantity::single},
	{"мн", quantity::multiple}
};

// Backward converter:
map<quantity, string> quantity_to_string_converter{
	{quantity::unknown, "WARNING!!! Они приближаются. Их КОЛИЧЕСТВО НЕОПОЗНАНО."},
	{quantity::single, "единственное"},
	{quantity::multiple, "множественное"}
};

void print_word_quantity(const quantity& quantity, ostream& out)
{
	out << quantity_to_string_converter[quantity];
}

// Soulness
map<string, soulness> string_to_soulness_converter{
	{"одуш", soulness::ensouled},
	{"неод", soulness::non_ensouled}
};

// Backward converter:
map<soulness, string> soulness_to_string_converter{
	{soulness::ensouled, "одушевлённый"},
	{soulness::non_ensouled, "неодушевлённый"},
	{soulness::unknown, "НЕИЗВЕСТНО, может быть ОНО ЖИВОЕ"}
};

void print_word_soulness(const soulness& soulness, ostream& out)
{
	out << soulness_to_string_converter[soulness];
}


// Tence
map<string, tence> string_to_tence_converter{
	{"прош", tence::past},
	{"наст", tence::present},
	{"буд", tence::future}
};

// Backward converter
map<tence, string> tence_to_string_converter{
	{tence::unknown, "НЕИЗВЕСТНОЕ ВРЕМЯ"},
	{tence::future, "Будущее"},
	{tence::present, "Настоящее"},
	{tence::past, "Прошедшее"},
};

void print_word_tence(const tence& tence, ostream& out)
{
	out << tence_to_string_converter[tence];
}

// Case

map<word_case, string> case_to_string_converter{
	{word_case::unknown, "Неопознанный падеж, может быть, звательный?)"},
	{word_case::nominative, "Именительный"},
	{word_case::parent, "Родительный"},
	{word_case::dative, "Дательный"},
	{word_case::accusative, "Винительный"},
	{word_case::ablative, "Творительный"},
	{word_case::prepositional, "Предложный"}
};

map<string, word_case> string_to_case_converter{
	{"им", word_case::nominative },
	{"род", word_case::parent },
	{ "дат", word_case::dative},
	{"вин", word_case::accusative },
	{"тв", word_case::ablative},
	{"пр", word_case::prepositional}
};

void print_word_case(const word_case& word_case, ostream& out)
{
	out << case_to_string_converter[word_case];
}


// Word personality:

map<word_personality, string> personality_to_string_converter {
	{word_personality::unknown, "Неопознанный тип (хорошо, лицо)"},
	{word_personality::first, "Первое лицо"},
	{word_personality::second, "Второе лицо"},
	{word_personality::third, "Третье лицо"}
};

map<string, word_personality> string_to_personality_converter {
	{"1-е", word_personality::first},
	{"2-е", word_personality::second },
	{"3-е", word_personality::third }
};

void print_word_personality(const word_personality& personality, ostream& out)
{
	out << personality_to_string_converter[personality];
}


map<word_types, bool> has_semantic_checker{
	// Unknown
	{ word_types::unknown, false },

	// Have semantic:
	{ word_types::verb, true },
	{ word_types::noun, true },
	{ word_types::adjective, true },
	{ word_types::communion, true },
	{ word_types::verb_communion, true },
	{ word_types::pronoun, true },
	{ word_types::count, true },
	{ word_types::adverb, true },
	{ word_types::predicative, true},


	// Have no semantic:
	{ word_types::conjunction, false },
	{ word_types::interjection, false },
	{ word_types::introduce, false },
	{ word_types::particle, false },
	{ word_types::preposition, false }

};


