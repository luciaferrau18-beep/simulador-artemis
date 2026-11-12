#ifndef ARTEMIS_H
#define ARTEMIS_H

/* ---------- Constantes del escenario (Situación 4) ---------- */
#define G                    9.80
#define MASA_NOMINAL         10400.0   /* kg  */
#define VI_NOMINAL           11000.0   /* m/s */
#define H_INICIAL_NOMINAL    120000.0  /* m   */
#define VF_NOMINAL           25.0      /* m/s */
#define H_PARACAIDAS_NOMINAL 2500.0    /* m   */
#define V_IMPACTO_NOMINAL    8.0       /* m/s */
#define DT_NOMINAL           400.0     /* s   */
#define D_HUNDIMIENTO_NOMINAL 1.50     /* m   */
#define GAMMA_NOMINAL        6.0       /* grados */
#define GAMMA_MIN            5.5
#define GAMMA_MAX            7.0

/* Resultado de evaluar el ángulo de reingreso */
#define GAMMA_SEGURO   0
#define GAMMA_EXCESIVO 1   /* gamma > 7,0  -> desaceleracion excesiva */
#define GAMMA_REBOTE   2   /* gamma < 5,5  -> rebote atmosferico      */

/* Datos de entrada de la simulación */
typedef struct {
    double masa;          /* kg  */
    double vi;            /* m/s: rapidez al reingresar            */
    double h_inicial;     /* m:   altitud de reingreso             */
    double vf;            /* m/s: rapidez al abrir paracaidas      */
    double h_paracaidas;  /* m:   altitud de apertura              */
    double v_impacto;     /* m/s: rapidez al amerizar              */
    double dt;            /* s:   duracion fase de max. desacel.   */
    double d_hundimiento; /* m:   profundidad que se hunde         */
    double gamma;         /* grados: angulo de reingreso           */
} Reingreso;

/* Resultados calculados (los llena el Integrante 1) */
typedef struct {
    double w_roz;          /* J   (a) trabajo de rozamiento        */
    double a_media;        /* m/s^2 (b)                            */
    double a_media_g;      /* en multiplos de g (b)                */
    double f_prom;         /* N   (c)                              */
    double f_prom_peso;    /* multiplos del peso (c)               */
    int    estado_gamma;   /* GAMMA_SEGURO / EXCESIVO / REBOTE (d) */
} Resultados;

/* ---------- Prototipos (Integrante 1: artemis.c) ---------- */
void   cargar_datos_nominales(Reingreso *datos);
double calcular_trabajo_rozamiento(const Reingreso *datos);
double calcular_desaceleracion_media(const Reingreso *datos);
double calcular_fuerza_impacto(const Reingreso *datos);
int    evaluar_angulo(double gamma);
void   calcular_resultados(const Reingreso *datos, Resultados *res);

#endif
