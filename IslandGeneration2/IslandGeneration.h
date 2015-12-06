// IslandGeneration.h
#ifndef ISLAND_GENERATION
#define ISLAND_GENERATION

#define PI 3.14159 
#define DELTA 30.00 // angle step difference for spiral
#define MAX_RADIUS 120
#define GRADIENT_DELTA 5



/* Window information */
#define windowWidth 1400
#define windowHeight 1200
#define ZPOS 0.8


// Points generation modes
enum Mode {Random=1, Spiral=2, Grid=3};

// Main
int inputter(enum Mode *);


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
//void biomesGeneration(double * colors, double elevation[windowWidth][windowHeight], terrain *, int, Biome biomesInfo[windowWidth][windowHeight]);
void biomesGeneration(double * colors, double elevation[windowWidth][windowHeight], terrain * waterLocations, int waterCt, Biome biomesInfo[windowWidth][windowHeight]);



#define elevDiffThreshold 0.3

int terrainInput(double elevation[windowWidth][windowHeight], Biome b[windowWidth][windowHeight], double *, double *);


double normalize(int, int);


// Functions for point generations
void generateRandomPoints(int **, int);
void generateSpiralPoints(int **, int);
void generateGridPoints(int **, int);

// Lloyd relaxation Functions
double * LloydRelaxation(double *);

// Water functions

// Perlin functions
void generatePerlinNoise(double *);

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
double * adjustVoronoi(int ** voronoiPositions, double ** voronoiColors, double elevation[windowWidth][windowHeight], double * landColor, int idx);
int VoronoiVerticesColors(VD vd, int ** voronoiPoints, double ** voronoiColors);


#endif