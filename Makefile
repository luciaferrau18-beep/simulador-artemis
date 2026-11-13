CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
LDFLAGS = -lm
TARGET  = simulador
OBJS    = main.o artemis.o validaciones.o reportes.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.c artemis.h validaciones.h reportes.h
	$(CC) $(CFLAGS) -c main.c

artemis.o: artemis.c artemis.h
	$(CC) $(CFLAGS) -c artemis.c

validaciones.o: validaciones.c validaciones.h
	$(CC) $(CFLAGS) -c validaciones.c

reportes.o: reportes.c reportes.h artemis.h
	$(CC) $(CFLAGS) -c reportes.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
