#pragma once
#include "common_types.h"
#include"grammar_parser.h"
#include "tree_renderer.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <stack>
#include<vector>
using namespace std;

class tree_renderer;

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
	tuple3d curr_basePoint, base_dir, vertex;
	vec3 curr_dir;
	stack<std::pair<char, pos_orient>> * posStack;
	unsigned int frameCount;
	/*Map of tree parts to static model*/
	//std::map<string, Model> modelMap;
	//TODO Include Parameters
	float currAngle, currbranch_l, currbranch_w, leaf_l, leaf_w;
	std::list<vec_lines> tree_vectors;
	/*
		Model curr_part;
		
	*/
	void clearStack();
	void popCurrentStackFrame();
	vec3 generateRotation(TURTLE_AXIS axis, vec3, short);
	
public:
	float contract_l, contract_w;
	tree_generator(grammar_parser *);
	void setRenderer(tree_renderer *);
	void setTreeBaseLocation(tuple3d);
	void setBaseOrientation(tuple3d, tuple3d);
	bool checkCollision(vec3, vec3, PART_TYPE);
	void generateTree(int);
	void analyzeTree();
	void printTree();
	bool traverseGeneratedTree();
	void calculateProperties();
	

	/*TreeNode * createNode(string symbol,TreeNode * parent);
	void generateTreeString();*/

	~tree_generator();
};

