#ifndef MATERIAS_H
#define MATERIAS_H

typedef struct {
	char nombre[50];
	char codigo[20];
	char estado[10];
} Materia;

void cargarDatosMaterias(Materia **materias, int *cantidad);
void guardarDatosMaterias(Materia *materias, int cantidad);
void gestionarMaterias(Materia **materias, int *cantidad);
void crearMateria(Materia **materias, int *cantidad);
void editarMateria(Materia *materias, int cantidad);
void mostrarMaterias(Materia *materias, int cantidad);
void liberarMemoriaMaterias(Materia *materias, int cantidad);
int verificarUnicidadMateria(const char *codigo);

#endif
