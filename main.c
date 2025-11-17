#include <stdio.h>
#include <string.h>
#include <ctype.h>  
#include <stdlib.h> 

#define MAX_PRODUCTOS 5
#define MAX_NOMBRE 50


int valida_int() {
    char buffer[100];
    int valido;

    do {
        fgets(buffer, 100, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; 

        valido = 1;
        int len = strlen(buffer);

        if (len == 0) {
            valido = 0; 
        }

        for (int i = 0; i < len; i++) {
            if (!isdigit(buffer[i])) {
                valido = 0; 
                break;
            }
        }

        if (valido == 0) {
            printf("ERROR. Ingrese un numero entero valido: ");
        }

    } while (valido == 0);

    return atoi(buffer); 
}


float valida_float() {
    char buffer[100];
    int valido;
    
    do {
        fgets(buffer, 100, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        valido = 1;
        int len = strlen(buffer);
        int puntoEncontrado = 0;

        if (len == 0) {
            valido = 0; 
        }

        for (int i = 0; i < len; i++) {
            if (isdigit(buffer[i])) {
                continue;
            } 
            else if (buffer[i] == '.' && puntoEncontrado == 0) {
                puntoEncontrado = 1; 
            } else {
                valido = 0;
                break;
            }
        }

        if (valido == 0) {
            printf("ERROR. Ingrese un numero valido (ej: 12.5): ");
        }

    } while (valido == 0);

    return atof(buffer); 
}



int esNombreValido(const char *nombre) {
    int len = strlen(nombre);
    if (len == 0) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (isdigit(nombre[i])) {
            return 0; 
        }
    }
    return 1; 
}

void ingresarProductos(char nombres[][MAX_NOMBRE],
                       int cantidades[],
                       float tiemposUnitarios[],
                       float recursosUnitarios[],
                       int *numProductos)
{
    int i;
    int total;

    printf("Cuantos productos desea ingresar, maximo cinco: ");
    total = valida_int(); 

    if (total < 1) {
        printf("Debe ingresar al menos un producto.\n");
        return;
    }

    if (total > MAX_PRODUCTOS) {
        total = MAX_PRODUCTOS;
        printf("Solo se tomaran en cuenta cinco productos.\n");
    }

    *numProductos = total;

    for (i = 0; i < total; i++) {
        printf("\nProducto %d\n", i + 1);

        
        do {
            printf("Nombre: ");
            
            fgets(nombres[i], MAX_NOMBRE, stdin);
            nombres[i][strcspn(nombres[i], "\n")] = '\0';

            if (!esNombreValido(nombres[i])) {
                printf("Error: El nombre no puede contener numeros ni estar vacio. Intente de nuevo.\n");
            }
        } while (!esNombreValido(nombres[i]));

        printf("Cantidad demandada: ");
        cantidades[i] = valida_int(); 

        printf("Tiempo de fabricacion por unidad en horas: ");
        tiemposUnitarios[i] = valida_float(); 

        printf("Recursos requeridos por unidad, unidades de recurso: ");
        recursosUnitarios[i] = valida_float(); 
    }
}

int buscarProducto(char nombres[][MAX_NOMBRE], int numProductos)
{
    char nombreBuscado[MAX_NOMBRE];
    int i;

    if (numProductos == 0) {
        printf("No hay productos registrados.\n");
        return -1;
    }

    printf("Ingrese el nombre del producto a buscar: ");
    
    fgets(nombreBuscado, MAX_NOMBRE, stdin);
    nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';

    for (i = 0; i < numProductos; i++) {
        if (strcmp(nombres[i], nombreBuscado) == 0) {
            return i;
        }
    }

    printf("Producto no encontrado.\n");
    return -1;
}

void editarProducto(char nombres[][MAX_NOMBRE],
                    int cantidades[],
                    float tiemposUnitarios[],
                    float recursosUnitarios[],
                    int numProductos)
{
    int indice;

    indice = buscarProducto(nombres, numProductos);
    if (indice == -1) {
        return;
    }

    printf("\nEditando producto: %s\n", nombres[indice]);

    
    {
        char nuevoNombre[MAX_NOMBRE];
        int nombreValido = 0;

        do {
            printf("Nuevo nombre, deje vacio para mantener: ");
            
            fgets(nuevoNombre, MAX_NOMBRE, stdin);
            nuevoNombre[strcspn(nuevoNombre, "\n")] = '\0';

            if (strlen(nuevoNombre) == 0) {
                nombreValido = 1; 
            } else if (!esNombreValido(nuevoNombre)) {
                printf("Error: El nombre no puede contener numeros. Intente de nuevo.\n");
                nombreValido = 0; 
            } else {
                strcpy(nombres[indice], nuevoNombre);
                nombreValido = 1; 
            }
        } while (nombreValido == 0);
    }

    printf("Nueva cantidad demandada, valor negativo para mantener: ");
    {
        int nuevaCantidad;
        nuevaCantidad = valida_int(); 
        if (nuevaCantidad >= 0) {
            cantidades[indice] = nuevaCantidad;
        }
    }

    printf("Nuevo tiempo por unidad en horas, valor negativo para mantener: ");
    {
        float nuevoTiempo;
        nuevoTiempo = valida_float(); 
        if (nuevoTiempo >= 0.0f) {
            tiemposUnitarios[indice] = nuevoTiempo;
        }
    }

    printf("Nuevos recursos por unidad, valor negativo para mantener: ");
    {
        float nuevoRecurso;
        nuevoRecurso = valida_float(); 
        if (nuevoRecurso >= 0.0f) {
            recursosUnitarios[indice] = nuevoRecurso;
        }
    }
}

void eliminarProducto(char nombres[][MAX_NOMBRE],
                      int cantidades[],
                      float tiemposUnitarios[],
                      float recursosUnitarios[],
                      int *numProductos)
{
    int indice;
    int i;

    indice = buscarProducto(nombres, *numProductos);
    if (indice == -1) {
        return;
    }

    for (i = indice; i < (*numProductos) - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        tiemposUnitarios[i] = tiemposUnitarios[i + 1];
        recursosUnitarios[i] = recursosUnitarios[i + 1];
    }

    (*numProductos)--;
    printf("Producto eliminado.\n");
}

void calcularTotales(int cantidades[],
                     float tiemposUnitarios[],
                     float recursosUnitarios[],
                     int numProductos,
                     float *tiempoTotal,
                     float *recursosTotales)
{
    int i;
    float tiempo = 0.0f;
    float recursos = 0.0f;

    for (i = 0; i < numProductos; i++) {
        tiempo = tiempo + tiemposUnitarios[i] * cantidades[i];
        recursos = recursos + recursosUnitarios[i] * cantidades[i];
    }

    *tiempoTotal = tiempo;
    *recursosTotales = recursos;
}

void mostrarResumen(char nombres[][MAX_NOMBRE],
                    int cantidades[],
                    float tiemposUnitarios[],
                    float recursosUnitarios[],
                    int numProductos)
{
    int i;
    float tiempoTotal;
    float recursosTotales;

    if (numProductos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    printf("\nResumen de productos\n");
    for (i = 0; i < numProductos; i++) {
        printf("\nProducto %d\n", i + 1);
        printf("Nombre: %s\n", nombres[i]);
        printf("Cantidad: %d\n", cantidades[i]);
        printf("Tiempo por unidad: %.2f horas\n", tiemposUnitarios[i]);
        printf("Recursos por unidad: %.2f unidades\n", recursosUnitarios[i]);
    }

    calcularTotales(cantidades, tiemposUnitarios, recursosUnitarios,
                    numProductos, &tiempoTotal, &recursosTotales);

    printf("\nTiempo total de fabricacion: %.2f horas\n", tiempoTotal);
    printf("Recursos totales requeridos: %.2f unidades\n", recursosTotales);
}

void verificarCapacidad(int cantidades[],
                        float tiemposUnitarios[],
                        float recursosUnitarios[],
                        int numProductos)
{
    float tiempoDisponible;
    float recursosDisponibles;
    float tiempoTotal;
    float recursosTotales;

    if (numProductos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    printf("Ingrese el tiempo disponible en horas: ");
    tiempoDisponible = valida_float(); 

    printf("Ingrese los recursos disponibles: ");
    recursosDisponibles = valida_float(); 

    calcularTotales(cantidades, tiemposUnitarios, recursosUnitarios,
                    numProductos, &tiempoTotal, &recursosTotales);

    printf("\nTiempo total requerido: %.2f horas\n", tiempoTotal);
    printf("Recursos totales requeridos: %.2f unidades\n", recursosTotales);

    if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
        printf("La fabrica puede cumplir con la demanda.\n");
    } else {
        printf("La fabrica no puede cumplir con la demanda.\n");
    }
}

int main(void)
{
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    int cantidades[MAX_PRODUCTOS];
    float tiemposUnitarios[MAX_PRODUCTOS];
    float recursosUnitarios[MAX_PRODUCTOS];
    int numProductos = 0;
    int opcion;

    do {
        printf("\nMenu principal\n");
        printf("1. Ingresar productos\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar resumen de produccion\n");
        printf("5. Verificar si se puede cumplir la demanda\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        opcion = valida_int(); 

        switch (opcion) {
        case 1:
            ingresarProductos(nombres, cantidades,
                              tiemposUnitarios, recursosUnitarios,
                              &numProductos);
            break;
        case 2:
            editarProducto(nombres, cantidades,
                           tiemposUnitarios, recursosUnitarios,
                           numProductos);
            break;
        case 3:
            eliminarProducto(nombres, cantidades,
                             tiemposUnitarios, recursosUnitarios,
                             &numProductos);
            break;
        case 4:
            mostrarResumen(nombres, cantidades,
                           tiemposUnitarios, recursosUnitarios,
                           numProductos);
            break;
        case 5:
            verificarCapacidad(cantidades,
                               tiemposUnitarios, recursosUnitarios,
                               numProductos);
            break;
        case 0:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opcion no valida.\n");
            break;
        }

    } while (opcion != 0);

    return 0;
}
