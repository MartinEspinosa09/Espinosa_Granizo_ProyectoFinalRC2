#ifndef EMPLEADOS_H
#define EMPLEADOS_H


typedef struct {
    char codigo_empleado[16]; 
    char nombre[100];
    char cargo[50];
    float sueldo_base;
    int horas_extra;
} Empleado;


void registrarEmpleado(Empleado empleados[], int *contador);
void listarEmpleados(Empleado empleados[], int contador);
void buscarEmpleado(Empleado empleados[], int contador);
void actualizarEmpleado(Empleado empleados[], int contador);
void eliminarEmpleado(Empleado empleados[], int *contador);
void guardarEnArchivo(Empleado empleados[], int contador);
void cargarDesdeArchivo(Empleado empleados[], int *contador);

#endif