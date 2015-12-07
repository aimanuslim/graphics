/*
 * Elevation.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: aimanuslim
 */

#include <iostream>
#include "GL/glut.h"
#include "math.h"
#include "stdlib.h"
#include "PerlinNoise.h"
#include "IslandGeneration.h"

int verticesCt = 0;
//double elevation[windowWidth][windowHeight] = {0};
//<vector<vector<double>> elevation(windowWidth, windowHeight);
double waterIntensity[windowWidth][windowHeight] = {0};

int vIdx = 0, colorIdx;

//void generatePerlinNoise(double elevation[][windowHeight], double waterValues[][windowHeight]){
//
//	PerlinNoise pn;
//	int x,y;
//	double n, i, j;
//	for(x = 0; x < windowWidth; x++){
//		for(y = 0; y < windowHeight; y++){
//			i = (double) x / windowWidth;
//			j = (double) y / windowHeight;
//			n = 20 * pn.noise((double) i, (double) j, 0.0);
//			n = n - floor(n);
//			if(waterValues[x][y] == 0){
//				elevation[x][y] = n;
//			}
//		}
//	}
//}

int terrainInput(double elevation[windowWidth][windowHeight], Biome biomesInformation[windowWidth][windowHeight], double * circleVertices, glm::vec3 circleColor[windowWidth][windowHeight], glm::vec3 perlinOffsets[windowWidth][windowHeight]){

	int waterIdx;
	int waterLocCount = 10;
	terrain  waterLocations[waterLocCount];
	for(waterIdx = 0; waterIdx < waterLocCount; waterIdx++){
		waterLocations[waterIdx].x = (rand() % (int) windowWidth) + 1;
//		waterLocations[waterIdx].x = 700;
		waterLocations[waterIdx].y = (rand() % (int) windowHeight) + 1;
//		waterLocations[waterIdx].y = 600;

		//printf("Water location %d -> x: %d y: %d\n", waterIdx, waterLocations[waterIdx].x, waterLocations[waterIdx].y);
		waterLocations[waterIdx].waterValue = 1.0f;
	}

	int circlesCt = 15;
	int circleIdx;
	//terrain allIntensity[circlesCt] = {intensity1, intensity2, intensity3, intensity4, intensity5, intensity6};
	terrain allIntensity[circlesCt];
	int heightRand;
	int maxHeight = 500;
	for(circleIdx = 0; circleIdx < circlesCt; circleIdx++){
		allIntensity[circleIdx].x = (rand() % (int) windowWidth) + 1;
		allIntensity[circleIdx].y = (rand() % (int) windowHeight) + 1;;
		heightRand = (rand() % maxHeight);
		allIntensity[circleIdx].intensity = 0.4f;
//		allIntensity[circleIdx].intensity = ((double) heightRand / maxHeight) * 0.4f;
	}

	double xpos0, xpos1, ypos0, ypos1, r, rmax, myPow;
	double theta = 0;
	int vi = 0, coli = 0, i;
	rmax = 400; // for circles
	r = 200;

	int x,y;
	i = 0;
	double distFromCenter;
	for(x = 0; x < windowWidth; x++){
		for(y = 0; y < windowHeight; y++){
			for(i = 0; i < circlesCt; i++){
//				r = (double) (rand() % (int) (rmax / 2)) + (rmax / 2);
				distFromCenter = sqrt( (double) pow(allIntensity[i].x - x, 2) + (double) pow(allIntensity[i].y - y, 2));
				distFromCenter = ((distFromCenter / r) > 1) ? 1.0f : (distFromCenter / r);

				if(distFromCenter <= 1.000000f){
					// the further you are, the less intensity, lower elevation

					if((1.0 - distFromCenter) < (1.0 /3.0)){
						myPow = 2;
					} else if((1.0 - distFromCenter) < (2.0 * 1.0 /3.0)){
						myPow = 1;
					} else {
						myPow = 0.5;
					}

					elevation[x][y] +=  allIntensity[i].intensity * pow(1.0 - distFromCenter, myPow);
				}
				else {
					elevation[x][y] +=  0.0f;
				}
			}
//			elevation[x][y] *= 0.6;
//			printf("Elevation at (%d, %d): %lf\n", x, y, elevation[x][y]);
//			printf("Elevation: %lf\n", elevation[x][y]);
		}
	}

//	r = 100; // for water
//	for(x = 0; x < windowWidth; x++){
//			for(y = 0; y < windowHeight; y++){
//				for(i = 0; i < waterLocCount; i++){
//					distFromCenter = sqrt( (double) pow(waterLocations[i].x - x, 2) + (double) pow(waterLocations[i].y - y, 2));
//					distFromCenter = ((distFromCenter / r) > 1) ? 1.0f : (distFromCenter / r);
//					if(distFromCenter < 1.000000f){
//						// the further you are, the less intensity, less water
//						waterIntensity[x][y] +=  waterLocations[i].waterValue * (1.0f - distFromCenter) -  elevation[x][y];
////						waterIntensity[x][y] *= 0.3;
//						if(waterIntensity[x][y] > 1.0){waterIntensity[x][y] = 1.0f;}
//						if(waterIntensity[x][y] < 0.0){waterIntensity[x][y] = 0.0f;}
//					}
//					else {
//						waterIntensity[x][y] +=  0.0f;
//					}
//				}
//			}
//		}



//
//	i = 0;
//	int j = 0;
//	int xtemp, ytemp;
//	while(j < windowHeight){
//		while(i < windowWidth * 3){
//			xtemp = i / 3;
//			circleVertices[i + j * windowWidth * 3] = normalize(xtemp, windowWidth);
////			circleColor[i + j * windowWidth * 3] = 1.0f - elevation[xtemp][j];
////			circleColor[i + j * windowWidth * 3] = (waterIntensity[xtemp][j] > 0) ? 0.0f : 1.0f - elevation[xtemp][j];
//			circleColor[i + j * windowWidth * 3] = 0.0f;
//
//			circleVertices[(i + 1) + j * windowWidth * 3] = normalize(j, windowHeight);
//			circleColor[(i + 1) + j * windowWidth * 3] = 1.0f - elevation[xtemp][j];
////			circleColor[(i + 1) + j * windowWidth * 3] = (waterIntensity[xtemp][j] > 0) ? 0.0f : 1.0f - elevation[xtemp][j];
//
////			circleVertices[(i + 2) + j * windowWidth * 3] = 0.0f;
////			circleVertices[(i + 2) + j * windowWidth * 3] = ZPOS + 0.2;;
//			circleVertices[(i + 2) + j * windowWidth * 3] = ZPOS - elevation[xtemp][j] - 0.7;
//
////			circleColor[(i + 2) + j * windowWidth * 3] = (waterIntensity[xtemp][j] > 0) ? waterIntensity[xtemp][j]: 1.0f - elevation[xtemp][j]; // BLUE value
////			circleColor[(i + 2) + j * windowWidth * 3] = 1.0f - elevation[xtemp][j];
//			circleColor[(i + 2) + j * windowWidth * 3] = 0.0f;
//
//
//			i += 3;
//		}
//		i = 0;
//		j++;
//	}

	// Perlin, may or may not be needed
	generatePerlinNoise(perlinOffsets, elevation);

	biomesGeneration(circleColor, elevation, waterLocations, waterLocCount, biomesInformation);

	return windowWidth * windowHeight;

}

