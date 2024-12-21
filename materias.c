#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "materias.h"


Materia *materias = NULL;
int totalMaterias = 0;
int capacidadMaterias = 0;


void inicializarMaterias() {
    FILE *archivo = fopen("materia.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo de materias. Creando lista vacía.\n");
        return;
    }

    capacidadMaterias = 10;
    materias = (Materia *)malloc(capacidadMaterias * sizeof(Materia));
    if (!materias) {
        printf("Error al asignar memoria para las materias.\n");
        fclose(archivo);
        return;
    }

    while (fscanf(archivo, "%49[^-]-%9[^-]-%d\n", materias[totalMaterias].nombre,
                  materias[totalMaterias].codigo, (int *)&materias[totalMaterias].estado) == 3) {
        totalMaterias++;

        
        if (totalMaterias >= capacidadMaterias) {
            capacidadMaterias *= 2;
            Materia *tmp = realloc(materias, capacidadMaterias * sizeof(Materia));
            if (!tmp) {
                printf("Error al ampliar el arreglo de materias.\n");
                free(materias);
                fclose(archivo);
                exit(EXIT_FAILURE); 
            }
            materias = tmp;
        }
    }

    fclose(archivo);
    printf("Materias cargadas con éxito.\n");
}



void guardarMaterias() {
    FILE *archivo = fopen("materia.txt", "w");
    if (!archivo) {
        printf("No se pudo abrir el archivo para guardar las materias.\n");
        return;
    }

    for (int i = 0; i < totalMaterias; i++) {
        fprintf(archivo, "%s-%s-%d\n", materias[i].nombre, materias[i].codigo, materias[i].estado);
    }

    fclose(archivo);
    printf("Materias guardadas con éxito.\n");
}


bool validarCodigoUnico(const char *codigo) {
    for (int i = 0; i < totalMaterias; i++) {
        if (strcmp(materias[i].codigo, codigo) == 0) {
            return false;
        }
    }
    return true;
}


void crearMateria() {
    Materia nuevaMateria;

    printf("Ingrese el nombre de la materia: ");
    scanf(" %49[^\n]", nuevaMateria.nombre);

    do {
        printf("Ingrese el código de la materia (único): ");
        scanf(" %9s", nuevaMateria.codigo);

        if (!validarCodigoUnico(nuevaMateria.codigo)) {
            printf("El código ya existe. Intente nuevamente.\n");
        }
    } while (!validarCodigoUnico(nuevaMateria.codigo));

    nuevaMateria.estado = true;

    
    if (totalMaterias >= capacidadMaterias) {
        capacidadMaterias *= 2;
        Materia *tmp = realloc(materias, capacidadMaterias * sizeof(Materia));
        if (!tmp) {
            printf("Error al ampliar el arreglo de materias.\n");
            free(materias);
            exit(EXIT_FAILURE); 
        }
        materias = tmp;
    }

    materias[totalMaterias++] = nuevaMateria;
    printf("Materia creada con éxito.\n");
}


void editarMateria() {
    char codigo[10];
    printf("Ingrese el código de la materia que desea editar: ");
    scanf(" %9s", codigo);

    for (int i = 0; i < totalMaterias; i++) {
        if (strcmp(materias[i].codigo, codigo) == 0) {
            printf("Materia encontrada: %s (%s)\n", materias[i].nombre, materias[i].codigo);
            printf("Estado actual: %s\n", materias[i].estado ? "Activo" : "Inactivo");

            int nuevoEstado;
            printf("Ingrese el nuevo estado (1 = Activo, 0 = Inactivo): ");
            scanf("%d", &nuevoEstado);

            
            if (nuevoEstado == 0) {
                printf("Verificando cursos asociados... (implementación pendiente)\n");
            }

            materias[i].estado = nuevoEstado;
            printf("Materia editada con éxito.\n");
            return;
        }
    }

    printf("No se encontró una materia con ese código.\n");
}


void listarMaterias() {
    printf("Listado de Materias:\n");
    for (int i = 0; i < totalMaterias; i++) {
        printf("%s - %s - %s\n", materias[i].nombre, materias[i].codigo,
               materias[i].estado ? "Activo" : "Inactivo");
    }
}



void liberarMaterias() {
    if (materias) {
        free(materias);
        materias = NULL;
    }
    totalMaterias = 0;
    capacidadMaterias = 0;
}

int obtenerTotalMaterias() {
    return totalMaterias;
}

// Devuelve un puntero a la materia en el índice dado
const Materia *obtenerMateriaPorIndice(int i) {
    if (i < 0 || i >= totalMaterias) {
        return NULL; // Si el índice no es válido, retorna NULL
    }
    return &materias[i];
}
