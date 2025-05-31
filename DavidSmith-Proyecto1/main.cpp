#include <iostream>
#include <locale.h>
#include <string>


using namespace std;


void mostrarMenu() {

    cout << "Menú Principal" << endl;
    cout << endl;
    cout << "1. Agregar tareas" << endl;
    cout << "2. Buscar tarea" << endl;
    cout << "3. Mostrar todas las tareas" << endl;
    cout << "4. Eliminar tarea" << endl;
    cout << "5. Salir del programa" << endl;
    cout << endl;
}

void solicitarInfoTarea() {
    unsigned int idTarea{0};
    string nombreTarea;
    string fechaVencimiento;
    string horaInicio;
    string horaFin;

    cout << "Ingrese la información de la tarea: " << endl;

    cout << "Código de la tarea(4 dígitos): ";
    cin >> idTarea;

    cout << "Nombre de la tarea: ";
    cin >> nombreTarea;

    cout << "Fecha de vencimiento (dd/mm/aaaa): ";
    cin >> fechaVencimiento;

    cout << "Hora de inicio (hh:mm): ";
    cin >> horaInicio;

    cout << "Hora de finización (hh:mm): ";
    cin >> horaFin;

    cout << endl;
}

void agregarTareas() {

    unsigned int cantidadTareas{0};

    cout << "Ingrese la cantidad de tareas que desea agregar: ";
    cin >> cantidadTareas;

    for(unsigned int i = 0; i < cantidadTareas; i++){
        solicitarInfoTarea();
        cout << "Tarea agregada exitosamente" << endl;
        cout << endl;
    }

}

void buscarTarea() {
}

void mostrarTareas() {
}

void eliminarTarea() {
}


int main()
{
    setlocale(LC_CTYPE, "");

    bool salir{false};
    unsigned int entradaMenu{0};


    do {
        mostrarMenu();
        cout << "Ingrese una opción del menú: ";
        cin >> entradaMenu;
        cout << endl;

        switch (entradaMenu) {
        case 1:
            agregarTareas();
            break;
        case 2:
            buscarTarea();
            break;
        case 3:
            mostrarTareas();
            break;
        case 4:
            eliminarTarea();
            break;
        case 5:
            salir = true;
            break;
        default:
            break;
        }
    } while (!salir);


    return 0;
}
