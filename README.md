*Este proyecto ha sido creado como parte del currículo de 42 por joaqumar.*

# 🖨️ ft_printf

## 📝 Descripción
El proyecto **ft_printf** consiste en recrear la famosa función `printf` de la librería estándar de C (`libc`). El objetivo principal es aprender a manejar **funciones variádicas** (usando la librería `stdarg.h`) y profundizar en la gestión eficiente de flujos de datos mediante el uso de un **buffer de salida**. 

Esta implementación imita el comportamiento original de `printf`, devolviendo el número total de caracteres impresos y gestionando diversos tipos de conversiones y flags de formato bajo las estrictas restricciones de la **Norma de 42**.

## 📂 Estructura del Proyecto

Para cumplir con la restricción de un máximo de 5 funciones por archivo, el código se organiza de la siguiente manera:


| Archivo | Responsabilidad |
| :--- | :--- |
| 🚀 `ft_printf.c` | Punto de entrada, gestión del ciclo de vida del buffer y bucle de formato. |
| 🔍 `ft_parser.c` | Análisis y captura de flags (`-0.# +`), ancho de campo y precisión. |
| 🛤️ `ft_dispatch.c` | Distribuidor de conversiones (Dispatcher) para cada especificador. |
| 🔢 `ft_print_nums.c` | Lógica de impresión para enteros (`%d`, `%i`, `%u`) con gestión de signos. |
| ⬢ `ft_print_hex.c` | Lógica para hexadecimales (`%x`, `%X`) y punteros (`%p`). |
| 🛠️ `ft_utils.c` | Herramientas base: cálculo de longitudes y gestión de bases numéricas. |

## ⚙️ Instrucciones

### Compilación
El proyecto se compila mediante un `Makefile` que incluye las reglas `all`, `clean`, `fclean` y `re`. Para generar la librería:
```bash
make
```

### Ejecución
Para utilizar `ft_printf` en tu código, incluye el encabezado y vincula el archivo `.a` generado:
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

## 📚 Recursos
- **Documentación**: Referencia de la función `printf(3)` del manual de Linux.
- **Tutoriales**: Guías sobre el manejo de la estructura `va_list` y macros asociadas.
- **Uso de IA**: Se ha utilizado inteligencia artificial generativa para:
    - Diseñar la arquitectura de la estructura unificada `t_printf`.
    - Optimizar la lógica del buffer para evitar llamadas excesivas a `write`.
    - Generar la documentación técnica y la estructura visual del README.

## 🏗️ Decisiones Técnicas: Algoritmo y Estructura de Datos

### 💾 Estructura de Datos: `t_printf`
Se ha diseñado una estructura de datos unificada que actúa como el "estado global" de la función. Contiene el buffer de caracteres, el índice actual, el contador total y todas las variables de flags.
- **Justificación**: Permite acceso total a la información mediante un único puntero, eliminando variables globales y facilitando la modularidad entre archivos.

### ⚡ Algoritmo de Salida: Gestión de Buffer
En lugar de imprimir cada carácter individualmente, se utiliza un buffer de **4096 bytes**.
- **Justificación**: Minimizar las llamadas al sistema (`write`) optimiza drásticamente el rendimiento, acumulando datos en RAM antes de enviarlos a la salida estándar.

### 🎯 Algoritmo de Formateo: Pre-cálculo
Para los flags de bonus, se utiliza un algoritmo de tres pasos:
1. **Captura**: El parser extrae los valores.
2. **Cálculo**: Se determina el tamaño total de la "caja" (espacios + ceros + prefijos + valor).
3. **Volcado**: Se envían los componentes al buffer en un orden jerárquico estricto.

---
