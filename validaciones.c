#include <stdio.h>
#include <string.h>
#include "validaciones.h"

// Limpia el búfer de entrada para evitar bucles infinitos con scanf/fgets
void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lee un entero validando que esté dentro de un rango [min, max]
int leer_entero_rango(const char *mensaje, int min, int max) {
    int valor;
    char buffer[100];
    int valido = 0;

    do {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Quitamos el salto de línea si lo tiene
            buffer[strcspn(buffer, "\n")] = 0;

            if (sscanf(buffer, "%d", &valor) == 1) {
                if (valor >= min && valor <= max) {
                    valido = 1;
                } else {
                    printf("Error: El valor debe estar entre %d y %d.\n", min, max);
                }
            } else {
                printf("Error: Debe ingresar un numero entero valido.\n");
            }
        }
    } while (!valido);

    return valor;
}

// Lee un double validando que esté dentro de un rango [min, max]
double leer_double_rango(const char *mensaje, double min, double max) {
    double valor;
    char buffer[100];
    int valido = 0;

    do {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;

            if (sscanf(buffer, "%lf", &valor) == 1) {
                if (valor >= min && valor <= max) {
                    valido = 1;
                } else {
                    printf("Error: El valor debe estar entre %.2f y %.2f.\n", min, max);
                }
            } else {
                printf("Error: Debe ingresar un numero valido.\n");
            }
        }
    } while (!valido);

    return valor;
}

// Pausa la ejecución esperando que el usuario presione Enter
void esperar_enter(void) {
    printf("\nPresione Enter para continuar...");
    getchar();
}