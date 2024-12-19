#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	Profesor *profesores = NULL;
	Curso *cursos = NULL;
	Estudiante *estudiantes = NULL;
	Materia *materias = NULL;
	int cantidadProfesores = 0, cantidadCursos = 0, cantidadEstudiantes = 0, cantidadMaterias = 0;

	cargarDatosProfesores(&profesores, &cantidadProfesores);
	cargarDatosCursos(&cursos, &cantidadCursos);
	cargarDatosEstudiantes(&estudiantes, &cantidadEstudiantes);
	cargarDatosMaterias(&materias, &cantidadMaterias);

	do{
		mostrarMenu();
		scanf("%d",&opcion);
		limpiarBuffer();

		switch (opcion) {
			case 1:
				gestionarMaterias(materias, &cantidadMaterias);
                		break;
            		case 2:
                		gestionarEstudiantes(estudiantes, &cantidadEstudiantes);
                		break;
            		case 3:
                		gestionarProfesores(profesores, &cantidadProfesores, materias, cantidadMaterias);
                		break;
            		case 4:
                		gestionarCursos(cursos, &cantidadCursos, estudiantes, cantidadEstudiantes, materias, cantidadMaterias, profesores, cantidadProfesores);
                		break;
            		case 5:
                		printf("Saliendo del programa\n");
                		break;
            		default:
                		printf("Opcion invalida o incorrecta\n");
                		break;
		}
	} while (opcion != 5);

	guardarDatosProfesores(profesores, cantidadProfesores);
    	guardarDatosCursos(cursos, cantidadCursos);
    	guardarDatosEstudiantes(estudiantes, cantidadEstudiantes);
    	guardarDatosMaterias(materias, cantidadMaterias);

	liberarMemoriaProfesores(profesores, cantidadProfesores);
	liberarMemoriaCursos(cursos, cantidadCursos);
	liberarMemoriaEstudiantes(estudiantes, cantidadEstudiantes);
	liberarMemoriaMaterias(materias, cantidadMaterias);

	return 0;
}
