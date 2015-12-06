/*
 * Perlin.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: aimanuslim
 *      Code implemented and taken from: https://github.com/sol-prog/Perlin_Noise
 */
#include "PerlinNoise.h"
#include "IslandGeneration.h"

void generatePerlinNoise(double * vertices){

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
		while(i < windowWidth * 3){
			n = pn.noise((double) i, (double) j, 0.0);
//			n = n - floor(n);
			n_int = n * 400;
			xtemp = i / 3;
			(vertices)[i + j * windowWidth * 3] = ((int) n_int % 2) ? n : -n;
			(vertices)[(i + 1) + j * windowWidth * 3] = ((int) n_int % 2) ? n : -n;
			i += 3;
		}
		i = 0;
		j++;
	}

}



