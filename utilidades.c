#include <string.h>
#include <stdio.h>
#include "utilidades.h"

void limpiarBuffer(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int validarFecha(const char *fecha) {
	if (strlen(fecha) != 10) {
		return 0;
	}

	if (fecha[2] != '/' || fecha[5] != '/') {
		return 0;
	}

	int dia, mes, anio;

	if (sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio) != 3) {
		return 0;
	}

	if (mes < 1 || mes > 12) {
		return 0;
	}

	if (anio < 1900 || anio > 2100) {
		 return 0;
	}

	return 1;
}
