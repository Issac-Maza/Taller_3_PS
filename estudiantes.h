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

void cargarDatosEstudiantes(Estudiante **estudiantes, int *cantidad);
void guardarDatosEstudiantes(Estudiante *estudiantes, int cantidad);
void gestionarEstudiantes(Estudiante **estudiantes, int *cantidad);
void crearEstudiante(Estudiante **estudiantes, int *cantidad);
void editarEstudiante(Estudiante *estudiantes, int cantidad);
void mostrarEstudiantes(Estudiante *estudiantes, int cantidad);
int verificarUnicidadEstudiante(const char *matricula, Estudiante *estudiantes, int cantidad);
void liberarMemoriaEstudiantes(Estudiante *estudiantes, int cantidad);

#endif
