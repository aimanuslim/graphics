/*

	Parser for parsing the input text file and generating structures for representing inormation
	Meta information (branching and phyllotactic angle, ratios, iterations)
	V - set of alphabets in grammar
	w - starting symbols
	P - production rules

	Turtle Interpretation (use rotation matrix for rotations)
	+ -> Turn left by alpha
	- -> Turn right by alpha
	& -> Pitch down by alpha
	^ -> Pitch up by alpha
	\ -> Roll left by alpha
	/ -> Roll right by alpha
	| -> Turn around
	[ -> Push to Stack current properties/position
	] -> Pop from stack current position/propoerties

	Format of input grammar file
	Meta-information
	(branch (for 2D) /divergence angle, diameter ratio, turtle alpha, eidth decrease rate (wr), contraction ratios) 
	set of axioms

	Starting symbol

	Production rules
	Example : F -> FF[F+F[F[L][-L]]+F[++L]][FFF[+L][L][-L]]-F-FF[L][-L]
	Example 2 (edge-rewriting) : F -> F[+F]F[-F][F]

	Example 3 (node-rewriting) : X -> F[+X][-X]FX

*/
#ifndef GRAMMAR_PARSER
#define GRAMMAR_PARSER

#include<stdlib.h>
#include<fstream>
#include<cstdio>
#include<string>
#include<map>
#include<list>
using namespace std;

class grammar_parser
{
	public:
		grammar_parser(string input_file);
		~grammar_parser();
		void parseFile();
		string file, grammar, start_symb;
		ifstream fp;
		unsigned short iterations;
		float angle;
		map<string, float> * model_data;// = new map<string, int>();
		map<string, string> * rules;
		list<string> axioms;
};

#endif /*GRAMMAR_PARSER_H*/