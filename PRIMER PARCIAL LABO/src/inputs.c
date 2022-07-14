#include "inputs.h"

//-----------------------------------------------PARA INGRESAR POR TECLADO----------------------------------------------

int myGets(char* cadena, int longitud)
{
	int retorno = -1;
	char bufferString[4096];

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)
		{
			if(bufferString[strlen(bufferString)-1] == '\n')
			{
				bufferString[strlen(bufferString)-1] = '\0';
			}
			if(strlen(bufferString) <= longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno = 0;
			}
		}
	}
	return retorno;
}

//-----------------------------------------------GET NUMERO INT---------------------------------------------------------

int utn_getNumero(char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos, int* pResultado)
{
	int retorno = -1;
	int rtnGetInt;
	int bufferInt;
	do
	{
		printf("%s",mensaje);
		rtnGetInt = getInt(&bufferInt);

		if(rtnGetInt == 0 && pResultado != NULL && mensaje != NULL && mensajeError != NULL
				&& reintentos >= 0 && bufferInt >= minimo && bufferInt <= maximo)
		{
			retorno = 0;
			*pResultado = bufferInt;
			break;
		}

		printf("%s",mensajeError);
		reintentos--;

	}while(reintentos>=0);

	return retorno;
}

int esNumerica(char* cadena, int limite)
{
	int retorno = -1;
	int i;

	if(cadena != NULL && limite > 0)
	{
		retorno = 1;
		for(i = 0; i<limite && cadena[i] != '\0'; i++)
		{
			if(i == 0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int getInt(int * pResultado)
{
	int retorno = -1;
	char buffer[4096];

	if(	pResultado != NULL &&
		myGets(buffer, sizeof(buffer)) == 0 &&
		esNumerica(buffer,sizeof(buffer)) )
		{
			*pResultado = atoi(buffer);
			retorno = 0;
		}
	return retorno;
}

//-----------------------------------------------GET NUMERO FLOAT-------------------------------------------------------

int utn_getNumFloat(char mensaje[], char mensajeError[], int minimo, int maximo, int reintentos, float *pNumeroIngresado)
{
	int retorno = -1;
	float auxiliarFloat;
	float rtnGetFloat;

	if(mensaje != NULL && minimo < maximo && mensajeError != NULL && pNumeroIngresado != NULL && reintentos > 0)
	{
		printf("%s",mensaje);
		rtnGetFloat = getFloat(&auxiliarFloat);
		do
		{
			if(rtnGetFloat == -1 || auxiliarFloat > maximo || auxiliarFloat < minimo)
			{
				printf("%s",mensajeError);
				fflush(stdin); //si ingresa letra no entra mas en el while
				getFloat(&auxiliarFloat);
				reintentos--;
			}
			else
			{
				reintentos = 0;
				*pNumeroIngresado = auxiliarFloat;
				retorno = 0;
			}
		}while(reintentos > 0);
	}
	return retorno;
}

int esNumericaFloat(char cadena[])
{
	int retorno = -1;
	int i = 0;
	int contadorPuntos = 0;

	if(cadena != NULL)
	{
		while(cadena[i] != '\0' || (cadena[i] > '9' && cadena[i] != '.') )
		{
			i++;
			if(cadena[i] == '.')
			{
				contadorPuntos++;
			}

			if(contadorPuntos > 1)
			{
				retorno = -2;
				puts("\nError, mas de un punto\n");
				break;
			}
		}
	}
	else
	{
		retorno = 0;
	}
	return retorno;
}

int getFloat(float* pNumeroTomado)
{
	int retorno = -1;
	char numeroAuxiliar[200];

	if( myGets(numeroAuxiliar, sizeof(numeroAuxiliar)) == 0
			&& esNumericaFloat(numeroAuxiliar) )
	{
		*pNumeroTomado = atof(numeroAuxiliar);
		retorno = 0;
	}

	return retorno;
}

//-----------------------------------------------GET STRING-------------------------------------------------------------

int utn_getString(char* mensaje, char* mensajeError, int reintentos,  int longitud, char* pResultado)
{
	char bufferString[4096];
	int retorno = -1;

	while(reintentos >= 0)
	{
		reintentos--;
		printf("%s",mensaje);

		if(getNombre(bufferString,sizeof(bufferString)) == 0 &&
				strnlen(bufferString,sizeof(bufferString)) < longitud)
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}

		printf("%s",mensajeError);
	}
	return retorno;
}

int getNombre(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	myGets(buffer,sizeof(buffer)) ==0 &&
    		esNombre(buffer, sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer)) < longitud )
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

int esNombre(char* cadena,int longitud)
{
	int i = 0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if( (cadena[i] < 'A' || cadena[i] > 'Z') &&
				(cadena[i] < 'a' || cadena[i] > 'z') &&
				(cadena[i] < '0' && cadena[i] > '9') &&
				(cadena[i] == 32) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

//-----------------------------------------------GET EMAIL--------------------------------------------------------------

int getEmail(char mensaje[], char mensajeError[], int reintentos, char correo[])
{
	int i;
	int flag = 0;
	int rtn = -1;
	char aux[TAM_CHAR];

	if(mensaje != NULL && mensajeError != NULL && correo != NULL && reintentos > 0)
	{
		printf(mensaje);
		fflush(stdin);
		myGets(aux, TAM_CHAR);

		do{
			for(i = 0; i < TAM_CHAR; i++)
			{
				if(aux[i] == 46 || aux[i] == 64)
				{
					flag = 1;
				}
			}

			if(flag != 1)
			{
				printf(mensajeError);
				fflush(stdin);
				myGets(aux, TAM_CHAR);
				reintentos--;
			}
			else
			{
				reintentos = 0;
				strcpy(correo, aux);
			}

		}while(reintentos > 0);
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

int getPassword(char mensaje[], char mensajeError[], int min, int max, int reintentos, char password[])
{
	int rtn = -1;
	char auxiliary[TAM_CHAR];
	int flag = 0;
	int i;

	if(mensaje != NULL && mensajeError != NULL && password != NULL)
	{
		fflush(stdin);
		printf(mensaje);
		myGets(auxiliary, TAM_CHAR);

		do{
			while(strlen(auxiliary) < min || strlen(auxiliary) > max)
			{
				printf(mensajeError);
				reintentos--;
				fflush(stdin);
				myGets(auxiliary, TAM_CHAR);
			}
			//RECORRO EL STRING
			for(i = 0; i < strlen(auxiliary); i++)
			{
				if(auxiliary[i] < '0' || (auxiliary[i] > '9' && auxiliary[i] < 'A')
						|| (auxiliary[i] > 'Z' && auxiliary[i] < 'a') || auxiliary[i] > 'z')
				{
					printf(mensajeError);
					reintentos--;
					fflush(stdin);
					myGets(auxiliary, TAM_CHAR);
					break;
				}
				else
				{
					if( (auxiliary[i] > '0' && auxiliary[i] < '9') || (auxiliary[i] > 'A' && auxiliary[i] < 'Z') ||
							(auxiliary[i] > 'a' && auxiliary[i] < 'z') )
					{
						flag = 1;
					}
				}
			}

			if(flag == 1)
			{
				reintentos = 0;
				strcpy(password, auxiliary);
				rtn = 1;

			}
			else
			{
				printf(mensajeError);
				reintentos--;
				fflush(stdin);
				myGets(auxiliary, TAM_CHAR);
			}
		}while(reintentos > 0);
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

//-----------------------------------------------HORA-------------------------------------------------------------------

long int time_Current(void)
{
	return time(NULL);
}

long int time_Add(double secondsAdd)
{
	return secondsAdd + time_Current();
}












