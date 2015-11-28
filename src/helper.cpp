/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 7 - ll1 table generator
 */

#include "helper.h"

namespace helper {
	// remove white space in string s
	std::string normalize (const std::string& s) {
		std::string temp = "";

		for (unsigned i = 0; i < s.size(); ++i) {
			if (s[i] != ' ') {
				temp += s[i];
			}
		}

		return temp;
	}

	void ridSpaces (std::set<std::string>& nonterminals, 
		std::set<std::string>& terminals,
		std::set<std::string>& symbols,
		std::vector<std::string>& LHSList,
		std::vector<std::string>& RHSList) {
			
		for (unsigned i = 0; i < RHSList.size(); ++i) {
			RHSList[i] = normalize (RHSList[i]);
			//std::cout << "\nRHS->" << RHSList[i] << "<-\n";
		}
		for (unsigned i = 0; i < LHSList.size(); ++i) {
			LHSList[i] = normalize (LHSList[i]);
			//std::cout << "\nLHS->" << l << "<-\n";
		}
		auto tmpnonterminals = nonterminals;
		for (std::set<std::string>::iterator itr = tmpnonterminals.begin(); itr != tmpnonterminals.end(); ++itr) {
			auto temp = normalize (*itr);
			nonterminals.insert(temp);
			nonterminals.erase(*itr);
		}
		auto tmpterminals = terminals;
		for (std::set<std::string>::iterator itr = tmpterminals.begin(); itr != tmpterminals.end(); ++itr) {
			auto temp = normalize (*itr);
			terminals.insert(temp);
			terminals.erase(*itr);
		}
		auto tmpsymbols = symbols;
		for (std::set<std::string>::iterator itr = tmpsymbols.begin(); itr != tmpsymbols.end(); ++itr) {
			auto temp = normalize (*itr);
			symbols.insert(temp);
			symbols.erase(*itr);
		}
	}
};