################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Proyecto/src/GPIO.c \
../Proyecto/src/Proyecto.c \
../Proyecto/src/cr_startup_lpc175x_6x.c \
../Proyecto/src/crp.c \
../Proyecto/src/display.c \
../Proyecto/src/funciones.c \
../Proyecto/src/motor.c \
../Proyecto/src/sensor_color.c 

OBJS += \
./Proyecto/src/GPIO.o \
./Proyecto/src/Proyecto.o \
./Proyecto/src/cr_startup_lpc175x_6x.o \
./Proyecto/src/crp.o \
./Proyecto/src/display.o \
./Proyecto/src/funciones.o \
./Proyecto/src/motor.o \
./Proyecto/src/sensor_color.o 

C_DEPS += \
./Proyecto/src/GPIO.d \
./Proyecto/src/Proyecto.d \
./Proyecto/src/cr_startup_lpc175x_6x.d \
./Proyecto/src/crp.d \
./Proyecto/src/display.d \
./Proyecto/src/funciones.d \
./Proyecto/src/motor.d \
./Proyecto/src/sensor_color.d 


# Each subdirectory must supply rules for building sources it contributes
Proyecto/src/%.o: ../Proyecto/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/pablodfritzler/LPCXpresso/INTENTO/Proyecto/freertos/inc" -I"/home/pablodfritzler/LPCXpresso/INTENTO/Proyecto/inc" -I"/home/pablodfritzler/LPCXpresso/INTENTO/Proyecto/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/pablodfritzler/LPCXpresso/INTENTO/Proyecto/lpc_chip_175x_6x/inc" -I"/home/pablodfritzler/LPCXpresso/INTENTO/Proyecto/lpc_chip_175x_6x/libs" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


