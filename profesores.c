#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "profesores.h"
#include "cursos.h"
#include "utilidades.h"

void cargarDatosProfesores(Profesor **profesores, int *cantidad, Materia *materias, int cantidadMaterias) {
    	FILE *archivo = fopen("archivos/profesores.txt", "r");
    	if (!archivo) {
        	printf("Error al abrir archivo de profesores.\n");
        	return;
    	}

    	*cantidad = 0;
    	*profesores = NULL;
    	Profesor temp;

    	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n", 
		temp.nombre, temp.apellidos, temp.cedula, temp.usuario, temp.clave, temp.estado, temp.materiasLista) != EOF) {

		temp.materiasLista = NULL;
		temp.cantidadMaterias = 0;

		char *materiaToken = strtok(temp.materiasLista, "/");
		while (materiaToken != NULL) {
			if (!verificarMateriaDuplicada(temp.materiasLista, temp.cantidadMaterias, materiaToken)) {
				temp.materiasLista = realloc(temp.materiasLista, (temp.cantidadMaterias + 1) * sizeof(char *));
				temp.materiasLista[temp.cantidadMaterias] = malloc(strlen(materiaToken) + 1);
				strcpy(temp.materiasLista[temp.cantidadMaterias], materiaToken);
				temp.cantidadMaterias++;
			}
			materiaToken = strtok(NULL, "/");
		}

		*profesores = realloc(*profesores, (*cantidad + 1) * sizeof(Profesor));
		(*profesores)[*cantidad] = temp;
		(*cantidad)++;
	}

	fclose(archivo);
}

void guardarDatosProfesores(Profesor *profesores, int cantidad) {
    	FILE *archivo = fopen("archivos/profesores.txt", "w");
    	if (!archivo) {
        	printf("Error al guardar archivo de profesores.\n");
        	return;
    	}

    	for (int i = 0; i < cantidad; i++) {
        	fprintf(archivo, "%s-%s-%s-%s-%s-%s", 
			profesores[i].nombre, profesores[i].apellidos, profesores[i].cedula, 
			profesores[i].usuario, profesores[i].clave, profesores[i].estado);

		for (int j = 0; j < profesores[i].cantidadMaterias; j++) {
			fprintf(archivo, "%s%s", profesores[i].materiasLista[j], 
				(j == profesores[i].cantidadMaterias - 1) ? "" : "/");
		}
		fprintf(archivo, "\n");
	}

    fclose(archivo);
}

void gestionarProfesores(Profesor **profesores, int *cantidad, Materia *materias, int cantidadMaterias) {
	int opcion;
	do {
        	printf("\n--- GESTIÓN DE PROFESORES ---\n");
        	printf("1. Crear Profesor\n");
        	printf("2. Editar Profesor\n");
        	printf("3. Mostrar Profesores\n");
        	printf("4. Volver al menú principal\n");
        	printf("Seleccione una opción: ");
        	scanf("%d", &opcion);
        	limpiarBuffer();

        	switch (opcion) {
            		case 1:
                		crearProfesor(profesores, cantidad);
                		break;
            		case 2:
                		editarProfesor(*profesores, *cantidad);
                		break;
            		case 3:
                		mostrarProfesores(*profesores, *cantidad);
                		break;
            		case 4:
                		printf("Volviendo al menú principal...\n");
                		break;
            		default:
                		printf("Opción inválida. Intente de nuevo.\n");
        	}
    	} while (opcion != 4);
}

void crearProfesor(Profesor **profesores, int *cantidad, Materia *materias, int cantidadMaterias) {
    	Profesor nuevoProfesor;

    	printf("Ingrese el nombre del profesor: ");
    	fgets(nuevoProfesor.nombre, sizeof(nuevoProfesor.nombre), stdin);
    	strtok(nuevoProfesor.nombre, "\n");

    	printf("Ingrese los apellidos del profesor: ");
    	fgets(nuevoProfesor.apellidos, sizeof(nuevoProfesor.apellidos), stdin);
    	strtok(nuevoProfesor.apellidos, "\n");

    	printf("Ingrese la C.C. del profesor: ");
    	fgets(nuevoProfesor.cedula, sizeof(nuevoProfesor.cc), stdin);
    	strtok(nuevoProfesor.cedula, "\n");

    	if (verificarUnicidadProfesor(*profesores, *cantidad, nuevoProfesor.cc, nuevoProfesor.usuario)) {
        	printf("Error: El profesor ya existe.\n");
        	return;
    	}

    	printf("Ingrese el usuario: ");
    	fgets(nuevoProfesor.usuario, sizeof(nuevoProfesor.usuario), stdin);
    	strtok(nuevoProfesor.usuario, "\n");

    	printf("Ingrese la clave: ");
    	fgets(nuevoProfesor.clave, sizeof(nuevoProfesor.clave), stdin);
    	strtok(nuevoProfesor.clave, "\n");

    	strcpy(nuevoProfesor.estado, "Activo");

    	nuevoProfesor.materiasLista = NULL;
    	nuevoProfesor.cantidadMaterias = 0;

    	int agregarMas;
    	do {
        	char codigoMateria[20];
        	printf("Ingrese el código de la materia a asignar (Ej: MAT001): ");
        	fgets(codigoMateria, sizeof(codigoMateria), stdin);
        	strtok(codigoMateria, "\n");

        	if (!verificarMateriaExistente(codigoMateria, materias, cantidadMaterias)) {
            		printf("Error: El código de materia no existe.\n");
        	} else if (verificarMateriaDuplicada(nuevoProfesor.materiasLista, nuevoProfesor.cantidadMaterias, codigoMateria)) {
            		printf("Error: El profesor ya tiene esta materia asignada.\n");
        	} else {
            		nuevoProfesor.materiasLista = realloc(nuevoProfesor.materiasLista, 
				(nuevoProfesor.cantidadMaterias + 1) * sizeof(char *));
            		nuevoProfesor.materiasLista[nuevoProfesor.cantidadMaterias] = strdup(codigoMateria);
            		nuevoProfesor.cantidadMaterias++;
            		printf("Materia asignada correctamente.\n");
        	}

        	printf("¿Desea agregar otra materia? (1: Sí / 0: No): ");
        	scanf("%d", &agregarMas);
        	limpiarBuffer();

    	} while (agregarMas == 1);

    	*profesores = realloc(*profesores, (*cantidad + 1) * sizeof(Profesor));
    	(*profesores)[*cantidad] = nuevoProfesor;
    	(*cantidad)++;

    	printf("Profesor creado exitosamente.\n");
}

