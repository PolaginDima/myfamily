################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IF/Cmd.cpp \
../src/IF/history.cpp \
../src/IF/model.cpp 

OBJS += \
./src/IF/Cmd.o \
./src/IF/history.o \
./src/IF/model.o 

CPP_DEPS += \
./src/IF/Cmd.d \
./src/IF/history.d \
./src/IF/model.d 


# Each subdirectory must supply rules for building sources it contributes
src/IF/%.o: ../src/IF/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D_DEBUG -I/usr/lib/x86_64-linux-gnu -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


