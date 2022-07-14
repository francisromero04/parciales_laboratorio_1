#include "trackings.h"

static int eTrack_obtenerID(void);
static int eTrack_obtenerID(void)
{
	static int tracking_idIncremental = 5000;
	static int rtn;

	rtn = tracking_idIncremental++;

	return rtn;
}

void eTrack_Inicializar(eTracking array[], int TAM)
{
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//SET ESTADO DE "LIBRE"
			array[i].isEmpty = LIBRE;
		}
	}
}

int eTrack_ObtenerIndexLibre(eTracking array[], int TAM)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//PREGUNTO POR EL ESTADO "LIBRE"
			if (array[i].isEmpty == LIBRE)
			{
				//OBTENGO EL PRIMER INDEX DEL VECTOR "LIBRE" Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

eTracking eTrack_CalcularHora(int idProducto, int codigoPostal)
{
	eTracking aux;
	char* horaLlegada;
	long int segundosAgregados;

	if(idProducto > 0 && codigoPostal > 0)
	{
		aux.idProducto = idProducto;

		if(codigoPostal < 9999 && codigoPostal > 8001)
		{
			aux.distanciaKm = 150;
		}
		else
		{
			if(codigoPostal < 8000 && codigoPostal > 5001)
			{
				aux.distanciaKm = 80;
			}
			else
			{
				if(codigoPostal < 5000 && codigoPostal > 3001)
				{
					aux.distanciaKm = 50;
				}
				else
				{
					if(codigoPostal < 3000 && codigoPostal > 1001)
					{
						aux.distanciaKm = 30;
					}
					else
					{
						aux.distanciaKm = 20;
					}
				}
			}
		}
	}

	segundosAgregados = aux.distanciaKm / 10 * 20;
	aux.horaLlegada = time_Add(segundosAgregados);
	horaLlegada = ctime(&aux.horaLlegada);
	printf("\nSU HORA DE LLEGADA ES: %s ", horaLlegada);

	return aux;
}

int eTrack_actualizarEstado(eTracking trackings[], int TAM)
{
	int i;
	int rtn = -1;
	long int horaActual;

	if(trackings != NULL && TAM > 0)
	{
		horaActual = time_Current();

		for(i = 0; i < TAM; i++)
		{
			if(trackings[i].horaLlegada > horaActual)
			{
				trackings[i].isEmpty = EN_VIAJE;
			}
			else
			{
				if(trackings[i].horaLlegada < horaActual)
				{
					trackings[i].isEmpty = ENTREGADO;
				}
			}
			rtn = 1;
		}
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

int eTrack_BuscarPorID(eTracking array[], int TAM, int ID)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (array[i].idTracking == ID && array[i].isEmpty == EN_VIAJE)
			{
				//SI ENCONTRE EL ID
				//DEVUELVO EL INDEX DE DONDE ESTA EL ID BUSCADO Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

int eTrack_BuscarPorIdUsuario(eTracking array[], int TAM, int idUsuario)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (array[i].FK_idUsuario == idUsuario && array[i].isEmpty == EN_VIAJE)
			{
				//SI ENCONTRE EL ID
				//DEVUELVO EL INDEX DE DONDE ESTA EL ID BUSCADO Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

void eTrack_Harcodeo(eTracking trackings[])
{
	trackings[0].FK_idUsuario = 100;
	trackings[0].horaLlegada = time_Current();
	trackings[0].distanciaKm = 30;
	trackings[0].isEmpty = EN_VIAJE;
	trackings[0].idProducto = 1000;
	trackings[0].cantidad = 1;
	trackings[0].idTracking = 5000;

	trackings[1].FK_idUsuario = 101;
	trackings[1].horaLlegada = time_Add(180);
	trackings[1].distanciaKm = 70;
	trackings[1].isEmpty = EN_VIAJE;
	trackings[1].idProducto = 1001;
	trackings[1].cantidad = 5;
	trackings[1].idTracking = 5001;

	trackings[2].FK_idUsuario = 102;
	trackings[2].horaLlegada = time_Add(55);
	trackings[2].distanciaKm = 500;
	trackings[2].isEmpty = EN_VIAJE;
	trackings[2].idProducto = 1002;
	trackings[2].cantidad = 10;
	trackings[2].idTracking = 5002;
}

int eTrack_Alta(eTracking trackings[], int TAM_T, int codigoPostal, int idProducto)
{
	int index;
	int rtn = -1;
	eTracking aux;

	//BUSCO ESPACIO EN ARRAY
	index = eTrack_ObtenerIndexLibre(trackings, TAM_T);

	//SI INDEX == -1 ARRAY LLENO
	//SI INDEX != -1 TENGO EN INDEX POSICION DE ARRAY LIBRE

	if(trackings != NULL && TAM_T)
	{
		aux = eTrack_CalcularHora(codigoPostal, idProducto);

		//SETEO ID UNICO - VARIABLE ESTATICA AUTOINCREMENTAL
		aux.idTracking = eTrack_obtenerID();

		printf("\nSE HA GENERADO UN ALTA DE TRACKING Y ESTE ID PARA PODER SEGUIR EL ESTADO DEL ENVIO: %d \n", aux.idTracking);

		//CAMBIO SU ESTADO A "EN VIAJE"
		aux.isEmpty = EN_VIAJE;

		//SETEO EL ARRAY CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
		trackings[index] = aux;

		rtn = index;
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

int eTrack_Baja(eTracking array[], int TAM)
{
	int rtn = -1;
	int idTracking;
	int index;

	//SI HAY trackings PARA DAR DE BAJA
	if(array != NULL && TAM > 0)
	{
		utn_getNumero("\nINGRESE EL ID DEL TRACKING A DAR DE BAJA: ", "\nERROR. ", 5000, 9999, 2, &idTracking);
		index = eTrack_BuscarPorID(array, TAM, idTracking);

		while(array[index].isEmpty != EN_VIAJE)
		{
			utn_getNumero("\nREINGRESE ID DE LA COMPRA: ", "\nERROR. ", 5000, 9999, 2, &idTracking);
			index = eTrack_BuscarPorID(array, TAM, idTracking);
		}

		//BAJA ACEPTADA - CAMBIO ESTADO A "BAJA"
		array[index].isEmpty = BAJA;

		puts("\nSE HA DADO DE BAJA LA COMPRA. ");

		//RETORNO 1 SI SE DIO DE BAJA CORRECTAMENTE
		rtn = 1;
	}

	return rtn;
}
