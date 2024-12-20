CC = gcc
CFLAGS = -Wall -Wextra -std=c99


SRCS = main.c estudiantes.c profesores.c materias.c cursos.c utilidades.c
OBJS = $(SRCS:.c=.o)


TARGET = gestion_colegio


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


tidy:
	rm -f $(OBJS)

clean: tidy
	rm -f $(TARGET)


run: all
	./$(TARGET)


main.o: main.c estudiantes.h profesores.h materias.h cursos.h utilidades.h
estudiantes.o: estudiantes.c estudiantes.h utilidades.h
profesores.o: profesores.c profesores.h utilidades.h
materias.o: materias.c materias.h utilidades.h
cursos.o: cursos.c cursos.h estudiantes.h profesores.h materias.h utilidades.h
utilidades.o: utilidades.c utilidades.h
