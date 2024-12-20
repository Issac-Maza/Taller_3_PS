#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilidades.h"
#include "estudiantes.h"

void cargarDatosEstudiantes(Estudiante **estudiantes, int *cantidad) {
    	FILE *archivo = fopen("archivos/estudiantes.txt", "r");
    	if (!archivo) {
        	printf("Error al abrir el archivo de estudiantes.\n");
        	return;
    	}

    	*cantidad = 0;
    	*estudiantes = NULL;
    	Estudiante temp;

    	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n", 
		temp.nombres, temp.apellidos, temp.matricula, temp.usuario, temp.clave, temp.estado) != EOF) {
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
			estudiantes[i].nombres, estudiantes[i].apellidos, estudiantes[i].matricula, 
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

    	printf("Ingrese los nombres del estudiante: ");
	fgets(nuevoEstudiante.nombres, sizeof(nuevoEstudiante.nombres), stdin);
	strtok(nuevoEstudiante.nombres, "\n");

	if (strlen(nuevoEstudiante.nombres) == 0) {
        	printf("Error: El nombre no puede estar vacío.\n");
        	return;
	}

    	printf("Ingrese los apellidos del estudiante: ");
	fgets(nuevoEstudiante.apellidos, sizeof(nuevoEstudiante.apellidos), stdin);
	strtok(nuevoEstudiante.apellidos, "\n");

	if (strlen(nuevoEstudiante.apellidos) == 0) {
        	printf("Error: Los apellidos no pueden estar vacíos.\n");
        	return;
	}

    	printf("Ingrese la matrícula: ");
	fgets(nuevoEstudiante.matricula, sizeof(nuevoEstudiante.matricula), stdin);
	strtok(nuevoEstudiante.matricula, "\n");

	if (verificarUnicidadEstudiante(nuevoEstudiante.matricula, *estudiantes, *cantidad)) {
        	printf("Error: Matrícula ya registrada.\n");
        	return;
	}

	if (strlen(nuevoEstudiante.matricula) == 0) {
        	printf("Error: La matrícula no puede estar vacía.\n");
        	return;
	}

    	printf("Ingrese el usuario: ");
	fgets(nuevoEstudiante.usuario, sizeof(nuevoEstudiante.usuario), stdin);
	strtok(nuevoEstudiante.usuario, "\n");

	if (strlen(nuevoEstudiante.usuario) == 0) {
		printf("Error: El usuario no puede estar vacío.\n");
		return;
	}

    	printf("Ingrese la clave: ");
	fgets(nuevoEstudiante.clave, sizeof(nuevoEstudiante.clave), stdin);
	strtok(nuevoEstudiante.clave, "\n");

	if (strlen(nuevoEstudiante.clave) == 0) {
		printf("Error: La clave no puede estar vacía.\n");
		return;
	}

    	strcpy(nuevoEstudiante.estado, "Activo");

	Estudiante *temp = realloc(*estudiantes, (*cantidad + 1) * sizeof(Estudiante));
	if (!temp) {
		printf("Error: No se pudo asignar memoria.\n");
		return;
	}

    	*estudiantes = temp;
	(*estudiantes)[*cantidad] = nuevoEstudiante;
	(*cantidad)++;

    	printf("Estudiante creado correctamente.\n");
}

void editarEstudiante(Estudiante *estudiantes, int cantidad) {
    	char matricula[15];

    	printf("Ingrese la matrícula del estudiante a editar: ");
    	fgets(matricula, sizeof(matricula), stdin);
    	strtok(matricula, "\n");

    	for (int i = 0; i < cantidad; i++) {
        	if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            		printf("Estudiante encontrado: %s %s\n", estudiantes[i].nombres, estudiantes[i].apellidos);

            		printf("Ingrese la nueva clave: ");
            		fgets(estudiantes[i].clave, sizeof(estudiantes[i].clave), stdin);
            		strtok(estudiantes[i].clave, "\n");

            		printf("Ingrese el nuevo estado (Activo/Inactivo): ");
            		fgets(estudiantes[i].estado, sizeof(estudiantes[i].estado), stdin);
            		strtok(estudiantes[i].estado, "\n");

            		printf("Estudiante actualizado correctamente.\n");
            		return;
        	}
    	}

	printf("Estudiante no encontrado.\n");
}

void mostrarEstudiantes(Estudiante *estudiantes, int cantidad) {
	printf("\n--- LISTA DE ESTUDIANTES ---\n");
	for (int i = 0; i < cantidad; i++) {
		printf("Nombres: %s %s - Matrícula: %s - Usuario: %s - Estado: %s\n", 
			estudiantes[i].nombres, estudiantes[i].apellidos, estudiantes[i].matricula, 
			estudiantes[i].usuario, estudiantes[i].estado);
    }
}

int verificarUnicidadEstudiante(const char *matricula, Estudiante *estudiantes, int cantidad) {
	for (int i = 0; i < cantidad; i++) {
		if (strcmp(estudiantes[i].matricula, matricula) == 0) {
			return 1;
        	}
    	}
	return 0;
}

void liberarMemoriaEstudiantes(Estudiante *estudiantes, int cantidad) {
	if (cantidad > 0 && estudiantes != NULL) {
		free(estudiantes);
	}
}
