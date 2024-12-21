#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cursos.h"


Curso *cursos = NULL;
int totalCursos = 0;
int capacidadCursos = 0;

bool validarFormatoFecha(const char *fecha) {
    if (strlen(fecha) != 10) return false;

    if (!isdigit(fecha[0]) || !isdigit(fecha[1]) || fecha[2] != '/' ||
        !isdigit(fecha[3]) || !isdigit(fecha[4]) || fecha[5] != '/' ||
        !isdigit(fecha[6]) || !isdigit(fecha[7]) || !isdigit(fecha[8]) || !isdigit(fecha[9])) {
        return false;
    }

    int dia = (fecha[0] - '0') * 10 + (fecha[1] - '0');
    int mes = (fecha[3] - '0') * 10 + (fecha[4] - '0');
    int anio = (fecha[6] - '0') * 1000 + (fecha[7] - '0') * 100 + (fecha[8] - '0') * 10 + (fecha[9] - '0');

    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;

    // Validar meses con menos de 31 días
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return false;

    // Validar febrero
    if (mes == 2) {
        bool bisiesto = (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
        if (dia > (bisiesto ? 29 : 28)) return false;
    }

    return true;
}



void inicializarCursos() {
    FILE *archivo = fopen("curso.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo de cursos. Creando lista vacía.\n");
        return;
    }

    capacidadCursos = 10;
    cursos = (Curso *)malloc(capacidadCursos * sizeof(Curso));
    if (!cursos) {
        printf("Error al asignar memoria para los cursos.\n");
        fclose(archivo);
        return;
    }

    while (fscanf(archivo, "%9[^-]-%9[^-]-%14[^-]-%10[^-]-%10[^-]-%299[^\n]\n",
                  cursos[totalCursos].codigoCurso,
                  cursos[totalCursos].codigoMateria,
                  cursos[totalCursos].cedulaProfesor,
                  cursos[totalCursos].fechaInicio,
                  cursos[totalCursos].fechaFin,
                  cursos[totalCursos].estudiantes) == 6) {
        if (!validarFormatoFecha(cursos[totalCursos].fechaInicio) ||
            !validarFormatoFecha(cursos[totalCursos].fechaFin)) {
            printf("Formato de fecha inválido en curso %s. Se omitirá este curso.\n",
                   cursos[totalCursos].codigoCurso);
            continue;
        }

        totalCursos++;

        if (totalCursos >= capacidadCursos) {
            capacidadCursos *= 2;
            Curso *tmp = realloc(cursos, capacidadCursos * sizeof(Curso));
            if (!tmp) {
                printf("Error al ampliar el arreglo de cursos.\n");
                free(cursos);
                fclose(archivo);
                exit(EXIT_FAILURE);
            }
            cursos = tmp;
        }
    }

    fclose(archivo);
    printf("Cursos cargados con éxito.\n");
}



void guardarCursos() {
    FILE *archivo = fopen("curso.txt", "w");
    if (!archivo) {
        printf("No se pudo abrir el archivo para guardar los cursos.\n");
        return;
    }

    for (int i = 0; i < totalCursos; i++) {
        fprintf(archivo, "%s-%s-%s-%s-%s-%s\n",
                cursos[i].codigoCurso, cursos[i].codigoMateria,
                cursos[i].cedulaProfesor, cursos[i].fechaInicio,
                cursos[i].fechaFin, cursos[i].estudiantes);
    }

    fclose(archivo);
    printf("Cursos guardados con éxito.\n");
}


bool validarCodigoCursoUnico(const char *codigoCurso) {
    for (int i = 0; i < totalCursos; i++) {
        if (strcmp(cursos[i].codigoCurso, codigoCurso) == 0) {
            return false;
        }
    }
    return true;
}

