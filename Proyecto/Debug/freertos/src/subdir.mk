################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/src/FreeRTOSCommonHooks.c \
../freertos/src/heap_3.c \
../freertos/src/list.c \
../freertos/src/port.c \
../freertos/src/queue.c \
../freertos/src/tasks.c 

OBJS += \
./freertos/src/FreeRTOSCommonHooks.o \
./freertos/src/heap_3.o \
./freertos/src/list.o \
./freertos/src/port.o \
./freertos/src/queue.o \
./freertos/src/tasks.o 

C_DEPS += \
./freertos/src/FreeRTOSCommonHooks.d \
./freertos/src/heap_3.d \
./freertos/src/list.d \
./freertos/src/port.d \
./freertos/src/queue.d \
./freertos/src/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/src/%.o: ../freertos/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\inc" -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\freertos\inc" -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\freertos\src" -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\lpc_board_nxp_lpcxpresso_1769\src" -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\lpc_chip_175x_6x\inc" -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\lpc_chip_175x_6x\libs" -I"C:\Users\agust\Documents\LPCXpresso_8.2.2_650\workspace\Proyecto\lpc_chip_175x_6x\src" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

