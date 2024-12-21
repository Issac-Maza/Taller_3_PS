#include <stdio.h>
#include <stdlib.h>
#include "materias.h"
#include "estudiantes.h"
#include "profesores.h"
#include "cursos.h"

void mostrarMenuPrincipal() {
    printf("\n================ Menú Principal ================\n");
    printf("1. Gestionar Materias\n");
    printf("2. Gestionar Estudiantes\n");
    printf("3. Gestionar Profesores\n");
    printf("4. Gestionar Cursos\n");
    printf("5. Salir\n");
    printf("Seleccione una opción: ");
}

void mostrarMenuGestion(const char *entidad) {
    printf("\n=========== Menú de Gestión de %s ===========\n", entidad);
    printf("1. Crear\n");
    printf("2. Editar\n");
    printf("3. Listar\n");
    printf("4. Volver al Menú Principal\n");
    printf("Seleccione una opción: ");
}

void gestionarMaterias() {
    int opcion;
    do {
        mostrarMenuGestion("Materias");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearMateria();
                break;
            case 2:
                editarMateria();
                break;
            case 3:
                listarMaterias();
                break;
            case 4:
                printf("Volviendo al Menú Principal...\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 4);
}

void gestionarEstudiantes() {
    int opcion;
    do {
        mostrarMenuGestion("Estudiantes");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearEstudiante();
                break;
            case 2:
                editarEstudiante();
                break;
            case 3:
                listarEstudiantes();
                break;
            case 4:
                printf("Volviendo al Menú Principal...\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 4);
}

void gestionarProfesores() {
    int opcion;
    do {
        mostrarMenuGestion("Profesores");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearProfesor();
                break;
            case 2:
                editarProfesor();
                break;
            case 3:
                listarProfesores();
                break;
            case 4:
                printf("Volviendo al Menú Principal...\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 4);
}

void gestionarCursos() {
    int opcion;
    do {
        mostrarMenuGestion("Cursos");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearCurso();
                break;
            case 2:
                editarCurso();
                break;
            case 3:
                listarCursos();
                break;
            case 4:
                printf("Volviendo al Menú Principal...\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 4);
}

int main() {
    int opcion;

    // Inicializar datos desde archivos
    inicializarMaterias();
    inicializarEstudiantes();
    inicializarProfesores();
    inicializarCursos();

    do {
        mostrarMenuPrincipal();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                gestionarMaterias();
                break;
            case 2:
                gestionarEstudiantes();
                break;
            case 3:
                gestionarProfesores();
                break;
            case 4:
                gestionarCursos();
                break;
            case 5:
                printf("Guardando datos y saliendo del programa...\n");
                guardarMaterias();
                guardarEstudiantes();
                guardarProfesores();
                guardarCursos();
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    // Liberar memoria dinámica antes de salir
    liberarMaterias();
    liberarEstudiantes();
    liberarProfesores();
    liberarCursos();

    printf("¡Hasta luego!\n");
    return 0;
}

