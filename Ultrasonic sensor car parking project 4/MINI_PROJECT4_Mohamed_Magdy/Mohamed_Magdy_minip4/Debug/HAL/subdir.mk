################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LED.c \
../HAL/Ultrasonic.c \
../HAL/buzzer.c \
../HAL/lcd.c 

OBJS += \
./HAL/LED.o \
./HAL/Ultrasonic.o \
./HAL/buzzer.o \
./HAL/lcd.o 

C_DEPS += \
./HAL/LED.d \
./HAL/Ultrasonic.d \
./HAL/buzzer.d \
./HAL/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


