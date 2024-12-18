#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H

typedef struct {
	char nombres[100];
	char apellidos[100];
	char matricula[15];
	char usuario[50];
	char clave[50];
	char estado[10];
} Estudiante;

void gestionarEstudiantes(void);
void crearEstudiante(void);
void editarEstudiante(void);
int verificarUnicidadEstudiante(const char *matricula, const char *usuario);

#endif
