#ifndef PROFESORES_H
#define PROFESORES_H

#include <stdbool.h>

// Estructura para un profesor
typedef struct {
    char nombres[50];
    char apellidos[50];
    char cedula[15];  // Identificación única (C.C.)
    char usuario[30]; // Usuario único
    char clave[20];   // Contraseña
    bool estado;      // true = Activo, false = Inactivo
    char materias[100]; // Lista de códigos de materias que puede dictar (separados por '/')
} Profesor;

// Declaraciones globales para el arreglo dinámico
extern Profesor *profesores; // Puntero dinámico a Profesor
extern int totalProfesores;  // Número actual de profesores
extern int capacidadProfesores; // Capacidad actual del arreglo dinámico

// Funciones relacionadas con los profesores
void inicializarProfesores();  // Inicializa los profesores desde un archivo
void guardarProfesores();      // Guarda los profesores en un archivo
void crearProfesor();          // Agrega un nuevo profesor
void editarProfesor();         // Edita un profesor existente
void listarProfesores();       // Lista todos los profesores
bool validarCedulaUnica(const char *cedula); // Verifica que la cédula sea única
bool validarUsuarioUnicoProfesor(const char *usuario); // Verifica que el usuario sea único
void liberarProfesores();      // Libera la memoria dinámica utilizada por el arreglo

#endif // PROFESORES_H

