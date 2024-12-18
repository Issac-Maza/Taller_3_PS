#ifndef PROFESORES_H
#define PROFESORES_H

typedef struct {
	char nombre[100];
	char apellidos[100];
	char cedula[15];
	char usuario[50];
	char clave[20];
	char estado[10];
	char materias[100];
} Profesor;

void gestionarProfesores(void);
void crearProfesor(void);
void editarProfesor(void);

#endif
