/*
 * main.c - Simulador Artemis: Reingreso, frenado aerodinamico y amerizaje
 * Responsable: Integrante 3 (Main & Menu)
 */
#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"
#include "reportes.h"

#define OPC_NOMINAL       1
#define OPC_PERSONALIZADO 2
#define OPC_HISTORIAL     3
#define OPC_SALIR         4

#define MAX_HISTORIAL     50
#define EXPORTAR_SI       1
#define EXPORTAR_NO       2

static void mostrar_menu(void);
static void cargar_datos_personalizados(Reingreso *datos);
static void ejecutar_simulacion(const Reingreso *datos,
                                Resultados historial[], int *cantidad);

int main(void)
{
    Reingreso datos;
    Resultados historial[MAX_HISTORIAL];
    int cantidad = 0;
    int opcion;

    do {
        mostrar_menu();
        opcion = leer_entero_rango("Seleccione una opcion: ", OPC_NOMINAL, OPC_SALIR);

        switch (opcion) {
            case OPC_NOMINAL:
                cargar_datos_nominales(&datos);
                ejecutar_simulacion(&datos, historial, &cantidad);
                break;
            case OPC_PERSONALIZADO:
                cargar_datos_personalizados(&datos);
                ejecutar_simulacion(&datos, historial, &cantidad);
                break;
            case OPC_HISTORIAL:
                mostrar_historial_misiones(historial, cantidad);
                esperar_enter();
                break;
            case OPC_SALIR:
                printf("\nFin de la simulacion.\n");
                break;
        }
    } while (opcion != OPC_SALIR);

    return 0;
}

static void mostrar_menu(void)
{
    printf("\n==============================================\n");
    printf("   ARTEMIS - REINGRESO Y AMERIZAJE DE ORION\n");
    printf("==============================================\n");
    printf(" 1. Simular con datos del enunciado\n");
    printf(" 2. Simular con datos propios\n");
    printf(" 3. Ver historial de simulaciones\n");
    printf(" 4. Salir\n");
    printf("----------------------------------------------\n");
}

/* Pide cada dato validando tipo y rango. Los limites dependen de los datos
 * ya ingresados para garantizar coherencia fisica. */
static void cargar_datos_personalizados(Reingreso *datos)
{
    printf("\n--- Ingreso de datos personalizados ---\n");

    datos->masa = leer_double_rango("Masa de la capsula [kg] (1000 - 50000): ",
                                    1000.0, 50000.0);
    datos->vi = leer_double_rango("Rapidez de reingreso vi [m/s] (100 - 15000): ",
                                  100.0, 15000.0);
    datos->h_inicial = leer_double_rango("Altitud de reingreso [m] (5000 - 200000): ",
                                         5000.0, 200000.0);
    datos->h_paracaidas = leer_double_rango(
        "Altitud de apertura de paracaidas [m] (100 - altitud de reingreso): ",
        100.0, datos->h_inicial - 1.0);
    datos->vf = leer_double_rango(
        "Rapidez al abrir paracaidas vf [m/s] (10 - menor que vi): ",
        10.0, datos->vi - 1.0);
    datos->v_impacto = leer_double_rango(
        "Rapidez de impacto en el agua [m/s] (1 - menor que vf): ",
        1.0, datos->vf - 1.0);
    datos->dt = leer_double_rango(
        "Duracion de la fase de mayor desaceleracion [s] (1 - 5000): ",
        1.0, 5000.0);
    datos->d_hundimiento = leer_double_rango(
        "Profundidad de hundimiento en el agua [m] (0.1 - 10): ",
        0.1, 10.0);
    datos->gamma = leer_double_rango(
        "Angulo de reingreso gamma [grados] (0.1 - 90): ",
        0.1, 90.0);
}

/* Calcula, muestra el reporte, lo guarda en el historial y ofrece exportarlo */
static void ejecutar_simulacion(const Reingreso *datos,
                                Resultados historial[], int *cantidad)
{
    Resultados res;
    int exportar;

    calcular_resultados(datos, &res);
    mostrar_reporte_mision(datos, &res);

    if (*cantidad < MAX_HISTORIAL) {
        historial[*cantidad] = res;
        (*cantidad)++;
    } else {
        printf("Aviso: el historial esta lleno, esta simulacion no se guardo en el.\n");
    }

    exportar = leer_entero_rango("Exportar reporte a archivo? (1 = Si, 2 = No): ",
                                 EXPORTAR_SI, EXPORTAR_NO);
    if (exportar == EXPORTAR_SI) {
        if (exportar_reporte_txt(datos, &res)) {
            printf("Reporte guardado en reporte_artemis.txt\n");
        } else {
            printf("Error: no se pudo crear el archivo del reporte.\n");
        }
    }

    esperar_enter();
}
