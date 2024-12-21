#ifndef MATERIAS_H
#define MATERIAS_H

#include <stdbool.h>


typedef struct {
    char nombre[50];
    char codigo[10];
    bool estado; // true = Activo, false = Inactivo
} Materia;


extern Materia *materias; 
extern int totalMaterias; 
extern int capacidadMaterias; 


void inicializarMaterias(); 
void guardarMaterias();     
void crearMateria();        
void editarMateria();       
void listarMaterias();      
bool validarCodigoUnico(const char *codigo); 
void liberarMaterias();     

int obtenerTotalMaterias();
const Materia *obtenerMateriaPorIndice(int i);

#endif // MATERIAS_H
