/*
 * Voronoi.cpp
 *
 *  Created on: Nov 23, 2015
 *      Author: aimanuslim
 */

#include <iostream>
#include "GL/glut.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "IslandGeneration.h"
#include "PerlinNoise.h"

// GLM stuffs
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


double * adjustVoronoi(int ** voronoiPositions, double ** voronoiColors, double elevation[IslandWidth][IslandHeight], glm::vec3 landColor[IslandWidth][IslandHeight], int idx){
	int x = 0, y = 0, i = 0;
	double currHeight;
	double * resVorPos;
	*voronoiColors =  (double *) calloc( idx,  sizeof(double) );
	resVorPos =  (double *) calloc( idx,  sizeof(double) );
	double maxElev = 0;

	PerlinNoise pn;
	double n;
	int maxrad = 1000, rad ;
	glm::vec2 center;
	glm::vec2 loc;

	center.x = IslandWidth / 2;
	center.y = IslandHeight / 2;
	double distanceFromCtr;



	while(i < idx){
//		x = (int) ( ( (double) ((*voronoiPositions)[i] + 1.0f) / 2.0f)     * IslandWidth);
//		y = (int) ( ( (double) ((*voronoiPositions)[i + 1] + 1.0f) / 2.0f) * IslandHeight);
		x = (*voronoiPositions)[i];
		y = (*voronoiPositions)[i + 1];
		loc.x = x;
		loc.y = y;


		if(
			(x >= 0 && x < IslandWidth) &&
			(y >= 0 && y < IslandHeight)
		){

			distanceFromCtr = (double) glm::length(loc - center);
			n = pn.noise( (double) x / IslandWidth, (double) y / IslandHeight, 0.0);
			rad = maxrad * (n - floor(n));
			//n = sin(x + y);
			n *= 1800;

			resVorPos[i] = normalize(x, IslandWidth);
			resVorPos[i + 1] = normalize(y, IslandHeight);
			//z-value
			currHeight = elevation[x][y];
			if(maxElev < currHeight){ maxElev = currHeight ; }
//			(*voronoiPositions)[i + 2] = -currHeight;
			resVorPos[i + 2] = (distanceFromCtr < (IslandRadius + n)) ? -currHeight:0.0f;
//			printf("Voronoi pos: (%d, %d) E: %f\n", x, y, resVorPos[i + 2]);

//			*voronoiColors =  (double *) realloc((*voronoiColors), (i+ 3) *  sizeof(double) );
			// r
			(*voronoiColors)[i] = landColor[x][y].r;
//			(*voronoiColors)[i] *= 1.3;
			// g
			(*voronoiColors)[i + 1] = landColor[x][y].g;
//			(*voronoiColors)[i + 1] *= 1.3;
			// b
			(*voronoiColors)[i + 2] = landColor[x][y].b;
//			(*voronoiColors)[i + 2] *= 0.4;

//			}

		} else{
			if(x < 0){ resVorPos[i] = -1; }
			else { resVorPos[i] = 1; }
			if(y < 0){ resVorPos[i + 1] = -1; }
			else { resVorPos[i + 1] = 1; }
			resVorPos[i + 2] = 0;
		}


		i += 3;

	}
	printf("Max voronoi height: %f", maxElev);
	return resVorPos;

}

double * findNormals(double * voronoiVertices, int vmax){
	int i = 0;
	glm::vec3 p0,p1,p2,n0,n1,n2;
	double * Normals = (double *) calloc(vmax,  sizeof(double));
	while(i < (vmax)){
		p0.x = voronoiVertices[i];
		p0.y = voronoiVertices[i + 1];
		p0.z = voronoiVertices[i + 2];

		p1.x = voronoiVertices[i + 3];
		p1.y = voronoiVertices[i + 4];
		p1.z = voronoiVertices[i + 5];

		p2.x = voronoiVertices[i + 6];
		p2.y = voronoiVertices[i + 7];
		p2.z = voronoiVertices[i + 8];

		n0 = glm::cross(p1 - p0, p2 - p0);
		n1 = glm::cross(p0 - p1, p2 - p1);
		n2 = glm::cross(p0 - p2, p1 - p2);

		Normals[i + 0] = n0.x;
		Normals[i + 1] = n0.y;
		Normals[i + 2] = n0.z;

		Normals[i + 3] = n1.x;
		Normals[i + 4] = n1.y;
		Normals[i + 5] = n1.z;

		Normals[i + 6] = n2.x;
		Normals[i + 7] = n2.y;
		Normals[i + 8] = n2.z;

		i += 9;

	}
	return Normals;

}

