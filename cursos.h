#ifndef CURSOS_H
#define CURSOS_H
#define TAM_LINEA 500

typedef struct {
	char codigo[20];
	char codigoMateria[10];
	char cedulaProfesor[15];
	char fechaInicio[12];
	char fechaFinal[12];
	char listaEstudiantes[TAM_LINEA];
} Curso;

void gestionarCursos(void);
void crearCurso(void);
void editarCurso(void);
int verificarUnicidadCurso(const char *codigo);
int verificarRelacionMaterias(const char *codigo);
int verificarRelacionProfesor(const char *cc);
int verificarRelacionEstudiantes(const char *matricula);

#endif
