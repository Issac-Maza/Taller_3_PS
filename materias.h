#ifndef MATERIAS_H
#define MATERIAS_H

#define TAM_LINEA 500

typedef struct {
	char nombre[50];
	char codigo[20];
	char estado[10];
} Materia;

void gestionarMaterias(void);
void crearMateria(void);
void editarMateria(void);
int verificarUnicidadMateria(const char *codigo);

#endif
