/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 7 - ll1 table generator
 */

#ifndef _GRAMMER_ANALYZER
#define _GRAMMER_ANALYZER

#include <vector>
#include <set>
#include <string>

namespace ga {

	void analyze (const std::vector<std::string>& ingrammer, 
			std::vector<std::string>& outgrammer, 
			std::set<std::string>& nonterminals, 
			std::set<std::string>& terminals,
			std::set<std::string>& symbols,
			std::vector<std::string>& LHSList,
			std::vector<std::string>& RHSList);
			

	bool is_terminal (const std::string& RHS);

	void read_productions (const char* filename, 
			std::vector<std::string>& grammer);

};

#endif
