#pragma once
#include"grammar_parser.h"
#include "tree_renderer.h"
#include <stack>
using namespace std;

class tree_generator
{

	struct TreeNode
	{
		float angle, length;
		TreeNode * parent;
		//Model * part;
		std::list<TreeNode *> children;
		string symbol;
	};

private:
	grammar_parser * parser;
	tree_renderer * renderer;
	std::map<string, TreeNode *> rule_trees;
	std::string currentTree;
	stack<std::pair<float, float>> * posStack;
	/*Map of tree parts to static model*/
	//std::map<string, Model> modelMap;
	
	//TODO Include Parameters
	float currAngle;
	/*
		Model curr_part;
		
	*/

public:
	tree_generator(grammar_parser *, tree_renderer *);
	void generateTree();
	void printTree();
	bool traverseGeneratedTree();
	void calculateProperties();
	/*TreeNode * createNode(string symbol,TreeNode * parent);
	void generateTreeString();*/

	~tree_generator();
};

