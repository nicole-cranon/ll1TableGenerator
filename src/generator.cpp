/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 7 - ll1 table generator
 */

#include "generator.h"
#include <fstream>
#include <iostream>
#include <iomanip>

namespace generate {
	void ll1Table (const std::vector<std::set<std::string>>& predict,
		const std::set<std::string>& terminals,
		const std::set<std::string>& nonterminals,
		const std::vector<std::string>& LHS,
		const char* outTable) {
		std::ofstream fWrite;
		fWrite.open (outTable);

		if (!fWrite.good()) {
			std::cerr << "\nError opening file: " << outTable << '\n';
			return;
		}

		// write terminals
		fWrite << std::setw(17) << "Terminals|";
		std::cout << std::setw(17) << "Terminals|";
		// fWrite << std::setw(17) << '|';
		// std::cout << std::setw(17) << '|';
		for (auto t : terminals) {
			if (t.size()) {
				fWrite << std::setw(11) << std::right << t;
				std::cout << std::setw(11) << std::right << t;
			}
		}	
		fWrite << '\n';
		std::cout << '\n';

		std::vector<std::vector<unsigned>> nonterminalT(nonterminals.size());
		std::vector<unsigned> tmp(terminals.size());

		fWrite << std::setw(17) << "Nonterminals_";
		fWrite << '\n';
		std::cout << std::setw(17) << "Nonterminals_";
		std::cout << '\n';
		for (auto nt : nonterminals) {
			fWrite << std::setw(17) << nt;
			std::cout << std::setw(17) << nt;
			for (auto t : terminals) {
				if (t.size()) {
					unsigned production = 0;
					production = getProductionIndex (t, nt, predict, terminals, LHS);
					fWrite << std::setw(11) << production;
					std::cout << std::setw(11) << production;
				}
			}
			fWrite << '\n';
			std::cout << '\n';
		}

		fWrite.close ();
	}

	unsigned getProductionIndex (const std::string& terminal,
		const std::string& nonterminal, 
		const std::vector<std::set<std::string>>& predict,
		const std::set<std::string>& terminals,
		const std::vector<std::string>& LHS) {
		for (unsigned i = 0; i < LHS.size(); ++i) {
			if (LHS[i] == nonterminal && predict[i].find(terminal) != predict[i].end()) {
				return i+1;
			}
		}
		return 999;
	}
};