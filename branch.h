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
	static branch * createBranch(float angle, std::pair<float, float> pos)
	{
		branch * model = new branch();
		model->setParameters(branch::length, angle);
		model->setPosition(pos.first, pos.second, 0.0);
		model->setColor(0.54, 0.27, 0.07);
		return model;
	}

	~branch()
	{
	}
};
