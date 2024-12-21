#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H

#include <stdbool.h>

// Estructura para un estudiante
typedef struct {
    char nombres[50];
    char apellidos[50];
    char matricula[15]; // Matrícula única
    char usuario[30];   // Usuario único
    char clave[20];     // Contraseña
    bool estado;        // true = Activo, false = Inactivo
} Estudiante;

// Declaraciones globales para el arreglo dinámico
extern Estudiante *estudiantes; // Puntero dinámico a Estudiante
extern int totalEstudiantes;    // Número actual de estudiantes
extern int capacidadEstudiantes; // Capacidad actual del arreglo dinámico

// Funciones relacionadas con los estudiantes
void inicializarEstudiantes();  // Inicializa los estudiantes desde un archivo
void guardarEstudiantes();      // Guarda los estudiantes en un archivo
void crearEstudiante();         // Agrega un nuevo estudiante
void editarEstudiante();        // Edita un estudiante existente
void listarEstudiantes();       // Lista todos los estudiantes
bool validarMatriculaUnica(const char *matricula); // Verifica que la matrícula sea única
bool validarUsuarioUnico(const char *usuario);     // Verifica que el usuario sea único
void liberarEstudiantes();      // Libera la memoria dinámica utilizada por el arreglo

#endif // ESTUDIANTES_H

