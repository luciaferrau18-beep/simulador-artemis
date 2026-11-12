
# Simulador Misión Artemis - Escenario 4: Reingreso Atmosférico

## 1. Información General y Cátedra
* **Universidad:** Universidad Tecnológica Nacional - Facultad Regional Resistencia
* **Cátedra:** Algoritmos y Estructuras de Datos
* **Carrera:** Ingeniería en Sistemas de Información
* **Comisión:** k1.3
* **Integrantes:**
  - Miguez Maia Joaquina Victoria- Legajo: 31076
  - Ramirez Oriana Micaela- Legajo: 29610
  - Ferrau Lucia Belen - Legajo: 29204
  - Dias Brisa - Legajo: 31482

---

## 2. Descripción del Escenario 4
Este sistema simula la fase final de retorno de la cápsula Orion ($m = 10.400\text{ kg}$) atravesando la atmósfera terrestre hasta el amerizaje.

### Cálculos realizados por el simulador:
1. **Trabajo de Rozamiento Atmosférico ($W_{roz}$):** Calcula la pérdida de energía entre los $120\text{ km}$ ($11.000\text{ m/s}$) y los $2,5\text{ km}$ ($25\text{ m/s}$).
2. **Desaceleración Media:** Determina la aceleración media ejercida en un tiempo $\Delta t = 400\text{ s}$ expresada en $\text{m/s}^2$ y en múltiplos de la gravedad ($g$).
3. **Fuerza Promedio de Amerizaje ($F_{prom}$):** Calcula la fuerza ejercida por el agua durante un hundimiento de $1,5\text{ m}$.
4. **Ángulo de Reingreso ($\gamma$):** Evalúa el rango seguro ($5,5^\circ \le \gamma \le 7,0^\circ$), alertando sobre rebotes fuera de la atmósfera o destrucción por fricción.

---

## 3. Arquitectura del Código
El programa fue desarrollado bajo el estándar C99 aplicando programación estructurada y modularización avanzada:
* `main.c`: Menú interactivo y flujo principal del programa.
* `artemis.h` / `artemis.c`: Definición de estructuras (`struct`) y funciones de física espacial.
* `validaciones.h` / `validaciones.c`: Control estricto contra entradas inválidas y limpieza de buffer de teclado.
* `Makefile`: Script para la compilación automatizada del proyecto.

---

## 4. Compilación y Ejecución

### Compilación Manual con GCC
```bash
gcc -Wall main.c artemis.c validaciones.c -o simulador -lm

## 5. Registro de Uso de Inteligencia Artificial (Bitácora).

## 4. Registro de Uso de Inteligencia Artificial (Bitácora)

En cumplimiento con las normativas de la cátedra, se detalla el uso ético y asistencial de herramientas de Inteligencia Artificial Generativa empleadas durante el desarrollo del proyecto:

## 4. Registro de Uso de Inteligencia Artificial (Bitácora)

En cumplimiento con las normativas de la cátedra, se detalla el uso ético y asistencial de herramientas de Inteligencia Artificial Generativa empleadas durante el desarrollo del proyecto:

| Herramienta de IA | Consulta o Prompt Realizado | Validación y Adaptación en el Código |
| :--- | :--- | :--- |
| Gemini | *"Sintaxis Markdown para estructurar el archivo README y tablas"* | Se utilizó la estructura generada para redactar la documentación oficial cumpliendo los requisitos formales de la rúbrica. |
| ChatGPT | *"¿Cómo vaciar el buffer de entrada en C tras usar scanf para evitar bucles infinitos al ingresar letras?"* | La IA sugirió un bucle `while(getchar() != '\n');`. Se adaptó y encapsuló dentro de la función `vaciar_buffer()` en el módulo `validaciones.c`. |
| GitHub Copilot | *"¿Cómo validar que el usuario realmente ingresó un número tipo float/double y no un caracter?"* | Sugirió verificar que el valor de retorno sea igual a 1 (`if(scanf("%lf", &valor) != 1)`). Lo integramos en los menús de ingreso de datos para evitar cierres inesperados del simulador. |
| ChatGPT | *"¿Por qué me da error de 'multiple definition' al separar mis funciones en main.c y artemis.c?"* | Explicó el uso de las guardas de inclusión (`#ifndef`, `#define`). Las implementamos en `artemis.h` y `validaciones.h` para proteger las estructuras y evitar que se compilen dos veces. |
| Claude | *"¿Cómo calculo un número elevado al cuadrado en lenguaje C para la fórmula de energía cinética?"* | Indicó que se debe usar la función `pow(base, 2)` de la librería `<math.h>` y compilar con `-lm`. Se aplicó en `artemis.c` para el cálculo de la fuerza de amerizaje y el trabajo de rozamiento. |



