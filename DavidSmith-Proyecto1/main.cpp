//David SMith SOlano / 15 de junio / programa de tareas
#include <iostream>

#include <locale>
#include <string>
#include <array>
#include <vector>
#include <iomanip> // Para el manejo y manupulación de los caracteres de salida para que tengan formato
#include <ctime> // para el manejo de fechas y horas
#include <sstream> // para manejar los flujos y separar fechas y horas
#include <cctype>
#include <algorithm>


using namespace std;


void mostrarMenu();

bool listaTareasVacia(vector<array<string, 5>>&);

string obtenerCodigoTarea();

string obtenerNombreTarea();

string obtenerFechaTarea();

bool esFechaValida(const string&);

string obtenerHoraTarea(string);

bool esHoraValida(const string&);

array<string, 5> solicitarInfoTarea(int&);

void agregarTareas(vector<array<string, 5>>&, int&);

void buscarTarea(vector<array<string, 5>>&);

void mostrarTareas(vector<array<string, 5>>&);

tm crearTiempo(string, string);

int calcularDiferenciaTiempoEnMinutos(tm, tm);

void eliminarTarea(vector<array<string, 5>>&, int&);

int obterIndiceTarea(vector<array<string, 5>>&, string);

void borrarTarea(vector<array<string, 5>>&, int);

void mostrarNoHayTareas();

bool regresarAlMenu();


int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8");

    bool salir{false};
    int entradaMenu{0};
    int contadorTareas{0};
    const int MAX_VALUE = 5;
    string entrada;
    bool regresarAMenu = false;
    vector<array<string, 5>> listaTareas;

    do {
        mostrarMenu();

        cout << "Ingrese una opción del menú: ";
        cin >> entrada;
        //getline(cin, entrada);
        cout << endl;

        try {
            entradaMenu = stoi(entrada); // Intentar convertir a número

            switch (entradaMenu) {
            case 1:
                cout << "Puede agregar un máximo de 5 tareas." << endl;
                cout << "Cantidad de tareas agregadas: << " << contadorTareas << " >>" << endl;
                cout << endl;
                if(contadorTareas == MAX_VALUE) {
                    cout << "Elimine alguna tarea si desea agregar una nueva tarea" << endl;
                    cout << endl;
                } else {
                    while(contadorTareas < MAX_VALUE) {
                        agregarTareas(listaTareas, contadorTareas);
                        ++contadorTareas;
                        if(contadorTareas < MAX_VALUE) {
                            if(regresarAlMenu()) {
                                break;
                            }
                        }
                    }
                }

                break;
            case 2:
                //do {
                    buscarTarea(listaTareas);
                  //  regresarAMenu = regresarAlMenu();
                //} while(!regresarAMenu);

                break;
            case 3:
                mostrarTareas(listaTareas);
                break;
            case 4:
                eliminarTarea(listaTareas, contadorTareas);
                break;
            case 5:
                salir = true;
                break;
            default:
                cout << "Opción inválida, vuelva a intentarlo." << endl;
                cout << endl;
                break;
            }
        } catch (exception& e) {

            cout << "ERROR: Entrada inválida. Por favor, ingrese una opción de menú válida." << endl;
            cout << endl;
        }




    } while (!salir);


    return 0;
}

void mostrarMenu() {

    cout << "* * * Menú Principal * * *" << endl;
    cout << endl;
    cout << "1. Agregar tareas" << endl;
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
        //getline(cin, idTarea);
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
    bool formatoValido{false};

    do{
        cout << "Fecha de vencimiento (dd/mm/aaaa): ";
        cin >> fechaVencimiento;

        if (esFechaValida(fechaVencimiento)) {
            cout << "Formato válido.\n";
            formatoValido = true;
        } else {
            cout << "ERROR: Formato inválido. Intente de nuevo";
            cout << endl;
        }

    } while(!formatoValido);


    return fechaVencimiento;
}

bool esFechaValida(const string& fecha) {

    // Verificar que la fecha tenga exactamente 10 caracteres
    if (fecha.length() != 10) {
        return false;
    }

    // Extraer substrings
    string dia = fecha.substr(0, 2);
    string mes = fecha.substr(3, 2);
    string ano = fecha.substr(6, 4);
    char separador1 = fecha[2];
    char separador2 = fecha[5];

    // Verificar que los separadores sean '/'
    if (separador1 != '/' || separador2 != '/') {
        return false;
    }

    // Verificar que los componentes sean números
    if (!all_of(dia.begin(), dia.end(), ::isdigit) ||
        !all_of(mes.begin(), mes.end(), ::isdigit) ||
        !all_of(ano.begin(), ano.end(), ::isdigit)) {
        return false;
    }

    // Convertir a números
    int diaNum = stoi(dia);
    int mesNum = stoi(mes);
    int anoNum = stoi(ano);

    // Validar rango de días
    if (diaNum < 1 || diaNum > 31) {
        return false;
    }

    // Validación básica del mes
    if (mesNum < 1 || mesNum > 12) {
        return false;
    }

    return true;
}

string obtenerHoraTarea(string tipoHora) {
    string hora;
    bool formatoValido{false};

    do{
        cout << "Hora de " << tipoHora << " (hh:mm): ";
        cin >> hora;

        if (esHoraValida(hora)) {
            cout << "Formato válido.\n";
            formatoValido = true;
        } else {
            cout << "ERROR: Formato inválido. Intente de nuevo";
            cout << endl;
        }

    } while(!formatoValido);

    return hora;
}

