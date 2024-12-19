#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilidades.h"
#include "estudiantes.h"

void cargarDatosEstudiantes(Estudiante **estudiantes, int *cantidad) {
    	FILE *archivo = fopen(ARCHIVO_ESTUDIANTES, "r");
    	if (!archivo) {
        	printf("Error al abrir el archivo de estudiantes.\n");
        	return;
    	}

    	*cantidad = 0;
    	*estudiantes = NULL;
    	Estudiante temp;

    	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n",
		 temp.nombre, temp.apellidos, temp.matricula, temp.usuario, temp.clave, temp.estado) != EOF) {
        	*estudiantes = realloc(*estudiantes, (*cantidad + 1) * sizeof(Estudiante));
        	(*estudiantes)[*cantidad] = temp;
        	(*cantidad)++;
    }
    fclose(archivo);
}

void guardarDatosEstudiantes(Estudiante *estudiantes, int cantidad) {
	FILE *archivo = fopen("archivos/estudiantes.txt", "w");
    	if (!archivo) {
        	printf("Error al abrir el archivo de estudiantes para guardar.\n");
        	return;
    	}

    	for (int i = 0; i < cantidad; i++) {
        	fprintf(archivo, "%s-%s-%s-%s-%s-%s\n",
			estudiantes[i].nombre, estudiantes[i].apellidos, estudiantes[i].matricula, 
			estudiantes[i].usuario, estudiantes[i].clave, estudiantes[i].estado);
    	}
    	fclose(archivo);
}

void gestionarEstudiantes(Estudiante **estudiantes, int *cantidad) {
    	int opcion;
    	do {
        	printf("\n     ADMINISTRAR DE ESTUDIANTES    \n");
        	printf("1. Crear Estudiante\n");
        	printf("2. Editar Estudiante\n");
        	printf("3. Mostrar Estudiantes\n");
        	printf("4. Volver al menú principal\n");
        	printf("Seleccione una opción: ");
        	scanf("%d", &opcion);
        	limpiarBuffer();

        	switch (opcion) {
            		case 1:
                		crearEstudiante(estudiantes, cantidad);
                		break;
            		case 2:
                		editarEstudiante(*estudiantes, *cantidad);
                		break;
            		case 3:
                		mostrarEstudiantes(*estudiantes, *cantidad);
                		break;
            		case 4:
                		printf("Volviendo al menú principal...\n");
                		break;
            		default:
                		printf("Opción inválida. Intente de nuevo.\n");
        	}
    	} while (opcion != 4);
}

void crearEstudiante(Estudiante **estudiantes, int *cantidad) {
	Estudiante nuevoEstudiante;

    	printf("Ingrese el nombre del estudiante: ");
    	fgets(nuevoEstudiante.nombre, sizeof(nuevoEstudiante.nombre), stdin);
    	strtok(nuevoEstudiante.nombre, "\n");

    	printf("Ingrese los apellidos del estudiante: ");
    	fgets(nuevoEstudiante.apellidos, sizeof(nuevoEstudiante.apellidos), stdin);
    	strtok(nuevoEstudiante.apellidos, "\n");

    	printf("Ingrese la matrícula del estudiante: ");
    	fgets(nuevoEstudiante.matricula, sizeof(nuevoEstudiante.matricula), stdin);
    	strtok(nuevoEstudiante.matricula, "\n");

    	if (verificarUnicidadEstudiante(nuevoEstudiante.matricula, nuevoEstudiante.usuario)) {
        	printf("Error: El estudiante ya existe.\n");
        	return;
    	}

    	printf("Ingrese el usuario: ");
    	fgets(nuevoEstudiante.usuario, sizeof(nuevoEstudiante.usuario), stdin);
    	strtok(nuevoEstudiante.usuario, "\n");

    	printf("Ingrese la clave: ");
    	fgets(nuevoEstudiante.clave, sizeof(nuevoEstudiante.clave), stdin);
    	strtok(nuevoEstudiante.clave, "\n");

    	strcpy(nuevoEstudiante.estado, "Activo");

    	*estudiantes = realloc(*estudiantes, (*cantidad + 1) * sizeof(Estudiante));
    	(*estudiantes)[*cantidad] = nuevoEstudiante;
    	(*cantidad)++;

    	printf("Estudiante creado exitosamente.\n");
}

void editarEstudiante(Estudiante *estudiantes, int cantidad) {
    	char matricula[15];
    	int encontrado = 0;

    	printf("Ingrese la matrícula del estudiante a editar: ");
    	fgets(matricula, sizeof(matricula), stdin);
    	strtok(matricula, "\n");

    	for (int i = 0; i < cantidad; i++) {
        	if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            		printf("Estudiante encontrado: %s %s\n", estudiantes[i].nombre, estudiantes[i].apellidos);

            		printf("Ingrese la nueva clave: ");
            		fgets(estudiantes[i].clave, sizeof(estudiantes[i].clave), stdin);
            		strtok(estudiantes[i].clave, "\n");

            		printf("Ingrese el nuevo estado (Activo/Inactivo): ");
            		fgets(estudiantes[i].estado, sizeof(estudiantes[i].estado), stdin);
            		strtok(estudiantes[i].estado, "\n");

            		printf("Estudiante actualizado correctamente.\n");
            		encontrado = 1;
            		break;
        	}
    	}

    	if (!encontrado) {
        	printf("Estudiante no encontrado.\n");
    	}
}

void mostrarEstudiantes(Estudiante *estudiantes, int cantidad) {
    	printf("\n--- LISTA DE ESTUDIANTES ---\n");
    	for (int i = 0; i < cantidad; i++) {
        	printf("Nombre: %s %s - Matrícula: %s - Usuario: %s - Estado: %s\n",
			estudiantes[i].nombre, estudiantes[i].apellidos, estudiantes[i].matricula, 
			estudiantes[i].usuario, estudiantes[i].estado);
    	}
}

int verificarUnicidadEstudiante(const char *matricula, const char *usuario) {
    	Estudiante estudiante;
    	FILE *archivo = fopen("archivos/estudiantes.txt", "r");

    	if (!archivo) return 0;

    	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n", 
		estudiante.nombre, estudiante.apellidos, estudiante.matricula, 
		estudiante.usuario, estudiante.clave, estudiante.estado) != EOF) {
		if (strcmp(estudiante.matricula, matricula) == 0 || strcmp(estudiante.usuario, usuario) == 0) {
			fclose(archivo);
			return 1;
		}
	}

	fclose(archivo);
	return 0;
}

void liberarMemoriaEstudiantes(Estudiante *estudiantes, int cantidad) {
	free(estudiantes);
}
