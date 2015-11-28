/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 7 - ll1 table generator
 */

#include "predictGenerator.h"
#include <algorithm>
#include <iostream>

namespace predict {
	markedVocabulary derivesLambda;
	symbolMap firstSet, 
		followSet;
	std::vector<std::set<std::string>> predictSet;


	symbolArr getRHS_stringList (std::vector<std::string> RHSList) {
			std::string symbol;
		unsigned split_pos = 0;

		std::vector<std::vector<std::string> > RHS_stringList;
		std::vector<std::string> RHSSet;

		for(unsigned i = 0; i< RHSList.size(); ++i) {
			while (!RHSList[i].empty()) {
				split_pos = RHSList[i].find("><");

				if (split_pos < RHSList[i].size() && split_pos+1 != RHSList[i].size()) {
					symbol = RHSList[i].substr(0, split_pos+1);
					unsigned RHSLength = RHSList[i].size() - split_pos-1;
					RHSList[i] = RHSList[i].substr(split_pos+1, RHSLength);
				} else {
					symbol = RHSList[i];
					RHSList[i] = "";
				}
				RHSSet.push_back (symbol);
			}

			RHS_stringList.push_back(RHSSet);
			RHSSet.clear();
		}

			// unsigned i = 0;
			// for (auto x : RHS_stringList) {
			// 	std::cout << "\nRHS List of Symbols " << i << " ";

			// 	for (auto v : x) {
			// 		std::cout << v << ',';
			// 	}
			// 	std::cout <<'\n';
			// 	++i;
			// }

		return RHS_stringList;
	}

	void markLambda (const std::vector<std::string>& lhsList, 
			const std::vector<std::vector<std::string> >& RHSStringList) {
		bool changes = true,
			rhsDerivesLambda;

		for (unsigned i = 0; i < lhsList.size(); ++i) {
			derivesLambda[lhsList[i]] = false;
		}

		while (changes) {
			changes = false;

			for (unsigned i = 0; i < lhsList.size(); ++i) {
				rhsDerivesLambda = true;

				for (unsigned j = 0; j < RHSStringList[i].size(); ++j) {
					rhsDerivesLambda = rhsDerivesLambda && derivesLambda[RHSStringList[i][j]];
				}

				if (rhsDerivesLambda && !(derivesLambda[lhsList[i]])) {
					changes = true;

					derivesLambda[lhsList[i]] = true;
					// std::cout << "\nlhs-> " << lhsList[i] << " yields lamda " << derivesLambda[lhsList[i]] << '\n';
				}
			}
		}
	}

	std::set<std::string> computeFirst (const std::vector<std::string>& RHSString) {
		std::set<std::string> terminalSet;

		if (RHSString.size() == 0) {
			terminalSet.insert("");
		}
		else {
			terminalSet = firstSet[RHSString[0]];
			terminalSet.erase("");

			unsigned i = 0;
			while (i < RHSString.size() && firstSet[RHSString[0]].find("") != firstSet[RHSString[i]].cend()) {
				++i;
				terminalSet.insert (firstSet[RHSString[i]].cbegin(), firstSet[RHSString[i]].cend());
				terminalSet.erase ("");
			}

			if ((i == RHSString.size() - 1) && firstSet[RHSString[i]].find("") != firstSet[RHSString[i]].cend()) {
				terminalSet.insert ("");
			}
		}
		
		return terminalSet;
	}

