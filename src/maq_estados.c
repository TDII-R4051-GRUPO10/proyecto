


#define error_max 10

enum {inicial, medicion,amarillo,rojo,azul,marron,verde};
int valor;
//todes putes menes conmigues

void maq_estados(void)
{
	static int error = 0;
	static int estado = inicial;

	switch(estado)
	{
		case inicial:
				//girar la rueda tantos grados hasta la posicion de medir con el sensor
				estado= medicion;
		break;

		case medicion:

		//obtener valor de la medicion valor = medicion_sensor();

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
						//titilar_led
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
