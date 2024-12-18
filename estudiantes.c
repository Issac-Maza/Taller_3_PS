#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilidades.h"
#include "estudiantes.h"

void gestionarEstudiantes() {
	int opcion;
	printf("\n----ADMINISTRACION DE ESTUDIANTES----\n");
	printf("1. Crear un estudiante\n");
	printf("2. Editar datos de un estudiante\n");
	printf("Escoja una opcion: ");
	scanf("%d", &opcion);
	limpiarBuffer();

	switch(opcion) {
        	case 1:
			crearEstudiante();
			break;
        	case 2:
			editarEstudiante();
			break;
        	default:
			printf("Opción inválida.\n");
			break;
    }
}

void crearEstudiante() {
	Estudiante nuevoEstudiante;
	FILE *archivo = fopen("archivos/estudiantes.txt", "a+");

	if (!archivo) {
		printf("Error al abrir el archivo.\n");
		return;
	}

	printf("Ingrese sus nombres: ");
	fgets(nuevoEstudiante.nombres, sizeof(nuevoEstudiante.nombres), stdin);
	strtok(nuevoEstudiante.nombres, "\n");

	printf("Ingrese sus apellidos: ");
	fgets(nuevoEstudiante.apellidos, sizeof(nuevoEstudiante.apellidos), stdin);
	strtok(nuevoEstudiante.apellidos, "\n");

	printf("Ingrese su matricula: ");
	fgets(nuevoEstudiante.matricula, sizeof(nuevoEstudiante.matricula), stdin);
	strtok(nuevoEstudiante.matricula, "\n");

	printf("Ingrese su usuario: ");
	fgets(nuevoEstudiante.usuario, sizeof(nuevoEstudiante.usuario), stdin);
	strtok(nuevoEstudiante.usuario, "\n");

	if (verificarUnicidadEstudiante(nuevoEstudiante.matricula, nuevoEstudiante.usuario)) {
        	printf("Error: Matrícula o usuario ya existente.\n");
        	fclose(archivo);
        	return;
    	}

	printf("Ingrese clave: ");
	fgets(nuevoEstudiante.clave, sizeof(nuevoEstudiante.clave), stdin);
	strtok(nuevoEstudiante.clave, "\n");

	strcpy(nuevoEstudiante.estado, "Activo");

	fprintf(archivo, "%s-%s-%s-%s-%s-%s\n", 
		nuevoEstudiante.nombres, nuevoEstudiante.apellidos, 
		nuevoEstudiante.matricula, nuevoEstudiante.usuario, 
		nuevoEstudiante.clave, nuevoEstudiante.estado);

	printf("Estudiante creado correctamente.\n");

	fclose(archivo);

}

void editarEstudiante() {
	char matricula[15];
	Estudiante estudiante;
	FILE *archivo = fopen("archivos/estudiantes.txt, "r+");
	FILE *temporal = fopen("archivos/temporal.txt", "w");

	if (!archivo || !temporal) {
		printf("Error al abrir los archivos.\n");
		return;
	}

	printf("Ingrese matrícula del estudiante a editar: ");
	fgets(matricula, sizeof(matricula), stdin);
	strtok(matricula, "\n");

	int encontrado = 0;

	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n",
                  estudiante.nombres, estudiante.apellidos, estudiante.matricula, 
                  estudiante.usuario, estudiante.clave, estudiante.estado) != EOF) {

        	if (strcmp(estudiante.matricula, matricula) == 0) {
			encontrado = 1;
			printf("Ingrese nueva clave: ");
			fgets(estudiante.clave, sizeof(estudiante.clave), stdin);
			strtok(estudiante.clave, "\n");

			printf("Cambiar estado (Activo/Inactivo): ");
			fgets(estudiante.estado, sizeof(estudiante.estado), stdin);
			strtok(estudiante.estado, "\n");
		}
		fprintf(temporal, "%s|%s|%s|%s|%s|%s\n", estudiante.nombres, estudiante.apellidos,
		estudiante.matricula, estudiante.usuario, estudiante.clave, estudiante.estado);
	}

	fclose(archivo);
	fclose(temporal);
	remove("archivos/estudiantes.txt");
	rename("archivos/temporal.txt", "archivos/estudiantes.txt");

	if (encontrado) {
		printf("Estudiante actualizado correctamente.\n");
	} else {
		printf("Estudiante no encontrado.\n");
	}
}

int verificarUnicidadEstudiante(const char *matricula, const char *usuario) {
	Estudiante estudiante;
	FILE *archivo = fopen("archivos/estudiantes.txt, "r");

	if (!archivo) return 0;

	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n",
                  estudiante.nombres, estudiante.apellidos, estudiante.matricula, 
                  estudiante.usuario, estudiante.clave, estudiante.estado) != EOF) {
		if (strcmp(estudiante.matricula, matricula) == 0 || strcmp(estudiante.usuario, usuario) == 0) {
			fclose(archivo);
			return 1;
		}
	}

	fclose(archivo);
	return 0;
}
