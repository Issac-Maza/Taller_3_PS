#ifndef CURSOS_H
#define CURSOS_H

#include <stdbool.h>

// Estructura para un curso
typedef struct {
    char codigoCurso[10];    // Código único del curso
    char codigoMateria[10];  // Código de la materia asociada
    char cedulaProfesor[15]; // Cédula del profesor
    char fechaInicio[11];    // Fecha de inicio (formato: YYYY-MM-DD)
    char fechaFin[11];       // Fecha de fin (formato: YYYY-MM-DD)
    char estudiantes[300];   // Matrículas de estudiantes separadas por '/'
} Curso;

// Declaraciones globales para el arreglo dinámico
extern Curso *cursos;        // Puntero dinámico a Curso
extern int totalCursos;      // Número actual de cursos
extern int capacidadCursos;  // Capacidad actual del arreglo dinámico

// Funciones relacionadas con los cursos
void inicializarCursos();         // Inicializa los cursos desde un archivo
void guardarCursos();             // Guarda los cursos en un archivo
void crearCurso();                // Agrega un nuevo curso
void editarCurso();               // Edita un curso existente
void listarCursos();              // Lista todos los cursos
bool validarCodigoCursoUnico(const char *codigoCurso); // Verifica que el código sea único
void liberarCursos();             // Libera la memoria dinámica utilizada por el arreglo

#endif // CURSOS_H

