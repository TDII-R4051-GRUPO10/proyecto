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

#define INTERRUPT_M1    2,13
#define INTERRUPT_M2    2,11
#define INTERRUPT_A     2,12
#define ALARM           0,26


//pines del display:

#define RS
#define R/W
#define ENA
#define DB0
#define DB1
#define DB2
#define DB3
#define DB4
#define DB5
#define DB6
#define DB7


// N:pasos del motor, PASO_MINIMO: movimiento minimo en grados que puede realizar el motor

#define N           
#define PASO_MINIMO         360/N
#define HORARIO             0
#define ANTI_HORARIO        1




void pararM1();
void pararM2();
void moverM2(int,int);
void posicionarM2(int,int);
void activar_Alarma();
void moverM1_360();
int  muestrearColor();
void escribirSD(int*);
void Habilitar_Interrupcion();
void Deshabilitar_Interrupcion();
void initHardware();
void apagarLeds();
void prenderLed();


