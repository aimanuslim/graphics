#include "tree_generator.h"
#include<map>
#include<math.h>
#include"branch.h"
#include"leaf.h"
constexpr auto PI =  3.14159265359;
#define _USE_MATH_DEFINES

unsigned short leaf::count = 0;
unsigned short leaf::length = 15;

unsigned short branch::count = 0;
unsigned short branch::length = 30;

tree_generator::tree_generator(grammar_parser * parser, tree_renderer * renderer)
{
	this->parser = parser;
	//rule_trees = new map<string, TreeNode *>();
	this->currentTree = this->parser->start_symb;
	this->posStack = new stack<std::pair<float, float>>();
	this->renderer = renderer;
	this->currAngle = PI / 2.0;
}

void tree_generator::generateTree()
{
	string iter_Tree;
	//std::iterator<map<string, float>> map_iter;
	this->currentTree = this->parser->start_symb;
	for (int i = 1; i <= int(this->parser->model_data->find(std::string("iterations"))->second); i++)
	{
		//printf("Entered loop - Starting symbol size : %d ", this->currentTree.size()); 
		iter_Tree = "";
		for (std::string::size_type index = 0; index < this->currentTree.size(); /*this->currentTree.begin(); it != this->currentTree.end();*/ index++)
		{
			//printf("Entered inner loop : %d", this->currentTree[index]);
			//_sleep(1000);
			if (parser->rules->find(std::string(1, this->currentTree[index])) != parser->rules->end())
				iter_Tree += parser->rules->find(std::string(1, this->currentTree[index]))->second;
			else
				iter_Tree += std::string(1,currentTree[index]);
		}
		this->currentTree = iter_Tree;
	}
}

void tree_generator::printTree()
{
	printf("Genrerted Tree  Status : %s\n", currentTree.c_str());
}

//TODO :: Needs to be expanded according to 3-D t=generation
/*void tree_generator::calculateProperties(char direction)
{

}*/

bool tree_generator::traverseGeneratedTree()
{
	/*Basic Testing of Line Tree
	Branch Length - 30
	Leaf Length - 0.2
	*/
	short branch_len = 30, leaf_len = 15, curr_len;
	this->posStack->push(std::pair<float, float>(300, 500));
	std::pair<float, float> vertex = this->posStack->top();
	for (std::string::size_type index = 0; index < this->currentTree.size(); index++)
	{
		//printf("Current String character : %c\n", this->currentTree[index]);
		//TODO : Will be scaled up for 3-D traversal
		switch (this->currentTree[index])
		{
		case '+': this->currAngle += PI * this->parser->angle / 180; break;
		case '-': this->currAngle -= PI * this->parser->angle / 180; break;
		case '[': this->posStack->push({ -1.0, -1.0 }); break;
		case ']': while (posStack->top().first != -1 && posStack->top().second != -1)
				  {
					this->posStack->pop();
				  }
					this->posStack->pop();
					if(this->posStack->size())
						vertex = this->posStack->top();
					break;
		default: //printf("Current angle is %f\n", this->currAngle);
			if (this->currentTree[index] == 'F')
			{
				curr_len = branch_len;
				this->renderer->addModel(branch::createBranch(this->currAngle, vertex));
			}
			else if (this->currentTree[index] == 'L')
			{
				curr_len = leaf_len;
				this->renderer->addModel(leaf::createLeaf(currAngle, vertex));
			}
			this->renderer->addVertex(vertex.first, vertex.second);
			vertex = { vertex.first + cos(this->currAngle) * curr_len,
						vertex.second - sin(this->currAngle) * curr_len };
			this->renderer->addVertex(vertex.first, vertex.second);
			posStack->push(vertex);
			this->currAngle = PI / 2.0;
		}
	}
	return true;
}

tree_generator::~tree_generator()
{
	/*
	for (auto entry : this->rule_trees)
	{
	}
	delete rule_trees;*/
}
