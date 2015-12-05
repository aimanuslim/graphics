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

tree_generator::tree_generator(grammar_parser * parser)
{
	this->parser = parser;
	//rule_trees = new map<string, TreeNode *>();
	this->currentTree = this->parser->start_symb;
	this->posStack = new stack<std::pair<char,tuple3d>>();
	//this->renderer = renderer;
	this->currAngle = PI / 2.0;
}

void tree_generator::setRenderer(tree_renderer * renderer)
{
	this->renderer = renderer;
}

void tree_generator::setTreeBaseLocation(tuple3d position)
{
	this->curr_basePoint = position;
}

void tree_generator::generateTree(int iterations)
{
	string iter_Tree;
	//std::iterator<map<string, float>> map_iter;
	for (int i = 1; i <= iterations; i++)
	{
		//printf("Entered loop - Starting symbol size : %d ", this->currentTree.size()); 
		iter_Tree = "";
		for (std::string::size_type index = 0; index < this->currentTree.size(); index++)
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
	/*Stacks keeping track of branch Level Heights and widths*/

	float currbranch_l = parser->model_data->find(std::string("branch_h"))->second,
		leaf_l = parser->model_data->find(std::string("leaf_h"))->second,
		currbranch_w = parser->model_data->find(std::string("branch_w"))->second,
		leaf_w = parser->model_data->find(std::string("leaf_w"))->second,
		contract_l = parser->model_data->find(std::string("contraction_ratio"))->second,
		contract_w = parser->model_data->find(std::string("diameter_ratio"))->second, 
		curr_len;

	vec3 curr_dir;
	bool collides;
	PART_TYPE part;
	this->clearStack();
	
	this->posStack->push({ 'B', this->curr_basePoint });

	tuple3d vertex = this->posStack->top().second;
	for (std::string::size_type index = 0; index < this->currentTree.size(); index++)
	{
		//printf("Current String character : %c\n", this->currentTree[index]);
		//TODO : Will be scaled up for 3-D traversal
		switch (this->currentTree[index])
		{
		case '+': 
		case '&' :
		case '\\' : this->currAngle += PI * this->parser->angle / 180;	break;
		case '-' :
		case '^' : 
		case '/' : this->currAngle -= PI * this->parser->angle / 180; break;
		case '|': this->currAngle = PI;  break;
		case '[': this->posStack->push({ '[',{ -1.0, -1.0 , -1.0} }); break;
		case ']': while (posStack->top().first != '[')
				  {
					  if (posStack->top().first == 'F')
					  {
						  currbranch_l /= contract_l;
						  currbranch_w /= contract_w;
					  }
					  this->posStack->pop();
				  }
					this->posStack->pop();
					if(this->posStack->size())
						vertex = this->posStack->top().second;
					break;
		default: 
			curr_len = (this->currentTree[index] == 'F') ? currbranch_l : leaf_l;
			curr_dir = (tuple3d(cos(currAngle), sin(currAngle), 0.0f) * curr_len).getVector();
			part = (this->currentTree[index] == 'F') ? PART_TYPE::BRANCH : PART_TYPE::LEAF;
			//if (collides = this->checkCollision(vertex.getVector(), curr_dir, part))
			//{
				//printf("Enters line registeration \n");
				this->tree_vectors.push_back(vec_lines(vertex.getVector(), curr_dir, part));
				if (this->currentTree[index] == 'F')
				{
					this->renderer->addModel(branch::createBranch(this->currAngle, vertex, currbranch_l, currbranch_w));
					currbranch_l *= contract_l;
					currbranch_w *= contract_w;
				}
				else if (this->currentTree[index] == 'L')
				{
					this->renderer->addModel(leaf::createLeaf(currAngle, vertex, leaf_l, leaf_w));
				}
				//this->renderer->addVertex(vertex.first, vertex.second);
				vertex = { vertex.first + cos(this->currAngle) * curr_len,
							vertex.second + sin(this->currAngle) * curr_len,
							vertex.third };
				//this->renderer->addVertex(vertex.first, vertex.second);
				posStack->push({ this->currentTree[index], vertex });
			//}
			/*else
			{
			/*	while (this->currentTree[index++] != ']')
				{}
			}*/
			this->currAngle = PI / 2.0;
			//printf("Current part collides : %d\n", collides);
		}
	}
	return true;
}

bool tree_generator::checkCollision(vec3 base, vec3 dir, PART_TYPE type)
{
	for (vec_lines part_line : this->tree_vectors)
	{
		//printf("Current dir : %f, %f, %f\n", part_line.dir.x, part_line.dir.y, part_line.dir.z);
		if (part_line.collides(vec_lines(base, dir, type)))
			return false;
	}
	return true;
}

void tree_generator::clearStack()
{
	while (!this->posStack->empty())
		this->posStack->pop();
	//delete this->posStack;
}

tree_generator::~tree_generator()
{
	delete this->posStack;
	/*
	for (auto entry : this->rule_trees)
	{
	}
	delete rule_trees;*/
}
