################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DOP/globfunc.cpp 

OBJS += \
./src/DOP/globfunc.o 

CPP_DEPS += \
./src/DOP/globfunc.d 


# Each subdirectory must supply rules for building sources it contributes
src/DOP/%.o: ../src/DOP/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/lib/x86_64-linux-gnu -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


