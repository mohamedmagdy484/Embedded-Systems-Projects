################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include HAL/subdir.mk
-include APP\ LAYER/subdir.mk
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


BUILD_ARTIFACT_NAME := Final_Project_Mohamed_MAGDY_Control_ECU
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Final_Project_Mohamed_MAGDY_Control_ECU.lss \

FLASH_IMAGE += \
Final_Project_Mohamed_MAGDY_Control_ECU.hex \

EEPROM_IMAGE += \
Final_Project_Mohamed_MAGDY_Control_ECU.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: main-build

# Main-build Target
main-build: Final_Project_Mohamed_MAGDY_Control_ECU.elf secondary-outputs

# Tool invocations
Final_Project_Mohamed_MAGDY_Control_ECU.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Final_Project_Mohamed_MAGDY_Control_ECU.map -mmcu=atmega32 -o "Final_Project_Mohamed_MAGDY_Control_ECU.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Final_Project_Mohamed_MAGDY_Control_ECU.lss: Final_Project_Mohamed_MAGDY_Control_ECU.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Final_Project_Mohamed_MAGDY_Control_ECU.elf  >"Final_Project_Mohamed_MAGDY_Control_ECU.lss"
	@echo 'Finished building: $@'
	@echo ' '

Final_Project_Mohamed_MAGDY_Control_ECU.hex: Final_Project_Mohamed_MAGDY_Control_ECU.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Final_Project_Mohamed_MAGDY_Control_ECU.elf  "Final_Project_Mohamed_MAGDY_Control_ECU.hex"
	@echo 'Finished building: $@'
	@echo ' '

Final_Project_Mohamed_MAGDY_Control_ECU.eep: Final_Project_Mohamed_MAGDY_Control_ECU.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Final_Project_Mohamed_MAGDY_Control_ECU.elf  "Final_Project_Mohamed_MAGDY_Control_ECU.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Final_Project_Mohamed_MAGDY_Control_ECU.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Final_Project_Mohamed_MAGDY_Control_ECU.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Final_Project_Mohamed_MAGDY_Control_ECU.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents main-build

-include ../makefile.targets
