#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"
#include "Controller.h"
#include "Peliculas.h"

int main()
{
    setbuf(stdout, NULL);

    int option;
    LinkedList* listaPeliculas = ll_newLinkedList();
    LinkedList* peliculasFiltradas;
    int flagCargarTexto = 0;

    do{
    	puts("\n\t\t\tMENU DE OPCIONES:\n"
    		"\t\t\t-----------------\n\n"
    		"1. Cargar los datos de las peliculas desde el archivo movies.csv (modo texto). \n"
    		"2. Listar peliculas. \n"
    		"3. Asignar rating \n"
    		"4. Asignar genero \n"
    		"5. Filtrar por genero \n"
    		"6. Ordenar peliculas por id \n"
    		"7. Guardar los datos de las peliculas en el archivo movies.csv (modo texto). \n"
    		"8. Salir \n");

    	utn_getNumero("INGRESE OPCION: ", "ERROR \n", 1, 8, 2, &option);

        switch(option)
        {
            case 1:
            	if(flagCargarTexto == 0)
            	{
            		controller_loadFromText("movies.csv",listaPeliculas);
					flagCargarTexto = 1;
            	}
            	else
            	{
            		puts("\nERROR, YA SE HA CARGADO LA LISTA (TXT).\n");
            	}
            break;

            case 2:
            	if(flagCargarTexto == 1)
				{
					controller_ListPeliculas(listaPeliculas);
				}
				else
				{
					puts("\nANTES DE LISTAR PRIMERO CARGUE LOS DATOS DEL ARCHIVO.\n");
				}
            break;

            case 3:
            	if(flagCargarTexto == 1)
				{
					ll_map(listaPeliculas, Peliculas_mapRating);
				}
				else
				{
					puts("\nANTES DE ASIGNAR UN GENERO PRIMERO CARGUE LOS DATOS DEL ARCHIVO.\n");
				}
            break;

            case 4:
            	if(flagCargarTexto == 1)
				{
					ll_map(listaPeliculas, Peliculas_mapGenero);
				}
				else
				{
					puts("\nANTES DE ASIGNAR UN GENERO PRIMERO CARGUE LOS DATOS DEL ARCHIVO.\n");
				}
            break;

            case 5:
            	if(flagCargarTexto == 1)
				{
					peliculasFiltradas = ll_filter(listaPeliculas, Pelicula_FiltrarDrama);
                	controller_saveAsText("moviesFiltradas.txt", listaPeliculas);
				}
				else
				{
					puts("\nANTES DE FILTRAR PRIMERO CARGUE LOS DATOS DEL ARCHIVO (TXT) .\n");
				}
            break;

            case 6:
            	if(flagCargarTexto == 1)
				{
                	controller_sortPeliculas(listaPeliculas);
                	controller_saveAsText("moviesOrdenadas.txt", listaPeliculas);
				}
				else
				{
					puts("\nANTES DE ORDENAR PRIMERO CARGUE LOS DATOS DEL ARCHIVO.\n");
				}
            break;

            case 7:
            	if(flagCargarTexto == 1)
            	{
					controller_saveAsText("movies.csv", listaPeliculas);
            	}
            	else
            	{
					puts("\nANTES DE GUARDAR PRIMERO CARGUE LOS DATOS DEL ARCHIVO (TXT) .\n");
            	}
           	break;

            case 8:
            	puts("\nPROGRAMA CERRADO.");
            break;
        }
    }while(option != 8);

    return EXIT_SUCCESS;
}
