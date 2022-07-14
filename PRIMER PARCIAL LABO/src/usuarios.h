#ifndef USUARIOS_H_
#define USUARIOS_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "inputs.h"

#define MAX_LEN_EMAIL 25
#define MAX_LEN_PASSWORD 10
#define MIN_LEN_PASSWORD 4
#define MAX_LEN_DIRECTION 50

#define ADMIN 1
#define USUARIO 2

#define LIBRE 0
#define OCUPADO 1
#define BAJA -1

typedef struct
{
	int idUsuario;
	short int isEmpty;
	short int tipo;
	char email[TAM_CHAR];
	char password[TAM_CHAR];
	char direccion[TAM_CHAR];
	int codigoPostal;
}eUsuario;

void eUs_Inicializar(eUsuario usuarios[], int TAM_U);
int eUs_ObtenerIndexLibre(eUsuario usuarios[], int TAM_U);
eUsuario eUs_CargarDatos(void);
int eUs_Alta(eUsuario usuarios[], int TAM_U);
int eUs_Baja(eUsuario usuarios[], int TAM_U);
int eUs_iniciarSesion(eUsuario usuarios[], int TAM_U);
void eUs_MostrarUno(eUsuario usuario);
int eUs_MostrarTodos(eUsuario usuarios[], int TAM_U);
int eUs_BuscarPorID(eUsuario usuarios[], int TAM_U, int givenID);
int eUs_BuscarPorEmail(eUsuario usuarios[], int TAM_U, char givenEmail[]);
void eUs_harcodeo(eUsuario usuarios[]);

#endif /* USUARIOS_H_ */
