#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

#include "inputs.h"

#define LIBRE 0
#define BAJA -1
#define OCUPADO 1

#define ROPA 3
#define TECNOLOGIA 4
#define ELECTRODOMESTICOS 2

typedef struct
{
	float precio;
	int idProducto;
	short int isEmpty;
	int FK_idUsuario;
	int stockDisponible;
	short int categoria;
	char nombreProducto[TAM_CHAR];
}eProducto;

void eProd_Inicializar(eProducto array[], int TAM);
int eProd_ObtenerIndexLibre(eProducto array[], int TAM);
int eProd_BuscarPorID(eProducto array[], int TAM, int ID);
void eProd_MostrarUno(eProducto producto);
int eProd_MostrarTodos(eProducto productos[], int TAM);
int eProd_Alta(eProducto array[], int TAM);
int eProd_Baja(eProducto productos[], int TAM_P);
eProducto eProd_CargarDatos(void);
int eProd_Comprar(eProducto productos[], int TAM);
void eProd_Harcodeo(eProducto productos[]);
int eProd_Ordenar(eProducto productos[], int TAM);

#endif /* PRODUCTOS_H_ */
