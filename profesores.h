#ifndef PROFESORES_H
#define PROFESORES_H

typedef struct {
	char nombre[100];
	char apellidos[100];
	char cedula[15];
	char usuario[50];
	char clave[50];
	char estado[10];
	char **materias[200];
	int cantidadMaterias;
} Profesor;

void cargarDatosProfesores(Profesor **profesores, int *cantidad);
void guardarDatosProfesores(Profesor *profesores, int cantidad);
void gestionarProfesores(Profesor **profesores, int *cantidad);
void crearProfesor(Profesor **profesores, int *cantidad);
void editarProfesor(Profesor *profesores, int cantidad);
void mostrarProfesores(Profesor *profesores, int cantidad);
void liberarMemoriaProfesores(Profesor *profesores, int cantidad);
int verificarUnicidadProfesor(Profesor *profesores, int cantidad, const char *cc, const char *usuario);
int verificarMateriaDuplicada(char **materiasLista, int cantidadMaterias, const char *materia);

#endif
