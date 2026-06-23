# ft_printf

## 👤 Descripción General del Proyecto y Colaboración con IA

Para mantener el proyecto comprensible, mantenible y alineado con el proceso de evaluación de 42, el desarrollo se estructuró en torno al manejo eficiente de argumentos variables, un sistema unificado de control de estados y un flujo optimizado de volcado de datos.

- **Arquitectura de estado unificada:** Diseñado e implementado un mecanismo de control basado en una estructura única (`t_printf`) para encapsular el buffer y los estados de los flags, eliminando la necesidad de variables globales.
- **Optimización de salida:** Implementado un sistema de almacenamiento intermedio (buffering) para mitigar el impacto de las llamadas al sistema, acumulando caracteres en RAM antes de realizar operaciones de escritura.
- **Modularidad avanzada:** Estructurado el flujo de control en módulos atómicos específicos para cumplir estrictamente con la restricción de un máximo de 5 funciones por archivo exigida por la Norma de 42.

---

## 📝 Descripción

El proyecto **ft_printf** consiste en recrear la famosa función `printf` de la librería estándar de C (`libc`). El objetivo principal es aprender a manejar funciones variádicas y profundizar en la gestión eficiente de flujos de datos mediante el uso de un buffer de salida.

Esta implementación imita fielmente el comportamiento original de `printf`, devolviendo el número total de caracteres impresos y gestionando diversos tipos de conversiones y flags de formato bajo las estrictas restricciones de la Norma de 42.

---

## 📂 Estructura del Proyecto

Para cumplir con la restricción de un máximo de 5 funciones por archivo, el código se organiza minuciosamente de la siguiente manera:

- **🚀 ft_printf.c:** Punto de entrada principal, gestión del ciclo de vida del buffer y bucle principal de análisis de formato.
- **🔍 ft_parser.c:** Análisis sintáctico y captura de flags (`-`, `0`, `.`, `#`, ` `, `+`), cálculo de ancho de campo (width) y precisión.
- **🛤️ ft_dispatch.c:** Distribuidor de conversiones (Dispatcher) encargado de derivar el control al módulo adecuado según el especificador.
- **🔢 ft_print_nums.c:** Lógica de procesamiento e impresión para enteros (`%d`, `%i`, `%u`) con gestión rigurosa de signos.
- **⬢ ft_print_hex.c:** Lógica de conversión para formatos hexadecimales (`%x`, `%X`) y direcciones de memoria/punteros (`%p`).
- **🛠️ ft_utils.c:** Herramientas base del proyecto, cálculo de longitudes numéricas y gestión de bases aritméticas.

---

## 📐 Decisiones Técnicas: Algoritmo y Estructura de Datos

El proyecto está diseñado bajo un paradigma modular donde la estructura de control dirige el flujo de datos a través de buffers de memoria antes de interactuar con el sistema operativo.

### 💾 Estructura de Datos Unificada: `t_printf`

Se ha diseñado una estructura de datos unificada que actúa como el "estado global" de la función. Contiene el buffer de caracteres, el índice actual, el contador total de bytes impresos y todas las variables booleanas y numéricas de los flags.

- **Justificación:** Permite el acceso total y seguro a la información mediante un único puntero pasándolo por referencia. Esto elimina por completo el uso de variables globales proscritas y facilita la comunicación modular entre los diferentes archivos del proyecto.

### ⚡ Algoritmo de Salida: Gestión de Buffer Activo

En lugar de imprimir cada carácter individualmente utilizando llamadas primitivas repetidas, el sistema utiliza un buffer estático de 4096 bytes en memoria.

- **Justificación:** Las llamadas al sistema (`write`) son operaciones computacionalmente costosas debido al cambio de contexto entre el espacio de usuario y el espacio de kernel. Minimizar estas llamadas optimiza drásticamente el rendimiento general de la función, acumulando los datos en la memoria RAM y vaciando el bloque (flush) únicamente cuando el buffer está lleno o la función finaliza.

### 🎯 Algoritmo de Formateo: Pre-cálculo Jerárquico

Para resolver correctamente la combinación compleja de flags de bonus, se utiliza un algoritmo predictivo de tres pasos:

