################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Color.cpp \
../Couleur.cpp \
../Intersection.cpp \
../Ray.cpp \
../Set.cpp \
../Shape.cpp \
../Sphere.cpp \
../Vector2.cpp \
../Vector3.cpp \
../application.cpp 

OBJS += \
./Color.o \
./Couleur.o \
./Intersection.o \
./Ray.o \
./Set.o \
./Shape.o \
./Sphere.o \
./Vector2.o \
./Vector3.o \
./application.o 

CPP_DEPS += \
./Color.d \
./Couleur.d \
./Intersection.d \
./Ray.d \
./Set.d \
./Shape.d \
./Sphere.d \
./Vector2.d \
./Vector3.d \
./application.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


