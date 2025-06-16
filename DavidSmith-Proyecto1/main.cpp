#include <iostream>
#include <locale>
#include <string>
#include <array>
#include <vector>
#include <iomanip> // Para el manejo y manupulación de los caracteres de salida para que tengan formato
#include <ctime> // para el manejo de fechas y horas
#include <sstream> // para manejar los flujos y separar fechas y horas


using namespace std;


void mostrarMenu();

bool listaTareasVacia(vector<array<string, 5>>&);

string obtenerCodigoTarea();

string obtenerNombreTarea();

string obtenerFechaTarea();

string obtenerHoraTarea(string);

array<string, 5> solicitarInfoTarea();

void agregarTareas(vector<array<string, 5>>&);

void buscarTarea(vector<array<string, 5>>&);

void mostrarTareas(vector<array<string, 5>>&);

tm crearTiempo(string, string);

int calcularDiferenciaTiempoEnMinutos(tm, tm);

void eliminarTarea(vector<array<string, 5>>&);

int obterIndiceTarea(vector<array<string, 5>>&, string);

void borrarTarea(vector<array<string, 5>>&, int);

bool regresarAlMenu();


int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8");

    bool salir{false};
    unsigned int entradaMenu{0};
    bool regresarAMenu = false;
    vector<array<string, 5>> listaTareas;

    do {
        mostrarMenu();
        cout << "Ingrese una opción del menú: ";
        cin >> entradaMenu;
        cout << endl;

        switch (entradaMenu) {
        case 1:
            do {
                agregarTareas(listaTareas);
                regresarAMenu = regresarAlMenu();
            } while(!regresarAMenu);

            break;
        case 2:
            do {
                buscarTarea(listaTareas);
                regresarAMenu = regresarAlMenu();
            } while(!regresarAMenu);

            break;
        case 3:
            do {
                mostrarTareas(listaTareas);
                regresarAMenu = regresarAlMenu();
            } while(!regresarAMenu);

            break;
        case 4:
            //do {
                eliminarTarea(listaTareas);
                //regresarAMenu = regresarAlMenu();
            //} while(!regresarAMenu);
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

    cout << "* * * Menú Principal * * *" << endl;
    cout << endl;
    cout << "1. Agregar tareas (entre 1 y 5 tareas)" << endl;
    cout << "2. Buscar tarea" << endl;
    cout << "3. Mostrar todas las tareas" << endl;
    cout << "4. Eliminar tarea" << endl;
    cout << "5. Salir del programa" << endl;
    cout << endl;
}

bool listaTareasVacia(vector<array<string, 5>>& listaTareas) {
    return listaTareas.empty() ? true : false;
}

string obtenerCodigoTarea() {
    string idTarea;
    unsigned int codigoTarea;
    bool esNumero{false};
    bool formatoCorrecto{false};

    do {
        cout << "Código de la tarea (4 dígitos): ";
        cin >> idTarea;
        //cout << endl;

        if (idTarea.length() == 4) {
            formatoCorrecto = true;

            try {
                codigoTarea = stoi(idTarea); // Intentar convertir a número
                esNumero = true;
            } catch (exception& e) {
                esNumero = false;
                cout << "ERROR: Entrada inválida. Por favor, ingrese un código de 4 dígitos." << endl;
                cout << endl;
            }
        } else {
            formatoCorrecto = false;
            cout << "ERROR: Debe ingresar un código de 4 dígitos." << endl;
            cout << endl;
        }

    } while (!(esNumero && formatoCorrecto));

    return idTarea;
}

string obtenerNombreTarea() {
    string nombreTarea;

    cout << "Nombre de la tarea: ";
    cin >> nombreTarea;

    return nombreTarea;
}

string obtenerFechaTarea() {
    string fechaVencimiento;

    cout << "Fecha de vencimiento (dd/mm/aaaa): ";
    cin >> fechaVencimiento;

    return fechaVencimiento;
}

string obtenerHoraTarea(string tipoHora) {
    string hora;

    cout << "Hora de " << tipoHora << " (hh:mm): ";
    cin >> hora;

    return hora;
}

array<string, 5> solicitarInfoTarea() {
    string idTarea;
    //unsigned int idTarea{0};
    string nombreTarea;
    string fechaVencimiento;
    string horaInicio;
    string horaFin;

    const unsigned int datosTarea = 5;
    array<string, datosTarea> tarea;

    cout << "Ingrese la información de la tarea: " << endl;

    tarea[0] = obtenerCodigoTarea();
    tarea[1] = obtenerNombreTarea();
    tarea[2] = obtenerFechaTarea();
    tarea[3] = obtenerHoraTarea("inicio");
    tarea[4] = obtenerHoraTarea("finalización");

    cout << endl;

    return tarea;

}

void agregarTareas(vector<array<string, 5>>& listaTareas) {
    unsigned int cantidadTareas{0};
    string entrada;
    array<string, 5> tarea;
    bool esNumero{false};
    bool numeroEnRango{false};

    // Seguir pidiendo la cantidad de tareas hasta que esté dentro del rango válido
    do {
        cout << "Ingrese la cantidad de tareas que desea agregar (entre 1 y 5): ";
        cin >> entrada;
        cout << endl;

        try {
            cantidadTareas = stoi(entrada); // Intentar convertir a entero
            esNumero = true;
            if (cantidadTareas < 1 || cantidadTareas > 5) {
                cout << "ERROR: Debe ingresar un número entre 1 y 5." << endl;
                cout << endl;
            } else {
                numeroEnRango = true;
            }

        } catch (exception& e) {
            cout << "ERROR: Entrada inválida. Por favor, ingrese un número entero entre 1 y 5." << endl;
            cout << endl;
        }


    } while (!(esNumero && numeroEnRango));


    for(unsigned int i = 0; i < cantidadTareas; i++){
        tarea = solicitarInfoTarea();
        cout << endl;

        listaTareas.push_back(tarea);
        cout << endl;
        cout << "Tarea agregada exitosamente" << endl;
        cout << endl;
    }

}

void buscarTarea(vector<array<string, 5>>& listaTareas) {
    string idTarea;
    bool listaVacia{false};
    unsigned int minutosTarea{0};

    listaVacia = listaTareasVacia(listaTareas); // verifica si hay tareas existentes

    if(!listaVacia) {
        cout << "Ingrese el código de la tarea que desea buscar: ";
        cin >> idTarea;
        cout << endl;

        for (size_t i = 0; i < listaTareas.size(); i++) {
            if(listaTareas[i][0] == idTarea) {
                cout << "+------------+----------------------------+----------------------------------+---------------------------+\n";
                cout << "| " << setw(11) << "Código"
                      << " | " << setw(26) << "Nombre"
                      << " | " << setw(32) << "Fecha Vencimiento"
                      << " | " << setw(25) << "Minutos Invertidos" << " |\n";
                cout << "+------------+----------------------------+----------------------------------+---------------------------+\n";

                tm tiempoInicio = crearTiempo(listaTareas[i][2], listaTareas[i][3]);
                tm tiempoFin = crearTiempo(listaTareas[i][2], listaTareas[i][4]);
                minutosTarea = calcularDiferenciaTiempoEnMinutos(tiempoInicio, tiempoFin);

                cout << "| " << setw(10) << listaTareas[i][0]
                      << " | " << setw(26) << listaTareas[i][1]
                      << " | " << setw(32) << listaTareas[i][2]
                      << " | " << setw(25) << minutosTarea   << " |\n";
                cout << "+------------+----------------------------+----------------------------------+---------------------------+\n";
                cout << endl;
                break;

            } else {
                cout << "No se encontró una tarea con el código de tarea " << idTarea << endl;
                cout << endl;
            }
        }


    } else {
        cout << "No hay tareas registradas." << endl;
        cout << endl;
    }
}

void mostrarTareas(vector<array<string, 5>>& listaTareas) {
    unsigned int minutosTarea{0};
    bool listaVacia{false};

    listaVacia = listaTareasVacia(listaTareas); // verifica si hay tareas existentes

    if(!listaVacia) {
        cout << "+------------+----------------------------+----------------------------------+---------------------------+\n";
        cout << "| " << setw(11) << "Código"
                  << " | " << setw(26) << "Nombre"
                  << " | " << setw(32) << "Fecha Vencimiento"
                  << " | " << setw(25) << "Minutos Invertidos" << " |\n";
        cout << "+------------+----------------------------+----------------------------------+---------------------------+\n";

        for (size_t i = 0; i < listaTareas.size(); i++) {

            tm tiempoInicio = crearTiempo(listaTareas[i][2], listaTareas[i][3]);
            tm tiempoFin = crearTiempo(listaTareas[i][2], listaTareas[i][4]);

            minutosTarea = calcularDiferenciaTiempoEnMinutos(tiempoInicio, tiempoFin);

             cout << "| " << setw(10) << listaTareas[i][0]
              << " | " << setw(26) << listaTareas[i][1]
              << " | " << setw(32) << listaTareas[i][2]
              << " | " << setw(25) << minutosTarea   << " |\n";

            cout << "+------------+----------------------------+----------------------------------+---------------------------+\n";
            cout << endl;
        }

    } else {
        cout << "No hay tareas registradas." << endl;
        cout << endl;
    }
}

tm crearTiempo(string fecha, string hora) {
    unsigned int dia{0};
    unsigned int mes{0};
    unsigned int ano{0};
    char separadorFecha = '/';

    stringstream flujoFecha(fecha);
    flujoFecha >> dia >> separadorFecha >> mes >> separadorFecha >> ano;
    //cout << "Day: " << dia << ", Month: " << mes << ", Year: " << ano << endl;

    unsigned int horas{0};
    unsigned int minutos{0};
    char separadorHora = ':';

    stringstream flujoHora(hora);
    flujoHora >> horas >> separadorHora >> minutos;

    tm tiempo = {};

    tiempo.tm_year = ano - 1900; // Year (subtract 1900)
    tiempo.tm_mon = mes;   // June (0-based index)
    tiempo.tm_mday = dia; // Day of the month
    tiempo.tm_hour = horas; // Hour (24-hour format)
    tiempo.tm_min = minutos;

    return tiempo;
}

int calcularDiferenciaTiempoEnMinutos(tm tiempoInicio, tm tiempoFin) {
    const unsigned int sesenta = 60;

    time_t tiempo1 = mktime(&tiempoInicio);
    time_t tiempo2 = mktime(&tiempoFin);

    // Compute the difference in seconds and convert to minutes
    return static_cast<int>(difftime(tiempo2, tiempo1) / sesenta);
}

void eliminarTarea(vector<array<string, 5>>& listaTareas) {
    string idTarea;
    int indice{0};
    bool listaVacia{false};
    bool borrarTarea = false;
    char entrada;

    listaVacia = listaTareasVacia(listaTareas); // en lugar de devolver true/false, podria deolver el nombre de la tarea

    if(!listaVacia) {
        cout << "Ingrese el código de la tarea a eliminar: ";
        cin >> idTarea;
        cout << endl;

        for (size_t i = 0; i < listaTareas.size(); ++i) {
            if (listaTareas[i][0] == idTarea) {
                cout << "Índice encontrado: " << i << endl;

                cout << "¿Está seguro de que desea eliminar la tarea " << idTarea << "? (S/N): ";
                cin >> entrada;
                cout << endl;

                if(entrada == 'S' || entrada == 's') {
                    // borrar tarea
                    listaTareas.erase(listaTareas.begin() + i);

                    cout << "Eliminadaaaaaaaaaa....." << endl;
                    cout << "Tarea eliminada exitosamente." << endl;
                    cout << endl;

                    break;
                } else {
                    cout << "Tarea no eliminada" << endl;
                    cout << endl;
                }

            } else {
                cout << "No se encontró una tarea con el código de tarea " << idTarea << endl;
                cout << endl;
            }
        }

    } else {
        cout << "No hay tareas registradas." << endl;
        cout << endl;
    }
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
