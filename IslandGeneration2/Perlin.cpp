/*
 * Perlin.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: aimanuslim
 *      Code implemented and taken from: https://github.com/sol-prog/Perlin_Noise
 */
#include "PerlinNoise.h"
#include "IslandGeneration.h"

void generatePerlinNoise(glm::vec3 perlinMatrix[IslandWidth][IslandHeight], double elevation[IslandWidth][IslandHeight]){

	PerlinNoise pn;
//	int x,y;
//	double n, i, j;
//	for(x = 0; x < IslandWidth; x++){
//		for(y = 0; y < IslandHeight; y++){
//			i = (double) x / IslandWidth;
//			j = (double) y / IslandHeight;
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
	while(j < IslandHeight){
		while(i < IslandWidth){
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



