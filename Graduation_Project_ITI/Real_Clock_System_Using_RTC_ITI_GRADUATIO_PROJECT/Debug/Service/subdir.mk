################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Service/Alarm.c \
../Service/CountDown.c \
../Service/service.c \
../Service/stopwatch.c 

OBJS += \
./Service/Alarm.o \
./Service/CountDown.o \
./Service/service.o \
./Service/stopwatch.o 

C_DEPS += \
./Service/Alarm.d \
./Service/CountDown.d \
./Service/service.d \
./Service/stopwatch.d 


# Each subdirectory must supply rules for building sources it contributes
Service/%.o: ../Service/%.c Service/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


