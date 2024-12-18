#ifndef PROFESORES_H
#define PROFESORES_H
#define TAM_LINEA 500

typedef struct {
	char nombre[100];
	char apellidos[100];
	char cedula[15];
	char usuario[50];
	char clave[50];
	char estado[10];
	char materias[200];
} Profesor;

void gestionarProfesores(void);
void crearProfesor(void);
void editarProfesor(void);
int verificarUnicidadProfesor(const char *cc, const char *usuario);

#endif
