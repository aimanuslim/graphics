#include "grammar_parser.h"
#include<string>
#include<regex>
#include<stdio.h>
grammar_parser::grammar_parser(std::string input_file)
{
	this->model_data = new std::map<string, float>();
	rules = new std::map<string, string>();
	fp = ifstream(input_file.c_str());
	if (fp)
	{
		grammar = "";
		std::string line;
		bool rules_flag = false;;
		printf("Opened grammar file for parsing");
		while (!fp.eof())
		{
			getline(fp, line);
			if (std::regex_search(line, std::regex("Production Rules")))
				rules_flag = true;
			if (!line.empty())
			{
				if (rules_flag)
					grammar += " " + line;
				else
					grammar += string(line);
			}
		}
	}
	else
		printf("Invalid file");
	}

void grammar_parser::parseFile()
{
	if (grammar.size() > 0)
	{
		std::regex meta_data ("Meta Information(.*)Alphabets");
		std::regex alphabets ("Alphabets(.*)Starting");
		std::regex starting_symb ("Starting Symbol(.*)Production Rules");
		std::regex rules_regex ("Production Rules\\s(.*)");
		std::smatch match;
		std::string substring;
		//printf("Read grammar content : %s", grammar.c_str());
		//Parse Meta Information

		if (std::regex_search(grammar, match, meta_data))
		{
			substring = match.str(1);
			printf("\ngrammar : %s \nMatched substring : %s\n", grammar.c_str(), substring.c_str());
			meta_data = std::regex("(\\w{1,})\\s(\\d+[\.]?[\\d]*)");
			while (std::regex_search(substring, match, meta_data))
			{
				printf("\nMatched string pattern for meta information : %s\n", match.str().c_str());
				//_sleep(1000);
				if (match.str(1) == "iterations")
					iterations = atoi((match).str(2).c_str());
				else if (match.str(1) == "angle")
				{
					printf("Enters angle recignition\n");
					angle = atof(match.str(2).c_str());
				}
				else
					model_data->insert(std::pair<string, float>(match.str(1), atof(match.str(2).c_str())));
				substring = match.suffix().str();
			}
			this->model_data->insert(std::pair <string, float >("iterations", this->iterations));
			this->model_data->insert(std::pair <string, float >("angle", this->angle));
		}

		//Alphabets
		if (std::regex_search(grammar, match, alphabets))
		{
			printf("Matched string pattern for alphabets : %s\n", match.str().c_str());
			substring = match.str(1);
			alphabets = std::regex("\\w{1}");
			while(std::regex_search(substring, match, alphabets))
			{
				printf("Matched alphabets : %s\n", match.str().c_str());
				//_sleep(1000);
				this->axioms.push_back(match.str());
				substring = match.suffix().str();
			}
		}

		//Starting Symbol
		if (std::regex_search(grammar, match, starting_symb))
		{
			printf("Matched string pattern for starting symbol : %s\n", match.str(1).c_str());
			if (match.size() > 0)
				this->start_symb = match.str(1);
		}

		//Production rules
		if (std::regex_search(grammar, match, rules_regex))
		{
			printf("Matched string pattern for rules : %s\n", match.str().c_str());
			substring = match.str(0);
			rules_regex = std::regex("(\\w+)\\s->\\s([\\w+^\\\+-\\[\\]]+)");
			while(std::regex_search(substring, match, rules_regex))
			{

				this->rules->insert(std::pair<string, string>(match.str(1), match.str(2)));
				printf("Rules : \n %s -> %s", match.str(1).c_str(), match.str(2).c_str());
				//_sleep(100);
				substring = match.suffix().str();
			}
		}
	}
}

grammar_parser::~grammar_parser()
{
}
