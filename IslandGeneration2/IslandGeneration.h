// IslandGeneration.h
#ifndef ISLAND_GENERATION
#define ISLAND_GENERATION

#define PI 3.14159 
#define DELTA 30.00 // angle step difference for spiral
#define MAX_RADIUS 120
#define GRADIENT_DELTA 5



/* Island information */

#define IslandWidth 1400
#define IslandHeight 1200
#define IslandRadius 600
#define ZPOS 0.8


// Points generation modes
enum Mode {Random=1, Spiral=2, Grid=3};

// Main
int inputter(enum Mode *);

#include "glm/vec3.hpp"

// Elevation
struct terrain{
	int x;
	int y;
	double intensity; // between 0-1
	double waterValue;
};

// Biomes
#define biomeMax 13
enum Biome{
	SNOW = 0,
	TUNDRA = 1,
	BARE = 2,
	SCORCHED = 3,
	TAIGA = 4,
	SHRUBLAND = 5,
	TEMPDESERT = 6,
	TEMPRAINF = 7,
	TEMPDECIDF = 8,
	GRASSLAND = 9,
	TROPRAINF = 10,
	TROPSEASONF = 11,
	SUBTROPDESERT = 12,
};
void findCategory(double elevation, double moisture, int * category);
//void biomesGeneration(double * colors, double elevation[IslandWidth][IslandHeight], terrain *, int, Biome biomesInfo[IslandWidth][IslandHeight]);
void biomesGeneration(glm::vec3 colors[IslandWidth][IslandHeight], double elevation[IslandWidth][IslandHeight], terrain * waterLocations, int waterCt, Biome biomesInfo[IslandWidth][IslandHeight]);



#define elevDiffThreshold 0.3

int terrainInput(double elevation[IslandWidth][IslandHeight], Biome biomesInformation[IslandWidth][IslandHeight], double * circleVertices, glm::vec3 circleColor[IslandWidth][IslandHeight], glm::vec3 perlinOffsets[IslandWidth][IslandHeight]);

// Utilities
double normalize(int, int);
double * convertToArray(glm::vec3 mat[IslandWidth][IslandHeight]);


// Functions for point generations
void generateRandomPoints(int **, int);
void generateSpiralPoints(int **, int);
void generateGridPoints(int **, int);

// Lloyd relaxation Functions
double * LloydRelaxation(double *);

// Water functions

// Perlin functions
void generatePerlinNoise(glm::vec3 perlin[IslandWidth][IslandHeight], double elevation[IslandWidth][IslandHeight]);

// includes for defining the Voronoi diagram adaptor
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>


// typedefs for defining the adaptor
typedef CGAL::Exact_predicates_inexact_constructions_kernel                  K;
typedef CGAL::Delaunay_triangulation_2<K>                                    DT;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DT>                 AT;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT> AP;
typedef CGAL::Voronoi_diagram_2<DT,AT,AP>                                    VD;

// typedef for the result type of the point location
typedef AT::Site_2                    Site_2;
typedef AT::Point_2                   Point_2;

typedef VD::Locate_result             Locate_result;
typedef VD::Vertex_handle             Vertex_handle;
typedef VD::Face_handle               Face_handle;
typedef VD::Halfedge_handle           Halfedge_handle;
typedef VD::Ccb_halfedge_circulator   Ccb_halfedge_circulator;


// Voronoi functions and definitions
VD generateVoronoi(int **, int);
double * adjustVoronoi(int ** voronoiPositions, double ** voronoiColors, double elevation[IslandWidth][IslandHeight], glm::vec3 landColor[IslandWidth][IslandHeight], int idx);
int VoronoiVerticesColors(VD vd, int ** voronoiPoints, double ** voronoiColors);
double * findCoords(int **, int);
double * findNormals(double * voronoiVertices, int vmax);

#endif
