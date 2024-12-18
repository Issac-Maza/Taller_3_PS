#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "profesores.h"
#include "utils.h"

void gestionarProfesores() {
	int opcion;
	printf("\n--- GESTIÓN DE PROFESORES ---\n");
	printf("1. Crear Profesor\n");
	printf("2. Editar Profesor\n");
	printf("Seleccione una opción: ");
	scanf("%d", &opcion);
	limpiarBuffer();

	switch(opcion) {
 		case 1:
			crearProfesor();
			break;
        	case 2:
			editarProfesor();
			break;
		default:
			printf("Opción inválida.\n");
			break;
	}
}

void crearProfesor() {
	Profesor nuevoProfesor;
	FILE *archivo = fopen("archivos/profesores.txt", "a+");

	if (!archivo) {
		printf("Error al abrir el archivo de profesores.\n");
		return;
	}

	printf("Ingrese los nombres: ");
	fgets(nuevoProfesor.nombre, sizeof(nuevoProfesor.nombre), stdin);
	strtok(nuevoProfesor.nombre, "\n");

	printf("Ingrese los apellidos: ");
	fgets(nuevoProfesor.apellidos, sizeof(nuevoProfesor.apellidos), stdin);
	strtok(nuevoProfesor.apellidos, "\n");

	printf("Ingrese la cedula C.C: ");
	fgets(nuevoProfesor.cc, sizeof(nuevoProfesor.cc), stdin);
	strtok(nuevoProfesor.cc, "\n");

	printf("Ingrese el nombre de usuario: ");
	fgets(nuevoProfesor.usuario, sizeof(nuevoProfesor.usuario), stdin);
	strtok(nuevoProfesor.usuario, "\n");

	if (verificarUnicidadProfesor(nuevoProfesor.cc, nuevoProfesor.usuario)) {
		printf("Error: C.C.(cedula) o usuario ya existente.\n");
		fclose(archivo);
		return;
	}

	printf("Ingrese la clave: ");
	fgets(nuevoProfesor.clave, sizeof(nuevoProfesor.clave), stdin);
	strtok(nuevoProfesor.clave, "\n");

	printf("Ingrese materias que puede dictar (códigos separados por comas): ");
	fgets(nuevoProfesor.materias, sizeof(nuevoProfesor.materias), stdin);
	strtok(nuevoProfesor.materias, "\n");

	strcpy(nuevoProfesor.estado, "Activo");

	fprintf(archivo, "%s-%s-%s-%s-%s-%s-%s\n", nuevoProfesor.nombre, nuevoProfesor.apellidos,
		nuevoProfesor.cc, nuevoProfesor.usuario, nuevoProfesor.clave, nuevoProfesor.estado, 
		nuevoProfesor.materias);

	printf("Profesor creado correctamente.\n");
	fclose(archivo);
}

void editarProfesor() {
	char cc[15];
	Profesor profesor;
	FILE *archivo = fopen("archivos/profesores.txt", "r+");
	FILE *temporal = fopen("archivos/temporal.txt", "w");

	if (!archivo || !temporal) {
		printf("Error al abrir los archivos.\n");
		return;
	}

	printf("Ingrese la C.C. del profesor a editar: ");
	fgets(cc, sizeof(cc), stdin);
	strtok(cc, "\n");

	int encontrado = 0;
	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n",
		profesor.nombre, profesor.apellidos, profesor.cc, profesor.usuario, profesor.clave,
		 profesor.estado, profesor.materias) != EOF) {

		if (strcmp(profesor.cc, cc) == 0) {
			encontrado = 1;
			printf("Ingrese la nueva clave: ");
			fgets(profesor.clave, sizeof(profesor.clave), stdin);
			strtok(profesor.clave, "\n");

			printf("Cambiar estado (Activo/Inactivo): ");
			fgets(profesor.estado, sizeof(profesor.estado), stdin);
			strtok(profesor.estado, "\n");
		}
		fprintf(temporal, "%s-%s-%s-%s-%s-%s-%s\n", profesor.nombre, profesor.apellidos,
		 profesor.cc, profesor.usuario, profesor.clave, profesor.estado, profesor.materias);
	}

	fclose(archivo);
	fclose(temporal);
	remove("archivos/profesores.txt");
	rename("archivos/temporal.txt", "archivos/profesores.txt");

	if (encontrado) {
		printf("Profesor actualizado correctamente.\n");
	} else {
		printf("Profesor no encontrado.\n");
	}
}

int verificarUnicidadProfesor(const char *cc, const char *usuario) {
	Profesor profesor;
	FILE *archivo = fopen("archivos/profesores.txt", "r");

	if (!archivo) {
		return 0;
	}

	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n",
		profesor.nombre, profesor.apellidos, profesor.cc, profesor.usuario,
		 profesor.clave, profesor.estado, profesor.materias) != EOF) {
		if (strcmp(profesor.cc, cc) == 0 || strcmp(profesor.usuario, usuario) == 0) {
			fclose(archivo);
			return 1;
		}
	}

	fclose(archivo);
	return 0;
}

