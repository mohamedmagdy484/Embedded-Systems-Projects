################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Service/subdir.mk
-include MCAL/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.lss \

FLASH_IMAGE += \
Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: main-build

# Main-build Target
main-build: Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf secondary-outputs

# Tool invocations
Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.map -mmcu=atmega32 -o "Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.lss: Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf  >"Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.lss"
	@echo 'Finished building: $@'
	@echo ' '

Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.hex: Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf  "Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Real_Clock_System_Using_RTC_ITI_GRADUATIO_PROJECT.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents main-build

-include ../makefile.targets
