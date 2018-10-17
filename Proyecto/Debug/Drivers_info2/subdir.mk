################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers_info2/FW_GPIO.c \
../Drivers_info2/FW_KitInit.c 

OBJS += \
./Drivers_info2/FW_GPIO.o \
./Drivers_info2/FW_KitInit.o 

C_DEPS += \
./Drivers_info2/FW_GPIO.d \
./Drivers_info2/FW_KitInit.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers_info2/%.o: ../Drivers_info2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\inc" -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


