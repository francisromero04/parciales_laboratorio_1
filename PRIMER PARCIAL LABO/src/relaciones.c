#include "relaciones.h"

int relacionUTP_Compra(eUsuario usuarios[], int TAM_U, eProducto productos[], int TAM_P, eTracking trackings[], int TAM_T, int sesionIniciada)
{
	int rtn = 0;
	int indexProd;
	int trackingIndex;

	if(trackings != NULL && productos != NULL && usuarios != NULL && TAM_P > 0 && TAM_T > 0 && TAM_U > 0)
	{
		indexProd = eProd_Comprar(productos, TAM_P);
		trackingIndex = eTrack_Alta(trackings, TAM_T, usuarios[sesionIniciada].codigoPostal, productos[indexProd].idProducto);
		productos[indexProd].idProducto = trackings[trackingIndex].idProducto;
		trackings[trackingIndex].FK_idUsuario = usuarios[sesionIniciada].idUsuario;
		puts("\nCOMPRA REALIZADA, MUCHAS GRACIAS POR ELEGIRNOS!");
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

void relacionUTP_imprimirCompra(eTracking tracking, eProducto producto)
{
	char estadoTracking[TAM_CHAR];

	//IMPRIME TODA LA INFO DE LA COMPRA DEL PRODUCTO Y SU TRACKING
	printf("|%-4d|%-16s|", tracking.idTracking, producto.nombreProducto);

	switch(tracking.isEmpty)
	{
		case EN_VIAJE:
			strncpy(estadoTracking, "EN VIAJE", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;

		case ENTREGADO:
			strncpy(estadoTracking, "ENTREGADO", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;

		case BAJA:
			strncpy(estadoTracking, "CANCELADO", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;
	}
}

int relacionUTP_imprimirCompras(eTracking trackings[], int TAM_T, eProducto productos[], int TAM_P, int idUsuario)
{
	int i;
	int j;
	int rtn = -1;

	puts("\n\tLISTADO DE COMPRAS");
	puts("+--------------------------------------+");
	puts("| ID |    PRODUCTO    |     ESTADO     |");
	puts("+--------------------------------------+");

	if (trackings != NULL && TAM_T > 0 && productos != NULL && TAM_P > 0)
	{
		for (i = 0; i < TAM_T; i++) //RECORRE ARRAY T
		{
			for(j = 0; j < TAM_P; j++)
			{
				if (trackings[i].FK_idUsuario == idUsuario)
				{
					if(productos[j].idProducto == trackings[i].idProducto)
					{
						if(relacionUTP_comprasRealizadas(trackings, TAM_T, idUsuario) == 1)
						{
							rtn = 1;
							relacionUTP_imprimirCompra(trackings[i], productos[j]);
						}
					}
				}
			}
		}
	}
	else
	{
		rtn = 0;
	}

	puts("+--------------------------------------+");

	return rtn;
}

int relacionUTP_comprasRealizadas(eTracking trackings[], int TAM_T, int idUsuario)
{

	int i;
	int rtn = -1;

	if(trackings != NULL && TAM_T > 0)
	{
		for (i = 0; i < TAM_T; i++)
		{
			if(trackings[i].FK_idUsuario == idUsuario)
			{
				if(trackings[i].isEmpty == ENTREGADO || trackings[i].isEmpty == BAJA || trackings[i].isEmpty == EN_VIAJE)
				{
					rtn = 1;
				}
			}
		}
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

int relacionUTP_estadoCompras(eTracking trackings[], int TAM_T, eProducto productos[], int TAM_P, eUsuario usuarios[], int TAM_U, int idUsuario)
{
	int rtn = -1;
	int opcion;
	int index;

	if(trackings != NULL && usuarios != NULL && TAM_T > 0 && TAM_U > 0)
	{
		index = eTrack_BuscarPorIdUsuario(trackings, TAM_T, idUsuario);

		if(index != -1)
		{
			eTrack_actualizarEstado(trackings, TAM_T); //ACTUALIZA EL ESTADO DE LA COMPRA
			relacionUTP_imprimirCompras(trackings, TAM_T, productos, TAM_P, idUsuario);

			do
			{
				puts("\nOPCIONES ESTADO DE COMPRAS");
				puts("\t1) CANCELAR COMPRA");
				puts("\t0) SALIR");

				utn_getNumero("\nELIJA UNA OPCION A REALIZAR: ", "ERROR .", 0, 1, 2, &opcion);

				if(opcion == 1)
				{
					eTrack_Baja(trackings, TAM_T); //SE DA DE BAJA Y CAMBIA ESTADO A CANCELADO
				}

			}while(opcion != 0);
		}

	}
	else
	{
		rtn = 0; //ERROR ARRAYS NULOS O MAL TAMAÑO
	}
	return rtn;
}

int relacionUTP_venta(eUsuario usuarios[], eProducto productos[], int sesionIniciada)
{
	int rtn = -1;
	int indexP;
	int opcion;

	if(productos != NULL && usuarios != NULL)
	{
		if(sesionIniciada == 1)
		{
			puts("\nVENTA DE PRODUCTO");
			puts("\t1) VENDER UN PRODUCTO");
			puts("\t0) VOLVER AL MENU ANTERIOR");
			utn_getNumero("\nINGRESE OPCION: ", "\nERROR: ", 0, 1, 2, &opcion);

			switch(opcion)
			{
				case 1:
					indexP = eProd_Alta(productos, TAM_CHAR);
					if(indexP != -1)
					{
						rtn = 1;
						productos[indexP].FK_idUsuario = usuarios[sesionIniciada].idUsuario;
					}
				break;
			}
		}
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

int relacionUTP_ventasRealizadas(eTracking trackings[], int TAM_T, int idUsuario)
{

	int i;
	int rtn = -1;

	if(trackings != NULL && TAM_T > 0)
	{
		for (i = 0; i < TAM_T; i++)
		{
			if(trackings[i].FK_idUsuario == idUsuario)
			{
				if(trackings[i].isEmpty == ENTREGADO || trackings[i].isEmpty == BAJA)
				{
					rtn = 1;
				}
			}
		}
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

int relacionUTP_imprimirVentas(eTracking trackings[], int TAM_T, eProducto productos[], int TAM_P, int idUsuario)
{

	int i;
	int j;
	int rtn = -1;

	puts("\n\tLISTADO DE VENTAS");
	puts("+--------------------------------------+");
	puts("| ID |    PRODUCTO    |     ESTADO     |");
	puts("+--------------------------------------+");

	if (trackings != NULL && TAM_T > 0)
	{
		for(i = 0; i < TAM_T; i++)
		{
			for(j = 0; j < TAM_P; j++)
			{
				if(trackings[i].FK_idUsuario == idUsuario)
				{
					if(productos[j].idProducto == trackings[i].idProducto)
					{
						if(relacionUTP_ventasRealizadas(trackings, TAM_T, idUsuario) == 1)
						{
							rtn = 1;
							relacionUTP_imprimirCompra(trackings[i], productos[j]);
						}
					}
				}

			}
		}
	}
	else
	{
		rtn = 0;
	}

	puts("+--------------------------------------+");

	return rtn;
}

int relacionUTP_estadoVentas(eTracking trackings[], int TAM_T, eProducto productos[], int TAM_P, eUsuario usuarios[], int TAM_U, int idUsuario)
{
	int rtn = -1;
	int opcion;

	if(trackings != NULL && TAM_T > 0)
	{
		do
		{
			puts("\nESTADO DE VENTA");
			puts("\t1) LISTADO DE VENTAS");
			puts("\t0) VOLVER AL MENU ANTERIOR");
			utn_getNumero("\nINGRESE OPCION: ", "\nERROR: ", 0, 1, 2, &opcion);

			if(opcion == 1)
			{
				rtn = 1;
				eTrack_actualizarEstado(trackings, TAM_T);
				relacionUTP_imprimirVentas(trackings, TAM_T, productos, TAM_P, idUsuario);
			}
		}while(opcion != 0);
	}
	else
	{
		rtn = 0;
	}
	return rtn;
}

int relacionUTP_menuUsuario(eUsuario usuarios[], int TAM_U, eProducto productos[], int TAM_P, eTracking trackings[], int TAM_T, int sesionIniciada)
{
	int opcion;
	int rtn = -1;

	if(usuarios != NULL && productos != NULL && trackings != NULL && TAM_U > 0 && TAM_P > 0 && TAM_T > 0)
	{
		do
		{
			puts("\n\n\t\t\t\t\t*********************************");
			puts("\t\t\t\t\t****** 1er EXAM LAB I - 1H ******");
			puts("\t\t\t\t\t*********** USUARIO *************");
			puts("\t\t\t\t\t*********************************\n");
			puts("1) COMPRAR");
			puts("2) VENDER");
			puts("3) ESTADO DE COMPRAS");
			puts("4) ESTADO DE VENTAS");
			puts("0) SALIR\n");

			utn_getNumero("INGRESE OPCION: ", "ERROR. \n", 0, 4, 2, &opcion);

			switch(opcion)
			{
				case 1:
					relacionUTP_Compra(usuarios, TAM_U, productos, TAM_P, trackings, TAM_T, sesionIniciada);
				break;

				case 2:
					relacionUTP_venta(usuarios, productos, sesionIniciada);
				break;

				case 3:
					relacionUTP_estadoCompras(trackings, TAM_T, productos, TAM_P, usuarios, TAM_U, usuarios[sesionIniciada].idUsuario);
				break;

				case 4:
					relacionUTP_estadoVentas(trackings, TAM_T, productos, TAM_P, usuarios, TAM_U, usuarios[sesionIniciada].idUsuario);
				break;
			}
		}while(opcion != 0);
	}
	else
	{
		rtn = 0; //ERROR ARRAYS NULOS
	}

	return rtn;
}

void relacionUTP_imprimirTracking(eTracking tracking)
{
	char estadoTracking[TAM_CHAR];

	printf("|%-16d|%-16d|%-16d|", tracking.idTracking, tracking.FK_idUsuario, tracking.FK_idUsuario);

	switch(tracking.isEmpty)
	{
		case EN_VIAJE:
			strncpy(estadoTracking, "EN VIAJE", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;

		case ENTREGADO:
			strncpy(estadoTracking, "ENTREGADO", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;

		case BAJA:
			strncpy(estadoTracking, "CANCELADO", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;
	}
}

int relacionUTP_imprimirTrackingGlobal(eTracking trackings[], int TAM_T)
{
	int i;
	int rtn = 0;

	puts("\n\t\t\tTRACKING GLOBAL");
	puts("+-------------------------------------------------------------------+");
	puts("|   ID TRACKING  |   ID VENDEDOR  |  ID COMPRADOR  |     ESTADO     |");
	puts("+-------------------------------------------------------------------+");

	if (trackings != NULL && TAM_T > 0)
	{
		for (i = 0; i < TAM_T; i++)
		{
			if (trackings[i].isEmpty != LIBRE)
			{
				relacionUTP_imprimirTracking(trackings[i]);
				break;
			}
		}
	}
	else
	{
		rtn = 0; //ERROR ARRAYS NULOS O MAL TAM
	}

	puts("+-------------------------------------------------------------------+");

	return rtn;
}

int relacionUTP_menuAdmin(eUsuario usuarios[], int TAM_U, eProducto productos[], int TAM_P, eTracking trackings[], int TAM_T)
{
	int rtn = -1;
	int opcion;

	if(trackings != NULL && productos != NULL && usuarios != NULL && TAM_T > 0 && TAM_P > 0 && TAM_U > 0)
	{
		do{
			puts("\n\t\t\t\t\t*********************************");
			puts("\t\t\t\t\t****** 1er EXAM LAB I - 1H ******");
			puts("\t\t\t\t\t************* ADMIN *************");
			puts("\t\t\t\t\t*********************************\n");
			puts("\tGESTION E INFORMES");
			puts("1) LISTAR ESTADO DE TODOS LOS USUARIOS");
			puts("2) LISTAR TODOS LOS PRODUCTOS POR CATEGORIA");
			puts("3) BAJA DE UN PRODUCTO");
			puts("4) BAJA DE UN USUARIO");
			puts("5) VER TRACKING GLOBAL");
			puts("0) SALIR");

			utn_getNumero("\nINGRESE OPCION: ", "\nERROR. ", 0, 5, 2, &opcion);

			switch(opcion)
			{
				case 1:
					eUs_MostrarTodos(usuarios, TAM_U);
				break;

				case 2:
					eProd_Ordenar(productos, TAM_P);
					eProd_MostrarTodos(productos, TAM_P);
				break;

				case 3:
					eProd_Baja(productos, TAM_P);
				break;

				case 4:
					eUs_Baja(usuarios, TAM_U);
				break;

				case 5:
					relacionUTP_imprimirTrackingGlobal(trackings, TAM_T);
				break;
			}

		} while(opcion != 0);
	}
	else
	{
		rtn = 0; //ERROR ARRAYS NULOS O MAL TAM
	}
	return rtn;
}

int relacionUTP_menuTipos(eUsuario usuarios[], int TAM_U, eProducto productos[], int TAM_P, eTracking trackings[], int TAM_T)
{
	int rtn = -1;
	int sesionIniciada;

	if(trackings != NULL && productos != NULL && usuarios != NULL && TAM_P > 0 && TAM_T > 0 && TAM_U > 0)
	{
		sesionIniciada = eUs_iniciarSesion(usuarios, TAM_U);

		if(usuarios[sesionIniciada].tipo == USUARIO)
		{
			relacionUTP_menuUsuario(usuarios, TAM_U, productos, TAM_P, trackings, TAM_T, sesionIniciada);
		}
		else
		{
			if(usuarios[sesionIniciada].tipo == ADMIN)
			{
				relacionUTP_menuAdmin(usuarios, TAM_U, productos, TAM_P, trackings, TAM_T);
			}
		}
	}
	else
	{
		rtn = 0; //ERROR ARRAYS NULOS O MAL TAM
	}

	return rtn;
}














