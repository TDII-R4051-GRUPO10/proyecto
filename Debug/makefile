################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Proyecto/src/subdir.mk
-include Proyecto/lpc_chip_175x_6x/src/subdir.mk
-include Proyecto/lpc_board_nxp_lpcxpresso_1769/src/subdir.mk
-include Proyecto/freertos/src/subdir.mk
-include Proyecto/Debug/src/subdir.mk
-include Proyecto/Debug/lpc_chip_175x_6x/src/subdir.mk
-include Proyecto/Debug/lpc_board_nxp_lpcxpresso_1769/src/subdir.mk
-include Proyecto/Debug/gen/subdir.mk
-include Proyecto/Debug/freertos/src/subdir.mk
-include Proyecto/Debug/Drivers_info2/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: INTENTO.axf

# Tool invocations
INTENTO.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="INTENTO.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "INTENTO_Debug.ld" -o "INTENTO.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) INTENTO.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "INTENTO.axf"; # arm-none-eabi-objcopy -v -O binary "INTENTO.axf" "INTENTO.bin" ; # checksum -p LPC1769 -d "INTENTO.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
