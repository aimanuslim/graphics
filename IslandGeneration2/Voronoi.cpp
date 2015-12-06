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

double * adjustVoronoi(int ** voronoiPositions, double ** voronoiColors, double elevation[windowWidth][windowHeight], double * landColor, int idx){
	int x = 0, y = 0, i = 0;
	double currHeight;
	double * resVorPos;
	*voronoiColors =  (double *) calloc( idx,  sizeof(double) );
	resVorPos =  (double *) calloc( idx,  sizeof(double) );

	while(i < idx){
//		x = (int) ( ( (double) ((*voronoiPositions)[i] + 1.0f) / 2.0f)     * windowWidth);
//		y = (int) ( ( (double) ((*voronoiPositions)[i + 1] + 1.0f) / 2.0f) * windowHeight);
		x = (*voronoiPositions)[i];
		y = (*voronoiPositions)[i + 1];
		x -= (x % 3);
		y -= (y % 3);

		if(
			(x >= 0 && x <= windowWidth) &&
			(y >= 0 && y <= windowHeight)
		){

			resVorPos[i] = normalize(x, windowWidth);
			resVorPos[i + 1] = normalize(y, windowHeight);
			//z-value
			currHeight = elevation[x][y];
//			(*voronoiPositions)[i + 2] = -currHeight;
			resVorPos[i + 2] = -currHeight;

//			*voronoiColors =  (double *) realloc((*voronoiColors), (i+ 3) *  sizeof(double) );
			// r
			(*voronoiColors)[i] = landColor[x + y * windowWidth * 3];
//			(*voronoiColors)[i] *= 1.3;
			// g
			(*voronoiColors)[i + 1] = landColor[x + 1 + y * windowWidth * 3];
//			(*voronoiColors)[i + 1] *= 1.3;
			// b
			(*voronoiColors)[i + 2] = landColor[x + 2 + y * windowWidth * 3];
//			(*voronoiColors)[i + 2] *= 0.4;

//			}
		}
		else{
//			(*voronoiPositions)[i + 0] = (x < 0) ? -1 : 1;
//			(*voronoiPositions)[i + 1] = (y < 0) ? -1 : 1;
//			(*voronoiPositions)[i + 2] = ZPOS - 0.7;
			resVorPos[i + 0] = (x < 0) ? -1 : 1;
			resVorPos[i + 1] = (y < 0) ? -1 : 1;
			resVorPos[i + 2] = ZPOS - 0.7;
		}

		i += 3;

	}
	return resVorPos;

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
							(currX >= 0 && currX <= windowWidth) && (currY >= 0) && (currY <= windowHeight)
//							(et->source()->point().x() > -1) && (et->source()->point().x() < 1) &&
//							(et->source()->point().y() > -1) && (et->source()->point().y() < 1)

					){
							double sx = et->source()->point().x();
							double sy = et->source()->point().y();
							double tx = et->target()->point().x();
							double ty = et->target()->point().y();

//							if(!(sx < -1 || sx > 1 || sy < -1 || sy > 1 || tx < -1 || tx > 1 || ty < -1 || ty > 1)){
							if(!(sx < 0 || sx > windowWidth || sy < 0 || sy > windowHeight || tx < 0 || tx > windowWidth || ty < 0 || ty > windowHeight)){
							// reallocate memory
							(*voronoiPoints) = (int *) realloc((*voronoiPoints), (idx + 9) * sizeof(int));

							(*voronoiPoints)[idx++] = currX;
							(*voronoiPoints)[idx++] = currY;
							(*voronoiPoints)[idx++] = ZPOS + 0.2;


//							voronoiColors[i++] = 0.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;//
//							voronoiColors[i++] = 1.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;// 0.0f;
//							voronoiColors[i++] = 0.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;//0.0f;

							// first vertex of triangle

							(*voronoiPoints)[idx++] = et->source()->point().x();
							(*voronoiPoints)[idx++] = et->source()->point().y();
			//					voronoiPoints[idx++] = 0;
							(*voronoiPoints)[idx++] = ZPOS + 0.2;
//							voronoiColors[i++] = 0.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;//
//							voronoiColors[i++] = 0.6f; //(double) ((rand() % (int) 255) + 1) / 255.0f;// 0.0f;
//							voronoiColors[i++] = 1.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;//0.0f;
			//
							// second vertex of triangle
							(*voronoiPoints)[idx++] = et->target()->point().x();
							(*voronoiPoints)[idx++] = et->target()->point().y();
			//				voronoiPoints[idx++] = 0;
							(*voronoiPoints)[idx++] = ZPOS + 0.2;
//							voronoiColors[i++] = 0.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;//
//							voronoiColors[i++] = 0.6f; //(double) ((rand() % (int) 255) + 1) / 255.0f;// 0.0f;
//							voronoiColors[i++] = 1.0f; //(double) ((rand() % (int) 255) + 1) / 255.0f;//0.0f;
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
