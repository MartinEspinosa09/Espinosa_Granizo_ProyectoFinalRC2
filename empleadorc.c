/*INTEGRANTES: Jair Granizo y Martin Espinosa
Fecha: 28-6-26
Descripcion: Un sistema diseñado en C que permite gestionar de manera integral el registro de empleados de una empresa. 
El programa maneja operaciones CRUD en memoria mediante arreglos de estructuras y asegura la persistencia de la informacion
a traves del almacenamiento automatico en un archivo plano (.csv).
Ademas, calcula automaticamente el sueldo total integrando las horas extra trabajadas con base en una tarifa fija.
*/
#include <stdio.h>
#include <string.h>
#include "empleadorc.h"

int max_empleados=100;
float valor_hora_extra = 5.0;

int main(){
    Empleado empleados[max_empleados];
    int contador=0;
    int opcion;

    cargarDesdeArchivo(empleados, &contador);
    do
    {
        printf("\n -GESTION DE EMPLEADOS- \n");
        printf("1. Registrar empleado\n");
        printf("2. Listar empleados\n");
        printf("3. Buscar empleado\n");
        printf("4. Actualizar empleado\n");
        printf("5. Eliminar empleado\n");
        printf("6. Guardar cambios en archivo\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        
       if (scanf("%d", &opcion) != 1) {
            printf("Error: Debe ingresar un numero entero.\n");
            
            while (getchar() != '\n'); 
            
            opcion = 0; 
        }

        switch (opcion)
        {
        case 1:

            registrarEmpleado(empleados, &contador);
            break;
        case 2:

            listarEmpleados(empleados, contador);
            break;
        case 3:

            buscarEmpleado(empleados, contador);
            break;
        case 4:

            actualizarEmpleado(empleados, contador);
            break;
        case 5:

            eliminarEmpleado(empleados, &contador);
            break;
        case 6:

            guardarEnArchivo(empleados, contador);
            break;        
        case 7:

            guardarEnArchivo(empleados, contador);
            printf("Datos guardados automaticamente.\n");
            break;

        default:
            printf("opcion no valida.");
            break;
        }
    } while (opcion != 7);
    return 0;
}
void registrarEmpleado(Empleado empleados[], int *contador){
    if (*contador >= max_empleados)
    {
        printf("ERROR: limite de empleados alcanzado\n");
        return;
    }
    Empleado nuevo;
    int repetido;
    printf("REGISTRAR\n");
    do
    {
        repetido=0;
        printf("ingresa el codigo\n");
        scanf("%s",nuevo.codigo_empleado);
        for (int i = 0; i < *contador; i++)
        {
            if (strcmp(empleados[i].codigo_empleado, nuevo.codigo_empleado)==0)
            {
                printf("ERROR: el codigo ya existe\n");
                repetido = 1;
                break;
            }
            
        }
        
    } while (repetido == 1);
    
    printf("Nombre: \n");
    scanf(" %[^\n]s", nuevo.nombre); 

    printf("Cargo: ");
    scanf(" %[^\n]s", nuevo.cargo);
    do {
        printf("Sueldo Base (mayor a 0): \n");
        scanf("%f", &nuevo.sueldo_base);
    } while (nuevo.sueldo_base <= 0);

    do {
        printf("Horas Extra (0 o mas): \n");
        scanf("%d", &nuevo.horas_extra);
    } while (nuevo.horas_extra < 0);

    empleados[*contador]=nuevo;
    (*contador)++;
    printf("empleado registrado con exito\n");
}

void listarEmpleados(Empleado empleados[], int contador){
    if (contador==0)
    {
        printf("no hay empleados registrados\n");
        return; 
    }
    printf("\n%-10s %-20s %-15s %-12s %-10s %-12s\n", "CODIGO", "NOMBRE", "CARGO", "SUELDO BASE", "H.EXTRA", "SUELDO TOTAL");

    for (int i = 0; i < contador; i++)
    {
        float sueldo_total=empleados[i].sueldo_base + (empleados[i].horas_extra*valor_hora_extra);

        printf("%-10s %-20s %-15s %-12.2f %-10d %-12.2f\n", empleados[i].codigo_empleado, empleados[i].nombre, empleados[i].cargo, empleados[i].sueldo_base, empleados[i].horas_extra, sueldo_total);
    }
    
}

void buscarEmpleado(Empleado empleados[], int contador){
    if (contador == 0)
    {
        printf("no hay empleados registrados para buscar\n");
        return;
    }
    
    char criterio[100];
    int encontrado=0; 
    printf("\nIngrese el codigo exacto o parte del nombre a buscar: \n");
    scanf(" %[^\n]s", criterio);

    for (int i = 0; i < contador; i++) {

        if (strcmp(empleados[i].codigo_empleado, criterio) == 0 || strstr(empleados[i].nombre, criterio) != NULL) {
            float sueldo_total = empleados[i].sueldo_base + (empleados[i].horas_extra * valor_hora_extra);
            
            printf("\n[Resultado] Codigo: %s | Nombre: %s | Cargo: %s | Sueldo Total: %.2f\n",
             empleados[i].codigo_empleado, empleados[i].nombre, empleados[i].cargo, sueldo_total);
            encontrado = 1;
        }
    }

    if (encontrado == 0) {
        printf("No se encontraron empleados con el criterio ingresado.\n");
    }
}

void actualizarEmpleado(Empleado empleados[], int contador) {
    char codigo[16];
    int encontrado = 0;

    printf("\nIngrese el codigo del empleado que desea modificar: ");
    scanf("%s", codigo);

    for (int i = 0; i < contador; i++) {
        if (strcmp(empleados[i].codigo_empleado, codigo) == 0) {
            encontrado = 1;
            printf("Modificando los datos de: %s\n", empleados[i].nombre);

            printf("Nuevo Nombre: ");
            scanf(" %[^\n]s", empleados[i].nombre);

            printf("Nuevo Cargo: ");
            scanf(" %[^\n]s", empleados[i].cargo);

            do {
                printf("Nuevo Sueldo Base (mayor a 0): ");
                scanf("%f", &empleados[i].sueldo_base);
            } while (empleados[i].sueldo_base <= 0);

            do {
                printf("Nuevas Horas Extra (0 o mas): ");
                scanf("%d", &empleados[i].horas_extra);
            } while (empleados[i].horas_extra < 0);

            printf("Empleado modificado correctamente.\n");
            break;
        }
    }

    if (encontrado == 0) {
        printf("Error: No se encontro ningun empleado con ese codigo.\n");
    }
}

void eliminarEmpleado(Empleado empleados[], int *contador) {
    char codigo[16];
    int encontrado = 0;
    char confirma;

    printf("\nIngrese el codigo del empleado que desea eliminar: ");
    scanf("%s", codigo);

    for (int i = 0; i < *contador; i++) {
        if (strcmp(empleados[i].codigo_empleado, codigo) == 0) {
            encontrado = 1;
            
            printf("¿Esta seguro de que desea eliminar a %s? (s/n): ", empleados[i].nombre);
            scanf(" %c", &confirma);

            if (confirma == 's' || confirma == 'S') {
                
                for (int j = i; j < *contador - 1; j++) {
                    empleados[j] = empleados[j + 1];
                }
                (*contador)--; 
                printf("Empleado eliminado del sistema.\n");
            } else {
                printf("Operacion cancelada.\n");
            }
            break;
        }
    }
    
    if (encontrado == 0) {
        printf("Error: Empleado no encontrado.\n");
    }
}

void guardarEnArchivo(Empleado empleados[], int contador) {
    FILE *archivo = fopen("empleados.csv", "w");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo para guardar datos.\n");
        return;
    }

    fprintf(archivo, "codigo_empleado,nombre,cargo,sueldo_base,horas_extra\n");

    for (int i = 0; i < contador; i++) {
        fprintf(archivo, "%s,%s,%s,%.2f,%d\n",
                empleados[i].codigo_empleado,
                empleados[i].nombre,
                empleados[i].cargo,
                empleados[i].sueldo_base,
                empleados[i].horas_extra);
    }
    fclose(archivo);
}

void cargarDesdeArchivo(Empleado empleados[], int *contador) {
    FILE *archivo = fopen("empleados.csv", "r");
    if (archivo == NULL) {
        return;
    }
    char cabecera[150];
    
    fgets(cabecera, sizeof(cabecera), archivo);

    while (fscanf(archivo, " %[^,],%[^,],%[^,],%f,%d\n",
                  empleados[*contador].codigo_empleado,
                  empleados[*contador].nombre,
                  empleados[*contador].cargo,
                  &empleados[*contador].sueldo_base,
                  &empleados[*contador].horas_extra) == 5) {
        
        (*contador)++;
        if (*contador >= max_empleados) {
            break;
        }
    }

    fclose(archivo);
}