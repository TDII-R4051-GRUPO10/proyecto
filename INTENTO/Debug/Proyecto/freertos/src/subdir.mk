################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Proyecto/freertos/src/FreeRTOSCommonHooks.c \
../Proyecto/freertos/src/heap_3.c \
../Proyecto/freertos/src/list.c \
../Proyecto/freertos/src/port.c \
../Proyecto/freertos/src/queue.c \
../Proyecto/freertos/src/tasks.c 

OBJS += \
./Proyecto/freertos/src/FreeRTOSCommonHooks.o \
./Proyecto/freertos/src/heap_3.o \
./Proyecto/freertos/src/list.o \
./Proyecto/freertos/src/port.o \
./Proyecto/freertos/src/queue.o \
./Proyecto/freertos/src/tasks.o 

C_DEPS += \
./Proyecto/freertos/src/FreeRTOSCommonHooks.d \
./Proyecto/freertos/src/heap_3.d \
./Proyecto/freertos/src/list.d \
./Proyecto/freertos/src/port.d \
./Proyecto/freertos/src/queue.d \
./Proyecto/freertos/src/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
Proyecto/freertos/src/%.o: ../Proyecto/freertos/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\freertos\inc" -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\inc" -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\lpc_chip_175x_6x\inc" -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\lpc_chip_175x_6x\libs" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


