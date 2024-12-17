#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"
#include "estudiantes.h"
#include "profesores.h"
#include "materias.h"
#include "cursos.h"

void mostrarMenu() {
	printf("\n  MENU PRINCIPAL   \n");
	printf("1. Administrar las Materias\n");
	printf("2. Administrar los Estudiantes\n");
	printf("3. Administrar los Profesores\n");
	printf("4. Administrar los Cursos\n");
	printf("5. Salir\n");
	printf("Opcion a elegir: ");

}

int main (){
	int opcion;
	do{
		mostrarMenu();
		scanf("%d",&opcion);
		switch(opcion){
		case 1:
			break;
		case 2:
                	break;
		case 3:
                	break;
		case 4:
                	break;
		case 5:
			printf("Saliendo del programa\n");
                	break;
		default:
			printf("Opcion invalida o incorrecta \n");
			break;
		}
	}while(opcion != 5 );

	return 0;
}
