#include "string.h"
#include "stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "GPIO.h"

//pines del display:


#define RS		0,9
#define RorW	0,8
#define ENA		0,7
#define DB4		0,17
#define DB5		0,15
#define DB6		0,16
#define DB7		0,23


#define DISPLAY_ALARM		111

#define INIT_DELAY		10000
#define WRITE_DELAY		0

void refrescarDisplay(int );
void initDisplay();
void Send(int);
void EnaDelay(int);
