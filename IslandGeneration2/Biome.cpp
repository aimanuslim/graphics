/*
 * Biome.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: aimanuslim
 */

#include "IslandGeneration.h"
#include "PerlinNoise.h"

int biomeColors[biomeMax][3] = {
		{248,248,248}, // snow
		{221,221,187}, // tundra
		{187,187,187}, // bare
		{146,146,146}, // scorched
		{204,212,187}, // taiga
		{196,204,187}, // shurbland
		{228,232,202}, // tempdesert
		{164,196,168}, // temprainf
		{180,201,169}, // tempdecidf
		{196,212,170}, // grassland
		{156,187,169}, // troprainf
		{169,204,164}, // tropseasonf
		{233,221,199}, // subtropdesert

};

 Biome biomeTable[4][6] = {
		{SUBTROPDESERT, GRASSLAND, TROPSEASONF, TROPSEASONF, TROPRAINF, TROPRAINF},
		{TEMPDESERT, GRASSLAND, GRASSLAND, TEMPDECIDF, TEMPDECIDF, TEMPRAINF},
		{TEMPDESERT, TEMPDESERT, SHRUBLAND, SHRUBLAND, TAIGA, TAIGA},
		{SCORCHED, BARE, TUNDRA, SNOW, SNOW, SNOW},
//		{TEMPDESERT, GRASSLAND, TROPSEASONF, TROPSEASONF, TROPRAINF, TROPRAINF},
//		{TEMPDESERT, GRASSLAND, GRASSLAND, TEMPDECIDF, TEMPDECIDF, TEMPRAINF},
//		{TEMPDESERT, TEMPDESERT, SHRUBLAND, SHRUBLAND, TAIGA, TAIGA},
//		{SCORCHED, BARE, TUNDRA, SNOW, SNOW, SNOW},
};

double elevationZoneDiv = (double) 1 / 4;
double moistureZoneDiv = (double) 1 / 6;
int category[2] = {0, 0};
double maxElevation = 0;

void findCategory(double elevation, double moisture, int * category){
	double  highThreshold = 0.6;
	elevationZoneDiv = highThreshold / 4.0f;

//	if((elevation / maxElevation) < (1.0f * elevationZoneDiv)){
	if((elevation / highThreshold) < (1.0f * elevationZoneDiv)){
		(category)[0] = 0;
	}
//	else if((elevation / maxElevation) < (2.0f * elevationZoneDiv))
	else if((elevation / highThreshold) < (2.0f * elevationZoneDiv))
	{
		(category)[0] = 1;
	}
//	else if((elevation / maxElevation) < (3.0f * elevationZoneDiv)){
	else if((elevation / highThreshold) < (3.0f * elevationZoneDiv)){
		(category)[0] = 2;
	} else {
		(category)[0] = 3;
	}


	if(moisture < (1.0 * moistureZoneDiv)){
		(category)[1] = 0;
	}
	else if(moisture < (2.0 * moistureZoneDiv))
	{
		(category)[1] = 1;
	}
	else if(moisture < (3.0 * moistureZoneDiv)){
		(category)[1] = 2;
	}
	else if(moisture < (4.0 * moistureZoneDiv)){
		(category)[1] = 3;
	}
	else if(moisture < (5.0 * moistureZoneDiv)){
		(category)[1] = 4;
	}
	else {
		(category)[1] = 5;
	}
//	if((elevation / maxElevation) > (3 * elevationZoneDiv)){
//		printf("Elevation: %.3f, idx=%d Moisture: %.3f, idx=%d\n", elevation, category[0], moisture, category[1]);
//	}
}


