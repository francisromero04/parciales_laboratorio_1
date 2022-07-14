#include <stdio.h>
#include <stdlib.h>

#include "relaciones.h"
#define	TAM_ARRAY 200

int main(void)
{
	setbuf(stdout, NULL);
	int opcion;

	eUsuario usuarios[TAM_ARRAY];
	eProducto productos[TAM_ARRAY];
	eTracking trackings[TAM_ARRAY];

	eUs_Inicializar(usuarios, TAM_ARRAY);
	eUs_harcodeo(usuarios);

	eProd_Inicializar(productos, TAM_ARRAY);
	eProd_Harcodeo(productos);

	eTrack_Inicializar(trackings, TAM_ARRAY);
	eTrack_Harcodeo(trackings);

	do{
		puts("\n\t\t\t\t\t*********************************");
		puts("\t\t\t\t\t****** 1er EXAM LAB I - 1H ******");
		puts("\t\t\t\t\t*********************************\n\n");
		puts("1) INGRESAR");
		puts("2) REGISTRARSE");
		puts("0) SALIR");

		utn_getNumero("\nINGRESE OPCION: ", "\nERROR. ", 0, 2, 2, &opcion);

		switch(opcion)
		{
			case 1:
				relacionUTP_menuTipos(usuarios, TAM_ARRAY, productos, TAM_ARRAY, trackings, TAM_ARRAY);
			break;

			case 2:
				eUs_Alta(usuarios, TAM_ARRAY);
			break;
		}

	}while(opcion != 0);

	return 0;
}
