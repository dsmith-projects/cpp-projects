#include <iostream>
#include <locale>
#include <string>


using namespace std;


void mostrarMenu();

bool verificarExistenciaTarea(unsigned int);

void solicitarInfoTarea();

void agregarTareas();

void buscarTarea();

void mostrarTareas();

void eliminarTarea();

bool regresarAlMenu();


int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8");

    bool salir{false};
    unsigned int entradaMenu{0};
    bool regresarAMenu = false;

    do {
        mostrarMenu();
        cout << "Ingrese una opción del menú: ";
        cin >> entradaMenu;
        cout << endl;

        switch (entradaMenu) {
        case 1:
            do {
                agregarTareas();
                regresarAMenu = regresarAlMenu();
            } while(!regresarAMenu);

            break;
        case 2:
            do {
                buscarTarea();
                regresarAMenu = regresarAlMenu();
            } while(!regresarAMenu);

            break;
        case 3:
            do {
                mostrarTareas();
                regresarAMenu = regresarAlMenu();
            } while(!regresarAMenu);

            break;
        case 4:
            do {
                eliminarTarea();
                regresarAMenu = regresarAlMenu();
            } while(!regresarAMenu);
            break;
        case 5:
            salir = true;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
            cout << endl;
            break;
        }
    } while (!salir);


    return 0;
}

void mostrarMenu() {

    cout << "¡Menú Principal!" << endl;
    cout << endl;
    cout << "1. Agregar tareas" << endl;
    cout << "2. Buscar tarea" << endl;
    cout << "3. Mostrar todas las tareas" << endl;
    cout << "4. Eliminar tarea" << endl;
    cout << "5. Salir del programa" << endl;
    cout << endl;
}

bool verificarExistenciaTarea(unsigned int idTarea) {
    return true;
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
    cout << endl;

    for(unsigned int i = 0; i < cantidadTareas; i++){
        solicitarInfoTarea();
        cout << "Tarea agregada exitosamente" << endl;
        cout << endl;
    }
}

void buscarTarea() {
    unsigned int idTarea{0};

    cout << "Ingrese el código de la tarea a buscar: " << endl;
    cin >> idTarea;
    cout << endl;
}

void mostrarTareas() {
}

void eliminarTarea() {
    unsigned int idTarea{0};
    bool tareaExiste{false};
    bool borrarTarea = false;
    char entrada;

    cout << "Ingrese el código de la tarea a eliminar: " << endl;
    cin >> idTarea;
    cout << endl;

    tareaExiste = verificarExistenciaTarea(idTarea); // en lugar de devolver true/false, podria deolver el nombre de la tarea

    if(tareaExiste) {
        cout << "¿Está seguro de que desea eliminar la tarea [Nombre de la tarea]? (S/N): ";
        cin >> entrada;
        cout << endl;

        if(entrada == 'S' || entrada == 's') {
            // ? borrarTarea = true : borrarTarea = false;
        } else {

        }


    } else {
        cout << "El código de la tarea ingresado no existe" << endl;
    }
    // Codigo para eliminar la tarea
}

bool regresarAlMenu() {
    bool regresarAMenu = false;
    char seguir;

    cout << "¿Desea regresar al menú principal? (S/N): ";
    cin >> seguir;
    cout << endl;

    seguir == 'S' || seguir == 's' ? regresarAMenu = true : regresarAMenu = false;

    return regresarAMenu;
}
