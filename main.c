/*
 * main.c - Simulador Artemis: Reingreso, frenado aerodinamico y amerizaje
 * Responsable: Integrante 3 (Main & Menu)
 */
#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"
#include "reportes.h"

#define OPC_NOMINAL      1
#define OPC_PERSONALIZADO 2
#define OPC_INFO         3
#define OPC_SALIR        4

static void mostrar_menu(void);
static void cargar_datos_personalizados(Reingreso *datos);
static void ejecutar_simulacion(const Reingreso *datos);

int main(void)
{
    Reingreso datos;
    int opcion;

    do {
        mostrar_menu();
        opcion = leer_entero_rango("Seleccione una opcion: ", OPC_NOMINAL, OPC_SALIR);

        switch (opcion) {
            case OPC_NOMINAL:
                cargar_datos_nominales(&datos);
                ejecutar_simulacion(&datos);
                break;
            case OPC_PERSONALIZADO:
                cargar_datos_personalizados(&datos);
                ejecutar_simulacion(&datos);
                break;
            case OPC_INFO:
                mostrar_escenario();
                esperar_enter();
                break;
            case OPC_SALIR:
                printf("\nFin de la simulacion. Buen amerizaje!\n");
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
    printf(" 1. Simulacion con datos nominales\n");
    printf(" 2. Simulacion con datos personalizados\n");
    printf(" 3. Ver descripcion del escenario\n");
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

static void ejecutar_simulacion(const Reingreso *datos)
{
    Resultados res;

    calcular_resultados(datos, &res);
    imprimir_reporte(datos, &res);
    esperar_enter();
}
