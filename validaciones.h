#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Integrante 2: validaciones.c */
void   limpiar_buffer(void);
int    leer_entero_rango(const char *mensaje, int min, int max);
double leer_double_rango(const char *mensaje, double min, double max);
void   esperar_enter(void);

#endif
