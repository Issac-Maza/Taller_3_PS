#include <stdio.h>
#include <string.h>

typedef struct {
	char nombre[50];
	char codigo[10];
	char estado[10];
} Materia;

void gestionMaterias() {
	int opcion;
	printf("\n--- ADMINISTRACION DE MATERIAS ---\n");
	printf("1. Crear Materia\n");
	printf("2. Editar Materia\n");
	printf("Escoja una opción: ");
	scanf("%d", &opcion);

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
	FILE *archivo = fopen("archivos/materias.txt", "a");

	if(!archivo) {
		printf("Error al abrir o encontrar el archivo\n");
		return;
	}

	printf("Ingrese el nombre de la Materia: ");
	scanf("%s", nuevaMateria.nombre);

	printf("Ingrese el codigo de la Materia: ");
	scanf("%s", nuevaMateria.codigo);

	strcpy(nuevaMateria.estado, "Activo");

	fprintf(archivo, "%s-%s-%s\n", nuevaMateria.nombre, nuevaMateria.codigo, nuevaMateria.estado);
	fclose(archivo);

	printf("Materia creada exitosamente.\n");
}

void editarMateria() {
	char codigo[10];
	printf("Ingrese el codigo(unico) de la materia que quiere editar");
	scanf("%s", codigo);

	FILE *archivo = fopen("archivos/materias.txt", "r");
	FILE *temp = fopen("archivos/temp.txt", "w");

	if(!archivo || !temp){
		printf("Error al abrir o encontrar los archivos");
	}

	Materia materia;
	int encontrado = 0;

	while (fscanf(archivo, "%[^-]-%[^-]-%[^\n]\n", materia.nombre, materia.codigo, materia.estado) != EOF) {
        	if (strcmp(materia.codigo, codigo) == 0) {
            		encontrado = 1;
            		printf("Materia encontrada. Cambiar estado (Activo/Inactivo): ");
            		scanf("%s", materia.estado);
        	}
        	fprintf(temp, "%s-%s-%s\n", materia.nombre, materia.codigo, materia.estado);
    	}

	fclose(archivo);
	fclose(temp);

	remove("archivos/materias.txt");
	rename("archivos/temp.txt", "data/materias.txt");
}
