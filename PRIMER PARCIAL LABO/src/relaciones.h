#ifndef RELACIONES_H_
#define RELACIONES_H_

#include "usuarios.h"
#include "productos.h"
#include "trackings.h"

int relacionUTP_Compra(eUsuario usuarios[], int TAM_U, eProducto productos[], int TAM_P, eTracking trackings[], int TAM_T, int sesionIniciada);
int relacionUTP_venta(eUsuario usuarios[], eProducto productos[], int sesionIniciada);
int relacionUTP_menuUsuario(eUsuario usuarios[], int TAM_U, eProducto productos[], int TAM_P, eTracking trackings[], int TAM_T, int sesionIniciada);
void relacionUTP_imprimirCompra(eTracking tracking, eProducto producto);
int relacionUTP_imprimirCompras(eTracking trackings[], int TAM_T, eProducto productos[], int TAM_P, int idUsuario);
int relacionUTP_estadoCompras(eTracking trackings[], int TAM_T, eProducto productos[], int TAM_P, eUsuario usuarios[], int TAM_U, int idUsuario);
int relacionUTP_estadoVentas(eTracking trackings[], int TAM_T, eProducto productos[], int TAM_P, eUsuario usuarios[], int TAM_U, int idUsuario);
int relacionUTP_ventasRealizadas(eTracking trackings[], int TAM_T, int idUsuario);
int relacionUTP_comprasRealizadas(eTracking trackings[], int TAM_T, int idUsuario);
int relacionUTP_imprimirVentas(eTracking trackings[], int TAM_T, eProducto productos[], int TAM_P, int idUsuario);
void relacionUTP_imprimirTracking(eTracking tracking);
int relacionUTP_imprimirTrackingGlobal(eTracking trackings[], int TAM_T);
int relacionUTP_menuAdmin(eUsuario usuarios[], int TAM_U, eProducto productos[], int TAM_P, eTracking trackings[], int TAM_T);
int relacionUTP_menuTipos(eUsuario usuarios[], int TAM_U, eProducto productos[], int TAM_P, eTracking trackings[], int TAM_T);

#endif /* RELACIONES_H_ */
