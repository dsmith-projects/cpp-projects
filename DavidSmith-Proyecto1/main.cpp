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

bool verificarExistenciaTarea(unsigned int);

array<string, 5> solicitarInfoTarea();

void agregarTareas(vector<array<string, 5>>&);

void buscarTarea();

void mostrarTareas(vector<array<string, 5>>&);

int calcularDiferenciaTiempoEnMinutos(tm, tm);

tm crearTiempo(string, string);

void eliminarTarea();

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
                buscarTarea();
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

    cout << "Código de la tarea(4 dígitos): ";
    cin >> idTarea;
    tarea[0] = idTarea;

    cout << "Nombre de la tarea: ";
    cin >> nombreTarea;
    tarea[1] = nombreTarea;

    cout << "Fecha de vencimiento (dd/mm/aaaa): ";
    cin >> fechaVencimiento;
    tarea[2] = fechaVencimiento;

    cout << "Hora de inicio (hh:mm): ";
    cin >> horaInicio;
    tarea[3] = horaInicio;

    cout << "Hora de finalización (hh:mm): ";
    cin >> horaFin;
    tarea[4] = horaFin;

    cout << endl;

    return tarea;

}

void agregarTareas(vector<array<string, 5>>& listaTareas) {
    unsigned int cantidadTareas{0};
    array<string, 5> tarea;

    cout << "Ingrese la cantidad de tareas que desea agregar: ";
    cin >> cantidadTareas;
    cout << endl;

    for(unsigned int i = 0; i < cantidadTareas; i++){
        tarea = solicitarInfoTarea();
        cout << endl;
//        cout << "\nPartes de la tarea:\n";
//        for (const string& parte : tarea) {
//            cout << " " << parte;
//        }
        listaTareas.push_back(tarea);
        cout << endl;
        cout << "Tarea agregada exitosamente" << endl;
        cout << endl;
    }

//    for (size_t i = 0; i < listaTareas.size(); i++) {
//        cout << "Tarea " << (i + 1) << ": ";
//        for (const string& tarea : listaTareas[i]) {
//            cout << tarea << " ";
//        }
//        cout << endl;
//    }

}

void buscarTarea() {
    unsigned int idTarea{0};

    cout << "Ingrese el código de la tarea a buscar: " << endl;
    cin >> idTarea;
    cout << endl;
}

void mostrarTareas(vector<array<string, 5>>& listaTareas) {
    unsigned int minutosTarea{0};

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
//
            cout << "+------------+----------------------------+----------------------------------+---------------------------+\n";
            //cout << tarea << " ";
       // }
        cout << endl;
    }
}

int calcularDiferenciaTiempoEnMinutos(tm tiempoInicio, tm tiempoFin) {
    const unsigned int sesenta = 60;

    time_t tiempo1 = mktime(&tiempoInicio);
    time_t tiempo2 = mktime(&tiempoFin);

    // Compute the difference in seconds and convert to minutes
    return static_cast<int>(difftime(tiempo2, tiempo1) / sesenta);
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
