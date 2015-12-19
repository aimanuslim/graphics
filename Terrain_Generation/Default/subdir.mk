################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Biome.o \
../Elevation.o \
../Main.o \
../Perlin.o \
../PerlinNoise.o \
../PointsGeneration.o \
../Voronoi.o \
../ppm.o 

CPP_SRCS += \
../Biome.cpp \
../Elevation.cpp \
../Main.cpp \
../Perlin.cpp \
../PerlinNoise.cpp \
../PointsGeneration.cpp \
../Voronoi.cpp \
../ppm.cpp 

OBJS += \
./Biome.o \
./Elevation.o \
./Main.o \
./Perlin.o \
./PerlinNoise.o \
./PointsGeneration.o \
./Voronoi.o \
./ppm.o 

CPP_DEPS += \
./Biome.d \
./Elevation.d \
./Main.d \
./Perlin.d \
./PerlinNoise.d \
./PointsGeneration.d \
./Voronoi.d \
./ppm.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/CGAL -I/home/aimanuslim/Documents/graphics/IslandGeneration/glm -I/usr/local/include/GLFW -IGLEW -I/usr/include/CGAL -O0 -g -Wall -c -fmessage-length=0 -frounding-math -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


