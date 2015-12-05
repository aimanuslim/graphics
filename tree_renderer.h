#pragma once
#include<iostream>
#include"common_types.h"
#include "GL/glut.h"
#include "glm/mat4x4.hpp"
#include "part_model.h"
#include "tree_generator.h"
#include<list>
#include<vector>

class tree_generator;

using namespace std;
class tree_renderer
{
	private:
		static struct pos
		{
			float x;
			float y;
			float z;
		};
		
		list<pos> vertices_list;
		float vertices[1000];
		float colors[1000];
		vector<part_model *> parts_list;
		tree_generator * generator;
		int treeVertexCount;
		float pitch, yaw, translate_x, translate_y, translate_z;
		short simCounter;
		
		/************Shader Rendering Parameters****************/
		///* The transformation matrices */
		//GLuint * verticesVbo;
		//GLuint * colorVbo;
		//GLuint * modelVao;

		//glm::mat4 modelMatrix;
		//glm::mat4 viewMatrix;
		//glm::mat4 projMatrix;

		//GLuint vertexShader = 0;
		//GLuint fragmentShader = 0;
		//GLuint shaderProgram = 0;

		///* The location of the transformation matrices */
		//GLint modelMatrixLocation;
		//GLint viewMatrixLocation;
		//GLint projMatrixLocation;
		
		
		void clearPartsList();
		void generateArrays();

	public:	
		int simThresh, iterations;
		bool firstRender;
		tree_renderer(tree_generator *);
		~tree_renderer();
		void init();
		void idle();
		void display();
		void addVertex(float x, float y);
		void addModel(part_model * part);
		void keyboard(unsigned char k, int x, int y);
		void special(int key, int x, int y);
		//void renderScene(int, char **);
};