


#define error_max 10

enum {inicial, medicion,amarillo,rojo,azul,marron,verde};
int valor;

void maq_estados(void)
{
	static int error = 0;
	static int estado = inicial;

	switch(estado)
	{
		case inicial:

			xSemaphoreGive(motor1);	//girar la rueda tantos grados hasta la posicion de medir con el sensor
			//esperar que se posicione en el sensor
				estado= medicion;
		break;

		case medicion:

			xSemaphoreGive(sensor_color);//obtener valor de la medicion (libera tarea medicion);
			//esperar a que me libere el semaforo de que ya obtuvo el valor
				if(valor = amarillo)
				{
					error=0;
					estado= amarillo;
				}

				if(valor = rojo)
				{
					error=0;
					estado= rojo;
				}

				if(valor = azul)
				{
					error=0;
					estado= azul;
				}

				if(valor = marron)
				{
					error=0;
					estado= marron;
				}

				if(valor = verde)
				{
					error=0;
					estado= verde;
				}
				else
				{
					//girar motor 1 a posicion inicial
					error++;

					if(error >= error_max)
					{

						//titilar_led habilitar tarea de parpadeo
						//enviar a display "recargar tolba"
					}

				}
		break;

		case amarillo:
				//girar motor dos hasta la posicion del recipiente correspondiente

				contador_amarillo++;

				//enviar contador_amarillo++ a pc y display

				// girar motor uno hasta posicion inicial

				estado= inicial;

		break;



		case rojo:
				//girar motor dos hasta la posicion del recipiente correspondiente

				contador_rojo++;

				//enviar contador_rojo++ a pc y display

				// girar motor uno hasta posicion inicial

				estado= inicial;
		break;


		case azul:
				//girar motor dos hasta la posicion del recipiente correspondiente

				contador_azul++;

				//enviar contador_azul++ a pc y display

				// girar motor uno hasta posicion inicial

				estado= inicial;
		break;

		case marron:
				//girar motor dos hasta la posicion del recipiente correspondiente

				contador_marron++;

				//enviar contador_marron++ a pc y display

				// girar motor uno hasta posicion inicial

				estado= inicial;

		break;

		case verde:
				//girar motor dos hasta la posicion del recipiente correspondiente

				contador_verde++;

				//enviar contador_rojo++ a pc y display

				// girar motor uno hasta posicion inicial

				estado= inicial;
				break;







	}
}
