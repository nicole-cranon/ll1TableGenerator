/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 7 - ll1 table generator
 */

#ifndef _LL1TABLE_GENERATOR
#define _LL1TABLE_GENERATOR

#include <vector>
#include <set>
#include <string>

namespace generate {
	void ll1Table (const std::vector<std::set<std::string>>& predict,
		const std::set<std::string>& terminals,
		const std::set<std::string>& nonterminals,
		const std::vector<std::string>& LHS,
		const char* outTable);

	unsigned getProductionIndex (const std::string& terminal,
		const std::string& nonterminal, 
		const std::vector<std::set<std::string>>& predict,
		const std::set<std::string>& terminals,
		const std::vector<std::string>& LHS);
};

#endif