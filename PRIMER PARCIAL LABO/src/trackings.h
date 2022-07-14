#ifndef TRACKINGS_H_
#define TRACKINGS_H_

#define LIBRE 0
#define BAJA -1
#define EN_VIAJE 3
#define ENTREGADO 1

#include "inputs.h"

typedef struct
{
	int idTracking;
	int idProducto;
	short int isEmpty;
	int FK_idUsuario;
	int cantidad;
	int distanciaKm;
	long int horaLlegada;
}eTracking;

void eTrack_Inicializar(eTracking array[], int TAM);
int eTrack_ObtenerIndexLibre(eTracking array[], int TAM);
eTracking eTrack_CalcularHora(int idProducto, int codigoPostal);
int eTrack_actualizarEstado(eTracking trackings[], int TAM);
int eTrack_BuscarPorID(eTracking array[], int TAM, int ID);
int eTrack_BuscarPorIdUsuario(eTracking array[], int TAM, int idUsuario);
void eTrack_Harcodeo(eTracking trackings[]);
int eTrack_Alta(eTracking trackings[], int TAM_T, int codigoPostal, int idProducto);
int eTrack_Baja(eTracking array[], int TAM);

#endif /* TRACKINGS_H_ */
