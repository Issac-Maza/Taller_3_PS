#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cursos.h"
#include "utilidades.h"

void gestionarCursos() {
	int opcion;
	printf("\n--- ADMINISTRAR DE CURSOS ---\n");
	printf("1. Crear curso\n");
	printf("2. Editar curso\n");
	printf("Escoja una opción: ");
	scanf("%d", &opcion);
	limpiarBuffer();

	switch(opcion) {
		case 1:
			crearCurso();
			break;
		case 2:
			editarCurso();
			break;
		default:
			printf("Opción inválida.\n");
			break;
	}
}

void crearCurso() {
	Curso nuevoCurso;
	FILE *archivo = fopen("archivos/cursos.txt", "a+");

	if (!archivo) {
		printf("Error al abrir el archivo de cursos.\n");
		return;
	}

	printf("Ingrese el código del curso: ");
	fgets(nuevoCurso.codigo, sizeof(nuevoCurso.codigo), stdin);
	strtok(nuevoCurso.codigo, "\n");

	if (verificarUnicidadCurso(nuevoCurso.codigo)) {
		printf("Error: El código del curso ya existe.\n");
		fclose(archivo);
		return;
	}

	printf("Ingrese el código de la materia: ");
	fgets(nuevoCurso.materia, sizeof(nuevoCurso.materia), stdin);
	strtok(nuevoCurso.materia, "\n");

	if (!verificarRelacionMaterias(nuevoCurso.materia)) {
		printf("Error: Materia no registrada.\n");
		fclose(archivo);
		return;
	}

	printf("Ingrese la C.C.(cedula) del profesor: ");
	fgets(nuevoCurso.profesor, sizeof(nuevoCurso.profesor), stdin);
	strtok(nuevoCurso.profesor, "\n");

	if (!verificarRelacionProfesor(nuevoCurso.profesor)) {
		printf("Error: Profesor no registrado.\n");
		fclose(archivo);
		return;
	}

	printf("Ingrese la fecha de inicio (DD/MM/AAAA): ");
	fgets(nuevoCurso.fechaInicio, sizeof(nuevoCurso.fechaInicio), stdin);
	strtok(nuevoCurso.fechaInicio, "\n");

	printf("Ingrese la fecha de fin (DD/MM/AAAA): ");
	fgets(nuevoCurso.fechaFin, sizeof(nuevoCurso.fechaFin), stdin);
	strtok(nuevoCurso.fechaFin, "\n");

	if (!validarFecha(nuevoCurso.fechaInicio) || !validarFecha(nuevoCurso.fechaFin)) {
		printf("Error: Formato de fecha incorrecto.\n");
		fclose(archivo);
		return;
	}

	if (strcmp(nuevoCurso.fechaInicio, nuevoCurso.fechaFin) >= 0) {
		printf("Error: La fecha de inicio debe ser anterior a la fecha de fin.\n");
		fclose(archivo);
		return;
	}

	printf("Ingrese matrículas de estudiantes (separadas por slash): ");
	fgets(nuevoCurso.listaEstudiantes, sizeof(nuevoCurso.listaEstudiantes), stdin);
	strtok(nuevoCurso.listaEstudiantes, "\n");

	fprintf(archivo, "%s-%s-%s-%s-%s-%s\n", nuevoCurso.codigo, nuevoCurso.materia, 
		nuevoCurso.profesor, nuevoCurso.fechaInicio, 
		nuevoCurso.fechaFin, nuevoCurso.listaEstudiantes);
	printf("Curso creado correctamente.\n");
	fclose(archivo);
}

void editarCurso() {
	char codigo[20];
	Curso curso;
	FILE *archivo = fopen("archivos/cursos.txt", "r+");
	FILE *temporal = fopen("data/temporal.txt", "w");

	if (!archivo || !temporal) {
		printf("Error al abrir los archivos.\n");
		return;
	}

	printf("Ingrese el código del curso a editar: ");
	fgets(codigo, sizeof(codigo), stdin);
	strtok(codigo, "\n");

	int encontrado = 0;
	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]\n", 
		curso.codigo, curso.materia, 
		curso.profesor, curso.fechaInicio, 
		curso.fechaFin, curso.listaEstudiantes) != EOF) {
		if (strcmp(curso.codigo, codigo) == 0) {
			encontrado = 1;
			printf("Ingrese nueva fecha de inicio (DD/MM/AAAA): ");
			fgets(curso.fechaInicio, sizeof(curso.fechaInicio), stdin);
			strtok(curso.fechaInicio, "\n");

			printf("Ingrese nueva fecha de fin (DD/MM/AAAA): ");
			fgets(curso.fechaFin, sizeof(curso.fechaFin), stdin);
			strtok(curso.fechaFin, "\n");
		}
		fprintf(temporal, "%s|%s|%s|%s|%s|%s\n", curso.codigo, curso.materia, curso.profesor, curso.fechaInicio, curso.fechaFin, curso.listaEstudiantes);
	}

	fclose(archivo);
	fclose(temporal);
	remove("archivos/cursos.txt");
	rename("data/temporal.txt", "archivos/cursos.txt");

	if (encontrado) {
		printf("Curso actualizado correctamente.\n");
	} else {
		printf("Curso no encontrado.\n");
	}
}

int verificarRelacionMaterias(const char *codigo) {
	Materia materia;
	FILE *archivo = fopen("archivos/materias.txt", "r");

    if (!archivo) return 0;

    while (fscanf(archivo, "%[^|]|%[^|]|%[^\n]\n",
                  materia.nombre, materia.codigo, materia.estado) != EOF) {
        if (strcmp(materia.codigo, codigo) == 0) {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

int verificarRelacionProfesor(const char *cc) {
    Profesor profesor;
    FILE *archivo = fopen("data/profesores.txt", "r");

    if (!archivo) return 0;

    while (fscanf(archivo, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  profesor.nombre, profesor.apellidos, profesor.cc, profesor.usuario, profesor.clave, profesor.estado, profesor.materias) != EOF) {
        if (strcmp(profesor.cc, cc) == 0) {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

int verificarRelacionEstudiantes(const char *matricula) {
    Estudiante estudiante;
    FILE *archivo = fopen("data/estudiantes.txt", "r");

    if (!archivo) return 0;

    while (fscanf(archivo, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  estudiante.nombres, estudiante.apellidos, estudiante.matricula, estudiante.usuario, estudiante.clave, estudiante.estado) != EOF) {
        if (strcmp(estudiante.matricula, matricula) == 0) {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}
