#pragma once
#include<stdlib.h>
#include<tuple>
#include<math.h>
#include "glm/glm.hpp"
//#include "tree_renderer.h"

using namespace std;
using namespace glm;

constexpr auto PI = 3.14159265359;
#define _USE_MATH_DEFINES

typedef struct tuple3d
{
	float first;
	float second;
	float third;

	tuple3d(float x, float y, float z)
	{
		first = x; second = y; third = z;
	}

	vec3 getVector()
	{
		return vec3(first, second, third);
	}

	tuple3d()
	{}

	tuple3d(vec3 pos)
	{
		first = pos.x;
		second = pos.y;
		third = pos.z;
	}

	tuple3d operator*(float value)
	{
		return tuple3d(first * value, second * value, third * value);
	}

};

enum PART_TYPE
{
	TRUNK,
	BRANCH,
	INTERNODE,
	SEGMENT,
	LEAF
};

enum TURTLE_AXIS
{
	H,
	L,
	U
};

typedef struct std::pair<tuple3d, tuple3d> pos_orient;

typedef struct vec_lines
{
	vec3 base_point;
	vec3 dir;
	PART_TYPE part;

	vec_lines(vec3 point, vec3 dir, PART_TYPE type)
	{
		base_point = point;
		this->dir = dir;
		this->part = type;
	}

	bool collides(vec_lines line2)
	{
		float t = 0, s = 0;
		float tolerance = 0.05;
		glm::vec3 num = this->base_point - line2.base_point,
			denom = glm::cross(this->dir, line2.dir);

		if (glm::dot(denom, { 1,1,1 }) != 0)
		{
			t = vec_mag(glm::cross(num, line2.dir)) / vec_mag(denom);
			s = vec_mag(glm::cross(num, this->dir)) / vec_mag(denom);
		}
		//printf("dir_line 1 :  (%f, %f, %f)\n dir_line 2 : (%f, %f, %f)\n", this->dir.x, this->dir.y, this->dir.z, line2.dir.x, line2.dir.y, line2.dir.z);
		//printf("direction cross : %f t : %f s : %f\n", denom.length(), t, s);
		//if ((line2.part == LEAF && this->part == LEAF || part == LEAF && line2.part == LEAF) && /*std::abs(float(base_point.x) - float(line2.base_point.x)) < 1*/  std::abs(float(base_point.y) - float(line2.base_point.y)) < 2)
		//{
			//printf("Collision detection : rxs : (%f, %f, %f) (%f) t : %f s : %f\n", denom.x, denom.y, denom.z, vec_mag(denom), t, s);
			//printf("dir 1 : (%f, %f, %f) Base 1 : (%f, %f, %f) \ndir 2 : (%f, %f, %f) Base 2 : (%f, %f, %f)\n", dir.x, dir.y, dir.z, base_point.x, base_point.y, base_point.z, line2.dir.x, line2.dir.y, line2.dir.z, line2.base_point.x, line2.base_point.y, line2.base_point.z);
			//printf("bp1 - bp2 : (%f, %f, %f)\n", num.x, num.y, num.z);
		//}	
		if (vec_mag(denom) != 0 && t <= 1 && s <= 1)
		{
			vec3 intersec_p1 = base_point + t * dir, intersec_p2 = line2.base_point + s * line2.dir;
			float dist_1 = this->Euclidean_dist(intersec_p1), dist_2 = line2.Euclidean_dist(intersec_p2);
			float len_1 = vec_mag(this->dir), len_2 = vec_mag(line2.dir);
			//printf("Intersection point 1 : (%f, %f, %f) Intersection point 2 : (%f, %f, %f)\n", intersec_p1.x, intersec_p1.y, intersec_p1.z, intersec_p2.x, intersec_p2.y, intersec_p2.z);
			//printf("Intersec point dist : (%f, %f) (%f, %f) \n", dist_1, len_1, dist_2, len_2);
/*			if(vec_mag(this->dir) > this->Euclidean_dist(intersec_point)
				&& vec_mag(line2.dir) >= line2.Euclidean_dist(intersec_point))
				return true;*/

			if (vec_mag(intersec_p1 - intersec_p2) < tolerance && dist_1 <= len_1 && dist_2 <= len_2 && s > tolerance)/*vec_mag(intersec_p1 - line2.base_point) > */
			{
				printf("Collides!\n");
				return true;
			}
		}
		return false;
	}

	float Euclidean_dist(vec3 point)
	{
		return sqrt(pow(point.x - this->base_point.x, 2.0f) + pow(point.y - this->base_point.y, 2.0f) + pow(point.z - this->base_point.z, 2.0f));
	}

	float vec_mag(vec3 vector)
	{
		return sqrt(pow(vector.x, 2.0f) + pow(vector.y, 2.0f) + pow(vector.z, 2.0f));
	}

};
