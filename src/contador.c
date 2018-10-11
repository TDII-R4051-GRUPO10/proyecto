#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif
#include <cr_section_macros.h>

int flag;


void ResetearContador(void)
{
	LPC_TIMER3->TCR = 2;
	LPC_TIMER3->TCR = 1;
}

unsigned int LeerContador(void)
{
	return LPC_TIMER3->TC;
}

void InicializarContador(void)
{
	LPC_SYSCTL->PCONP|=1<<23;
	LPC_SYSCTL->PCLKSEL[1]&= ~(1<<15);
	LPC_SYSCTL->PCLKSEL[1]&=  (1<<14);
	LPC_IOCON->PINSEL[1]|= (0x03<<14);
	LPC_TIMER3->CTCR = 0x05;
	ResetearContador();
}


int main(void) {
	int dummy;
#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    flag = 0;
    SysTick_Config(SystemCoreClock/1000);
    InicializarContador();
    while(1)
    {
    	if(flag)
    	{
    		flag = 0;
    		dummy = LeerContador();
    		ResetearContador();
    	}
    }
    return 0 ;
}


void SysTick_Handler()
{
	static int segundo = 1000;
	if(!--segundo)
	{
		segundo = 1000;
		flag = 1;
	}
}
