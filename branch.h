#pragma once
#include "part_model.h"

class branch : public part_model
{
public:

	static unsigned short length;
	static unsigned short count;

	branch() : part_model(BRANCH)
	{
		branch::count++;
	}

	//Default branch Instance Creator
	static branch * createBranch(vec3 direction, tuple3d pos /*std::pair<float, float> pos2*/,  float length, float width)
	{
		branch * model = new branch();
		model->setParameters(length, width, 0.0);
		model->setDirection(direction.x, direction.y, direction.z);
		model->setPosition(pos.first, pos.second, 0.0);
		model->setColor(0.54, 0.27, 0.07);
		return model;
	}

	~branch()
	{
	}
};
