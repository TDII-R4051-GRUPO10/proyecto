################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Proyecto/lpc_board_nxp_lpcxpresso_1769/src/board.c \
../Proyecto/lpc_board_nxp_lpcxpresso_1769/src/board_sysinit.c \
../Proyecto/lpc_board_nxp_lpcxpresso_1769/src/lpc_phy_smsc87x0.c 

OBJS += \
./Proyecto/lpc_board_nxp_lpcxpresso_1769/src/board.o \
./Proyecto/lpc_board_nxp_lpcxpresso_1769/src/board_sysinit.o \
./Proyecto/lpc_board_nxp_lpcxpresso_1769/src/lpc_phy_smsc87x0.o 

C_DEPS += \
./Proyecto/lpc_board_nxp_lpcxpresso_1769/src/board.d \
./Proyecto/lpc_board_nxp_lpcxpresso_1769/src/board_sysinit.d \
./Proyecto/lpc_board_nxp_lpcxpresso_1769/src/lpc_phy_smsc87x0.d 


# Each subdirectory must supply rules for building sources it contributes
Proyecto/lpc_board_nxp_lpcxpresso_1769/src/%.o: ../Proyecto/lpc_board_nxp_lpcxpresso_1769/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\freertos\inc" -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\inc" -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\lpc_chip_175x_6x\inc" -I"C:\sebas\FACULTAD\Digitales_2\workspace\INTENTO\Proyecto\lpc_chip_175x_6x\libs" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


