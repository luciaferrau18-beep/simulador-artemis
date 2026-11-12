#include <stdio.h>
#include "reportes.h"

void mostrar_reporte_mision(const Reingreso *datos, const Resultados *res) {
    printf("\n============================================================\n");
    printf("       REPORTE FINAL DE MISION - CAPSULA ORION (ESC. 4)     \n");
    printf("============================================================\n");
    
    printf("\n[1] PARAMETROS DE ENTRADA:\n");
    printf("  - Masa de la capsula       : %.2f kg\n", datos->masa);
    printf("  - Velocidad de reingreso   : %.2f m/s\n", datos->vi);
    printf("  - Altitud inicial / paraca.: %.0f m -> %.0f m\n", datos->h_inicial, datos->h_paracaidas);
    printf("  - Velocidad paracaidas     : %.2f m/s\n", datos->vf);
    printf("  - Velocidad de impacto     : %.2f m/s (Hundimiento: %.2f m)\n", datos->v_impacto, datos->d_hundimiento);
    printf("  - Tiempo desaceleracion    : %.2f s\n", datos->dt);
    printf("  - Angulo de reingreso      : %.2f grados\n", datos->gamma);

    printf("\n[2] RESULTADOS FISICOS CALCULADOS:\n");
    printf("  - Trabajo de rozamiento    : %.2e J\n", res->w_roz);
    printf("  - Desaceleracion media     : %.2f m/s^2 (%.2f G)\n", res->a_media, res->a_media_g);
    printf("  - Fuerza promedio del agua : %.2f N (%.2f veces su peso)\n", res->f_prom, res->f_prom_peso);

    printf("\n[3] DIAGNOSTICO DE SEGURIDAD DE LA MISION:\n");
    if (res->estado_gamma == GAMMA_REBOTE) {
        printf("  >>> ESTADO: FRACASO - REBOTE ATMOSFERICO <<<\n");
        printf("  Motivo: El angulo (%.2f grados) es menor a %.1f grados. La nave reboto al espacio.\n", datos->gamma, GAMMA_MIN);
    } else if (res->estado_gamma == GAMMA_EXCESIVO) {
        printf("  >>> ESTADO: FRACASO - DESINTEGRACION ESTRUCTURAL <<<\n");
        printf("  Motivo: El angulo (%.2f grados) supera los %.1f grados. Desaceleracion y friccion excesivas.\n", datos->gamma, GAMMA_MAX);
    } else {
        printf("  >>> ESTADO: EXITO - AMERIZAJE SEGURO EN EL PACIFICO <<<\n");
        printf("  Motivo: Angulo dentro de la ventana segura (%.1f a %.1f grados).\n", GAMMA_MIN, GAMMA_MAX);
    }
    printf("============================================================\n\n");
}

int exportar_reporte_txt(const Reingreso *datos, const Resultados *res) {
    FILE *archivo = fopen("reporte_artemis.txt", "w");
    if (archivo == NULL) {
        return 0; /* Error al crear el archivo */
    }

    fprintf(archivo, "============================================================\n");
    fprintf(archivo, "       REPORTE OFICIAL MISION ARTEMIS - ESCENARIO 4         \n");
    fprintf(archivo, "============================================================\n\n");
    fprintf(archivo, "Masa de la nave          : %.2f kg\n", datos->masa);
    fprintf(archivo, "Velocidad inicial        : %.2f m/s\n", datos->vi);
    fprintf(archivo, "Tiempo desaceleracion    : %.2f s\n", datos->dt);
    fprintf(archivo, "Angulo de reingreso      : %.2f grados\n\n", datos->gamma);
    fprintf(archivo, "--- CALCULOS DE REINGRESO Y AMERIZAJE ---\n");
    fprintf(archivo, "Trabajo de rozamiento    : %.2e J\n", res->w_roz);
    fprintf(archivo, "Desaceleracion media     : %.2f m/s^2 (%.2f G)\n", res->a_media, res->a_media_g);
    fprintf(archivo, "Fuerza promedio del agua : %.2f N (%.2f x Peso)\n\n", res->f_prom, res->f_prom_peso);

    if (res->estado_gamma == GAMMA_SEGURO) {
        fprintf(archivo, "RESULTADO FINAL: MISION EXITOSA\n");
    } else if (res->estado_gamma == GAMMA_REBOTE) {
        fprintf(archivo, "RESULTADO FINAL: MISION FALLIDA (Rebote atmosferico - gamma < %.1f)\n", GAMMA_MIN);
    } else {
        fprintf(archivo, "RESULTADO FINAL: MISION FALLIDA (Desaceleracion excesiva - gamma > %.1f)\n", GAMMA_MAX);
    }

    fclose(archivo);
    return 1;
}

void mostrar_historial_misiones(const Resultados historial[], int cantidad) {
    int i;
    if (cantidad <= 0) {
        printf("\n[!] Todavia no se realizo ninguna simulacion en esta sesion.\n");
        return;
    }

    printf("\n--- HISTORIAL DE SIMULACIONES DE LA SESION ---\n");
    printf("Nro | W_roz (J)   | Desacel. (G) | Fuerza Agua (N) | Estado\n");
    printf("-----------------------------------------------------------------\n");
    for (i = 0; i < cantidad; i++) {
        printf(" %2d | %11.2e | %10.2f G | %15.2f | %s\n",
               i + 1,
               historial[i].w_roz,
               historial[i].a_media_g,
               historial[i].f_prom,
               (historial[i].estado_gamma == GAMMA_SEGURO) ? "SEGURA" : "PELIGRO");
    }
    printf("-----------------------------------------------------------------\n\n");
}