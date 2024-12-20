#ifndef PROFESORES_H
#define PROFESORES_H

#include "materias.h"
#include "cursos.h"

typedef struct {
    	char nombre[100];
    	char apellidos[100];
    	char cedula[20];
    	char usuario[50];
    	char clave[50];
    	char estado[10];
    	int cantidadMaterias;
    	char **materiasLista;
} Profesor;

void cargarDatosProfesores(Profesor **profesores, int *cantidad, Materia *materias, int cantidadMaterias);
void guardarDatosProfesores(Profesor *profesores, int cantidad);
void gestionarProfesores(Profesor **profesores, int *cantidad, Materia *materias, int cantidadMaterias);
void crearProfesor(Profesor **profesores, int *cantidad, Materia *materias, int cantidadMaterias);
void editarProfesor(Profesor *profesores, int cantidad, Curso *cursos, int cantidadCursos);
void liberarMemoriaProfesores(Profesor *profesores, int cantidad);
int verificarUnicidadProfesor(Profesor *profesores, int cantidad, const char *cedula, const char *usuario);
int verificarMateriaDuplicada(char **materiasLista, int cantidadMaterias, const char *codigoMateria);
int verificarMateriaExistente(const char *codigoMateria, Materia *materias, int cantidadMaterias);

#endif
