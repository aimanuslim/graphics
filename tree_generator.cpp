#include "tree_generator.h"
#include<map>
#include<math.h>
#include"branch.h"
#include"leaf.h"

unsigned short leaf::count = 0;
unsigned short leaf::length = 15;

unsigned short branch::count = 0;
unsigned short branch::length = 30;

tree_generator::tree_generator(grammar_parser * parser)
{
	this->parser = parser;
	//rule_trees = new map<string, TreeNode *>();
	this->currentTree = this->parser->start_symb;
	this->posStack = new stack<std::pair<char,pos_orient>>();
	//this->renderer = renderer;
	frameCount = 0;
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

void tree_generator::setBaseOrientation(tuple3d position, tuple3d normal)
{
	this->setTreeBaseLocation(position);
	this->base_dir = normal;
	this->curr_dir = normal.getVector();
}	


void tree_generator::generateTree(int iterations)
{
	string iter_Tree;
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

vec3 tree_generator::generateRotation(TURTLE_AXIS axis,  vec3 currdir_pos, short sign)
{
	//return rot;
	switch(axis)
	{
		case L : return glm::mat3(1, 0, 0, 0 , cos(parser->angle * sign * PI / 180), sin(parser->angle * -sign * PI / 180) , 0, -sin(parser->angle * sign * PI / 180), cos(parser->angle * -sign * PI / 180)) *  currdir_pos/*tuple3d(currdir_pos.x, curr_dir.y, -curr_dir.z).getVector()*/;
				break;
		case H : return glm::mat3(cos(parser->angle * sign * PI / 180), 0, sin(parser->angle * sign * PI / 180), 0, 0, 0, -sin(parser->angle * sign * PI / 180), 0, cos(parser->angle * sign * PI / 180)) * currdir_pos;
				break;
		case U:	return glm::mat3(cos(parser->angle * sign * PI / 180), sin(parser->angle * sign * PI / 180), 0.0, -sin(parser->angle * sign * PI / 180), cos(parser->angle * sign * PI / 180), 0.0, 0.0, 0.0, 1.0) * currdir_pos; 
				break;
		default: return vertex.getVector() + vec3(cos(parser->angle * sign * PI / 180), sin(parser->angle * sign * PI / 180), 0.0f);
	}
	//return rot_dir;
}

void tree_generator::printTree()
{
	printf("Genrerted Tree Status : %s\n", currentTree.c_str());
}

//TODO :: Needs to be expanded according to 3-D generation
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

	currbranch_l = parser->model_data->find(std::string("branch_h"))->second;
	leaf_l = parser->model_data->find(std::string("leaf_h"))->second;
	currbranch_w = parser->model_data->find(std::string("branch_w"))->second;
	leaf_w = parser->model_data->find(std::string("leaf_w"))->second;
	contract_l = parser->model_data->find(std::string("contraction_ratio"))->second;
	contract_w = parser->model_data->find(std::string("diameter_ratio"))->second; 
	float curr_len;
	//printf("Diamater ratio : %f Contraction Ratio : %f\n", contract_w, contract_l);
	bool collides;
	PART_TYPE part;
	this->clearStack();
	curr_dir = this->base_dir.getVector();
	vec3 dir_pos; 
	this->posStack->push({ 'B', {this->curr_basePoint, this->base_dir } });

	vertex = this->posStack->top().second.first;
	for (std::string::size_type index = 0; index < this->currentTree.size(); index++)
	{
		//printf("Current String character : %c Direction : (%f,%f,%f) Unit dir : (%f, %f, %f)\n", this->currentTree[index], curr_dir.x,curr_dir.y,curr_dir.z, dir_pos.x, dir_pos.y, dir_pos.z);
		switch (this->currentTree[index])
		{
		case '+': curr_dir = this->generateRotation(U, curr_dir, 1); break;
		case '^' : curr_dir = this->generateRotation(L, curr_dir, 1); 
					//curr_dir.z = -curr_dir.z;
					//printf("Obtained direction :  (%f,%f,%f)\n", curr_dir.x, curr_dir.y, curr_dir.z);
					break;
		case '\\' : /*this->currAngle += this->parser->angle * PI / 180 ;*/
			      curr_dir = this->generateRotation(H, dir_pos, 1);break;
		case '-':curr_dir = this->generateRotation(TURTLE_AXIS::U, curr_dir, -1);  
				//printf("Obtained direction :  (%f,%f,%f)\n", curr_dir.x, curr_dir.y, curr_dir.z);
				break;
		case '&' : curr_dir = this->generateRotation(L, curr_dir, -1);
				//curr_dir.z = -curr_dir.z;
				//printf("Obtained direction :  (%f,%f,%f)\n", curr_dir.x, curr_dir.y, curr_dir.z);
				break;
		case '/' : /*this->currAngle -=  this->parser->angle * PI / 180;*/
				  curr_dir = this->generateRotation(H, dir_pos, -1) ; break; break;
		case '|': curr_dir = vec3(curr_dir.x,-curr_dir.y, curr_dir.z); break;
		case '[': frameCount++; 
			this->posStack->push({ '[',{ { -1.0, -1.0 , -1.0}, curr_dir } }); break;
		case ']':	popCurrentStackFrame();
					break;
		default: 
			curr_len = (this->currentTree[index] == 'F') ? currbranch_l : leaf_l;
		//	curr_dir = (tuple3d(curr_dir.x, curr_dir.y, curr_dir.z) * curr_len).getVector();
			part = (this->currentTree[index] == 'F') ? PART_TYPE::BRANCH : PART_TYPE::LEAF;
			if (collides = this->checkCollision(vertex.getVector(), (tuple3d(curr_dir) * curr_len).getVector() , part))
			{
				register;
				//printf("Enters line registeration \n");
				this->tree_vectors.push_back(vec_lines(vertex.getVector(), curr_dir, part));
				if (this->currentTree[index] == 'F')
				{
					this->renderer->addModel(branch::createBranch(this->curr_dir, vertex, curr_len, currbranch_w));					
					//printf("Current branch width : %f\n", currbranch_w);
					currbranch_l *= contract_l;
					currbranch_w *= contract_w;
				}
				else if (this->currentTree[index] == 'L')
					this->renderer->addModel(leaf::createLeaf(this->curr_dir, vertex, curr_len, leaf_w));		
				vertex = { vertex.first + curr_dir.x * curr_len,
							vertex.second + curr_dir.y * curr_len,
							vertex.third + curr_dir.z * curr_len};
				//printf("Vertex top (%f, %f, %f)\n", vertex.first, vertex.second, vertex.third);
				posStack->push({ this->currentTree[index], {vertex, curr_dir} });
			}
			else
			{
				short interim_frame = 0;
				//printf("Before Index : %d Orginal Tree : %s \n Remaining tree string : %s\n", index, currentTree.c_str(), this->currentTree.substr(index, currentTree.size()).c_str());
				//printf("Vertex Position : (%f, %f, %f)\n", vertex.first, vertex.second, vertex.third);
				while (index < this->currentTree.size())
				{
					if (this->currentTree[index] == ']' && interim_frame == 0)
						break;
					if (currentTree[index++] == '[')
						interim_frame++;
					else if (currentTree[index - 1] == ']')
						interim_frame--;
				}
				//printf("After Index : %d Orginal Tree : %s \n Remaining tree string : %s\n", index, currentTree.c_str(), this->currentTree.substr(index, currentTree.size()).c_str());
				if(frameCount)
					popCurrentStackFrame();
				//printf("Vertex Position : (%f, %f, %f)\n", vertex.first, vertex.second, vertex.third);
				//printf("\n");
			}
			this->currAngle = PI / 2.0;
			//curr_dir = this->base_dir.getVector();
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

void tree_generator::popCurrentStackFrame()
{
	while (!posStack->empty() && posStack->top().first != '[')
	{
		if (posStack->top().first == 'F')
		{
			currbranch_l /= contract_l;
			currbranch_w /= contract_w;
		}
		this->posStack->pop();
	}

	if (!posStack->empty() && posStack->top().first == '[')
	{
		this->posStack->pop();
		frameCount--;
		vertex = posStack->top().second.first;
		curr_dir = posStack->top().second.second.getVector();
	}
}
void tree_generator::clearStack()
{
	while (!this->posStack->empty())
		this->posStack->pop();
	this->tree_vectors.clear();
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
