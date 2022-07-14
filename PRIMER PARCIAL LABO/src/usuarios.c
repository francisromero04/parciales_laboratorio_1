#include "usuarios.h"

static int eUs_obtenerID(void);
static int eUs_obtenerID(void)
{
	static int id_incremental = 100;
	return id_incremental++;
}

void eUs_Inicializar(eUsuario usuarios[], int TAM_U)
{
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if(usuarios != NULL && TAM_U > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM_U; i++)
		{
			//SET ESTADO DE "LIBRE"
			usuarios[i].isEmpty = LIBRE;
		}
	}

}

int eUs_ObtenerIndexLibre(eUsuario usuarios[], int TAM_U)
{

	int i;
	int rtn = -1;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (usuarios != NULL && TAM_U > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM_U; i++)
		{
			//PREGUNTO POR EL ESTADO "LIBRE"
			if (usuarios[i].isEmpty == LIBRE)
			{
				//OBTENGO EL PRIMER INDEX DEL VECTOR "LIBRE" Y SALGO
				rtn = i;
				break;
			}
		}
	}
	else
	{
		rtn = 0; //ERROR ARRAY NULO O MAL TAM
	}

	return rtn;
}

eUsuario eUs_CargarDatos(void)
{
	eUsuario aux;

	aux.tipo = USUARIO;

	getEmail("\nINGRESE SU EMAIL: ", "\nERROR, REINGRESE EMAIL: ", 2, aux.email);

	getPassword("\nINGRESE CONTRASEÑA (mínimo 4 letras y alfanumérico): ",
			"\nERROR. ", 4, 10, 2, aux.password);

	utn_getString("\nINGRESE DIRECCION: ", "\nERROR. ", 2, TAM_CHAR, aux.direccion);

	utn_getNumero("\nINGRESE SU CODIGO POSTAL: ", "\nERROR. ", 1, 9999, 2, &aux.codigoPostal);

	return aux;
}

int eUs_iniciarSesion(eUsuario usuarios[], int TAM_U)
{
	int rtn = -1;
	int indexCorreo = 0;
	char email[MAX_LEN_EMAIL];
	char password[MAX_LEN_PASSWORD];

	if(usuarios != NULL && TAM_U > 0)
	{
		getEmail("\nINGRESE SU EMAIL: ", "\nERROR. ", 2, email);
		indexCorreo = eUs_BuscarPorEmail(usuarios, TAM_U, email);

		while(usuarios[indexCorreo].isEmpty == OCUPADO)
		{
			getPassword("\nINGRESE SU CONTRASEÑA: ", "\nCONTRASEÑA/EMAIL INCORRECTOS. ", 4, 10, 2, password);

			if(strcmp(usuarios[indexCorreo].password, password) == 0)
			{
				rtn = 1;
				puts("\nSE HA INICIADO SESION CORRECTAMENTE. ");
				break;
			}
		}

		rtn = indexCorreo;
	}

	return rtn;
}

void eUs_MostrarUno(eUsuario usuario)
{
	char estadoUsuario[25];

	printf("|%4d|%-25s|", usuario.idUsuario, usuario.email);

	switch(usuario.isEmpty)
	{
		case OCUPADO:
			strncpy(estadoUsuario, "ACTIVO", sizeof(estadoUsuario));
			printf("%-16s|\n", estadoUsuario);
		break;

		case BAJA:
			strncpy(estadoUsuario, "ELIMINADO", sizeof(estadoUsuario));
			printf("%-16s|\n", estadoUsuario);
		break;
	}
}

int eUs_MostrarTodos(eUsuario usuarios[], int TAM_U)
{
	int i;
	int rtn = 0;
	int cantidad = 0;
	int vueltas = 0 ;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (usuarios != NULL && TAM_U > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM_U; i++)
		{
			//PREGUNTO POR SU ESTADO "OCUPADO"
			if (usuarios[i].isEmpty == OCUPADO)
			{
				vueltas++;
				if(vueltas == 1)
				{
					//CABECERA
					puts("\n+-----------------------------------------------+");
					puts("| ID |          CORREO         |     ESTADO     |");
					puts("+-----------------------------------------------+");
				}

				//IMPRIMO UN SOLO usuario
				eUs_MostrarUno(usuarios[i]);
				//CONTADOR DE usuarios
				cantidad++;
				puts("+-----------------------------------------------+");
			}
		}
	}

	//SI CANTIDAD == 0 - NO HUBO usuarios PARA MOSTRAR (ARRAY SIN ALTAS)
	if (cantidad > 0)
	{
		rtn = 1;
	}

	return rtn;
}

