TARGET = IslandGen
TARGETFAST = IslandGenFAST
LIBS = -lGLU -lGL -lglut -lGLEW -lCGAL -lgmp -lmpfr
FLAGS = -g -O0 -std=c++11 
FFAST= -O3 -std=c++11
CC = g++

.PHONY: default all clean fast

default: $(TARGET)

all: default

debug: $(TARGET)
	gdb $(TARGET)

fast: $(TARGETFAST)

run: $(TARGET)
	./$(TARGET)

runfast: $(TARGETFAST)
	./$(TARGETFAST)

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp)) 
SOURCE = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

#Perlin.o: Perlin.cpp PerlinNoise.h
#	$(CC) -g -O0 -std=c++11 $(FLAGS) -c Perlin.cpp

%.o: %.cpp $(HEADERS)
	$(CC) $(FLAGS) -c $< $(LIBS) -o $@



.PRECIOUS: $(TARGET) $(TARGETFAST) $(OBJECTS)

$(TARGETFAST): $(OBJECTS)
	$(CC) $(FFAST) -c $(OBJECTS) -Wall $(LIBS) -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)	
	-rm -f data

#Main.o: Main.cpp $(HEADERS)
#	g++ -c $(OPTIONS) Main.cpp -o Main.o $(FLAGS)

#PointsGeneration.o: PointsGeneration.cpp $(HEADERS)
#	g++ -c $(OPTIONS) PointsGeneration.cpp -o PointsGeneration.o $(FLAGS)

#Voronoi.o: Voronoi.cpp $(HEADERS)
#	g++ -c $(OPTIONS) Voronoi.cpp -o Voronoi.o $(FLAGS)

#Elevation.o: Elevation.cpp $(HEADERS)
#	g++ -c $(OPTIONS) Elevation.cpp -o Elevation.o $(FLAGS)