double * findCoords(int ** voronoiPoints, int vmax){
	int i = 0;
	glm::vec2 p0,p1,p2;
	int vp = vmax / 3;
	double * Coords = (double *) malloc(vp * 2 * sizeof(double));
	while(i < (vp * 2)){
		p0.x = (double) (*voronoiPoints)[i] / IslandWidth;
		p0.y = (double) (*voronoiPoints)[i + 1] / IslandHeight;
		Coords[i++] = p0.x;
		Coords[i++] = p0.y;
	}
	return Coords;
}

int VoronoiVerticesColors(VD vd, int ** voronoiPoints, double ** voronoiColors){

	// Fill in points for voronoi edges
	VD::Face_iterator ft = vd.faces_begin();
	//	DT dt = vd.dual();
	//	DT::Vertex_iterator dv_iter = dt.vertices_begin();

	int	i = 0, ict=0, x, y, idx = 0;
	double currHeight;

	// specify voronoi surfaces
	for(;ft != vd.faces_end();ft++){
	//	for(;ict<5;ft++, ict++){
		if(!(*ft).is_unbounded()){
			VD::Delaunay_vertex_handle vh = (*ft).dual();
			Point_2 center = vh->point();
			double currX = center.x();
			double currY = center.y();
			Ccb_halfedge_circulator et_start = (*ft).ccb();
			Ccb_halfedge_circulator et = et_start;

			do {
				if(et->has_source() && et->has_target()){

					// middle
	//					delaunayPoints[didx++] = currX;
	//					delaunayPoints[didx++] = currY;
	//					delaunayPoints[didx++] = ZPOS - 0.4;
	//					delaunayColors[didx++] = 1.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;//
	//					delaunayColors[didx++] = 0.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;// 0.0f;
	//					delaunayColors[didx++] = 0.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;//0.0f;
					if(
//							(currX > -1 && currX < 1) && (currY > -1) && (currY < 1)
							(currX >= 0 && currX <= IslandWidth) && (currY >= 0) && (currY <= IslandHeight)
//							(et->source()->point().x() > -1) && (et->source()->point().x() < 1) &&
//							(et->source()->point().y() > -1) && (et->source()->point().y() < 1)

					){
							double sx = et->source()->point().x();
							double sy = et->source()->point().y();
							double tx = et->target()->point().x();
							double ty = et->target()->point().y();

							if(!(sx < 0 || sx > IslandWidth || sy < 0 || sy > IslandHeight || tx < 0 || tx > IslandWidth || ty < 0 || ty > IslandHeight)){
							// reallocate memory
							(*voronoiPoints) = (int *) realloc((*voronoiPoints), (idx + 9) * sizeof(int));

							(*voronoiPoints)[idx + 0] = currX;
							(*voronoiPoints)[idx + 1] = currY;
							(*voronoiPoints)[idx + 2] = ZPOS + 0.2;


							// first vertex of triangle
							(*voronoiPoints)[idx + 3] = et->source()->point().x();
							(*voronoiPoints)[idx + 4] = et->source()->point().y();
							(*voronoiPoints)[idx + 5] = ZPOS + 0.2;


							// second vertex of triangle
							(*voronoiPoints)[idx + 6] = et->target()->point().x();
							(*voronoiPoints)[idx + 7] = et->target()->point().y();
							(*voronoiPoints)[idx + 8] = ZPOS + 0.2;

							idx += 9;



							}


					}

				}

			} while ( ++et != et_start );

		}
	}
	return idx;
}





VD generateVoronoi(int ** setPoints, int numberofPoints){
	VD vd;

	int i = 0;
	for(i = 0; i < numberofPoints * 3; i+=3){
		Site_2 p(Point_2((*setPoints)[i], (*setPoints)[i + 1]));
		vd.insert(p);
	}

	return vd;

}
