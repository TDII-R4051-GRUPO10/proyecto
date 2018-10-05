#include "sensor_color.h"

void init_color_sensor() {

	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, gpioSensor[S0].port, gpioSensor[S0].pin); //S0
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, gpioSensor[S1].port, gpioSensor[S1].pin); //S1
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, gpioSensor[S2].port, gpioSensor[S2].pin); //S2
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, gpioSensor[S3].port, gpioSensor[S3].pin); //S3

	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, gpioSensor[OUT].port, gpioSensor[OUT].pin); //Output

	disable_sensor();
}


void disable_sensor() {
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S0].port, gpioSensor[S0].pin, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S1].port, gpioSensor[S1].pin, 0);
	vTaskDelay(1/portTICK_RATE_MS);

	return;
}

void activa_sensor() {
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S0].port, gpioSensor[S0].pin, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S1].port, gpioSensor[S1].pin, 0);
}

int sensa_rojo() {
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S2].port, gpioSensor[S2].pin, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S3].port, gpioSensor[S3].pin, 0);
	vTaskDelay(1/portTICK_RATE_MS);

	return lee_sensor();
}

int sensa_verde() {
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S2].port, gpioSensor[S2].pin, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S3].port, gpioSensor[S3].pin, 1);
	vTaskDelay(1/portTICK_RATE_MS);

	return lee_sensor();
}

int sensa_azul() {
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S2].port, gpioSensor[S2].pin, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpioSensor[S3].port, gpioSensor[S3].pin, 1);
	vTaskDelay(1/portTICK_RATE_MS);

	return lee_sensor();
}

int lee_sensor() {
	portTickType inicio, fin;

	//Espero por termino de pulso anterior
	while(Chip_GPIO_GetPinState(LPC_GPIO_PORT, gpioSensor[OUT].port, gpioSensor[OUT].pin));

	//Espero por el comienzo del pulso
	while(!Chip_GPIO_GetPinState(LPC_GPIO_PORT, gpioSensor[OUT].port, gpioSensor[OUT].pin));

	//Cuento hasta fin de pulso
	inicio = xTaskGetTickCount();

	while(Chip_GPIO_GetPinState(LPC_GPIO_PORT, gpioSensor[OUT].port, gpioSensor[OUT].pin));

	fin = xTaskGetTickCount();

	return (int)((fin-inicio)*portTICK_RATE_MS/1000);
}
