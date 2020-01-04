################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UI/listui.cpp \
../src/UI/mainui.cpp \
../src/UI/peui.cpp 

OBJS += \
./src/UI/listui.o \
./src/UI/mainui.o \
./src/UI/peui.o 

CPP_DEPS += \
./src/UI/listui.d \
./src/UI/mainui.d \
./src/UI/peui.d 


# Each subdirectory must supply rules for building sources it contributes
src/UI/%.o: ../src/UI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/lib/x86_64-linux-gnu -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


