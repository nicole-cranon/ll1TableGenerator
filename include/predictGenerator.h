/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 7 - ll1 table generator
 */

#ifndef _PREDICT_GENERATOR
#define _PREDICT_GENERATOR

#include <set>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

namespace predict {
	typedef std::unordered_map<std::string,bool> markedVocabulary;
	typedef std::unordered_map<std::string,std::set<std::string>> symbolMap;
	typedef std::vector<std::vector<std::string>> symbolArr;

	extern std::vector<std::set<std::string>> predictSet;
	extern markedVocabulary derivesLambda;
	extern symbolMap firstSet, 
		followSet;


	symbolArr getRHS_stringList (std::vector<std::string> RHSList);

	void markLambda (const std::vector<std::string>& lhs,
		const std::vector<std::vector<std::string> >& RHSStringList);

	std::set<std::string> computeFirst (const std::vector<std::string>& RHSString);

	void fillFirstSet (const std::set<std::string> nonterminals, 
		const std::set<std::string> terminals,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS,
		const std::vector<std::vector<std::string>>& RHSStringList);

	void fillFollowSet (const std::set<std::string> nonterminals, 
		const std::set<std::string> terminals,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS,
		const std::vector<std::vector<std::string>>& RHSStringList);

	void predict (const std::vector<std::string>& LHS, 
		const std::vector<std::string>& RHS, 
		const std::vector<std::vector<std::string>>& RHSStringList);

	bool derives (const std::string& nonterminal,
		const std::string& terminal,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS,
		const std::vector<std::vector<std::string> >& RHSStringList);

	/*
	if nonterminal yields terminal, returns true, else returns false
	that is nonterminal -> terminal
	*/
	bool yields (const std::string& nonterminal,
		const std::string& terminal,
		const std::vector<std::string> LHS,
		const std::vector<std::string> RHS);
};

#endif
