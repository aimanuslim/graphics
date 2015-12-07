#include <iostream>
#include "GL/glut.h"
#include <cstdlib> 
#include <ctime> 
#include <math.h>

#include "IslandGeneration.h"


using namespace std;

void inputter(){
	int m;
	cout<< "Enter number of points: ";
 	cin >> numberofPoints;
 	cout<< "Enter point generation mode (Random=1, Spiral=2, Grid=3): ";
 	cin >> m;
 	pointMode = (Mode) m; 
 	cout << endl;
}

void generateRandomPoints(){
 	setPoints = (float *) malloc(sizeof(float) * numberofPoints * 2);

 	srand((unsigned)time(0)); 
     
    for(int i=0; i<numberofPoints * 2; i++){
    	
    	if((i + 1) % 2 == 0){
    		setPoints[i] = (rand() % (int) windowHeight) + 1;
    	} else{ 
        	setPoints[i] = (rand() % (int) windowWidth) + 1;
        }
        cout << setPoints[i] << " " ; 
   	} 
}

void generateSpiralPoints(){
	// x = R * cos(theta), y = R * sin(theta)
	float x, y, R;
	float theta; // theta is in radians
	int i = 0;
 	setPoints = (float *) malloc(sizeof(float) * numberofPoints * 2);
	x = 0; y = 0; R = 10;
	for(theta = 0; i + 1 < numberofPoints * 2; theta += (PI / DELTA)){
		x = R * cos(theta) + windowWidth / 2;
		y = R * sin(theta) + windowHeight / 2;
		R += 10;
		setPoints[i] = x;
		setPoints[i + 1] = y; 
		i += 2;
	}
}

void generateGridPoints(){
	int cellcount, xcellct, ycellct, cellxwidth, cellyheight, xp, yp, i;
	cellcount = windowHeight * windowWidth / numberofPoints;
	xcellct = windowWidth / (numberofPoints / 2);
	ycellct = windowHeight / (numberofPoints / 2);
	cellxwidth = windowWidth / xcellct;
	cellyheight = windowHeight / ycellct;
	for(xp = cellxwidth / 2, yp = cellyheight / 2; (xp < windowWidth) && (yp < windowHeight) && (i  + 1 < numberofPoints * 2); xp += cellxwidth, yp += cellyheight){
		setPoints[i] = xp;
		setPoints[i + 1] = yp;
		i += 2;
	}

}

