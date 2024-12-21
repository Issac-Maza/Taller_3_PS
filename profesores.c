#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "profesores.h"

// Inicialización de variables globales
Profesor *profesores = NULL;
int totalProfesores = 0;
int capacidadProfesores = 0;

// Inicializa los profesores leyendo de un archivo
void inicializarProfesores() {
    FILE *archivo = fopen("profesor.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo de profesores. Creando lista vacía.\n");
        return;
    }

    // Asignar una capacidad inicial al arreglo dinámico
    capacidadProfesores = 10;
    profesores = (Profesor *)malloc(capacidadProfesores * sizeof(Profesor));
    if (!profesores) {
        printf("Error al asignar memoria para los profesores.\n");
        fclose(archivo);
        return;
    }

    // Leer los profesores del archivo
    while (fscanf(archivo, "%49[^-]-%49[^-]-%14[^-]-%29[^-]-%19[^-]-%d-%99[^\n]\n",
                  profesores[totalProfesores].nombres,
                  profesores[totalProfesores].apellidos,
                  profesores[totalProfesores].cedula,
                  profesores[totalProfesores].usuario,
                  profesores[totalProfesores].clave,
                  (int *)&profesores[totalProfesores].estado,
                  profesores[totalProfesores].materias) == 7) {
        totalProfesores++;

        // Ampliar la capacidad del arreglo si es necesario
        if (totalProfesores >= capacidadProfesores) {
            capacidadProfesores *= 2;
            profesores = (Profesor *)realloc(profesores, capacidadProfesores * sizeof(Profesor));
            if (!profesores) {
                printf("Error al ampliar el arreglo de profesores.\n");
                fclose(archivo);
                return;
            }
        }
    }

    fclose(archivo);
    printf("Profesores cargados con éxito.\n");
}

// Guarda los profesores en un archivo
void guardarProfesores() {
    FILE *archivo = fopen("profesor.txt", "w");
    if (!archivo) {
        printf("No se pudo abrir el archivo para guardar los profesores.\n");
        return;
    }

    for (int i = 0; i < totalProfesores; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s-%d-%s\n",
                profesores[i].nombres, profesores[i].apellidos,
                profesores[i].cedula, profesores[i].usuario,
                profesores[i].clave, profesores[i].estado,
                profesores[i].materias);
    }

    fclose(archivo);
    printf("Profesores guardados con éxito.\n");
}

// Verifica que la cédula sea única
bool validarCedulaUnica(const char *cedula) {
    for (int i = 0; i < totalProfesores; i++) {
        if (strcmp(profesores[i].cedula, cedula) == 0) {
            return false;
        }
    }
    return true;
}

// Verifica que el usuario sea único
bool validarUsuarioUnicoProfesor(const char *usuario) {
    for (int i = 0; i < totalProfesores; i++) {
        if (strcmp(profesores[i].usuario, usuario) == 0) {
            return false;
        }
    }
    return true;
}

// Agrega un nuevo profesor
void crearProfesor() {
    Profesor nuevoProfesor;

    printf("Ingrese los nombres del profesor: ");
    scanf(" %49[^\n]", nuevoProfesor.nombres);

    printf("Ingrese los apellidos del profesor: ");
    scanf(" %49[^\n]", nuevoProfesor.apellidos);

    do {
        printf("Ingrese la cédula del profesor (única): ");
        scanf(" %14s", nuevoProfesor.cedula);

        if (!validarCedulaUnica(nuevoProfesor.cedula)) {
            printf("La cédula ya existe. Intente nuevamente.\n");
        }
    } while (!validarCedulaUnica(nuevoProfesor.cedula));

    do {
        printf("Ingrese el usuario del profesor (único): ");
        scanf(" %29s", nuevoProfesor.usuario);

        if (!validarUsuarioUnicoProfesor(nuevoProfesor.usuario)) {
            printf("El usuario ya existe. Intente nuevamente.\n");
        }
    } while (!validarUsuarioUnicoProfesor(nuevoProfesor.usuario));

    printf("Ingrese la clave del profesor: ");
    scanf(" %19s", nuevoProfesor.clave);

    printf("Ingrese los códigos de materias que puede dictar (separados por '/'): ");
    scanf(" %99[^\n]", nuevoProfesor.materias);

    nuevoProfesor.estado = true;

    // Ampliar la capacidad del arreglo si es necesario
    if (totalProfesores >= capacidadProfesores) {
        capacidadProfesores *= 2;
        profesores = (Profesor *)realloc(profesores, capacidadProfesores * sizeof(Profesor));
        if (!profesores) {
            printf("Error al ampliar el arreglo de profesores.\n");
            return;
        }
    }

    profesores[totalProfesores++] = nuevoProfesor;
    printf("Profesor creado con éxito.\n");
}

// Edita un profesor existente
void editarProfesor() {
    char cedula[15];
    printf("Ingrese la cédula del profesor que desea editar: ");
    scanf(" %14s", cedula);

    for (int i = 0; i < totalProfesores; i++) {
        if (strcmp(profesores[i].cedula, cedula) == 0) {
            printf("Profesor encontrado: %s %s (%s)\n", profesores[i].nombres,
                   profesores[i].apellidos, profesores[i].cedula);
            printf("Estado actual: %s\n", profesores[i].estado ? "Activo" : "Inactivo");

            printf("Ingrese la nueva clave del profesor: ");
            scanf(" %19s", profesores[i].clave);

            int nuevoEstado;
            printf("Ingrese el nuevo estado (1 = Activo, 0 = Inactivo): ");
            scanf("%d", &nuevoEstado);

            profesores[i].estado = nuevoEstado;
            printf("Profesor editado con éxito.\n");
            return;
        }
    }

    printf("No se encontró un profesor con esa cédula.\n");
}

// Lista todos los profesores
void listarProfesores() {
    printf("Listado de Profesores:\n");
    for (int i = 0; i < totalProfesores; i++) {
        printf("%s %s - %s - %s - %s - %s\n",
               profesores[i].nombres, profesores[i].apellidos,
               profesores[i].cedula, profesores[i].usuario,
               profesores[i].materias, profesores[i].estado ? "Activo" : "Inactivo");
    }
}

// Libera la memoria dinámica utilizada por el arreglo
void liberarProfesores() {
    free(profesores);
    profesores = NULL;
    totalProfesores = 0;
    capacidadProfesores = 0;
}

