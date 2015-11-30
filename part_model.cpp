#include "part_model.h"

part_model::part_model(part_model::PART_TYPE part)
{
	this->type = part;
}

void part_model::setParameters(short length, float angle)
{
	this->length = length;
	this->angle = angle;
}

void part_model::setPosition(float x, float y, float z)
{
	this->basePos = std::pair<float, float>(x, y);
}

void part_model::setColor(float r, float g, float b)
{
	this->color = std::tuple<float, float, float>(r, g, b);
}

std::pair<float, float>& part_model::getBasePos()
{
	return this->basePos;
}

std::tuple<float, float, float>& part_model::getColor()
{
	return this->color;
}

float part_model::getAngle()
{
	return angle;
}

int part_model::getLength()
{
	return this->length;
}

part_model::~part_model()
{
}
