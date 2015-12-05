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
	static leaf * createLeaf(double angle, tuple3d pos, float length, float width)
	{
		leaf * model = new leaf();
		model->setParameters(length, width, angle);
		model->setPosition(pos.first, pos.second, 0.0);
		model->setColor(0, 1.0, 0.0);
		return model;
	}
	~leaf()
	{

	}
};

