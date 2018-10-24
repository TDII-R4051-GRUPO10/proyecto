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

static const io_port_t gpioSensor[] = {{2,5},{2,6},{2,8},{2,7},{2,10}};

void init_color_sensor();
void disable_sensor(void);
void activa_sensor();
unsigned int sensa_rojo();
unsigned int sensa_verde();
unsigned int sensa_azul();
unsigned int lee_sensor();
