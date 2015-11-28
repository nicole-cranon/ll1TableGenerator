/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 7 - ll1 table generator
 */

#include "predictGenerator.h"
#include "grammerAnalyzer.h"
#include "helper.h"
#include "generator.h"
#include <iostream>
#include <algorithm>

int main (int argc, char *argv[]) {
	if (argc < 3) {
		std::cerr << "\nNot enough arguments provided!\n";
		std::cerr << "\nCorrect input is [executable] [grammerFile] [outTableFile]\n";
		return 0;
	}

	std::vector<std::string> ingrammer, 
		outgrammer,
		RHSList,
		LHSList;

	std::set<std::string> nonterminals,
		terminals,
		symbols;

	ga::read_productions (argv[1], ingrammer);

	ga::analyze (ingrammer, outgrammer, nonterminals, terminals, symbols, 
			LHSList, RHSList);

	helper::ridSpaces (nonterminals, terminals, symbols, LHSList, RHSList);

	auto RHSStringList = predict::getRHS_stringList (RHSList);

	predict::markLambda (LHSList, RHSStringList);

	predict::fillFirstSet (nonterminals, terminals, LHSList, RHSList, RHSStringList);

	predict::fillFollowSet (nonterminals, terminals, LHSList, RHSList, RHSStringList);

	predict::predict (LHSList, RHSList, RHSStringList);

	std::cout << "\nPredict Sets";
	for (unsigned i = 0; i < predict::predictSet.size(); ++i) {
		if (!RHSList[i].empty()) {
			std::cout << "\n " << i+1 << ". First(" << RHSList[i] << ") = {";
		} else {
			std::cout << "\n " << i+1 << ". (First(lambda) U Follow (" << LHSList[i] << ")) - lambda = {";
		}
		for (auto elem: predict::predictSet[i]) {
			std::cout << elem << ',';
		}
		std::cout << "}";
	}
	
	std::cout << "\n\n";

	std::cout << "\nLL1 Table\n";
	generate::ll1Table (predict::predictSet, terminals, nonterminals, LHSList, argv[2]); 
}
