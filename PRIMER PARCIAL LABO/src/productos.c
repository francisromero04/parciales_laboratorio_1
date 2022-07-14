#include "productos.h"

static int eProd_obtenerID(void);
static int eProd_obtenerID(void)
{
	static int producto_idIncremental = 1000;
	static int rtn;

	rtn = producto_idIncremental++;

	return rtn;
}

void eProd_Inicializar(eProducto productos[], int TAM)
{
	int i;

	//SI EXISTE EL productos Y EL LIMITE ES VALIDO
	if (productos != NULL && TAM > 0)
	{
		//RECORRO EL productos
		for (i = 0; i < TAM; i++)
		{
			//SET ESTADO DE "LIBRE"
			productos[i].isEmpty = LIBRE;
		}
	}
}

int eProd_ObtenerIndexLibre(eProducto productos[], int TAM)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL productos Y EL LIMITE ES VALIDO
	if (productos != NULL && TAM > 0)
	{
		//RECORRO EL productos
		for (i = 0; i < TAM; i++)
		{
			//PREGUNTO POR EL ESTADO "LIBRE"
			if (productos[i].isEmpty == LIBRE)
			{
				//OBTENGO EL PRIMER INDEX DEL VECTOR "LIBRE" Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

int eProd_BuscarPorID(eProducto productos[], int TAM, int ID)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL productos Y EL LIMITE ES VALIDO
	if (productos != NULL && TAM > 0)
	{
		//RECORRO EL productos
		for (i = 0; i < TAM; i++)
		{
			//BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (productos[i].idProducto == ID && productos[i].isEmpty == OCUPADO)
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

void eProd_MostrarUno(eProducto producto)
{
	char categoria[TAM_CHAR];

	printf("|%-16s|%-16d|%-16.2f|%4d|", producto.nombreProducto, producto.stockDisponible, producto.precio, producto.idProducto);

	switch(producto.categoria)
	{
		case TECNOLOGIA:
			strncpy(categoria, "TECNOLOGIA", sizeof(categoria));
			printf("%-17s|\n", categoria);
		break;

		case ROPA:
			strncpy(categoria, "ROPA", sizeof(categoria));
			printf("%-17s|\n", categoria);
		break;

		case ELECTRODOMESTICOS:
			strncpy(categoria, "ELECTRODOMESTICOS", sizeof(categoria));
			printf("%-17s|\n", categoria);
		break;
	}
}

int eProd_MostrarTodos(eProducto productos[], int TAM)
{
	int i;
	int rtn = 0;
	int cantidad = 0;
	int vueltas = 0 ;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (productos != NULL && TAM > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//PREGUNTO POR SU ESTADO "OCUPADO"
			if (productos[i].isEmpty == OCUPADO)
			{
				vueltas++;
				if(vueltas == 1)
				{
					puts("\n\t\t\t LISTA DE PRODUCTOS");
					puts("+-------------------------------------------------------------------------+");
					puts("|     NOMBRE     |      STOCK     |     PRECIO     | ID |     CATEGORIA   |");
					puts("+-------------------------------------------------------------------------+");
				}

				//IMPRIMO UN SOLO productos
				eProd_MostrarUno(productos[i]);
				//CONTADOR DE productos
				cantidad++;
				puts("+-------------------------------------------------------------------------+");
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

int eProd_Ordenar(eProducto productos[], int TAM)
{
	int i;
	int j;
	int rtn = -1;
	eProducto aux;

	//SI EXISTE EL productos Y EL LIMITE ES VALIDO
	if (productos != NULL && TAM > 0)
	{
		for (i = 0; i < TAM - 1; i++)
		{
			for (j = i + 1; j < TAM; j++)
			{
				if (productos[i].isEmpty == OCUPADO && productos[j].isEmpty == OCUPADO)
				{
					if (productos[i].categoria > productos[j].categoria) //ORDENO POR CATEGORIA
					{
						//CAMBIO POSICIONES
						aux = productos[i];
						productos[i] = productos[j];
						productos[j] = aux;
					}
					else
					{
						if(productos[i].categoria == productos[j].categoria) //SI LAS CATEGORIAS SON IGUALES ORDENO POR EL NOMBRE
						{
							if(( strcmp(productos[i].nombreProducto, productos[j].nombreProducto) ) > 0) //COMPARA CADENAS PARA SABER CUAL ES MAYOR
							{
								//CAMBIO POSICIONES
								aux = productos[i];
								productos[i] = productos[j];
								productos[j] = aux;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		rtn = 0; //ERROR productosS NULOS O MAL TAM
	}
	return rtn;
}

int eProd_Comprar(eProducto productos[], int TAM)
{
	int rtn = -1;
	float precioTotal;
	int idProducto;
	int cantidadRequerida;
	int indexProd;
	int opcion;

	if(productos != NULL && TAM > 0)
	{
		do
		{
			puts("\nCOMPRA DE PRODUCTO");
			puts("\t1) COMPRAR PRODUCTO ");
			puts("\t0) REGRESAR");
			utn_getNumero("\nINGRESE OPCION: ", "\nERROR. ", 0, 1, 2, &opcion);

			if(opcion == 1)
			{
				eProd_MostrarTodos(productos, TAM);
				utn_getNumero("\nINGRESE ID DEL PRODUCTO A COMPRAR: ", "\nERROR. ", 1000, 9999, 2, &idProducto);
				utn_getNumero("\nINGRESE CANTIDAD REQUERIDA DEL PRODUCTO: ", "\nERROR. ", 1, 100, 2, &cantidadRequerida);

				indexProd = eProd_BuscarPorID(productos, TAM, idProducto);

				if(indexProd != -1)
				{
					productos[indexProd].idProducto = idProducto;
					productos[indexProd].stockDisponible -= cantidadRequerida;
					precioTotal = productos[indexProd].precio * cantidadRequerida;
					printf("\nPRECIO A PAGAR: $%.2f \n", precioTotal);

					while(productos[indexProd].stockDisponible == 0)
					{
						utn_getNumero("\nPRODUCTO SIN STOCK, INGRESE OTRO ID: ", "\nERROR. ", 1000, 9999, 2, &idProducto);
						indexProd = eProd_BuscarPorID(productos, TAM, idProducto);
					}
				}
				rtn = 1;
			}
		}while(opcion != 0);
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

eProducto eProd_CargarDatos(void)
{
	eProducto auxiliar;
	int opcionCategoria;

	utn_getString("\nINGRESE NOMBRE DEL PRODUCTO: ", "\nERROR. ", 2, TAM_CHAR, auxiliar.nombreProducto);

	utn_getNumFloat("INGRESE PRECIO DEL PRODUCTO: ", "\nERROR. ", 0, 999999, 2, &auxiliar.precio);

	utn_getNumero("INGRESE LA CATEGORIA DEL PRODUCTO (TIPO 1: ELECTRODOMESTICOS | TIPO 2: ROPA | TIPO 3: TECNOLOGIA): ",
				"ERROR \n", 1, 3, 2, &opcionCategoria);
	switch(opcionCategoria)
	{
		case 1:
			auxiliar.categoria = ELECTRODOMESTICOS;
		break;

		case 2:
			auxiliar.categoria = ROPA;
		break;

		case 3:
			auxiliar.categoria = TECNOLOGIA;
		break;
	}

	utn_getNumero("INGRESE STOCK DISPONIBLE DEL PRODUCTO: ", "\nERROR. ", 0, 500, 2, &auxiliar.stockDisponible);

	return auxiliar;
}

void eProd_Harcodeo(eProducto productos[])
{
	productos[0].precio = 2500;
	productos[0].idProducto = 1006;
	productos[0].FK_idUsuario = 100;
	productos[0].isEmpty = OCUPADO;
	productos[0].stockDisponible = 50;
	productos[0].categoria = TECNOLOGIA;
	strcpy(productos[0].nombreProducto, "Mouse Logitech");

	productos[1].precio = 25000;
	productos[1].categoria = ROPA;
	productos[1].isEmpty = OCUPADO;
	productos[1].idProducto = 1001;
	productos[1].FK_idUsuario = 100;
	productos[1].stockDisponible = 70;
	strcpy(productos[1].nombreProducto, "Puffer Polo");

	productos[2].precio = 20000;
	productos[2].idProducto = 1002;
	productos[2].isEmpty = OCUPADO;
	productos[2].FK_idUsuario = 100;
	productos[2].stockDisponible = 60;
	productos[2].categoria = ELECTRODOMESTICOS;
	strcpy(productos[2].nombreProducto, "Lavavajillas");

	productos[3].precio = 23000;
	productos[3].categoria = ROPA;
	productos[3].idProducto = 1003;
	productos[3].isEmpty = OCUPADO;
	productos[3].FK_idUsuario = 100;
	productos[3].stockDisponible = 25;
	strcpy(productos[3].nombreProducto, "Nike blazer");

	productos[4].precio = 2000;
	productos[4].idProducto = 1004;
	productos[4].isEmpty = OCUPADO;
	productos[4].FK_idUsuario = 100;
	productos[4].stockDisponible = 85;
	productos[4].categoria = ELECTRODOMESTICOS;
	strcpy(productos[4].nombreProducto, "Microondas");

	productos[5].isEmpty = OCUPADO;
	productos[5].categoria = TECNOLOGIA;
	productos[5].precio = 50000;
	productos[5].idProducto = 1005;
	productos[5].FK_idUsuario = 100;
	productos[5].stockDisponible = 100;
	strcpy(productos[5].nombreProducto, "Tv Samsung");
}

int eProd_Alta(eProducto productos[], int TAM)
{
	int rtn = -1;
	eProducto auxProductos;

	//BUSCO ESPACIO EN productos
	int index = eProd_ObtenerIndexLibre(productos, TAM);

	//SI INDEX == -1 productos LLENO
	//SI INDEX != -1 TENGO EN INDEX POSICION DE productos LIBRE

	if (index != -1)
	{
		//PIDO DATOS - CARGO Productos AUXILIAR
		auxProductos = eProd_CargarDatos();

		//SETEO ID UNICO - VARIABLE ESTATICA AUTOINCREMENTAL
		auxProductos.idProducto = eProd_obtenerID();

		//CAMBIO SU ESTADO A "OCUPADO"
		auxProductos.isEmpty = OCUPADO;

		//SETEO EL productos CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
		productos[index] = auxProductos;

		//RETORNO 1 PARA SABER QUE FUE DADO DE ALTA SATISFACTORIAMENTE
		rtn = 1;
	}

	return rtn;
}

int eProd_Baja(eProducto productos[], int TAM_P)
{
	int rtn = 0;
	int idusuario;
	int index;
	int flag = 0;

	//LISTO TODOS LOS productos
	if(eProd_MostrarTodos(productos, TAM_P))
	{
		//BANDERA EN 1 SI HAY productos DADOS DE ALTA PARA LISTAR
		flag = 1;
	}

	//SI HAY productos PARA DAR DE BAJA
	if(flag)
	{
		//PIDO ID A DAR DE BAJA
		utn_getNumero("\nINGRESE ID DEL PRODUCTO A DAR DE BAJA: ", "\nERROR. ", 1000, 9999, 3, &idusuario);

		//BUSCO INDEX POR ID EN ARRAY
		while (eProd_BuscarPorID(productos, TAM_P, idusuario) == -1)
		{
			puts("\nNO EXISTE ID.");

			//PIDO OTRA VEZ ID A DAR DE BAJA
			utn_getNumero("\nINGRESE ID DEL PRODUCTO A DAR DE BAJA: ", "\nERROR. ", 1000, 9999, 3, &idusuario);
		}

		//OBTENGO INDEX DEL ARRAY DE productos A DAR DE BAJA
		index = eProd_BuscarPorID(productos, TAM_P, idusuario);

		//BAJA ACEPTADA - CAMBIO ESTADO A "BAJA"
		productos[index].isEmpty = BAJA;

		puts("\nSE HA DADO DE BAJA EL PRODUCTO. ");

		//RETORNO 1 SI SE DIO DE BAJA CORRECTAMENTE
		rtn = 1;
	}

	return rtn;
}
