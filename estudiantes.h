#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H

#include <stdbool.h>


typedef struct {
    char nombres[50];
    char apellidos[50];
    char matricula[15]; // Matrícula única
    char usuario[30];   // Usuario único
    char clave[20];     
    bool estado;        // true = Activo, false = Inactivo
} Estudiante;


extern Estudiante *estudiantes; 
extern int totalEstudiantes;    
extern int capacidadEstudiantes; 


void inicializarEstudiantes();  
void guardarEstudiantes();      
void crearEstudiante();         
void editarEstudiante();        
void listarEstudiantes();       
bool validarMatriculaUnica(const char *matricula); // Verifica que la matrícula sea única
bool validarUsuarioUnico(const char *usuario);     // Verifica que el usuario sea único
void liberarEstudiantes();      // Libera la memoria dinámica utilizada por el arreglo

#endif // ESTUDIANTES_H

