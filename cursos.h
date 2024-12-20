#ifndef CURSOS_H
#define CURSOS_H
#define MAX_ESTUDIANTES 30

typedef struct {
	char codigo[20];	//CODIGO UNICO DEL CURSO
	char materia[20];	//CODIGO DE LA MATERIA
	char profesor[15];	//CEDULA DEL PROFESOR
	char fechaInicio[11];     // FORMATO DE FECHA DD/MM/AAAA
	char fechaFin[11];        // Formato DE FECHA DD/MM/AAAA
	char estudiantesLista[MAX_ESTUDIANTES][15];
	int cantidadEstudiantes;
} Curso;

void cargarDatosCursos(Curso **cursos, int *cantidad);
void guardarDatosCursos(Curso *cursos, int cantidad);
void gestionarCursos(Curso **cursos, int *cantidad, Estudiante *estudiantes, int cantidadEstudiantes, 
		Materia *materias, int cantidadMaterias, Profesor *profesores, int cantidadProfesores);
void crearCurso(Curso **cursos, int *cantidad, Estudiante *estudiantes, int cantidadEstudiantes, 
		Materia *materias, int cantidadMaterias, Profesor *profesores, int cantidadProfesores);
void editarCurso(Curso *cursos, int cantidad);
void mostrarCursos(Curso *cursos, int cantidad);
void liberarMemoriaCursos(Curso *cursos, int cantidad);
int verificarUnicidadCurso(const char *codigo, Curso *cursos, int cantidad);
int verificarRelacionMaterias(const char *codigo, Materia *materias, int cantidad);
int verificarRelacionProfesor(const char *cc, Profesor *profesores, int cantidad);
int verificarRelacionEstudiantes(const char *matricula, Estudiante *estudiantes, int cantidad);
int verificarCursosAsignados(const Curso *cursos, int cantidadCursos, const char *codigo);
int verificarMaxEstudiantes(int cantidadEstudiantes);

#endif
