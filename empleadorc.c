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

