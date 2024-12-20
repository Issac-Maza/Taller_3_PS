#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "materias.h"
#include "cursos.h"
#include "utilidades.h"

void cargarDatosMaterias(Materia **materias, int *cantidad) {
	FILE *archivo = fopen("archivos/materias.txt", "r");
	if (!archivo) {
		printf("Error al abrir el archivo de materias.\n");
		return;
	}

	*cantidad = 0;
	*materias = NULL;
	Materia temp;

	while (fscanf(archivo, "%[^-]-%[^-]-%[^]\n", temp.codigo, temp.nombre, temp.estado) != EOF) {
		*materias = realloc(*materias, (*cantidad + 1) * sizeof(Materia));
		(*materias)[*cantidad] = temp;
		(*cantidad)++;
	}
	fclose(archivo);
}

void guardarDatosMaterias(Materia *materias, int cantidad) {
	FILE *archivo = fopen("archivos/materias.txt", "w");
	if (!archivo) {
		printf("Error al abrir el archivo de materias para guardar.\n");
		return;
	}

	for (int i = 0; i < cantidad; i++) {
		fprintf(archivo, "%s-%s-%s\n", materias[i].codigo, materias[i].nombre, materias[i].estado);
	}
	fclose(archivo);
}

void gestionMaterias(Materia **materias, int *cantidad) {
	int opcion;
	do {
		printf("\n--- GESTIÓN DE MATERIAS ---\n");
        	printf("1. Crear Materia\n");
        	printf("2. Editar Materia\n");
        	printf("3. Mostrar Materias\n");
        	printf("4. Volver al menú principal\n");
        	printf("Seleccione una opción: ");
        	scanf("%d", &opcion);
		limpiarBuffer();

		switch (opcion) {
			case 1:
				crearMateria(materias, cantidad);
				break;
			case 2:
				editarMateria(*materias, *cantidad);
				break;
			case 3:
				mostrarMaterias(*materias, *cantidad);
				break;
			case 4:
                		printf("Volviendo al menú principal...\n");
                		break;
            		default:
                		printf("Opción inválida. Intente de nuevo.\n");
        	}
	} while (opcion != 4)
}

void crearMateria(Materia **materias, int *cantidad) {
	Materia nuevaMateria;

    	printf("Ingrese el código de la materia: ");
    	fgets(nuevaMateria.codigo, sizeof(

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

void liberarMemoriaMaterias(Materia *materias, int cantidad) {
	if (cantidad > 0 && materias != NULL) {
		free(materias);
	}
}
