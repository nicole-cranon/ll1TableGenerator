/*
	nicole cranon <nicole.cranon@ucdenver.edu>
	csci 4640, fall 2015
	assignment 7 - ll1 table generator
 */

#include "grammerAnalyzer.h"
#include <fstream>
#include <iostream>

namespace ga {

	void analyze (const std::vector<std::string>& ingrammer, 
			std::vector<std::string>& outgrammer, 
			std::set<std::string>& nonterminals, 
			std::set<std::string>& terminals,
			std::set<std::string>& symbols,
			std::vector<std::string>& LHSList,
			std::vector<std::string>& RHSList) {

		std::string LHS = "",
			RHS = "";
		unsigned sepIndex = 0;

		for (unsigned i = 0; i < ingrammer.size(); ++i) {

			sepIndex = ingrammer[i].find ("->");

			if (sepIndex != std::string::npos) {

				LHS = ingrammer[i].substr (0, sepIndex);
				RHS = ingrammer[i].substr (sepIndex+2);

				LHSList.push_back (LHS);
				RHSList.push_back (RHS);

				if (is_terminal(RHS)) {
					if (RHS.compare("") != 0) {
						terminals.insert (RHS);
						symbols.insert (RHS);
					}
					nonterminals.insert (LHS);
				} else {
					nonterminals.insert (LHS);
					symbols.insert (LHS);
				}

			} else {

				std::cerr << "\nError in production formatting : \" " << 
					ingrammer[i] << ".\n";

				exit(1);

			}

			LHS = "",
			RHS = "";

		}

		// since we are not currently manipulating the input grammer
		outgrammer = ingrammer;


	}

	bool is_terminal (const std::string& RHS) {

		// the RHS is not the empty string and does not contain '<..>' and so
		// is a terminal expression
		if (RHS != "" && RHS.find ('<') == std::string::npos 
				&& RHS.find ('>') == std::string::npos) {

			return true;

		}

		return false;	

	}

	void read_productions (const char* filename, 
			std::vector<std::string>& grammer) {

		std::ifstream inFileStream;
		std::string production = "";
		inFileStream.open (filename);

		if (!inFileStream.good ()) {

			std::cerr << "\nError opening file " << filename << ".\n";
			exit (1);

		}

		while (inFileStream.good () && inFileStream.peek () != EOF) {

			getline (inFileStream, production);
			if (production != "") {
				grammer.push_back (production);
			}

		}

	}

};
