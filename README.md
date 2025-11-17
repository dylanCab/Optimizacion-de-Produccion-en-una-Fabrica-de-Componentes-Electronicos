# Sistema de Optimización de Producción (Taller RC1)

Este repositorio es una aplicación de consola desarrollada en **Lenguaje C** que simula un sistema para gestionar y optimizar la producción en una fábrica de componentes electrónicos. El programa calcula los recursos y tiempos totales requeridos para una demanda específica y verifica si la fábrica tiene la capacidad de cumplirla.

## Características Principales

El programa es completamente robusto y maneja un menú interactivo con las siguientes funcionalidades:

* **Ingresar Productos:** Permite registrar hasta 5 productos distintos.
* **Editar Productos:** Modificar los datos de un producto existente (nombre, cantidad, etc.).
* **Eliminar Productos:** Borrar un producto de la lista.
* **Mostrar Resumen:** Calcula y muestra el tiempo total y los recursos totales necesarios para la demanda actual.
* **Verificar Capacidad:** Compara los totales requeridos con los recursos disponibles de la fábrica para determinar si la producción es viable.
* **Validación Robusta:** Incluye validación de **todas** las entradas del usuario:
    * Evita que se ingresen números en los nombres de los productos.
    * Impide que la aplicación falle si se ingresan letras en campos numéricos (usando `valida_int` y `valida_float`).

## Restricciones Técnicas del Proyecto

Este proyecto fue desarrollado adhiriéndose a las estrictas restricciones de la consigna académica, demostrando un manejo de C a bajo nivel:

* **Sin Estructuras (`structs`):** La gestión de los datos de los productos se implementa mediante **arreglos paralelos**.
* **Sin Persistencia de Datos:** El programa no utiliza archivos; todos los datos se manejan en memoria durante la ejecución.
* **Lógica de Búsqueda Propia:** La función `buscarProducto` implementa una búsqueda lineal (`for` + `strcmp`) y no utiliza funciones predefinidas de C como `bsearch`.
* **Uso de Punteros:** Se utilizan punteros (`int *numProductos`) para modificar el estado del programa (el contador de productos) desde funciones externas.

## Cómo Compilar y Ejecutar

El programa está contenido en un único archivo (`main.c`) y no requiere dependencias externas más allá de las librerías estándar de C.

1.  Clona el repositorio:
    ```bash
    git clone [URL_DE_TU_REPOSITORIO_GITHUB]
    ```

2.  Navega al directorio del proyecto:
    ```bash
    cd [NOMBRE_DEL_DIRECTORIO]
    ```

3.  Compila el programa usando `gcc`:
    ```bash
    gcc main.c -o optimizador
    ```

4.  Ejecuta el programa:
    ```bash
    ./optimizador
    ```

## Autores

* Dylan Cabascango
* Nick Garzón
