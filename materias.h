#ifndef MATERIAS_H
#define MATERIAS_H

#include <stdbool.h>

// Estructura para una materia
typedef struct {
    char nombre[50];
    char codigo[10];
    bool estado; // true = Activo, false = Inactivo
} Materia;

// Declaraciones globales para el arreglo dinámico
extern Materia *materias; // Puntero dinámico a Materia
extern int totalMaterias; // Número actual de materias
extern int capacidadMaterias; // Capacidad actual del arreglo dinámico

// Funciones relacionadas con las materias
void inicializarMaterias(); // Inicializa las materias desde un archivo
void guardarMaterias();     // Guarda las materias en un archivo
void crearMateria();        // Agrega una nueva materia
void editarMateria();       // Edita una materia existente
void listarMaterias();      // Lista todas las materias
bool validarCodigoUnico(const char *codigo); // Verifica que el código sea único
void liberarMaterias();     // Libera la memoria dinámica utilizada por el arreglo

int obtenerTotalMaterias();
const Materia *obtenerMateriaPorIndice(int i);

#endif // MATERIAS_H
