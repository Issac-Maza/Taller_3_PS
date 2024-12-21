#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudiantes.h"


Estudiante *estudiantes = NULL;
int totalEstudiantes = 0;
int capacidadEstudiantes = 0;


void inicializarEstudiantes() {
    FILE *archivo = fopen("estudiante.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo de estudiantes. Creando lista vacía.\n");
        return;
    }

    capacidadEstudiantes = 10;
    estudiantes = (Estudiante *)malloc(capacidadEstudiantes * sizeof(Estudiante));
    if (!estudiantes) {
        printf("Error al asignar memoria para los estudiantes.\n");
        fclose(archivo);
        return;
    }

    while (fscanf(archivo, "%49[^-]-%49[^-]-%14[^-]-%29[^-]-%19[^-]-%d\n",
                  estudiantes[totalEstudiantes].nombres,
                  estudiantes[totalEstudiantes].apellidos,
                  estudiantes[totalEstudiantes].matricula,
                  estudiantes[totalEstudiantes].usuario,
                  estudiantes[totalEstudiantes].clave,
                  (int *)&estudiantes[totalEstudiantes].estado) == 6) {
        totalEstudiantes++;

        if (totalEstudiantes >= capacidadEstudiantes) {
            capacidadEstudiantes *= 2;
            Estudiante *tmp = realloc(estudiantes, capacidadEstudiantes * sizeof(Estudiante));
            if (!tmp) {
                printf("Error al ampliar el arreglo de estudiantes.\n");
                free(estudiantes);
                fclose(archivo);
                exit(EXIT_FAILURE); // Salida segura en caso de error
            }
            estudiantes = tmp;
        }
    }

    fclose(archivo);
    printf("Estudiantes cargados con éxito.\n");
}



void guardarEstudiantes() {
    FILE *archivo = fopen("estudiante.txt", "w");
    if (!archivo) {
        printf("No se pudo abrir el archivo para guardar los estudiantes.\n");
        return;
    }

    for (int i = 0; i < totalEstudiantes; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s-%d\n",
                estudiantes[i].nombres, estudiantes[i].apellidos,
                estudiantes[i].matricula, estudiantes[i].usuario,
                estudiantes[i].clave, estudiantes[i].estado);
    }

    fclose(archivo);
    printf("Estudiantes guardados con éxito.\n");
}


bool validarMatriculaUnica(const char *matricula) {
    for (int i = 0; i < totalEstudiantes; i++) {
        if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            return false;
        }
    }
    return true;
}


bool validarUsuarioUnico(const char *usuario) {
    for (int i = 0; i < totalEstudiantes; i++) {
        if (strcmp(estudiantes[i].usuario, usuario) == 0) {
            return false;
        }
    }
    return true;
}


void crearEstudiante() {
    Estudiante nuevoEstudiante;

    printf("Ingrese los nombres del estudiante: ");
    scanf(" %49[^\n]", nuevoEstudiante.nombres);

    printf("Ingrese los apellidos del estudiante: ");
    scanf(" %49[^\n]", nuevoEstudiante.apellidos);

    do {
        printf("Ingrese la matrícula del estudiante (única): ");
        scanf(" %14s", nuevoEstudiante.matricula);

        if (!validarMatriculaUnica(nuevoEstudiante.matricula)) {
            printf("La matrícula ya existe. Intente nuevamente.\n");
        }
    } while (!validarMatriculaUnica(nuevoEstudiante.matricula));

    do {
        printf("Ingrese el usuario del estudiante (único): ");
        scanf(" %29s", nuevoEstudiante.usuario);

        if (!validarUsuarioUnico(nuevoEstudiante.usuario)) {
            printf("El usuario ya existe. Intente nuevamente.\n");
        }
    } while (!validarUsuarioUnico(nuevoEstudiante.usuario));

    printf("Ingrese la clave del estudiante: ");
    scanf(" %19s", nuevoEstudiante.clave);

    nuevoEstudiante.estado = true;

    if (totalEstudiantes >= capacidadEstudiantes) {
        capacidadEstudiantes *= 2;
        Estudiante *tmp = realloc(estudiantes, capacidadEstudiantes * sizeof(Estudiante));
        if (!tmp) {
            printf("Error al ampliar el arreglo de estudiantes.\n");
            free(estudiantes);
            exit(EXIT_FAILURE); // Salida segura
        }
        estudiantes = tmp;
    }

    estudiantes[totalEstudiantes++] = nuevoEstudiante;
    printf("Estudiante creado con éxito.\n");
}



void editarEstudiante() {
    char matricula[15];
    printf("Ingrese la matrícula del estudiante que desea editar: ");
    scanf(" %14s", matricula);

    for (int i = 0; i < totalEstudiantes; i++) {
        if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            printf("Estudiante encontrado: %s %s (%s)\n", estudiantes[i].nombres,
                   estudiantes[i].apellidos, estudiantes[i].matricula);
            printf("Estado actual: %s\n", estudiantes[i].estado ? "Activo" : "Inactivo");

            printf("Ingrese la nueva clave del estudiante: ");
            scanf(" %19s", estudiantes[i].clave);

            int nuevoEstado;
            printf("Ingrese el nuevo estado (1 = Activo, 0 = Inactivo): ");
            scanf("%d", &nuevoEstado);

            
            if (nuevoEstado == 0) {
                printf("Verificando cursos asociados... (implementación pendiente)\n");
            }

            estudiantes[i].estado = nuevoEstado;
            printf("Estudiante editado con éxito.\n");
            return;
        }
    }

    printf("No se encontró un estudiante con esa matrícula.\n");
}


void listarEstudiantes() {
    printf("Listado de Estudiantes:\n");
    for (int i = 0; i < totalEstudiantes; i++) {
        printf("%s %s - %s - %s - %s\n",
               estudiantes[i].nombres, estudiantes[i].apellidos,
               estudiantes[i].matricula, estudiantes[i].usuario,
               estudiantes[i].estado ? "Activo" : "Inactivo");
    }
}


void liberarEstudiantes() {
    if (estudiantes) {
        free(estudiantes);
        estudiantes = NULL;
    }
    totalEstudiantes = 0;
    capacidadEstudiantes = 0;
}