void biomesGeneration(glm::vec3 colors[windowWidth][windowHeight], double elevation[windowWidth][windowHeight], terrain * waterLocations, int waterCt, Biome biomesInfo[windowWidth][windowHeight]){
	int x, y, xidx, waterIdx;
	double r, g, b;
	int isWater, isHighest;
	int maxrad = 1000, rad;

	maxElevation = 0.0;
	for(y = 0; y < windowHeight; y++){
			for(x = 0; x < windowWidth; x++){
				if(maxElevation < elevation[x][y]){ maxElevation = elevation[x][y];}
			}
	}

//	printf("Max elevation: %f\n", maxElevation);

	PerlinNoise pn;
	float n;
	double moisture, distFromCenter;
	for(y = 0; y < windowHeight; y++){
		for(x = 0; x < windowWidth; x++){
//			xidx = x / 3;
			xidx = x;

			moisture = 0;
			for(waterIdx = 0; waterIdx < waterCt; waterIdx++){
				n = pn.noise( (double) x / windowWidth, (double) y / windowHeight, 0.0);
				rad = maxrad * (n - floor(n));
				// find moisture
				distFromCenter = sqrt( (double) pow(waterLocations[waterIdx].x - xidx, 2) + (double) pow(waterLocations[waterIdx].y - y, 2));
				distFromCenter = ((distFromCenter / rad) > 1) ? 1.0f : (distFromCenter / rad);
//				printf("Distance: %.3f\n", distFromCenter);
				moisture += waterLocations[waterIdx].waterValue * (1.0 - distFromCenter);

				if(moisture > 1.0){moisture = 1.0f;}
				if(moisture < 0.0){moisture = 0.0f;}
			}
//			printf("Elevation at (%d, %d): %f\n", xidx, y, elevation[xidx][y]);
//			printf("Moisture at (%d, %d): %f\n", xidx, y, moisture);
			//			moisture *= 0.6;
//			moisture *= 0.3;

			// find category
			findCategory(elevation[xidx][y], moisture, category);
			//printf(" %f ", elevation[x][y]);
			// use category to index into biomeTable
			Biome thisBiome = biomeTable[category[0]][category[1]];
			biomesInfo[xidx][y] = thisBiome;


			// define colors using biomeColors
			r = (double) biomeColors[thisBiome][0] / 255;
			g = (double) biomeColors[thisBiome][1] / 255;
			b = (double) biomeColors[thisBiome][2] / 255;
//			r = (double) biomeColors[TROPRAINF][0] / 255;
//			g = (double) biomeColors[TROPRAINF][1] / 255;
//			b = (double) biomeColors[TROPRAINF][2] / 255;


//			switch(thisBiom)
//				printf("Elevation: %.3f, Moisture: %.3f -> SNOW\n", elevation[xidx][y], moisture);



//
//			switch(thisBiome){
//				case TROPRAINF: printf("Elevation: %.3f, Moisture: %.3f -> TROPRAINF idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case TEMPRAINF: printf("Elevation: %.3f, Moisture: %.3f -> TEMPRAINF idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case TROPSEASONF: printf("Elevation: %.3f, Moisture: %.3f -> TROPSEASONF idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case TEMPDECIDF: printf("Elevation: %.3f, Moisture: %.3f -> TEMPDECIDF idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case GRASSLAND: printf("Elevation: %.3f, Moisture: %.3f -> GRASSLAND idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case SHRUBLAND: printf("Elevation: %.3f, Moisture: %.3f -> SHRUBLAND idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case TAIGA: printf("Elevation: %.3f, Moisture: %.3f -> TAIGA idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case TUNDRA: printf("Elevation: %.3f, Moisture: %.3f -> TUNDRA idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case BARE: printf("Elevation: %.3f, Moisture: %.3f -> BARE idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case SCORCHED: printf("Elevation: %.3f, Moisture: %.3f -> SCORCHED idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case SUBTROPDESERT: printf("Elevation: %.3f, Moisture: %.3f -> SUBTROPDESERT idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case SNOW:printf("Elevation: %.3f, Moisture: %.3f -> SNOW idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//				case TEMPDESERT: printf("Elevation: %.3f, Moisture: %.3f -> TEMPDESERT idx: e: %d m: %d\n", elevation[xidx][y], moisture, category[0], category[1]); break;
//			}

//			if(moisture < 5 * moistureZoneDiv){ g *= 1.1;}
//			else{ b *= 1.5; }


			// change colors
			double m = (double) 1 / 2;
//			if(x % 3 == 0){
				colors[x][y].r = ((moisture > 0.8) && (elevation[xidx][y] == 0.00000000000000000000000f)) ? 0.0f : r * 0.8;
				colors[x][y].g = ((moisture > 0.8) && (elevation[xidx][y] == 0.00000000000000000000000f)) ? 0.0f : g * 0.8;
				colors[x][y].b = ((moisture > 0.8) && (elevation[xidx][y] == 0.00000000000000000000000f)) ? moisture - 0.5 : b * 0.8;

//				colors[(x + 0) + y * windowWidth * 3] = ((moisture > 0.8) && (elevation[xidx][y] == 0.00000000000000000000000f)) ? 0.0f : r * 0.8;

//				colors[(x + 1) + y * windowWidth * 3] = ((moisture > 0.6) && (elevation[xidx][y] < ((double) 1.0 / pow(10, 6)))) ? 0.0f : g * 0.8;
//				colors[(x + 1) + y * windowWidth * 3] = ((moisture > 0.8) && (elevation[xidx][y] == 0.00000000000000000000000f)) ? 0.0f : g * 0.8;


//				colors[(x + 2) + y * windowWidth * 3] = ((moisture > 0.8) && (elevation[xidx][y] == 0.00000000000000000000000f)) ? moisture - 0.5 : b * 0.8;
				if(((elevation[xidx][y] != 0.0000000000000000000f))){
//					printf("Non zero Elevation: %0.8lf\n", elevation[xidx][y]);
				}
//				colors[(x + 2) + y * windowWidth * 3] *= 2;

//				if(colors[(x + 0) + y * windowWidth * 3] > 1.0){colors[(x + 0) + y * windowWidth * 3] = 1.0;}
//				if(colors[(x + 1) + y * windowWidth * 3] > 1.0){colors[(x + 1) + y * windowWidth * 3] = 1.0;}
//				if(colors[(x + 2) + y * windowWidth * 3] > 1.0){colors[(x + 2) + y * windowWidth * 3] = 1.0;}

//				if(thisBiome == SUBTROPDESERT){
//							colors[(x + 0) + y * windowWidth * 3] = r * 0.9;
//							colors[(x + 1) + y * windowWidth * 3] = g * 0.9;
//							colors[(x + 2) + y * windowWidth * 3] = b * 0.9;
//						}
//			}

		}
	}
	x = 0;
}