1. **Captura:** El parser extrae los valores numéricos del ancho de campo, la precisión y activa los flags presentes.
2. **Cálculo:** Se determina matemáticamente el tamaño total que ocupará la "caja" de texto final (calculando espacios de padding, ceros de precisión, prefijos como `0x` o signos `+`/`-` junto al valor numérico).
3. **Volcado:** Se envían los componentes al buffer en un orden jerárquico estricto y secuencial, garantizando que el formato final sea idéntico al de la `libc`.

---

## 🧠 Guía de Defensa y Casos Borde (Edge Cases)

Para superar los tests automatizados más exigentes de la comunidad de 42, el código implementa soluciones nativas para escenarios críticos:

- **Gestión del Puntero Nulo (`%s` y `%p` con NULL):** Si se pasa un puntero `NULL` a un especificador de cadena, imprime de forma segura `(null)` (o las variantes según el sistema operativo). Para punteros `%p`, gestiona la salida correcta como `(nil)` o `0x0`.
- **Desbordamientos de Enteros (Overflows):** El manejo de números como `LONG_MIN` o `INT_MIN` se realiza mediante el uso de tipos de datos de mayor capacidad (`long long` o `unsigned long long`) durante los cálculos intermedios para evitar comportamientos indeterminados.
- **Conflicto de Flags Proclives a Anularse:** El código cuenta con lógica de precedencia implícita. Por ejemplo, el flag `-` (alineación a la izquierda) anula el efecto del flag `0` (relleno de ceros), y el flag `+` (mostrar siempre signo) tiene prioridad sobre el flag ` ` (espacio en blanco).

---

## 🛠️ Uso y Compilación

### Requisitos
- `cc`, `clang` o `gcc`
- Herramienta de automatización `make`
- Entorno basado en Unix (Linux, macOS)

### Compilación de la Librería

Para generar el archivo de librería estática (`libftprintf.a`), ejecuta el comando base en la raíz del proyecto:
```bash
make
```
El Makefile incluye las reglas obligatorias exigidas por el enunciado: `all`, `clean`, `fclean` y `re`.

### Vinculación e Integración

Para utilizar `ft_printf` en tu propio código fuente en C, incluye su encabezado y vincula el archivo `.a` generado durante la compilación de tu binario final:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hola %s, el número es %+10.5d\n", "Mundo", 42);
    return (0);
}
```

```bash
gcc main.c libftprintf.a -o mi_programa
./mi_programa
```

---

## 📚 Recursos y Referencias

### Referencias Bibliográficas
- Manual de Linux: Referencia de la función `printf(3)`.
- Estándar ISO/IEC 9899: Documentación oficial sobre tipos variádicos y macros asociadas (`va_list`, `va_start`, `va_arg`, `va_end`).
- Directrices de optimización de llamadas al sistema en sistemas POSIX.

### Declaración de Uso de IA
La asistencia de inteligencia artificial generativa se utilizó estrictamente como una herramienta de soporte y optimización arquitectónica durante el flujo de trabajo:
- **Diseño Arquitectónico:** Conceptualización de la estructura de control unificada `t_printf` para la modularidad entre archivos.
- **Optimización de Memoria:** Refactorización de la lógica del buffer de salida para garantizar la mínima cantidad de llamadas a `write()`.
- **Documentación:** Generación y formatting estructural de los esquemas visuales de este archivo README.md.

Toda la implementación fue auditada, adaptada, compilada y aprobada manualmente mediante la suite de herramientas oficiales, garantizando el cumplimiento total de la Norminette de 42 y la ausencia absoluta de fugas de memoria.

---

## ⚖️ Descargo de Responsabilidad (Disclaimer)

Este repositorio ha sido creado con fines puramente académicos y como parte de mi proceso de aprendizaje en el plan de estudios de **42**.

* **Uso bajo tu propio riesgo:** No me hago responsable del uso que se le dé al código de este repositorio, ni de las consecuencias derivadas de su copia, modificación o reutilización en tus propias entregas.
* **Política de copia de 42 (Plagio):** Se recuerda a los estudiantes de 42 que el plagio o la copia directa de código sin comprender su funcionamiento infringe las normas de la escuela y puede ser penalizado de forma severa por los sistemas de evaluación automática o manual (*Moulinette* / Evaluadores).
* **Propósito:** El código se comparte con el único objetivo de servir como referencia, consulta técnica o inspiración para resolver arquitecturas de Makefiles complejos y automatización de tests interactivos.
