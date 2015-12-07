/*
 * Perlin.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: aimanuslim
 *      Code implemented and taken from: https://github.com/sol-prog/Perlin_Noise
 */
#include "PerlinNoise.h"
#include "IslandGeneration.h"

void generatePerlinNoise(glm::vec3 perlinMatrix[windowWidth][windowHeight], double elevation[windowWidth][windowHeight]){

	PerlinNoise pn;
//	int x,y;
//	double n, i, j;
//	for(x = 0; x < windowWidth; x++){
//		for(y = 0; y < windowHeight; y++){
//			i = (double) x / windowWidth;
//			j = (double) y / windowHeight;
//			n = 20 * pn.noise((double) i, (double) j, 0.0);
//			n = n - floor(n);
//			if(elevation[x][y] == 0){
//				elevation[x][y] += ((int) floor(n) % 2) ? n : -n;
//			}
//		}
//	}

	int i = 0, j = 0, xtemp;
	double n;
	int n_int;
	while(j < windowHeight){
		while(i < windowWidth){
			n = 2.0 * pn.noise((double) i, (double) j, elevation[i][j]);
			perlinMatrix[i][j].x = 0;
			perlinMatrix[i][j].y = 0;
			perlinMatrix[i][j].z = n;
			i++;
		}
		i = 0;
		j++;
	}

}