void crearCurso() {
    Curso nuevoCurso;

    do {
        printf("Ingrese el código del curso (único): ");
        scanf(" %9s", nuevoCurso.codigoCurso);

        if (!validarCodigoCursoUnico(nuevoCurso.codigoCurso)) {
            printf("El código ya existe. Intente nuevamente.\n");
        }
    } while (!validarCodigoCursoUnico(nuevoCurso.codigoCurso));

    printf("Ingrese el código de la materia asociada: ");
    scanf(" %9s", nuevoCurso.codigoMateria);

    printf("Ingrese la cédula del profesor asociado: ");
    scanf(" %14s", nuevoCurso.cedulaProfesor);

    do {
        printf("Ingrese la fecha de inicio del curso (DD/MM/YYYY): ");
        scanf(" %10s", nuevoCurso.fechaInicio);
        if (!validarFormatoFecha(nuevoCurso.fechaInicio)) {
            printf("Formato de fecha inválido. Intente nuevamente.\n");
        }
    } while (!validarFormatoFecha(nuevoCurso.fechaInicio));

    do {
        printf("Ingrese la fecha de fin del curso (DD/MM/YYYY): ");
        scanf(" %10s", nuevoCurso.fechaFin);
        if (!validarFormatoFecha(nuevoCurso.fechaFin)) {
            printf("Formato de fecha inválido. Intente nuevamente.\n");
        }
    } while (!validarFormatoFecha(nuevoCurso.fechaFin));

    printf("Ingrese las matrículas de los estudiantes (separadas por '/'): ");
    scanf(" %299[^\n]", nuevoCurso.estudiantes);

    if (totalCursos >= capacidadCursos) {
        capacidadCursos *= 2;
        Curso *tmp = realloc(cursos, capacidadCursos * sizeof(Curso));
        if (!tmp) {
            printf("Error al ampliar el arreglo de cursos.\n");
            free(cursos);
            exit(EXIT_FAILURE);
        }
        cursos = tmp;
    }

    cursos[totalCursos++] = nuevoCurso;
    printf("Curso creado con éxito.\n");
}


void editarCurso() {
    char codigoCurso[10];
    printf("Ingrese el código del curso que desea editar: ");
    scanf(" %9s", codigoCurso);

    for (int i = 0; i < totalCursos; i++) {
        if (strcmp(cursos[i].codigoCurso, codigoCurso) == 0) {
            printf("Curso encontrado: %s\n", cursos[i].codigoCurso);
            printf("Materia: %s, Profesor: %s\n", cursos[i].codigoMateria, cursos[i].cedulaProfesor);
            printf("Fecha de inicio: %s, Fecha de fin: %s\n", cursos[i].fechaInicio, cursos[i].fechaFin);

            do {
                printf("Ingrese la nueva fecha de inicio (DD/MM/YYYY): ");
                scanf(" %10s", cursos[i].fechaInicio);
                if (!validarFormatoFecha(cursos[i].fechaInicio)) {
                    printf("Formato de fecha inválido. Intente nuevamente.\n");
                }
            } while (!validarFormatoFecha(cursos[i].fechaInicio));

            do {
                printf("Ingrese la nueva fecha de fin (DD/MM/YYYY): ");
                scanf(" %10s", cursos[i].fechaFin);
                if (!validarFormatoFecha(cursos[i].fechaFin)) {
                    printf("Formato de fecha inválido. Intente nuevamente.\n");
                }
            } while (!validarFormatoFecha(cursos[i].fechaFin));

            printf("Ingrese las nuevas matrículas de estudiantes (separadas por '/'): ");
            scanf(" %299[^\n]", cursos[i].estudiantes);

            printf("Curso editado con éxito.\n");
            return;
        }
    }

    printf("No se encontró un curso con ese código.\n");
}


void listarCursos() {
    printf("Listado de Cursos:\n");
    for (int i = 0; i < totalCursos; i++) {
        printf("%s - Materia: %s - Profesor: %s - Inicio: %s - Fin: %s - Estudiantes: %s\n",
               cursos[i].codigoCurso, cursos[i].codigoMateria, cursos[i].cedulaProfesor,
               cursos[i].fechaInicio, cursos[i].fechaFin, cursos[i].estudiantes);
    }
}

void liberarCursos() {
    if (cursos) {
        free(cursos);
        cursos = NULL;
    }
    totalCursos = 0;
    capacidadCursos = 0;
}


