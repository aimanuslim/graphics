#pragma once
#include<stdlib.h>
#include<cstdlib>
#include<list>
#include<tuple>
using namespace std;

class part_model
{
public:
	static enum PART_TYPE
	{
		TRUNK,
		BRANCH,
		INTERNODE,
		SEGMENT,
		LEAF
	};

	void setParameters(short, float);
	void setPosition(float, float, float);
	void setColor(float, float, float);
	std::pair<float, float>& getBasePos();
	std::tuple<float, float, float>& getColor();
	float getAngle();
	int getLength();

	part_model(PART_TYPE);
	~part_model();


protected:
	//short number;
	short length;
	std::pair<float, float> basePos;
	float angle;
	std::tuple<float, float, float> color;
	PART_TYPE type;
};

