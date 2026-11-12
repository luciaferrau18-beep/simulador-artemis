#include "artemis.h"

// -------------------------------------------------------------------------
// 1. CARGA DE DATOS POR DEFECTO
// Esta función llena la ficha de la nave con los datos nominales del trabajo
// -------------------------------------------------------------------------
void cargar_datos_nominales(Reingreso *datos) {
    datos->masa = MASA_NOMINAL;
    datos->vi = VI_NOMINAL;
    datos->h_inicial = H_INICIAL_NOMINAL;
    datos->vf = VF_NOMINAL;
    datos->h_paracaidas = H_PARACAIDAS_NOMINAL;
    datos->v_impacto = V_IMPACTO_NOMINAL;
    datos->dt = DT_NOMINAL;
    datos->d_hundimiento = D_HUNDIMIENTO_NOMINAL;
    datos->gamma = GAMMA_NOMINAL;
}

// -------------------------------------------------------------------------
// 2. CÁLCULO DEL TRABAJO DE ROZAMIENTO (Wroz) - Punto A
// Fórmula: Variación de Energía Mecánica (Energía Final - Energía Inicial)
// Energía Mecánica = Energía Cinética (0.5 * m * v^2) + Energía Potencial (m * g * h)
// -------------------------------------------------------------------------
double calcular_trabajo_rozamiento(const Reingreso *datos) {
    // Calculamos la energía allá arriba (a 120.000 metros)
    double energia_cinetica_inicial = 0.5 * datos->masa * (datos->vi * datos->vi);
    double energia_potencial_inicial = datos->masa * G * datos->h_inicial;
    double energia_mecanica_inicial = energia_cinetica_inicial + energia_potencial_inicial;

    // Calculamos la energía al momento de abrir el paracaídas (a 2.500 metros)
    double energia_cinetica_final = 0.5 * datos->masa * (datos->vf * datos->vf);
    double energia_potencial_final = datos->masa * G * datos->h_paracaidas;
    double energia_mecanica_final = energia_cinetica_final + energia_potencial_final;

    // El trabajo del rozamiento es la diferencia (el resultado dará negativo porque pierde energía)
    return energia_mecanica_final - energia_mecanica_inicial;
}

// -------------------------------------------------------------------------
// 3. CÁLCULO DE DESACELERACIÓN Y FUERZAS G - Punto B
// Fórmula: a = (Velocidad final - Velocidad inicial) / tiempo
// -------------------------------------------------------------------------
double calcular_desaceleracion_media(const Reingreso *datos) {
    // Calculamos cuánto frenó. Lo hacemos al revés (vi - vf) para que el número de 
    // desaceleración dé en positivo.
    double desaceleracion = (datos->vi - datos->vf) / datos->dt;
    return desaceleracion;
}

// -------------------------------------------------------------------------
// 4. CÁLCULO DE FUERZA DE IMPACTO EN EL AGUA - Punto C
// Al chocar contra el agua, el agua absorbe la energía cinética del impacto.
// Fórmula de Trabajo: Fuerza * distancia = Energía Cinética
// -------------------------------------------------------------------------
double calcular_fuerza_impacto(const Reingreso *datos) {
    // Energía cinética justo en el instante de tocar el agua a 8 m/s
    double energia_cinetica_impacto = 0.5 * datos->masa * (datos->v_impacto * datos->v_impacto);
    
    // Fuerza requerida para frenar esa energía en solo 1,5 metros (datos->d_hundimiento)
    // Le sumamos el propio peso de la nave (masa * G) que también empuja hacia abajo.
    double fuerza_agua = (energia_cinetica_impacto / datos->d_hundimiento) + (datos->masa * G);
    
    return fuerza_agua;
}

// -------------------------------------------------------------------------
// 5. EVALUACIÓN DE LA VENTANA DE SEGURIDAD - Punto D
// Analiza si el ángulo (gamma) es seguro, muy abierto o muy cerrado.
// -------------------------------------------------------------------------
int evaluar_angulo(double gamma) {
    if (gamma > GAMMA_MAX) {
        return GAMMA_EXCESIVO; // Es mayor a 7.0
    } else if (gamma < GAMMA_MIN) {
        return GAMMA_REBOTE;   // Es menor a 5.5
    } else {
        return GAMMA_SEGURO;   // Está entre 5.5 y 7.0
    }
}

// -------------------------------------------------------------------------
// 6. ENSAMBLAJE DE RESULTADOS
// Esta función es llamada por el menú principal. Ejecuta todas las fórmulas
// de arriba y guarda las respuestas en la ficha "Resultados".
// -------------------------------------------------------------------------
void calcular_resultados(const Reingreso *datos, Resultados *res) {
    res->w_roz = calcular_trabajo_rozamiento(datos);
    
    res->a_media = calcular_desaceleracion_media(datos);
    res->a_media_g = res->a_media / G; // Convertimos la aceleración en fuerzas G
    
    res->f_prom = calcular_fuerza_impacto(datos);
    res->f_prom_peso = res->f_prom / (datos->masa * G); // Lo expresamos como múltiplo del peso
    
    res->estado_gamma = evaluar_angulo(datos->gamma);
}