int eUs_BuscarPorID(eUsuario usuarios[], int TAM_U, int ID)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (usuarios != NULL && TAM_U > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM_U; i++)
		{
			//BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (usuarios[i].idUsuario == ID && usuarios[i].isEmpty == OCUPADO)
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

int eUs_BuscarPorEmail(eUsuario usuarios[], int TAM_U, char correoIngresado[])
{
	int i;
	int rtn = -1;

	if(usuarios != NULL && TAM_U > 0)
	{
		for (i = 0; i < TAM_U; i++)
		{
			if((strcmp(usuarios[i].email, correoIngresado)) == 0 && usuarios[i].isEmpty != LIBRE)
			{
				rtn = i;
				break;
			}
			else
			{
				rtn = -2;
			}
		}

	}
	else
	{
		rtn = 0;
	}
	return rtn;
}

void eUs_harcodeo(eUsuario usuarios[])
{
	usuarios[0].idUsuario = 107;
	usuarios[0].isEmpty = OCUPADO;
	usuarios[0].codigoPostal = 1822;
	usuarios[0].tipo = ADMIN;
	strcpy(usuarios[0].email, "admin@gmail.com");
	strcpy(usuarios[0].password, "admin1");
	strcpy(usuarios[0].direccion, "Eduardo Madero 1768");

	usuarios[1].idUsuario = 101;
	usuarios[1].isEmpty = OCUPADO;
	usuarios[1].codigoPostal = 2240;
	usuarios[1].tipo = USUARIO;
	strcpy(usuarios[1].email, "usuario@gmail.com");
	strcpy(usuarios[1].password, "usuario1");
	strcpy(usuarios[1].direccion, "Jose Moreno 350");
}

int eUs_Alta(eUsuario usuarios[], int TAM_U)
{
	int rtn = -1;
	eUsuario auxUsuario;

	//BUSCO ESPACIO EN ARRAY
	int index = eUs_ObtenerIndexLibre(usuarios, TAM_U);

	//SI INDEX == -1 ARRAY LLENO
	//SI INDEX != -1 TENGO EN INDEX POSICION DE ARRAY LIBRE

	if (index != -1)
	{
		//PIDO DATOS - CARGO usuarios AUXILIAR
		auxUsuario = eUs_CargarDatos();

		//SETEO ID UNICO - VARIABLE ESTATICA AUTOINCREMENTAL
		auxUsuario.idUsuario = eUs_obtenerID();

		//CAMBIO SU ESTADO A "OCUPADO"
		auxUsuario.isEmpty = OCUPADO;

		//SETEO EL ARRAY CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
		usuarios[index] = auxUsuario;

		//RETORNO 1 PARA SABER QUE FUE DADO DE ALTA SATISFACTORIAMENTE
		rtn = 1;
	}

	return rtn;
}

int eUs_Baja(eUsuario usuarios[], int TAM_U)
{
	int rtn = 0;
	int idusuario;
	int index;
	int flag = 0;

	//LISTO TODOS LOS usuarios
	if(eUs_MostrarTodos(usuarios, TAM_U))
	{
		//BANDERA EN 1 SI HAY usuarios DADOS DE ALTA PARA LISTAR
		flag = 1;
	}

	//SI HAY usuarios PARA DAR DE BAJA
	if(flag)
	{
		//PIDO ID A DAR DE BAJA
		utn_getNumero("\nINGRESE ID DEL USUARIO A DAR DE BAJA: ", "\nERROR. ", 100, 999, 3, &idusuario);

		//BUSCO INDEX POR ID EN ARRAY
		while (eUs_BuscarPorID(usuarios, TAM_U, idusuario) == -1)
		{
			puts("\nNO EXISTE ID.");

			//PIDO OTRA VEZ ID A DAR DE BAJA
			utn_getNumero("\nINGRESE ID DEL USUARIO A DAR DE BAJA: ", "\nERROR. ", 100, 999, 3, &idusuario);
		}

		//OBTENGO INDEX DEL ARRAY DE usuarios A DAR DE BAJA
		index = eUs_BuscarPorID(usuarios, TAM_U, idusuario);

		//BAJA ACEPTADA - CAMBIO ESTADO A "BAJA"
		usuarios[index].isEmpty = BAJA;

		puts("\nSE HA DADO DE BAJA EL USUARIO. \n");

		//RETORNO 1 SI SE DIO DE BAJA CORRECTAMENTE
		rtn = 1;
	}

	return rtn;
}
