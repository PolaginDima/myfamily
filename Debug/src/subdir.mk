################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/application.cpp \
../src/consolework.cpp \
../src/myfamily.cpp \
../src/observer.cpp \
../src/people.cpp \
../src/workbdadapter.cpp 

OBJS += \
./src/application.o \
./src/consolework.o \
./src/myfamily.o \
./src/observer.o \
./src/people.o \
./src/workbdadapter.o 

CPP_DEPS += \
./src/application.d \
./src/consolework.d \
./src/myfamily.d \
./src/observer.d \
./src/people.d \
./src/workbdadapter.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D_DEBUG -I/usr/lib/x86_64-linux-gnu -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


