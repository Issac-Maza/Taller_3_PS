#ifndef PROFESORES_H
#define PROFESORES_H

#include <stdbool.h>


typedef struct {
    char nombres[50];
    char apellidos[50];
    char cedula[15];  
    char usuario[30]; // Usuario único
    char clave[20];   
    bool estado;      // true = Activo, false = Inactivo
    char materias[100]; 
} Profesor;


extern Profesor *profesores; 
extern int totalProfesores;  
extern int capacidadProfesores; 


void inicializarProfesores();  
void guardarProfesores();      
void crearProfesor();          
void editarProfesor();         
void listarProfesores();       
bool validarCedulaUnica(const char *cedula); 
bool validarUsuarioUnicoProfesor(const char *usuario); 
void liberarProfesores();      /

#endif // PROFESORES_H

