#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cursos.h"
#include "materias.h"
#include "profesores.h"
#include "utilidades.h"

void cargarDatosCursos(Curso **cursos, int *cantidad) {
    	FILE *archivo = fopen("archivos/cursos.txt", "r");
    	if (!archivo) {
        	printf("Error al abrir el archivo de cursos.\n");
        	return;
    	}

    	*cantidad = 0;
    	*cursos = NULL;
    	Curso temp;

    	while (fscanf(archivo, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^]\n", 
		temp.codigo, temp.materia, temp.profesorCedula, temp.fechaInicio, temp.fechaFin, temp.estudiantesLista[0]) != EOF) {

        	temp.cantidadEstudiantes = 0;

        	char *estudianteToken = strtok(temp.estudiantesLista[0], "/");
        	while (estudianteToken && temp.cantidadEstudiantes < MAX_ESTUDIANTES) {
            		strcpy(temp.estudiantesLista[temp.cantidadEstudiantes], estudianteToken);
            		temp.cantidadEstudiantes++;
            		estudianteToken = strtok(NULL, "/");
        	}

		*cursos = realloc(*cursos, (*cantidad + 1) * sizeof(Curso));
        	(*cursos)[*cantidad] = temp;
        	(*cantidad)++;
    	}
    	fclose(archivo);
}

void guardarDatosCursos(Curso *cursos, int cantidad) {
    	FILE *archivo = fopen("archivos/cursos.txt", "w");
    	if (!archivo) {
        	printf("Error al abrir el archivo de cursos para guardar.\n");
        	return;
    	}

    	for (int i = 0; i < cantidad; i++) {
        	fprintf(archivo, "%s-%s-%s-%s-%s-", 
			cursos[i].codigo, cursos[i].materia, cursos[i].profesorCedula, 
			cursos[i].fechaInicio, cursos[i].fechaFin);

        	for (int j = 0; j < cursos[i].cantidadEstudiantes; j++) {
            		fprintf(archivo, "%s%s", cursos[i].estudiantesLista[j], 
			j < cursos[i].cantidadEstudiantes - 1 ? "/" : "\n");
        	}
    	}
    	fclose(archivo);
}

void gestionarCursos(Curso **cursos, int *cantidad, Estudiante *estudiantes, int cantidadEstudiantes, 
		Materia *materias, int cantidadMaterias, Profesor *profesores, int cantidadProfesores) {
    	int opcion;
    	do {
        	printf("\n--- GESTIÓN DE CURSOS ---\n");
        	printf("1. Crear Curso\n");
        	printf("2. Editar Curso\n");
        	printf("3. Mostrar Cursos\n");
        	printf("4. Volver al menú principal\n");
        	printf("Seleccione una opción: ");
        	scanf("%d", &opcion);
        	limpiarBuffer();

        	switch (opcion) {
            		case 1:
                		crearCurso(cursos, cantidad, estudiantes, 
					cantidadEstudiantes, materias, cantidadMaterias, profesores, cantidadProfesores);
                	break;
            		case 2:
                		editarCurso(*cursos, *cantidad);
                		break;
            		case 3:
                		mostrarCursos(*cursos, *cantidad);
                		break;
            		case 4:
                		printf("Volviendo al menú principal...\n");
                		break;
            		default:
                		printf("Opción inválida. Intente de nuevo.\n");
        	}
    	} while (opcion != 4);
}

void crearCurso(Curso **cursos, int *cantidad, Estudiante *estudiantes, int cantidadEstudiantes, 
                Materia *materias, int cantidadMaterias, Profesor *profesores, int cantidadProfesores) {
    	Curso nuevoCurso;

    	printf("Ingrese el código del curso: ");
    	fgets(nuevoCurso.codigo, sizeof(nuevoCurso.codigo), stdin);
    	strtok(nuevoCurso.codigo, "\n");

    	if (verificarUnicidadCurso(nuevoCurso.codigo, *cursos, *cantidad)) {
        	printf("Error: El curso ya existe.\n");
        	return;
    	}

    	printf("Ingrese el código de la materia: ");
    	fgets(nuevoCurso.materia, sizeof(nuevoCurso.materia), stdin);
    	strtok(nuevoCurso.materia, "\n");

    	if (!verificarRelacionMaterias(nuevoCurso.materia, materias, cantidadMaterias)) {
        	printf("Error: Materia no encontrada.\n");
        	return;
    	}

    	printf("Ingrese la C.C.(CEDULA) del profesor: ");
    	fgets(nuevoCurso.profesorCedula, sizeof(nuevoCurso.profesorCedula), stdin);
    	strtok(nuevoCurso.profesorCedula, "\n");

    	if (!verificarRelacionProfesor(nuevoCurso.profesorCedula, profesores, cantidadProfesores)) {
        	printf("Error: Profesor no encontrado.\n");
        	return;
    	}

    	printf("Ingrese la fecha de inicio (DD/MM/AAAA): ");
    	fgets(nuevoCurso.fechaInicio, sizeof(nuevoCurso.fechaInicio), stdin);
    	strtok(nuevoCurso.fechaInicio, "\n");

    	printf("Ingrese la fecha de fin (DD/MM/AAAA): ");
    	fgets(nuevoCurso.fechaFin, sizeof(nuevoCurso.fechaFin), stdin);
    	strtok(nuevoCurso.fechaFin, "\n");

    	if (!validarFecha(nuevoCurso.fechaInicio) || !validarFecha(nuevoCurso.fechaFin) || strcmp(nuevoCurso.fechaInicio, nuevoCurso.fechaFin) >= 0) {
        	printf("Error: Fecha inválida.\n");
        	return;
    	}

    	nuevoCurso.cantidadEstudiantes = 0;

    	int agregarEstudiante;
    	do {
        	if (verificarMaxEstudiantes(nuevoCurso.cantidadEstudiantes)) {
            		printf("Se ha alcanzado el límite máximo de estudiantes.\n");
            		break;
        	}

        	char matricula[15];
        	printf("Ingrese la matrícula del estudiante: ");
        	fgets(matricula, sizeof(matricula), stdin);
        	strtok(matricula, "\n");

        	if (!verificarRelacionEstudiantes(matricula, estudiantes, cantidadEstudiantes)) {
            		printf("Error: Matrícula no encontrada.\n");
        	} else {
            		strcpy(nuevoCurso.estudiantesLista[nuevoCurso.cantidadEstudiantes], matricula);
            		nuevoCurso.cantidadEstudiantes++;
            		printf("Estudiante agregado correctamente.\n");
        	}

        	printf("¿Desea agregar otro estudiante? (1: Sí / 0: No): ");
        	scanf("%d", &agregarEstudiante);
        	limpiarBuffer();
    	} while (agregarEstudiante == 1);

    	*cursos = realloc(*cursos, (*cantidad + 1) * sizeof(Curso));
    	(*cursos)[*cantidad] = nuevoCurso;
    	(*cantidad)++;

    	printf("Curso creado exitosamente.\n");
}