void editarProfesor(Profesor *profesores, int cantidad, struct Curso *cursos, int cantidadCursos) {
    	char cedula[20];
    	printf("Ingrese la cédula del profesor a editar: ");
    	fgets(cedula, sizeof(cedula), stdin);
    	strtok(cedula, "\n");

    	for (int i = 0; i < cantidad; i++) {
        	if (strcmp(profesores[i].cedula, cedula) == 0) {
            		printf("Profesor encontrado: %s %s\n", profesores[i].nombre, profesores[i].apellidos);

            		int estaAsignado = 0;
            		for (int j = 0; j < cantidadCursos; j++) {
                		if (strcmp(cursos[j].profesorCedula, cedula) == 0) {
                    			estaAsignado = 1;
                    			break;
                		}
            		}

            		printf("Ingrese la nueva clave: ");
			fgets(profesores[i].clave, sizeof(profesores[i].clave), stdin);
			strtok(profesores[i].clave, "\n");

            		printf("Ingrese el nuevo estado (Activo/Inactivo): ");
            		char nuevoEstado[10];
            		fgets(nuevoEstado, sizeof(nuevoEstado), stdin);
            		strtok(nuevoEstado, "\n");

            		if (estaAsignado && strcmp(nuevoEstado, "Inactivo") == 0) {
                		printf("Error: El profesor está asignado a uno o más cursos y no puede ser inactivado.\n");
            		} else {
                		strcpy(profesores[i].estado, nuevoEstado);
                		printf("Profesor actualizado correctamente.\n");
            		}
            		return;
        	}
    	}
    	printf("Profesor no encontrado.\n");
}

void mostrarProfesores(Profesor *profesores, int cantidad) {
    	printf("\n--- LISTA DE PROFESORES ---\n");
    	for (int i = 0; i < cantidad; i++) {
        	printf("Nombre: %s %s - C.C.: %s - Usuario: %s - Estado: %s\n", 
			profesores[i].nombre, profesores[i].apellidos, profesores[i].cedula, 
			profesores[i].usuario, profesores[i].estado);
    	}
}

int verificarUnicidadProfesor(Profesor *profesores, int cantidad, const char *cedula, const char *usuario) {
    	for (int i = 0; i < cantidad; i++) {
        	if (strcmp(profesores[i].cedula, cedula) == 0 || strcmp(profesores[i].usuario, usuario) == 0) {
            		return 1;  
        	}
    	}
    	return 0;  
}

int verificarMateriaExistente(const char *codigoMateria, Materia *materias, int cantidadMaterias) {
    	for (int i = 0; i < cantidadMaterias; i++) {
        	if (strcmp(materias[i].codigo, codigoMateria) == 0) {
            		return 1;
        	}
    	}
    	return 0;
}

int verificarMateriaDuplicada(char **materiasLista, int cantidadMaterias, const char *materia) {
    	for (int i = 0; i < cantidadMaterias; i++) {
        	if (strcmp(materiasLista[i], materia) == 0) {
            		return 1;  
        	}
    	}
    	return 0;
}


void liberarMemoriaProfesores(Profesor *profesores, int cantidad) {
    	if (cantidad > 0 && profesores != NULL) {
        	for (int i = 0; i < cantidad; i++) {
            		if (profesores[i].materiasLista != NULL) {
                		for (int j = 0; j < profesores[i].cantidadMaterias; j++) {
                    			free(profesores[i].materiasLista[j]);
                		}
                		free(profesores[i].materiasLista);
            		}
        	}
        	free(profesores);
    	}
}
