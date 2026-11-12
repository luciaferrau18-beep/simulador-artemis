#ifndef REPORTES_H
#define REPORTES_H

#include "artemis.h"

/* Muestra en consola el informe completo de una simulacion */
void mostrar_reporte_mision(const Reingreso *datos, const Resultados *res);

/* Guarda el reporte final en un archivo de texto (.txt). Devuelve 1 si tuvo exito, 0 si fallo */
int exportar_reporte_txt(const Reingreso *datos, const Resultados *res);

/* Muestra una tabla resumen usando un arreglo con todas las simulaciones hechas en la sesion */
void mostrar_historial_misiones(const Resultados historial[], int cantidad);

#endif