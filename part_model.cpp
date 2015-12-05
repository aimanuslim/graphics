#include "part_model.h"

part_model::part_model(PART_TYPE part)
{
	this->type = part;
}

void part_model::setParameters(float length, float width, double angle)
{
	this->length = length;
	this->angle = angle;
	this->width = width;
}

void part_model::setPosition(float x, float y, float z)
{
	this->basePos = tuple3d(x, y, z);
}

void part_model::setColor(float r, float g, float b)
{
	this->color = tuple3d(r, g, b);
}

tuple3d& part_model::getBasePos()
{
	return this->basePos;
}

tuple3d& part_model::getColor()
{
	return this->color;
}

tuple3d& part_model::getDir()
{
	return this->dir;
}

double part_model::getAngle()
{
	return angle;
}

float part_model::getLength()
{
	return this->length;
}

float part_model::getWidth()
{
	return this->length;
}


part_model::~part_model()
{
}
