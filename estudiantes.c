#include <stdio.h>
#include <string.h>

typedef struct {
	char nombres[100];
	char apellidos[100];
	char matricula[15];
	char usuario[50];
	char clave[50];
	char estado[10];
} Estudiante;

void gestionarEstudiantes() {
	int opcion;
	printf("\n----ADMINISTRACION DE ESTUDIANTES----\n");
	printf("1. Crear un estudiante\n");
	printf("2. Editar datos de un estudiante\n");
	printf("Escoja una opcion: ");
	scanf("%d", &opcion);

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
	FILE *archivo = fopen("archivos/estudiantes.txt", "a");

	if (!archivo) {
		printf("Error al abrir el archivo.\n");
		return;
	}

	printf("Ingrese sus nombres: ");
	scanf("%s", nuevoEstudiante.nombres);

	printf("Ingrese sus apellidos: ");
	scanf("%s", nuevoEstudiante.apellidos);

	printf("Ingrese Matrícula: ");
	scanf("%s", nuevoEstudiante.matricula);

	printf("Ingrese Usuario: ");
	scanf("%s", nuevoEstudiante.usuario);

	printf("Ingrese Clave: ");
	scanf("%s", nuevoEstudiante.clave);

	strcpy(nuevoEstudiante.estado, "Activo");

	fprintf(archivo, "%s-%s-%s-%s-%s-%s\n", 
		nuevoEstudiante.nombres, nuevoEstudiante.apellidos, 
		nuevoEstudiante.matricula, nuevoEstudiante.usuario, 
		nuevoEstudiante.clave, nuevoEstudiante.estado);
	fclose(archivo);

	printf("Estudiante creado exitosamente.\n");
}
