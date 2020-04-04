#pragma once
#include "pch.h"
#include "Basic_language.h"
#include "Light_language.h"
#include "morphem_worker.h"

class language : public light_language
{
	/*
	 * This is the language class with the biggest amount of features
	 * Here are they:
	 *		1) Word decay
	 *		2) Vocabulary renewing during parsing new words
	 *		3) 
	*/
public:
	explicit language(const string& filename);

	map<string, vector<string>> prefixes;
	map<string, vector<string>> postfixes;
	map<string, vector<string>> endings;



	
};