/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 7 - ll1 table generator
 */

#ifndef _HELPER
#define _HELPER

#include "grammerAnalyzer.h"

namespace helper {
	// remove white space in string s
	std::string normalize (const std::string& s);

	void ridSpaces (std::set<std::string>& nonterminals, 
			std::set<std::string>& terminals,
			std::set<std::string>& symbols,
			std::vector<std::string>& LHSList,
			std::vector<std::string>& RHSList);
};

#endif