void editarCurso(Curso *cursos, int cantidad) {
    	char codigo[20];

    	printf("Ingrese el código del curso a editar: ");
    	fgets(codigo, sizeof(codigo), stdin);
    	strtok(codigo, "\n");

    	for (int i = 0; i < cantidad; i++) {
        	if (strcmp(cursos[i].codigo, codigo) == 0) {
            		printf("Curso encontrado: %s\n", cursos[i].codigo);

            		printf("Ingrese la nueva fecha de inicio (DD/MM/AAAA): ");
            		fgets(cursos[i].fechaInicio, sizeof(cursos[i].fechaInicio), stdin);
            		strtok(cursos[i].fechaInicio, "\n");

            		printf("Ingrese la nueva fecha de fin (DD/MM/AAAA): ");
            		fgets(cursos[i].fechaFin, sizeof(cursos[i].fechaFin), stdin);
            		strtok(cursos[i].fechaFin, "\n");

            		if (!validarFecha(cursos[i].fechaInicio) || !validarFecha(cursos[i].fechaFin) || 
				strcmp(cursos[i].fechaInicio, cursos[i].fechaFin) >= 0) {
                		printf("Error: Fechas inválidas.\n");
                		return;
            		}
            		printf("Curso actualizado correctamente.\n");
            		return;
        	}
    	}
    	printf("Error: Curso no encontrado.\n");
}

void mostrarCursos(Curso *cursos, int cantidad) {
    	printf("\n--- LISTA DE CURSOS ---\n");
    	for (int i = 0; i < cantidad; i++) {
        	printf("Código: %s - Materia: %s - Profesor: %s - Fecha Inicio: %s - Fecha Fin: %s\n", 
			cursos[i].codigo, cursos[i].materia, cursos[i].profesor, cursos[i].fechaInicio, cursos[i].fechaFin);

        	printf("Estudiantes Inscritos: ");
        	for (int j = 0; j < cursos[i].cantidadEstudiantes; j++) {
            		printf("%s%s", cursos[i].estudiantesLista[j], j < 
				cursos[i].cantidadEstudiantes - 1 ? ", " : "\n");
        	}
    	}
}

void liberarMemoriaCursos(Curso *cursos, int cantidad) {
	if (cantidad > 0 && cursos != NULL) {
		for (int i = 0; i < cantidad; i++) {
			if (cursos[i].estudiantesLista != NULL) {
				for (int j = 0; j < cursos[i].cantidadEstudiantes; j++) {
					free(cursos[i].estudiantesLista[j]);
				}
				free(cursos[i].estudiantesLista);
			}
		}
		free(cursos);
	}
}

int verificarUnicidadCurso(const char *codigo, Curso *cursos, int cantidad) {
    	for (int i = 0; i < cantidad; i++) {
        	if (strcmp(cursos[i].codigo, codigo) == 0) {
            		return 1;
        	}
    	}
    	return 0;
}


int verificarRelacionMaterias(const char *codigo, Materia *materias, int cantidad) {
    	for (int i = 0; i < cantidad; i++) {
        	if (strcmp(materias[i].codigo, codigo) == 0) {
            		return 1;
        	}
    	}
    	return 0;
}

int verificarRelacionProfesor(const char *cc, Profesor *profesores, int cantidad) {
    	for (int i = 0; i < cantidad; i++) {
        	if (strcmp(profesores[i].cc, cc) == 0) {
            		return 1;
        	}
    	}
    	return 0;
}

int verificarRelacionEstudiantes(const char *matricula, Estudiante *estudiantes, int cantidad) {
    	for (int i = 0; i < cantidad; i++) {
        	if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            		return 1;
        	}
    	}
    	return 0;
}

int verificarCursosAsignados(const Curso *cursos, int cantidadCursos, const char *codigo) {
    	for (int i = 0; i < cantidadCursos; i++) {
        	if (strcmp(cursos[i].codigo, codigo) == 0) {
            		return 1;
        	}
    	}
    	return 0;
}

int verificarMaxEstudiantes(int cantidadEstudiantes) {
    	return cantidadEstudiantes >= 30;
}
