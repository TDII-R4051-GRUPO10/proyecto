#define		ISER		( (volatile uint32_t *) 0xE000E100UL )
//!< 0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( (volatile uint32_t *) 0xE000E180UL )

//!< Registros ISER:
#define		ISER0		ISER[0]
#define		ISER1		ISER[1]

//!< Registros ICER:
#define		ICER0		ICER[0]
#define		ICER1		ICER[1]




#define		EXT		( (volatile uint32_t *) 0x400FC140UL )

#define		EXTINT		EXT[0]
#define		EXTMODE		EXT[2]
#define		EXTPOLAR	EXT[3]


#define GPIO_INPUT	0
#define GPIO_OUTPUT	1



void SetPINSEL(uint8_t port, uint8_t pin, uint8_t sel);
void SetPINMODE(uint8_t port, uint8_t pin, uint8_t mode);
void SetDIR(uint8_t port, uint8_t pin, uint8_t dir);
void SetPIN(uint8_t port, uint8_t pin, uint8_t value);
uint8_t GetPIN(uint8_t port, uint8_t pin);



