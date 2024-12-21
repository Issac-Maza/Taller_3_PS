#ifndef CURSOS_H
#define CURSOS_H

#include <stdbool.h>


typedef struct {
    char codigoCurso[10];    
    char codigoMateria[10];  
    char cedulaProfesor[15]; 
    char fechaInicio[11];    // (formato: YYYY-MM-DD)
    char fechaFin[11];       
    char estudiantes[300];   
} Curso;


extern Curso *cursos;        
extern int totalCursos;      
extern int capacidadCursos;  


void inicializarCursos();         
void guardarCursos();             
void crearCurso();                
void editarCurso();               
void listarCursos();              
bool validarCodigoCursoUnico(const char *codigoCurso); // Verifica que el código sea único
void liberarCursos();             

#endif // CURSOS_H

