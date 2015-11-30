#pragma once
#include "part_model.h"

class leaf : public part_model
{
public:

	static unsigned short length;
	static unsigned short count;

	leaf() : part_model(LEAF)
	{
		leaf::count++;
	}
		
	//Default Leaf Instance Creator
	static leaf * createLeaf(float angle, std::pair<float, float> pos)
	{
		leaf * model = new leaf();
		model->setParameters(leaf::length, angle);
		model->setPosition(pos.first, pos.second, 0.0);
		model->setColor(0, 1.0, 0);
		return model;
	}
	~leaf()
	{

	}
};

