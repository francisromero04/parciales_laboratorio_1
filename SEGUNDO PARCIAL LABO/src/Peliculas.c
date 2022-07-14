#include "Peliculas.h"

Peliculas* Peliculas_new()
{
	Peliculas* aux = NULL;
	aux = (Peliculas*)malloc(sizeof(Peliculas));
	return aux;
}

Peliculas* new_PeliculasConParametros(char* idStr, char* tituloStr, char* generoStr, char* rating)
{
	Peliculas* peliculaNueva=NULL;
    peliculaNueva = Peliculas_new();

    if(peliculaNueva!=NULL)
    {
        if(!(Pelicula_SetId(peliculaNueva, atoi(idStr))
             && Pelicula_SetTitulo(peliculaNueva, tituloStr)
             && Pelicula_SetGenero(peliculaNueva, generoStr)
             && Pelicula_SetRating(peliculaNueva, atof(rating))))
        {
			Peliculas_delete(peliculaNueva);
        }
    }

    return peliculaNueva;
}

void Peliculas_delete(Peliculas* this)
{
	if(this != NULL)
	{
		free(this);
		this = NULL;
	}
}

int Pelicula_SetId(Peliculas* pelicula, int id)
{
    int todoOk=-1;

    if(pelicula!=NULL && id>=0)
    {
        pelicula->id=id;

        todoOk=1;
    }

    return todoOk;
}
int Pelicula_SetTitulo(Peliculas* pelicula, char* titulo)
{
    int todoOk=-1;

    if(pelicula!=NULL && titulo!=NULL)
    {
        if(strlen(titulo)<50 && strlen(titulo)>4)
        {
            strcpy(pelicula->titulo, titulo);

            todoOk=1;
        }
    }

    return todoOk;
}
int Pelicula_SetGenero(Peliculas* pelicula, char* genero)
{
    int todoOK=-1;

    if(pelicula!=NULL && genero!=NULL)
    {
        if(strlen(genero)<50 && strlen(genero)>4)
        {
            strcpy(pelicula->genero, genero);

            todoOK=1;
        }
    }

    return todoOK;
}
int Pelicula_SetRating(Peliculas* pelicula, float rating)
{
    int todoOK=-1;

    if(pelicula!=NULL && rating>=0)
    {
        pelicula->rating=rating;

        todoOK=1;
    }

    return todoOK;
}
int Pelicula_GetId(Peliculas* pelicula, int* id)
{
    int todoOk=-1;

    if(pelicula!=NULL && id!=NULL)
    {
        *id=pelicula->id;

        todoOk=1;
    }

    return todoOk;
}
int Pelicula_GetTitulo(Peliculas* pelicula, char* titulo)
{
    int todoOk=-1;

    if(pelicula!=NULL && titulo!=NULL)
    {
        strcpy(titulo, pelicula->titulo);

        todoOk=1;
    }

    return todoOk;
}
int Pelicula_GetGenero(Peliculas* pelicula, char* genero)
{
    int todoOk=-1;

    if(pelicula!=NULL && genero!=NULL)
    {
        strcpy(genero, pelicula->genero);

        todoOk=1;
    }

    return todoOk;
}
int Pelicula_GetRating(Peliculas* pelicula, float* rating)
{
    int todoOk=-1;

    if(pelicula!=NULL && rating!=NULL)
    {
        *rating=pelicula->rating;

        todoOk=1;
    }

    return todoOk;
}
int Pelicula_GetGeneroDescripcion(int numero, char* Genero)
{
        int todoOk=0;

    if(numero<=4 &&  numero>=1 && Genero!=NULL)
    {
        if(numero==1)
        {
            strcpy(Genero, "drama");
        }
        else if(numero==2)
        {
            strcpy(Genero, "comedia");
        }
        else if(numero==3)
        {
            strcpy(Genero, "accion");
        }
        else if(numero==4)
        {
            strcpy(Genero, "terror");
        }
        todoOk=1;
    }

    return todoOk;
}

void Peliculas_imprimir(Peliculas* pelicula)
{
	int id;
    char titulo[30];
    char genero[30];
    float rating;

	Pelicula_GetId(pelicula, &id);
	Pelicula_GetTitulo(pelicula, titulo);
	Pelicula_GetGenero(pelicula, genero);
	Pelicula_GetRating(pelicula, &rating);

	printf("|%-4d|%-20s|%-20s|%-10.1f|\n",pelicula->id, pelicula->titulo, pelicula->genero, pelicula->rating);
}

int Peliculas_actualizarUltimoId(int idAnterior)
{
	int rtn = -1;

	FILE* pFile = fopen("ultimoId.txt", "w");

	if(pFile != NULL)
	{
		fprintf(pFile, "%d\n", idAnterior+1);
		rtn = 1;
	}
	fclose(pFile);

	return rtn;
}

int Pelicula_FiltrarDrama(void* elemento)
{
    int todoOk=-1;
    char generoPelicula[30]={"drama"};
    Peliculas* generoAux;
    generoAux=(Peliculas*) elemento;

    if(generoAux!=NULL)
    {
        if(strcmp(generoAux->genero, generoPelicula)==0)
        {
            todoOk=1;
        }
        else
        {
            todoOk=0;
        }
    }

    return todoOk;
}

void* Peliculas_mapGenero(void* pElement)
{
	Peliculas* auxPelicula=NULL;
    char descripcion[30];
    int numeros;
    int maximo=4;
    int minimo=1;

    if(pElement!=NULL)
    {
        auxPelicula=(Peliculas*)pElement;

        if(auxPelicula!=NULL)
        {
            numeros=rand()%(maximo-minimo+1)+minimo;
            Pelicula_GetGeneroDescripcion(numeros, descripcion);
            Pelicula_SetGenero(auxPelicula, descripcion);
        }
    }

    return auxPelicula;
}

void* Peliculas_mapRating(void* a)
{
	Peliculas* pPelicula = NULL;

	if(a != NULL)
	{
		pPelicula = (Peliculas*) a;

		int min = 10;
		int max = 100;
		float valor;

		valor = (float) ((rand() % (max - min + 1)) + min)/10;
		pPelicula->rating = valor;
	}

	return pPelicula;
}

int Pelicula_OrdenamientoPorGeneroRating(void* punteroUno, void* punteroDos)
{
    int todoOk=0;
    float ratingUno;
    float ratingDos;
    char generoUno[30];
    char generoDos[30];
    Peliculas* peliculaUno=NULL;
    Peliculas* peliculaDos=NULL;

	peliculaUno=(Peliculas*)punteroUno;
    peliculaDos=(Peliculas*)punteroDos;

    if(peliculaUno!=NULL && punteroDos!=NULL)
    {
        Pelicula_GetRating(peliculaUno, &ratingUno);
        Pelicula_GetRating(peliculaDos, &ratingDos);
        Pelicula_GetGenero(peliculaUno, generoUno);
        Pelicula_GetGenero(peliculaDos, generoDos);

        if(strcmp(generoUno, generoDos)<0)
        {
            todoOk=1;
        }
        else if(strcmp(generoUno, generoDos)>0)
        {
            todoOk=-1;
        }
        else
        {
            if(strcmp(generoUno, generoDos)==0)
            {
                if(ratingUno > ratingDos)
                {
                    todoOk = 1;
                }
                else if(ratingUno < ratingDos)
                {
                    todoOk = -1;
                }
            }
        }
    }

    return todoOk;
}
