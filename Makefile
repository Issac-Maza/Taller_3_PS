# Nombre del compilador
CC = gcc

# Flags para el compilador
CFLAGS = -Wall -Wextra -g

# Archivos fuente y objeto
SRC = main.c materias.c estudiantes.c profesores.c cursos.c
OBJ = $(SRC:.c=.o)

# Nombre del ejecutable
EXEC = programa

# Regla principal
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar archivos .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f $(OBJ) $(EXEC)

# Regla para limpiar completamente (incluyendo archivos de datos temporales)
cleanall: clean
	rm -f *.txt