bool esHoraValida(const string& hora) {
    // Verificar que la cadena tenga exactamente 5 caracteres (hh:mm)
    if (hora.length() != 5) {
        return false;
    }

    // Extraer substrings
    string horasStr = hora.substr(0, 2);
    string minutosStr = hora.substr(3, 2);
    char separador = hora[2];

    // Verificar que el separador sea ':'
    if (separador != ':') {
        return false;
    }

    // Verificar que las partes sean numéricas
    if (!all_of(horasStr.begin(), horasStr.end(), ::isdigit) ||
        !all_of(minutosStr.begin(), minutosStr.end(), ::isdigit)) {
        return false;
    }

    // Convertir a enteros
    int horas = stoi(horasStr);
    int minutos = stoi(minutosStr);

    // Validar rangos
    if (horas < 0 || horas > 23) {
        return false;
    }
    if (minutos < 0 || minutos > 59) {
        return false;
    }

    return true;

}

array<string, 5> solicitarInfoTarea(int& numTarea) {
    string idTarea;
    //unsigned int idTarea{0};
    string nombreTarea;
    string fechaVencimiento;
    string horaInicio;
    string horaFin;

    const unsigned int datosTarea = 5;
    array<string, datosTarea> tarea;

    cout << "* * * TAREA " << numTarea + 1 << " * * *" << endl;
    //cout << "Ingrese la información de la TAREA " << numTarea << ": " << endl;
    cout << endl;

    tarea[0] = obtenerCodigoTarea();
    tarea[1] = obtenerNombreTarea();
    tarea[2] = obtenerFechaTarea();
    tarea[3] = obtenerHoraTarea("inicio");
    tarea[4] = obtenerHoraTarea("finalización");

    cout << endl;

    return tarea;

}

void agregarTareas(vector<array<string, 5>>& listaTareas, int& contadorTareas) {
    string entrada;
    array<string, 5> tarea;

    tarea = solicitarInfoTarea(contadorTareas);
    listaTareas.push_back(tarea);
    cout << endl;
    cout << "¡Tarea agregada exitosamente!" << endl;
    cout << endl;
}

void buscarTarea(vector<array<string, 5>>& listaTareas) {
    string idTarea;
    bool listaVacia{false};
    bool tareaEncontrada{false};
    unsigned int minutosTarea{0};

    listaVacia = listaTareasVacia(listaTareas); // verifica si hay tareas existentes

    if(!listaVacia) {
        cout << "Ingrese el código de la tarea que desea buscar: ";
        cin >> idTarea;
        cout << endl;

        for (size_t i = 0; i < listaTareas.size(); i++) {
            if(listaTareas[i][0] == idTarea) {
                tareaEncontrada = true;

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

            }
        }
        if(!tareaEncontrada) {
            cout << "No se encontró una tarea con el código de tarea " << idTarea << endl;
            cout << endl;
        }

    } else {
        mostrarNoHayTareas();
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
        }
        cout << endl;
    } else {
        mostrarNoHayTareas();
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

void eliminarTarea(vector<array<string, 5>>& listaTareas, int& contadorTareas) {
    string idTarea;
    bool listaVacia{false};
    bool tareaEncontrada{false};
    char entrada;

    listaVacia = listaTareasVacia(listaTareas); // en lugar de devolver true/false, podria deolver el nombre de la tarea

    if(!listaVacia) {
        cout << "Ingrese el código de la tarea a eliminar: ";
        cin >> idTarea;
        cout << endl;

        for (size_t i = 0; i < listaTareas.size(); ++i) {
            if (listaTareas[i][0] == idTarea) {
                tareaEncontrada = true;

                cout << "¿Está seguro de que desea eliminar la tarea " << idTarea << "? (S/N): ";
                cin >> entrada;
                cout << endl;

                if(entrada == 'S' || entrada == 's') {
                    // borrar tarea
                    listaTareas.erase(listaTareas.begin() + i);
                    contadorTareas--;

                    cout << "Eliminadaaaaaaaaaa....." << endl;
                    cout << "Tarea eliminada exitosamente." << endl;
                    cout << endl;

                    break;
                } else {
                    cout << "Tarea NO eliminada" << endl;
                    cout << endl;
                }

            } else {
                tareaEncontrada = false;
            }
        }
        if(!tareaEncontrada) {
            cout << "No se encontró una tarea con el código de tarea " << idTarea << endl;
            cout << endl;
        }

    } else {
        mostrarNoHayTareas();
    }
}

void mostrarNoHayTareas() {
    cout << "No hay tareas registradas. Debe ingresar al menos una tarea." << endl;
    cout << endl;
}


bool regresarAlMenu() {
    bool regresarAMenu{false};
    char seguir;
    bool entradaValida{false};

    do {
        cout << "¿Desea regresar al menú principal? (S/N): ";
        cin >> seguir;
        cout << endl;

        if (seguir == 's' || seguir == 'S') {
            regresarAMenu = true;
            entradaValida = true;
        } else if (seguir == 'n' || seguir == 'N') {
            regresarAMenu = false;
            entradaValida = true;
        } else {
            cout << "ERROR: Entrada inválida. Por favor, ingrese (S/N)" << endl;
            cout << endl;
        }

    } while(!entradaValida);

    return regresarAMenu;
}
