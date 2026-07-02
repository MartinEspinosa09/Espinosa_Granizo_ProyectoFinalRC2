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
