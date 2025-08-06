################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/DC_Motor.c \
../HAL/buzzer.c \
../HAL/lcd.c \
../HAL/servo.c 

OBJS += \
./HAL/DC_Motor.o \
./HAL/buzzer.o \
./HAL/lcd.o \
./HAL/servo.o 

C_DEPS += \
./HAL/DC_Motor.d \
./HAL/buzzer.d \
./HAL/lcd.d \
./HAL/servo.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


