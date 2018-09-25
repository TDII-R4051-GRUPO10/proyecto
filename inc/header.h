#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "FW_GPIO.h"
#include "Parcial.h"


#define INICIO		1
#define LECT_COLOR  2
#define MOV_MOTOR1  3
#define MOV_MOTOR2  4
#define ALARMA		5

#define DELAY   	300
#define NON			0

#define ROJO		1
#define AZUL		2
#define AMARILLO	3
#define VERDE		4
#define NARANJA		5

#define INTERRUPT1  2,13
#define INTERRUPT2  2,12
#define MOTOR		0,22
#define	LED1		0,21
#define LED2		0,3
#define LED3		0,2
#define LED4		1,31
#define LED5		1,30
#define ALARM       0,26

void pararM1();
void posicionarM2(int);
void activar_Alarma();
void moverM1_360();
int  muestrearColor();
void escribirSD(int*);
void Habilitar_Interrupcion();
void initHardware();
void apagarLeds();
void prenderLed();


