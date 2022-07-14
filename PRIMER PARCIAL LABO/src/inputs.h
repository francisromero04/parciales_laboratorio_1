#ifndef INPUTS_H_
#define INPUTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_CHAR 25

//PROTOTIPO myGets | SE USA EN TODAS
int myGets(char* cadena, int longitud);

//PROTOTIPOS FUNCIONES GET INT
int utn_getNumero(char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos, int* pResultado);
int esNumerica(char* cadena, int limite);
int getInt(int *pResultado);

//PROTOTIPOS FUNCIONES GET FLOAT
int utn_getNumFloat(char mensaje[], char mensajeError[], int minimo, int maximo, int reintentos, float *pNumeroIngresado);
int esNumericaFloat(char arrayPosiblesNumeros[]);
int getFloat(float* pNumeroTomado);

//PROTOTIPOS FUNCIONES GET STRING
int utn_getString(char* mensaje, char* mensajeError, int reintentos,  int longitud, char* pResultado);
int getNombre(char* pResultado, int longitud);
int esNombre(char* cadena,int longitud);

//PROTOTIPOS FUNCIONES GET EMAIL / PASSWORD
int getEmail(char mensaje[], char mensajeError[], int reintentos, char correo[]);
int getPassword(char mensaje[], char mensajeError[], int min, int max, int reintentos, char cadenaPass[]);

//PROTOTIPOS FUNCIONES TIEMPO
long int time_Add(double secondsAdd);
long int time_Current(void);

#endif
