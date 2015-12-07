################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../glm/detail/dummy.cpp \
../glm/detail/glm.cpp 

OBJS += \
./glm/detail/dummy.o \
./glm/detail/glm.o 

CPP_DEPS += \
./glm/detail/dummy.d \
./glm/detail/glm.d 


# Each subdirectory must supply rules for building sources it contributes
glm/detail/%.o: ../glm/detail/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/CGAL -I/home/aimanuslim/Documents/graphics/IslandGeneration/glm -I/usr/local/include/GLFW -IGLEW -I/usr/include/CGAL -O0 -g -Wall -c -fmessage-length=0 -frounding-math -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