	void fillFirstSet (const std::set<std::string> nonterminals, 
		const std::set<std::string> terminals,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS,
		const std::vector<std::vector<std::string>>& RHSStringList) {

		auto ntItr = nonterminals.begin();
		auto tItr = terminals.begin();

		for (; ntItr != nonterminals.end(); ++ntItr) {
			if (derivesLambda [*ntItr]) {
				firstSet[*ntItr].insert ("");
			} else {
				firstSet[*ntItr].clear ();
			}
		}

		for (; tItr != terminals.end(); ++tItr) {
			if (tItr->compare("") != 0){
				firstSet[*tItr].insert (*tItr);
			}

			for (ntItr = nonterminals.begin(); ntItr != nonterminals.end(); ++ntItr) {
				if (yields(*ntItr, *tItr, LHS, RHS)) {
					firstSet[*ntItr].insert (*tItr);
				}
			}
		}

		bool changes = true;
		while (changes) {
			auto prevFirstSet = firstSet;

			for (unsigned i = 0; i < LHS.size(); ++i) {
				auto rhsFirst = computeFirst (RHSStringList[i]);
				firstSet[LHS[i]].insert(rhsFirst.begin(), rhsFirst.end());
			}

			if (prevFirstSet == firstSet) {
				changes = false;
			}
		}


	}

	void fillFollowSet (const std::set<std::string> nonterminals, 
		const std::set<std::string> terminals,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS,
		const std::vector<std::vector<std::string>>& RHSStringList) {

		auto ntItr = nonterminals.begin();

		for (; ntItr != nonterminals.end(); ++ntItr) {
			followSet [*ntItr].clear ();
		}

		followSet["<systemgoal>"].insert ("");

		bool changes = true;
		while (changes) {
			auto prevFollowSet = followSet;
			for (unsigned i = 0; i < LHS.size(); ++i) {
				for (unsigned j = 0; j < RHSStringList[i].size(); ++j) {
					if (terminals.find (RHSStringList[i][j]) == terminals.end()) {
						if (j+1 < RHSStringList[i].size()) {
							auto firstsetNext = firstSet[RHSStringList[i][j+1]];
							firstsetNext.erase ("");
							followSet[RHSStringList[i][j]].insert (firstsetNext.begin(), firstsetNext.end());

							if (firstSet[RHSStringList[i][j+1]].find("") != firstSet[RHSStringList[i][j+1]].end()) {
								followSet[RHSStringList[i][j]].insert (followSet[LHS[i]].begin(), followSet[LHS[i]].end());
							}
						}

						else if (firstSet[RHSStringList[i][j]].find("") != firstSet[RHSStringList[i][j]].end()) {
							followSet[RHSStringList[i][j]].insert (followSet[LHS[i]].begin(), followSet[LHS[i]].end());
						}
					}
				}
			}

			if (prevFollowSet == followSet) {
				changes = false;
			}
		}
	}

	void predict (const std::vector<std::string>& LHS, 
		const std::vector<std::string>& RHS, 
		const std::vector<std::vector<std::string>>& RHSStringList) {
		predictSet.resize (LHS.size());

		for (unsigned i = 0; i < LHS.size(); ++i) {
			if (RHS[i].compare("") == 0) {
				predictSet[i] = followSet[LHS[i]];
				predictSet[i].erase ("");
			} else {
				predictSet[i] = computeFirst(RHSStringList[i]);
			}
		}
	}

	bool derives (const std::string& nonterminal,
		const std::string& terminal,
		const std::vector<std::string>& LHS,
		const std::vector<std::string>& RHS,
		const std::vector<std::vector<std::string> >& RHSStringList) {
		for (unsigned i = 0; i < LHS.size(); ++i) {
			if (LHS[i].compare(nonterminal) == 0) {
				for (unsigned j = 0; j < RHSStringList[i].size(); ++j) {
					// current right hand side element is a terminal
					if (RHSStringList[i][j].compare(terminal) == 0) {
						return true;
					}
					// current right hand side element is a nonterminal
					if (yields (RHSStringList[i][j], terminal, LHS, RHS)) {
						return true;
					}
				}
			}
		}

		return false;
	}

	bool yields (const std::string& nonterminal,
		const std::string& terminal,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS) {
		for (unsigned i = 0; i < LHS.size(); ++i) {
			if (LHS[i].compare(nonterminal) == 0 && RHS[i].compare (terminal) == 0) {
				return true;
			}
		}

		return false;
	}

}