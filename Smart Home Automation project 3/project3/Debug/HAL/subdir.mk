################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/DC_Motor.c \
../HAL/FlameSensor.c \
../HAL/LDR.c \
../HAL/LED.c \
../HAL/buzzer.c \
../HAL/lcd.c \
../HAL/lm35_sensor.c 

OBJS += \
./HAL/DC_Motor.o \
./HAL/FlameSensor.o \
./HAL/LDR.o \
./HAL/LED.o \
./HAL/buzzer.o \
./HAL/lcd.o \
./HAL/lm35_sensor.o 

C_DEPS += \
./HAL/DC_Motor.d \
./HAL/FlameSensor.d \
./HAL/LDR.d \
./HAL/LED.d \
./HAL/buzzer.d \
./HAL/lcd.d \
./HAL/lm35_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


