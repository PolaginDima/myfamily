################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/workbdupdate/ver10.cpp \
../src/workbdupdate/ver20.cpp \
../src/workbdupdate/workbdupdate.cpp \
../src/workbdupdate/workbdver.cpp 

OBJS += \
./src/workbdupdate/ver10.o \
./src/workbdupdate/ver20.o \
./src/workbdupdate/workbdupdate.o \
./src/workbdupdate/workbdver.o 

CPP_DEPS += \
./src/workbdupdate/ver10.d \
./src/workbdupdate/ver20.d \
./src/workbdupdate/workbdupdate.d \
./src/workbdupdate/workbdver.d 


# Each subdirectory must supply rules for building sources it contributes
src/workbdupdate/%.o: ../src/workbdupdate/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D_DEBUG -I/usr/lib/x86_64-linux-gnu -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


