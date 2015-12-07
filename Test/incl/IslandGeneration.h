// IslandGeneration.h
#ifndef ISLAND_GENERATION
#define ISLAND_GENERATION

#define PI 3.14159 
#define DELTA 6 // angle step difference for spiral

/* Window information */
float windowWidth = 800;
float windowHeight = 600;

// Main
void inputter();

// Points
float * setPoints;
int numberofPoints;

// Points generation modes
enum Mode {Random=1, Spiral=2, Grid=3} pointMode;

// Functions for point generations
void generateRandomPoints();
void generateSpiralPoints();
void generateGridPoints();

// Lloyd relaxation Functions
float * LloydRelaxation(float *);


// Voronoi functions and definitions
void generateVoronoi();



#endif
