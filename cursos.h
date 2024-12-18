#ifndef CURSOS_H
#define CURSOS_H

typedef struct {
	char codigo[20];
	char codigoMateria[10];
	char cedulaProfesor[15];
	char fechaInicio[12];
	char fechaFinal[12];
	char listaEstudiantes[450];
} Curso;

void gestionarCursos(void);
void crearCurso(void);
void editarCurso(void);

#endif
