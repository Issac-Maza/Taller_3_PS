#ifndef CURSOS_H
#define CURSOS_H

#include "materias.h"
#include "estudiantes.h"


struct Profesor;


typedef struct {
    char codigo[20];
    char materia[20];
    char profesorCedula[20];
    char fechaInicio[11];
    char fechaFin[11];
    char estudiantesLista[30][15];
    int cantidadEstudiantes;
} Curso;


void cargarDatosCursos(Curso **cursos, int *cantidad);
void guardarDatosCursos(Curso *cursos, int cantidad);
void gestionarCursos(Curso **cursos, int *cantidad, Estudiante *estudiantes, int cantidadEstudiantes, Materia *materias, int cantidadMaterias, Profesor *profesores, int cantidadProfesores);
void crearCurso(Curso **cursos, int *cantidad, Estudiante *estudiantes, int cantidadEstudiantes, Materia *materias, int cantidadMaterias, Profesor *profesores, int cantidadProfesores);
void editarCurso(Curso *cursos, int cantidad);
void mostrarCursos(Curso *cursos, int cantidad);
void liberarMemoriaCursos(Curso *cursos, int cantidad);


int verificarUnicidadCurso(const char *codigo, Curso *cursos, int cantidad);
int verificarRelacionMaterias(const char *codigo, Materia *materias, int cantidad);
int verificarRelacionProfesor(const char *cedula, Profesor *profesores, int cantidad);
int verificarRelacionEstudiantes(const char *matricula, Estudiante *estudiantes, int cantidad);
int verificarCursosAsignados(const Curso *cursos, int cantidadCursos, const char *codigo);
int verificarMaxEstudiantes(int cantidadEstudiantes);

#endif
