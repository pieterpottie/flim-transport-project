################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AccelStepper.cpp \
../DCMotor.cpp \
../LCD.cpp \
../LiquidCrystal.cpp \
../PDController.cpp \
../SoftPWM.cpp \
../StepperMotor.cpp \
../main.cpp 

OBJS += \
./AccelStepper.o \
./DCMotor.o \
./LCD.o \
./LiquidCrystal.o \
./PDController.o \
./SoftPWM.o \
./StepperMotor.o \
./main.o 

CPP_DEPS += \
./AccelStepper.d \
./DCMotor.d \
./LCD.d \
./LiquidCrystal.d \
./PDController.d \
./SoftPWM.d \
./StepperMotor.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../../libCore/arduino -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


