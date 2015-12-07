#pragma once
#include"common_types.h"
#include<cstdlib>
#include<list>
#include<tuple>
using namespace std;

class part_model
{
public:
	void setParameters(float, float, double);
	void setPosition(float, float, float);
	void setColor(float, float, float);
	void setDirection(float x, float y, float z);
	tuple3d& getBasePos();
	tuple3d& getColor();
	double getAngle();
	float getLength();
	float getWidth();
	PART_TYPE getType();
	//For 3-D object orientation
	tuple3d& getDir();
	part_model(PART_TYPE);
	~part_model();

protected:
	float length;
	tuple3d basePos;
	double angle;
	float width;
	tuple3d color, dir;
	PART_TYPE type;
	//std::vector<char> orient_order;
};

