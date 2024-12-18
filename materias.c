#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "materias.h"
#include "utilidades.h"

void gestionMaterias() {
	int opcion;
	printf("\n--- ADMINISTRACION DE MATERIAS ---\n");
	printf("1. Crear Materia\n");
	printf("2. Editar Materia\n");
	printf("Escoja una opción: ");
	scanf("%d", &opcion);
	limpiarBuffer();

	switch(opcion) {
		case 1:
			crearMateria();
			break;
		case 2:
			editarMateria();
			break;
		deafult:
			printf("Opcion no valida\n");
			break;
	}
}

void crearMateria() {
	Materia newMateria;
	FILE *archivo = fopen("archivos/materias.txt", "a+");

	if(!archivo) {
		printf("Error al abrir o encontrar el archivo\n");
		return;
	}

	printf("Ingrese nombre de la materia: ");
	fgets(newMateria.nombre, sizeof(newMateria.nombre), stdin);
	strtok(newMateria.nombre, "\n");

	printf("Ingrese el codigo de la Materia: ");
	fgets(newMateria.codigo, sizeof(newMateria.codigo), stdin);
	strtok(newMateria.codigo, "\n");

	if (verificarUnicidadMateria(newMateria.codigo)) {
       		printf("Error: El código de la materia ya existe.\n");
        	fclose(archivo);
        	return;
	}

	strcpy(nuevaMateria.estado, "Activo");

	fprintf(archivo, "%s-%s-%s\n", nuevaMateria.nombre, nuevaMateria.codigo, nuevaMateria.estado);
	fclose(archivo);

	printf("Materia creada exitosamente.\n");
}

void editarMateria() {
	char codigo[20];
	printf("Ingrese el codigo(unico) de la materia que quiere editar");
	fgets(codigo, sizeof(codigo), stdin);
	strtok(codigo, "\n");

	FILE *archivo = fopen("archivos/materias.txt", "r+");
	FILE *temporal = fopen("archivos/temporal.txt", "w+");

	if(!archivo || !temporal){
		printf("Error al abrir o encontrar los archivos");
		return;
	}

	Materia materia;
	int encontrado = 0;

	while (fscanf(archivo, "%[^-]-%[^-]-%[^\n]\n", materia.nombre, materia.codigo, materia.estado) != EOF) {
        	if (strcmp(materia.codigo, codigo) == 0) {
            		encontrado = 1;
            		printf("Materia encontrada. Cambiar estado (Activo/Inactivo): ");
            		ffgets(materia.estado, sizeof(materia.estado), stdin);
			strtok(materia.estado, "\n");
        	}
        	fprintf(temp, "%s-%s-%s\n", materia.nombre, materia.codigo, materia.estado);
    	}

	fclose(archivo);
	fclose(temp);

	remove("archivos/materias.txt");
	rename("archivos/temporal.txt", "archivos/materias.txt");

	if(encontrado) {
		printf("La materia se ha actualizado con exito.\n");
	} else {
		printf("Materia no encontrada.\n");
	}
}

int verificarUnicidadMateria(const char *codigo) {
	Materia materia;
	FILE *archivo = fopen("archivos/materias.txt", "r");

	if (!archivo) {
		return 0;
	}

	while (fscanf(archivo, "%[^-]-%[^-]-%[^\n]\n",
		materia.nombre, materia.codigo, materia.estado) != EOF) {
		if (strcmp(materia.codigo, codigo) == 0) {
			fclose(archivo);
			return 1;
		}
	}

	fclose(archivo);
	return 0;
}
