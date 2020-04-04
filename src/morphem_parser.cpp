#include "pch.h"

#include "morphem_parser.h"
#include <optional>

#include <include/base_func.h>

void morphem_parser::load(const string& filename)
{
	load_and_parse_data(filename);
	parse_word_parts();
}

optional<vector<string>> extract_word_decay(string& to_decay, string& atomic_word)
{
	initializer_list<char> additional_allowed_symbols = {'/', '-', '`', '\'' };

	
	
	string for_splitting;
	for(auto c : to_decay) {
		if (!is_in(c, additional_allowed_symbols) && !is_digit(c) && !is_russian(c)) break;
		if(c != '\'' && c != '`') for_splitting.push_back(c);
	}
	for_splitting = cut_symbols(for_splitting, { '/' });

	if (is_digit(atomic_word.front())) { atomic_word = Slice(atomic_word, 1); for_splitting = Slice(for_splitting, 1); }
	if (is_digit(atomic_word.back())) { atomic_word = Slice(atomic_word, noslice, atomic_word.size() - 1); for_splitting = Slice(for_splitting, noslice, for_splitting.size() - 1); }

	
	vector<string> res = split(for_splitting, { '/' });
	for (size_t index = 0; index < res.size(); index++) {
		if (res[index][0] == '-') {
			string tmp = Slice(res[index], 1);

			res[index] = "-";
			res.insert(res.begin() + index + 1, tmp);
		}
	}
	
	// cout << atomic_word << " " << for_splitting << " " << res << endl;
	return res;
}

void morphem_parser::load_and_parse_data(const string& filename)
{
	string raw_data = readFile(filename);
	auto lines = split_lines(raw_data);
	size_t good_counter = 0;
	for(auto& l: lines) {
		auto splitted = split(l, { '|' });
		if (splitted.size() != 2) { cout << splitted << " " << splitted.size() << endl; continue; }
		transform(splitted.begin(), splitted.end(), splitted.begin(), [](auto& s) {return cut_spaces(s); });

		string atomic_word = splitted[0];

		auto decayed = extract_word_decay(splitted[1], atomic_word);
		if (!decayed) continue;
		
		parsed_data[atomic_word] = *decayed;
		good_counter++;
	}
	if constexpr(debug_morph) cout << "Good percent: " << 100 * double(good_counter) / lines.size() << " % " << endl;
}

void morphem_parser::parse_word_parts()
{
	unordered_map<string, size_t> prefix_counter;
	unordered_map<string, size_t> postfix_counter;
	unordered_map<string, size_t> ending_counter;
	unordered_map<string, size_t> root_counter;

	for(auto& word_data : parsed_data) {
		vector<string> word_decay = word_data.second;
		string prefix = word_decay[0];
		string ending = word_decay[word_decay.size() - 1];

		++prefix_counter[prefix];
		++ending_counter[ending];
	}

	
	vector<pair<string, size_t>> prefix_freq(prefix_counter.size());
	vector<pair<string, size_t>> endings_freq(ending_counter.size());

	// prefix_freq.reserve(prefix_counter.size());
	// prefix_freq.reserve(ending_counter.size());
	
	copy(prefix_counter.begin(), prefix_counter.end(), prefix_freq.begin());
	copy(ending_counter.begin(), ending_counter.end(), endings_freq.begin());

	sort(prefix_freq.begin(), prefix_freq.end(), [](auto p1, auto p2) {return p1.second > p2.second; });
	sort(endings_freq.begin(), endings_freq.end(), [](auto p1, auto p2) {return p1.second > p2.second; });

	m_prefix_freq = move(prefix_freq);
	m_ending_freq = move(endings_freq);
}

void morphem_parser::store_in_human_file(string&& filename, const size_t amount)
{
	cout << "Prefixes total: " << m_prefix_freq.size() << endl;
	cout << "Endings total: " << m_ending_freq.size() << endl;
	size_t prefix_amount = amount, ending_amount = amount;
	if (amount > m_prefix_freq.size()) {
		cout << "Too big required amount of prefixes!" << endl;
		prefix_amount = m_prefix_freq.size();
	}
	if (amount > m_ending_freq.size()) {
		cout << "Too big required amount of endings!" << endl;
		ending_amount = m_ending_freq.size();
	}
	
	string res;
	ofstream file(filename);
	file << "Most popular prefixes:" << endl << endl;
	for(size_t pr_index = 0; pr_index < prefix_amount; pr_index++) {
		auto[str, number] = m_prefix_freq[pr_index];
		file << str << " : " << number << endl;
		// cout << str << " : " << number << endl;
	}

	file << endl << endl << endl;
	
	file << "Most popular endings:" << endl << endl;
	for (size_t pr_index = 0; pr_index < ending_amount; pr_index++) {
		auto [str, number] = m_ending_freq[pr_index];
		// cout << str << " : " << number << endl;
		file << str << " : " << number << endl;
	}

	file.close();
}

void morphem_parser::store_in_machine_files(const string& filename)
{
}
