#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#define S0 	0
#define S1 	1
#define S2 	2
#define S3 	3
#define OUT 4

typedef struct {
	uint8_t port;
	uint8_t pin;
} io_port_t;

static const io_port_t gpioSensor[] = {{3,0},{3,3},{3,4},{5,15},{5,16}};

void init_color_sensor();
void disable_sensor(void);
void activa_sensor();
int sensa_rojo();
int sensa_verde();
int sensa_azul();
int lee_sensor();
