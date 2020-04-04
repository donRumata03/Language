#include "pch.h"

#include <Word.h>
#include <word_util.h>



// Word to enums convertors:


// Free characteristics
map<string, free_properties> string_to_free_properties_converter{
	{"���", free_properties::modal},
	{"������", free_properties::predicate}
};

// Backwards converter
map<free_properties, string> free_properties_to_string_converter{
	{free_properties::predicate, "�������������"},
	{free_properties::modal, "���������"},
	{free_properties::unknown, "������������"}
};

void print_word_free_property(free_properties& free_property, ostream& out)
{
	out << free_properties_to_string_converter[free_property];
}

// Type:
map<string, word_types> string_to_word_type_converter{
	{"����", word_types::conjunction},
	{"���", word_types::noun},
	{"����", word_types::particle},
	{"����", word_types::interjection},
	{"���", word_types::adjective},
	{"��", word_types::verb},
	{"���", word_types::communion},
	{"���", word_types::adverb},
	{"���", word_types::noun},
	{"���", word_types::noun},
	{"����", word_types::verb_communion},
	{"����", word_types::count},
	{"����", word_types::pronoun},
	{"����", word_types::introduce},
	{"�����", word_types::preposition},
	{"������" , word_types::predicative}
};

// Backward converter:
map<word_types, string> word_type_to_string_converter{
	{word_types::unknown, "����������� ����� ����"},
	{word_types::conjunction, "����"},
	{word_types::noun, "���������������"},
	{word_types::particle, "�������" },
	{word_types::interjection, "����������" },
	{word_types::adjective, "��������������" },
	{word_types::verb, "�������" },
	{word_types::communion, "���������" },
	{word_types::adverb, "�������" },
	{word_types::verb_communion, "������������"},
	{word_types::count, "������������"},
	{word_types::introduce, "������� �����"},
	{word_types::preposition, "�������"},
	{word_types::pronoun, "�����������"},
	{word_types::predicative, "����������"}
};


void print_word_type(const word_types& word_type, ostream& out)
{
	out << word_type_to_string_converter[word_type];
}


// Gender
map<string, gender> string_to_gender_converter{
	{"���", gender::male},
	{"���", gender::female},
	{"��", gender::neuter}
};

// Backward converter:
map<gender, string> gender_to_string_converter{
	{gender::male, "�������" },
	{gender::female, "�������" },
	{gender::neuter, "�������" },
	{gender::unknown, "WARNING: ������������ ������" }
};

void print_word_gender(const gender& gender, ostream& out)
{
	out << gender_to_string_converter[gender];
}

// Quantity
map<string, quantity> string_to_quantity_converter{
	{"��", quantity::single},
	{"��", quantity::multiple}
};

// Backward converter:
map<quantity, string> quantity_to_string_converter{
	{quantity::unknown, "WARNING!!! ��� ������������. �� ���������� ����������."},
	{quantity::single, "������������"},
	{quantity::multiple, "�������������"}
};

void print_word_quantity(const quantity& quantity, ostream& out)
{
	out << quantity_to_string_converter[quantity];
}

// Soulness
map<string, soulness> string_to_soulness_converter{
	{"����", soulness::ensouled},
	{"����", soulness::non_ensouled}
};

// Backward converter:
map<soulness, string> soulness_to_string_converter{
	{soulness::ensouled, "�����������"},
	{soulness::non_ensouled, "�������������"},
	{soulness::unknown, "����������, ����� ���� ��� �����"}
};

void print_word_soulness(const soulness& soulness, ostream& out)
{
	out << soulness_to_string_converter[soulness];
}


// Tence
map<string, tence> string_to_tence_converter{
	{"����", tence::past},
	{"����", tence::present},
	{"���", tence::future}
};

// Backward converter
map<tence, string> tence_to_string_converter{
	{tence::unknown, "����������� �����"},
	{tence::future, "�������"},
	{tence::present, "���������"},
	{tence::past, "���������"},
};

void print_word_tence(const tence& tence, ostream& out)
{
	out << tence_to_string_converter[tence];
}

// Case

map<word_case, string> case_to_string_converter{
	{word_case::unknown, "������������ �����, ����� ����, ����������?)"},
	{word_case::nominative, "������������"},
	{word_case::parent, "�����������"},
	{word_case::dative, "���������"},
	{word_case::accusative, "�����������"},
	{word_case::ablative, "������������"},
	{word_case::prepositional, "����������"}
};

map<string, word_case> string_to_case_converter{
	{"��", word_case::nominative },
	{"���", word_case::parent },
	{ "���", word_case::dative},
	{"���", word_case::accusative },
	{"��", word_case::ablative},
	{"��", word_case::prepositional}
};

void print_word_case(const word_case& word_case, ostream& out)
{
	out << case_to_string_converter[word_case];
}


// Word personality:

map<word_personality, string> personality_to_string_converter {
	{word_personality::unknown, "������������ ��� (������, ����)"},
	{word_personality::first, "������ ����"},
	{word_personality::second, "������ ����"},
	{word_personality::third, "������ ����"}
};

map<string, word_personality> string_to_personality_converter {
	{"1-�", word_personality::first},
	{"2-�", word_personality::second },
	{"3-�", word_personality::third }
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


