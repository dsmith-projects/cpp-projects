// David Smith Slano
// 6 de julio
// Proyecto 2: este proyecto trata del manejo de estudiantes y de notas de estudiantes de diferentes cursos.
// El programa tambien permite hacer operaciones CRUD con estudiantes y notas y hay persistencia de datos en archivos.

#include <iostream>
#include <locale>
#include <string>
#include <array>
#include <vector>
#include <iomanip> // Para el manejo y manipulacion de los caracteres de salida para que tengan formato
#include <cstdlib> // Prototipo de exit

// Para el manejo de archivos
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

constexpr size_t NUM_CERO = 0; // Indice que contiene el id de un estudiante
constexpr size_t NUM_UNO = 1; // Indice que contiene el nombre del estudiante o de la materia
constexpr size_t NUM_CINCO = 5;
constexpr size_t NUM_SIETE = 7; // constexpr es una constante computada en tiempo de compilacion y no en tiempo de ejecucion
constexpr size_t NUM_NUEVE = 9;

using RegistroEstudiante = array<string, NUM_SIETE>;


// Lista de los prototipos de una funcion.
void continuar();
bool cargarArchivoEstudiantesEnMemoria(const string&, vector<RegistroEstudiante>&);
bool cargarArchivoNotasEnMemoria(const string&, vector<array<string, NUM_NUEVE>>&);
bool agregarEstudianteAlArchivo(const string&, const array<string, NUM_SIETE>&);
bool agregarNotasAlArchivo(const string&, const array<string, NUM_NUEVE>&);
bool sobrescribirArchivoEstudiantes(const string&, const vector<RegistroEstudiante>&);
bool sobrescribirArchivoNotas(const string&, const vector<array<string, NUM_NUEVE>>&);
void mostrarMenu();
void registrarEstudiante(const string&, vector<RegistroEstudiante>&);
string obtenerIdEstudiante();
bool esIdValido(const string&);
string obtenerInformacion(const string&);
string obtenerEdadEstudiante();
bool esNumerico(const string&);
bool estaEnRango(const string&, int, int);
bool estaEnRangoNotas(const double, double, double);
void mostrarOpcionesGenero();
string obtenerGenero();
array<string, NUM_SIETE> guardarEstudianteEnArchivo(const string, const string, const string, const string, const string, const string, const string);
void ingresarCalificaciones(const string&, const vector<RegistroEstudiante>&, const string&, vector<array<string, NUM_NUEVE>>&);
array<string, NUM_NUEVE> guardarNotasEnArreglo(const string&, const string&, const array<double, NUM_CINCO>&, const double&, const string&);
string doubleToString(double value);
bool existeEstudiante(const string, const vector<RegistroEstudiante>&);
array<double, NUM_CINCO> solicitarCalificaciones();
void mostrarNotas(const array<double, NUM_CINCO>&);
double calcularPromedio(const array<double, NUM_CINCO>&);
string determinarResultado(double&);
void mostrarResultadoCurso(double, string);
void modificarDatosEstudiante(const string&, vector<RegistroEstudiante>&);
bool hacerPreguntaDeRespuestaBinaria(const string&);
void modificarRegistroNotas(const string&, const vector<RegistroEstudiante>&, const string&, vector<array<string, NUM_NUEVE>>&);
void buscarMateriasRegistradasPorEstudiante(string, vector<array<string, NUM_NUEVE>>&);
void mostrarMateriasRegistradasPorEstudiante(const vector<array<string, NUM_NUEVE>>&);
void salvarNotasModificadasEnArchivo(array<string, NUM_NUEVE>&);
void reporteEstudiantesYNotasFinales(const string&, const vector<RegistroEstudiante>&, const string&, const vector<array<string, NUM_NUEVE>>&);
void reporteEstudiantes(const vector<RegistroEstudiante>&);
void reporteCalificaciones(const vector<array<string, NUM_NUEVE>>&);
string conseguirNombreEstudiante(const string, const vector<RegistroEstudiante>&);
void eliminarEstudiante(const string&, vector<RegistroEstudiante>&, const string&, vector<array<string, NUM_NUEVE>>&);
bool terminarPrograma();

int main()
{
    setlocale(LC_ALL, "spanish");

    bool salir{false};
    int entradaMenu{0};
    string entrada;

    // Nombre de los archivos
    string nombreArchivoEstudiantes = "estudiantes.txt";
    string nombreArchivoNotas = "notas.txt";

    // Matrices para el manejo de estudiantes y de notas
    vector<array<string, NUM_SIETE>> listaEstudiantes;
    vector<array<string, NUM_NUEVE>> notasEstudiantes;


    if (cargarArchivoEstudiantesEnMemoria(nombreArchivoEstudiantes, listaEstudiantes)) {
        cout << "    - ATENCION: Se cargaron " << listaEstudiantes.size() << " registros de estudiantes." << endl;
    } else {
        cout << "    - ATENCION: Puede que el archivo estudiantes.txt no exista." << endl;
        cout << endl;
    }

    if (cargarArchivoNotasEnMemoria(nombreArchivoNotas, notasEstudiantes)) {
        cout << "    - ATENCION: Se cargaron " << notasEstudiantes.size() << " registros de calificaciones." << endl;
        cout << endl;
    } else {
        cout << "    - ATENCION: Puede que el archivo notas.txt no exista." << endl;
        cout << endl;
    }

    continuar();

    do {
        mostrarMenu();

        cout << "Ingrese una opcion del menu: ";
        getline(cin, entrada);
        cout << endl;

        try {
            entradaMenu = stoi(entrada); // Intentar convertir a numero

            switch (entradaMenu) {
            case 1:
                registrarEstudiante(nombreArchivoEstudiantes, listaEstudiantes); // funcion que registra un estudiante
                continuar();
                break;
            case 2:
                ingresarCalificaciones(nombreArchivoEstudiantes, listaEstudiantes, nombreArchivoNotas, notasEstudiantes);
                continuar();
                break;
            case 3:
                modificarDatosEstudiante(nombreArchivoEstudiantes, listaEstudiantes);
                continuar();
                break;
            case 4:
                modificarRegistroNotas(nombreArchivoEstudiantes, listaEstudiantes, nombreArchivoNotas, notasEstudiantes);
                continuar();
                break;
            case 5:
                eliminarEstudiante(nombreArchivoEstudiantes, listaEstudiantes, nombreArchivoNotas, notasEstudiantes);
                continuar();
                break;
            case 6:
                reporteEstudiantesYNotasFinales(nombreArchivoEstudiantes, listaEstudiantes, nombreArchivoNotas, notasEstudiantes);
                continuar();
                break;
            case 7:
                salir = terminarPrograma();
                if(!salir) {
                    continuar();
                }
                break;
            default:
                cout << "    - ERROR: Opcion invalida, vuelva a intentarlo." << endl;
                cout << endl;
                break;
            }
        } catch (exception& e) {

            cout << "    - ERROR: Entrada invalida. Por favor, ingrese una opcion de menu valida." << endl;
            cout << endl;
        }

    } while (!salir);

    return 0;
}

void continuar() {
    cout << "Presione 'Enter' para continuar...";
    cin.get();
    system("cls");
}

// Funciones de manejo de archivos. Cargar datos en memoria

bool cargarArchivoEstudiantesEnMemoria(const string& archivoEstudiantes, vector<RegistroEstudiante>& matrizEstudiantes) {

    ifstream archivo(archivoEstudiantes);

    if (!archivo.is_open()) {
        cerr << "    - ERROR: No se pudo abrir el archivo '" << archivoEstudiantes << endl;
        return false;
    }

    string linea;
    matrizEstudiantes.clear();

    while (getline(archivo, linea)) {
        istringstream ss(linea);

        RegistroEstudiante registro; // Alternativa a escribir array<string, 7> registro;
        string dato;

        for (size_t i = 0; i < NUM_SIETE; ++i) {
            if (!getline(ss, dato, ',')) { // Por si hay algun dato incompleto/defectuoso y deseo omitirlo
                cerr << "    - ADVERTENCIA: Se omitio un registro defectuoso." << endl;
                break;
            }

            registro[i] = dato;
        }

        // Solo cargamos en memoria si realmente habian datos en el archivo
        if (!registro[0].empty()) {
            matrizEstudiantes.push_back(registro);
        }

    }

    archivo.close();
    return true;
}

bool cargarArchivoNotasEnMemoria(const string& archivoNotas, vector<array<string, NUM_NUEVE>>& matrizNotas) {

    ifstream archivo(archivoNotas);

    if (!archivo.is_open()) {
        cerr << "    - ERROR: No se pudo abrir el archivo." << archivoNotas << endl;
        return false;
    }

    string linea;
    matrizNotas.clear();

    while (getline(archivo, linea)) {
        istringstream ss(linea);

        array<string, NUM_NUEVE> registro;
        string dato;

        for (size_t i = 0; i < NUM_NUEVE; ++i) {
            if (!getline(ss, dato, ',')) { // Por si hay algun dato incompleto/defectuoso y deseo omitirlo
                cerr << "    - ADVERTENCIA: Se omitio un registro defectuoso." << endl;
                break;
            }

            registro[i] = dato;
        }

        // Solo cargamos en memoria si realmente habian datos en el archivo
        if (!registro[0].empty()) {
            matrizNotas.push_back(registro);
        }

    }

    archivo.close();
    return true;
}


bool agregarEstudianteAlArchivo(const string& archivoEstudiantes, const array<string, NUM_SIETE>& estudiante) {
    ofstream archivo(archivoEstudiantes, ios::app); // Abre el archivo en modo de agregar nuevos estudiantes

    if (!archivo.is_open()) {
        cerr << "    - ERROR: No se pudo abrir el archivo '" << archivoEstudiantes << "' para agregar nuevos estudiantes." << endl;
        return false;
    }

    // Se escribe cada dato del estudiante separado por una coma
    for (size_t i = 0; i < NUM_SIETE; ++i) {
        archivo << estudiante[i];
        if (i < NUM_SIETE - 1) {
            archivo << ","; // Para evitar la coma despues del ultimo dato
        }
    }
    archivo << "\n";

    archivo.close();
    return true;
}

bool agregarNotasAlArchivo(const string& archivoNotas, const array<string, NUM_NUEVE>& calificaciones) {
    ofstream archivo(archivoNotas, ios::app); // Abre el archivo en modo de agregar nuevos estudiantes. App significa append

    if (!archivo.is_open()) {
        cerr << "    - ERROR: No se pudo abrir el archivo '" << archivoNotas << "' para agregar nuevas calificaciones." << endl;
        return false;
    }

    // Se escribe cada dato del arreglo de calificaciones separado por una coma
    for (size_t i = 0; i < NUM_NUEVE; ++i) {
        archivo << calificaciones[i];
        if (i < NUM_NUEVE - 1) {
            archivo << ","; // Para evitar la coma despues del ultimo dato
        }
    }
    archivo << "\n";

    archivo.close();
    return true;
}

bool sobrescribirArchivoEstudiantes(const string& archivoEstudiantes, const vector<RegistroEstudiante>& matrizEstudiantes) {
    ofstream archivo(archivoEstudiantes); // abrir archivo en mode de sobrescrtura

    if (!archivo.is_open()) {
        cerr << "    - ERROR: No se pudo abrir el archivo '" << archivoEstudiantes << "' para sobrescribirlo." << endl;
        return false;
    }

    for (const auto& estudiante : matrizEstudiantes) {
        for (size_t i = 0; i < NUM_SIETE; ++i) {
            archivo << estudiante[i];
            if (i < NUM_SIETE - 1) archivo << ","; // agrega el delimitador de como excepto en la ultima posicion
        }
        archivo << "\n";
    }

    archivo.close();
    return true;
}

bool sobrescribirArchivoNotas(const string& archivoNotas, const vector<array<string, NUM_NUEVE>>& matrizNotas) {
    ofstream archivo(archivoNotas); // abrir archivo en modo de sobrescrtura

    if (!archivo.is_open()) {
        cerr << "    - ERROR: No se pudo abrir el archivo '" << archivoNotas << "' para sobrescribirlo." << endl;
        return false;
    }

    for (const auto& registro : matrizNotas) {
        for (size_t i = 0; i < NUM_NUEVE; ++i) {
            archivo << registro[i];
            if (i < NUM_NUEVE - 1) archivo << ","; // agrega el delimitador de coma excepto en la ultima posicion
        }
        archivo << "\n";
    }

    archivo.close();
    return true;
}

void mostrarMenu() {

    cout << " " << string(114, '-') << endl;
    cout << "| " << left << setw(38) << "MENU PRINCIAL" << right << setw(76) << "|" << endl;
    cout << " " << string(114, '-') << endl;
    cout << endl;

    cout << "    " << left << setw(15) << "1. Registrar estudiante" << endl;
    cout << "    " << left << setw(15) << "2. Ingresar calificaciones" << endl;
    cout << "    " << left << setw(15) << "3. Modificar datos del estudiante" << endl;
    cout << "    " << left << setw(15) << "4. Modificar notas por estudiante" << endl;
    cout << "    " << left << setw(15) << "5. Eliminar registro de estudiante" << endl;
    cout << "    " << left << setw(15) << "6. Reporte de estudiantes y calificaciones finales" << endl;
    cout << "    " << left << setw(15) << "7. Salir del programa" << endl;
    cout << endl;
}

void registrarEstudiante(const string& archivoEstudiantes, vector<RegistroEstudiante>& matrizEstudiantes){ //Registrar a un estudiante nuevo
    string idEstudiante;
    string nombre;
    string provincia;
    string canton;
    string distrito;
    string edad;
    string genero;
    array<string, NUM_SIETE> estudiante;
    bool idEncontrado{false};

    cout << " " << string(114, '-') << endl;
    cout << "| " << left << setw(38) << "REGISTRO DE NUEVO ESTUDIANTE" << right << setw(76) << "|" << endl;
    cout << " " << string(114, '-') << endl;
    cout << endl;

    idEstudiante = obtenerIdEstudiante();
    cout << endl;
    idEncontrado = existeEstudiante(idEstudiante, matrizEstudiantes);

    if(idEncontrado) { // Verificacion de que el id a registar no sea repetido.
        cout << "    - ATENCION: La cedula ingresada ya se encuentra registrada. Ingrese un id diferente." << endl;
        cout << endl;
        return;
    }

    nombre = obtenerInformacion("Ingrese el nombre completo (nombre y dos apellidos): ");

    cout << endl;

    cout << "Ingrese el lugar de residencia: " << endl;
    cout << "    " << left << setw(15);// << "- Provincia: ";
    provincia = obtenerInformacion("- Provincia: ");
    cout << "    " << left << setw(15);// << "- Canton: ";
    canton = obtenerInformacion("- Canton: ");
    cout << "    " << left << setw(15);// << "- Distrito: ";
    distrito = obtenerInformacion("- Distrito: ");

    cout << endl;

    edad = obtenerEdadEstudiante();

    cout << endl;

    mostrarOpcionesGenero();

    genero = obtenerGenero();
    cout << "Genero seleccionado: " << genero << endl;

    cout << endl;

//    cout << "Id: " << idEstudiante << endl;
//    cout << "Nombre completo: " << nombre << endl;
//    cout << "Residencia: " << provincia << " " << canton << " " << distrito << endl;
//    cout << "Edad: " << edad << endl;
//    cout << "Genero: " << genero << endl;

    estudiante = guardarEstudianteEnArchivo(idEstudiante, nombre, provincia, canton, distrito, edad, genero);
    cout << endl;

    // Agregar nuevo registro al archivo
    if(agregarEstudianteAlArchivo(archivoEstudiantes, estudiante)) {
        cout << "    - ATENCION: Estudiante registrado con exito en ESTUDIANTES.txt." << endl;
    } else {
        cout << "ATENCION: No se pudo registrar el estudiante en el archivo ESTUDIANTES.txt." << endl;
    }

    // Actualizar memoria volatil
    if(cargarArchivoEstudiantesEnMemoria(archivoEstudiantes, matrizEstudiantes)) {
        cout << "    - ATENCION: Memoria actualizada con nuevo estudiante." << endl;
    } else {
        cout << "    - ATENCION: Memoria NO actualizada con nuevo estudiante." << endl;
    }
    cout << endl;
    cout << endl;
}

string obtenerIdEstudiante(){
    string identificacion;
    bool idEstudianteValido{false};

    do {
        cout << "Ingrese la identificacion del estudiante (10 digitos): ";
        getline(cin, identificacion);

        if(esIdValido(identificacion)) {
            idEstudianteValido = true;
        } else {
            cout << "    - ERROR: Identificacion invalida. Ingrese una identificacion de 10 digitos, sin letras, ni espacios en blanco." << endl;
            cout << endl;
        }

    } while(!idEstudianteValido);

    return identificacion;
}

bool esIdValido(const string& id) {
    bool esValido = true;

    if(id.length() != 10){
        esValido = false;
    } else {
        for(char caracter : id) {
            if(!isdigit(caracter)) {
                esValido = false;
                break;
            }
        }
    }

    return esValido;
}

string obtenerInformacion(const string& enunciado) {
    string datos;

    while (true) {
        cout << enunciado;
        getline(cin, datos);

        if (!datos.empty()) {
            return datos;
        }

        cout << "    - ERROR: Ingrese un valor. Intente de nuevo." << endl;
        cout << endl;
    }

}

string obtenerEdadEstudiante(){
    string edad;
    bool edadEstudianteValida{false};

    do {
        edad = obtenerInformacion("Ingrese la edad (entre 18 y 100): ");

        if(esNumerico(edad)) {
            if(estaEnRango(edad, 18, 100)) {
                edadEstudianteValida = true;
                break;
            } else {
                cout << "    - ERROR: Edad invalida. Ingrese una edad numerica entre 18 y 100." << endl;
                cout << endl;
            }
        } else {
            cout << "    - ERROR: Edad invalida. Ingrese una edad numerica entre 18 y 100, sin letras, ni espacios en blanco." << endl;
            cout << endl;
        }

    } while(!edadEstudianteValida);

    return edad;
}

bool esNumerico(const string& valorIngresado) {
    bool esValido = true;

    if(valorIngresado.empty()){
        esValido = false;
    } else {
        for(char caracter : valorIngresado) {
            if(!isdigit(caracter)) {
                esValido = false;
                break;
            }
        }
    }

    return esValido;
}

bool estaEnRango(const string& valorIngresado, int limiteInferior, int limiteSuperior) {
    bool estaEnRango = false;
    int valorEnNumero = stoi(valorIngresado);

    if(valorEnNumero >= limiteInferior && valorEnNumero <= limiteSuperior) {
        estaEnRango = true;
    }

    return estaEnRango;
}

bool estaEnRangoNotas(const double valorIngresado, double limiteInferior, double limiteSuperior) {
    return (valorIngresado >= limiteInferior && valorIngresado <= limiteSuperior) ? true : false;
}

void mostrarOpcionesGenero() {
    cout << "Seleccione el genero con el que se identifica: " << endl;
    cout << endl;
    cout << "    " << left << setw(15) << "[1] Femenino" << endl;
    cout << "    " << left << setw(15) << "[2] Masculino" << endl;
    cout << "    " << left << setw(15) << "[3] No binario" << endl;
    cout << endl;
}

string obtenerGenero() {
    string entrada;
    bool opcionValida{false};

    do {
        entrada = obtenerInformacion("Ingrese una opcion: ");

        if (entrada.length() == 1) {
            char opcion = tolower(entrada[0]);

            switch (opcion) {
                case '1':
                    return "femenino";
                    opcionValida = true;
                case '2':
                    return "masculino";
                    opcionValida = true;
                case '3':
                    return "no binario";
                    opcionValida = true;
                default:
                    break;
            }
        }
        cout << endl;
        cout << "    - ERROR: Opcion invalida. Ingrese una opcion de genero valida.\n";
    } while (!opcionValida);
}

// Guardar datos del estudante en un arreglo

array<string, NUM_SIETE> guardarEstudianteEnArchivo(const string idEstudiante, const string nombre, const string provincia, const string canton, const string distrito, const string edad, const string genero) {
    array<string, NUM_SIETE> estudiante;

    estudiante[0] = idEstudiante;
    estudiante[1] = nombre;
    estudiante[2] = provincia;
    estudiante[3] = canton;
    estudiante[4] = distrito;
    estudiante[5] = edad;
    estudiante[6] = genero;

    return estudiante;
}

// Opcion 2: ingresar calificaciones

void ingresarCalificaciones(const string& archivoEstudiantes, const vector<RegistroEstudiante>& matrizEstudiantes, const string& archivoNotas, vector<array<string, NUM_NUEVE>>& matrizNotas) { //Registrar las calificaciones de un estudiante
    string idEstudiante;
    bool idEncontrado{false};
    bool opcionValida{false};
    string entrada;
    array<double, NUM_CINCO> notas;
    array<string, NUM_NUEVE> calificaciones;
    double promedio;
    string estadoCurso;
    string materia;

    cout << " " << string(114, '-') << endl;
    cout << "| " << left << setw(38) << "REGISTRO DE NOTAS POR MATERIA" << right << setw(76) << "|" << endl;
    cout << " " << string(114, '-') << endl;
    cout << endl;

    idEstudiante = obtenerIdEstudiante();
    idEncontrado = existeEstudiante(idEstudiante, matrizEstudiantes);

    if(idEncontrado) {
        cout << endl;
        cout << "    - ATENCION: El estudiante se encuentra registrado." << endl;
        cout << endl;

        while (true) {
            materia = obtenerInformacion("Ingrese el nombre de la materia que cursa: ");
            notas = solicitarCalificaciones();
    //        mostrarNotas(notas);
            promedio = calcularPromedio(notas);
            estadoCurso = determinarResultado(promedio);

            mostrarResultadoCurso(promedio, estadoCurso);

            calificaciones = guardarNotasEnArreglo(idEstudiante, materia, notas, promedio, estadoCurso);
            cout << endl;

            if(agregarNotasAlArchivo(archivoNotas, calificaciones)) {
                cout << "    - ATENCION: Notas registradas con exito en NOTAS.txt." << endl;
            } else {
                cout << "    - ATENCION: No se pudo registrar las notas en el archivo NOTAS.txt." << endl;
            }
            // actualizar memoria volatil
            if(cargarArchivoNotasEnMemoria(archivoNotas, matrizNotas)) {
                cout << "    - ATENCION: Memoria actualizada con nuevo conjunto de notas." << endl;
            } else {
                cout << "    - ATENCION: Memoria NO actualizada con nuevo conjunto de notas." << endl;
            }

            cout << endl;

            bool agregarNuevaMateria = hacerPreguntaDeRespuestaBinaria("¿Desea agregar notas de otra materia? (S/N): ");
            cout << endl;

            if (agregarNuevaMateria) {
                continue;
            } else {
                break;
            }
        }
    } else {
        cout << "Estudiante no registrado. " << endl;
        cout << endl;

        do {
            entrada = obtenerInformacion("¿Desea ingresar otra identificacion? [S/N]: ");
            cout << endl;

            if (entrada.length() == 1) {
                char opcion = tolower(entrada[0]);

                switch (opcion) {
                    case 's':
                    case 'S':
                        ingresarCalificaciones(archivoEstudiantes, matrizEstudiantes, archivoNotas, matrizNotas);
                        opcionValida = true;
                    case 'n':
                    case 'N':
                        opcionValida = true;
                        break;
                    default:
                        cout << "    - ERROR: Opcion invalida. Ingrese solo [S/N]."<< endl;
                        cout << endl;
                        opcionValida = false;
                        break;
                }
            } else {
                cout << endl;
                cout << "    - ERROR: Opcion invalida. Ingrese una opcion valida [S/N]." << endl;
                cout << endl;
            }
        } while(!opcionValida);

    }

}

array<string, NUM_NUEVE> guardarNotasEnArreglo(const string& idEstudiante, const string& materia, const array<double, NUM_CINCO>& calificaciones, const double& promedio, const string& estado) {
    array<string, NUM_NUEVE> notas;

    notas[0] = idEstudiante;
    notas[1] = materia;
    notas[2] = doubleToString(calificaciones[0]); // proyecto 1
    notas[3] = doubleToString(calificaciones[1]); // proyecto 2
    notas[4] = doubleToString(calificaciones[2]); // ensayo
    notas[5] = doubleToString(calificaciones[3]); // foro
    notas[6] = doubleToString(calificaciones[4]); // defensa
    notas[7] = doubleToString(promedio);
    notas[8] = estado;

    return notas;
}

string doubleToString(double value) {
    const int PRECISION = 2;
    ostringstream flujo;

    flujo.precision(PRECISION);
    flujo << fixed << value;

    return flujo.str();
}

bool existeEstudiante(const string id, const vector<RegistroEstudiante>& matrizEstudiantes) {
    for (const auto& registro : matrizEstudiantes) {
        if (registro[NUM_CERO] == id) {
            return true; // estudiante fue encontrado
        }
    }
    return false; // el estudiante no fue encontrado

}

array<double, NUM_CINCO> solicitarCalificaciones() {
    string calificacion;
    const double CALIF_MIN = 0.0;
    const double CALIF_MAX = 10.0;
    array<double, NUM_CINCO> notas;
    string entrada;
    double nota;
    int indiceActividadEvaluativa = 0;
    string actividadEvaluativa;

    for (size_t i = 0; i < notas.size(); ++i) {
        while (true) {
            indiceActividadEvaluativa = i + 1;

            switch(indiceActividadEvaluativa) {
                case 1:
                    actividadEvaluativa = "Proyecto 1";
                    break;
                case 2:
                    actividadEvaluativa = "Proyecto 2";
                    break;
                case 3:
                    actividadEvaluativa = "Ensayo";
                    break;
                case 4:
                    actividadEvaluativa = "Foro";
                    break;
                case 5:
                    actividadEvaluativa = "Defensa";
                    break;
                default:
                    break;
            }

            cout << "    " << left << setw(15);
            entrada = obtenerInformacion("- " + actividadEvaluativa +": ");

            try {
                nota = stod(entrada);

                if (estaEnRangoNotas(nota, CALIF_MIN, CALIF_MAX)) {
                    notas[i] = nota;
                    break;
                } else {
                    cout << "    - ATENCION: La nota debe estar entre 0.0 y 10.0." << endl;
                    cout << endl;
                }
            } catch (...) {
                cout << "    - ERROR: Calificacion invalida. Ingrese una nota valida." << endl;
                cout << endl;
            }
        }
    }

    return notas;
}

void mostrarNotas(const array<double, NUM_CINCO>& notas) {
    // Mostrar notas ingresadas
    cout << "Notas ingresadas:" << endl;

    for (size_t i = 0; i < notas.size(); ++i) {
        cout << "Nota #" << i + 1 << ": " << notas[i] << endl;
    }
}

double calcularPromedio(const array<double, NUM_CINCO>& notas) {
    double notaFinal = 0.0;
    const array<double, NUM_CINCO> pesos = {0.1, 0.2, 0.3, 0.1, 0.3};

    for (size_t i = 0; i < notas.size(); ++i) {
        notaFinal += notas[i] * pesos[i];
    }

    return notaFinal; // El tamaña del arreglo de notas es 5
}

string determinarResultado(double& promedio) {
    if (promedio >= 7.0) {
        return "Aprobado";
    } else if (promedio >= 5.0) {
        return "Reposicion";
    } else {
        return "Reprobado";
    }
}

void mostrarResultadoCurso(double promedio, string estadoCurso) {
    cout << fixed << setprecision(2);
    cout << endl;
    cout << "Promedio del curso: " << promedio << endl;
    cout << "Estado del estudiante: " << estadoCurso << endl;
    cout << endl;
}

// Opcion 3: Modificar datos de un estudiante

void modificarDatosEstudiante(const string& archivoEstudiantes, vector<RegistroEstudiante>& matrizEstudiantes) {
    string idEstudiante;
    string opcion;
    string entrada;
    string nuevaEdad;
    string nuevaProvincia;
    string nuevoCanton;
    string nuevoDistrito;
    bool intentarDeNuevo{false};
    int seleccion{0};
    bool salirCiclo{false};

    cout << " " << string(114, '-') << endl;
    cout << "| " << left << setw(38) << "ACTUALIZACION DE DATOS DEL ESTUDIANTE" << right << setw(76) << "|" << endl;
    cout << " " << string(114, '-') << endl;
    cout << endl;

    while (true) {
        idEstudiante = obtenerIdEstudiante();
        cout << endl;

        if (!existeEstudiante(idEstudiante, matrizEstudiantes)) {
            cout << "    - ATENCION: No se encontraron registros de la identificacion del estudiante." << endl;
            cout << endl;

            intentarDeNuevo = hacerPreguntaDeRespuestaBinaria("¿Desea intentar de nuevo? [S/N]: ");

            if(intentarDeNuevo) {
                continue; // comienza una nueva iteracion del ciclo
            } else {
                cout << "Regresando al menu..." << endl;
                return;
            }
        }


        for (auto& registro : matrizEstudiantes) {
            if (registro[NUM_CERO] == idEstudiante) {
                cout << "Registro de estudiante encontrado:" << endl;

                cout << "    " << left << setw(15) << "- Edad: " << registro[5] << endl;
                cout << "    " << left << setw(15) << "- Provincia: " << registro[2] << endl;
                cout << "    " << left << setw(15) << "- Canton: " << registro[3] << endl;
                cout << "    " << left << setw(15) << "- Distrito: " << registro[4] << endl;
                cout << endl;

                // Preguntar al usuario, ¿que desea actualizar?
                do {
                    cout << "Puede actualizar la edad del estudiante o el lugar de residencia o ambas." << endl;
                    cout << endl;
                    entrada = obtenerInformacion("Opciones:\n    [1] Actualizar la edad o\n    [2] Actualizar el lugar de residencia o\n    [3] Actualizar ambas\n\nIngrese un opcion: ");
                    cout << endl;

                    try {
                        seleccion = stoi(entrada); // Intentar convertir a numero

                        switch (seleccion) {
                            case 1:
                                registro[5] = obtenerEdadEstudiante();
                                cout << endl;
                                salirCiclo = true;
                                break;
                            case 2:
                                registro[2] = obtenerInformacion("- Provincia: ");
                                registro[3] = obtenerInformacion("- Canton: ");
                                registro[4] = obtenerInformacion("- Distrito: ");
                                cout << endl;
                                salirCiclo = true;
                                break;
                            case 3:
                                registro[5] = obtenerEdadEstudiante();
                                registro[2] = obtenerInformacion("- Provincia: ");
                                registro[3] = obtenerInformacion("- Canton: ");
                                registro[4] = obtenerInformacion("- Distrito: ");
                                cout << endl;
                                salirCiclo = true;
                                break;
                            default:
                                cout << "    - ERROR: Opcion invalida, vuelva a intentarlo." << endl;
                                cout << endl;
                                break;
                        }
                    } catch (exception& e) {
                        cout << "    - ERROR: Entrada invalida. Por favor, ingrese una opcion valida." << endl;
                        cout << endl;
                    }

                } while (!salirCiclo);

                break;
            }
        }


        // Sobrescribir el archivo de estudiantes con los registros actualizados
        if (sobrescribirArchivoEstudiantes(archivoEstudiantes, matrizEstudiantes)) {
            cout << "    - ATENCION: Registro de estudiante actualizado exitosamente." << endl;
            cout << endl;
        } else {
            cout << "    - ERROR: No se pudo actualizar el archivo." << endl;
            cout << endl;
        }

        return;
    }

}

bool hacerPreguntaDeRespuestaBinaria(const string& pregunta) {
    bool opcionValida{false};
    string entrada;

    do {
        entrada = obtenerInformacion(pregunta);

        if (entrada.length() == 1) {
            char opcion = tolower(entrada[0]);

            switch (opcion) {
                case 's':
                    return true;
                    break;
                case 'n':
                    return false;
                    break;
                default:
                    cout << "    - ERROR: Opcion invalida. Ingrese solo [S/N]."<< endl;
                    cout << endl;
                    opcionValida = false;
                    break;
            }
        } else {
            cout << endl;
            cout << "    - ERROR: Opcion invalida. Ingrese una opcion valida, solo [S/N]." << endl;
        }
    } while(!opcionValida);

    return false;
}

// Opcion 4: Modificar registro de notas

void modificarRegistroNotas(const string& archivoEstudiantes, const vector<RegistroEstudiante>& matrizEstudiantes, const string& archivoNotas, vector<array<string, NUM_NUEVE>>& matrizNotas) { // agregar el nombre del archivo de estudiantes y al matriz de estudiantes
    string idEstudiante;
    bool idEncontrado{false};
    vector<array<string, NUM_NUEVE>> registrosPorEstudiante;
    array<string, NUM_NUEVE> registroPorModificar;
    string entrada;
    bool opcionValida{false};

    cout << " " << string(114, '-') << endl;
    cout << "| " << left << setw(38) << "ACTUALIZACION DE NOTAS POR MATERIA" << right << setw(76) << "|" << endl;
    cout << " " << string(114, '-') << endl;
    cout << endl;

    idEstudiante = obtenerIdEstudiante();
    idEncontrado = existeEstudiante(idEstudiante, matrizEstudiantes);

    if(idEncontrado) {
        cout << endl;
        cout << "    - ATENCION: Estudiante registrado." << endl;
        cout << endl;

        // Buscarlo en el archivo de notas
        buscarMateriasRegistradasPorEstudiante(idEstudiante, matrizNotas); // vector con todos los registros que coincidan con el id del estudiante

        // Sobrescribir el archivo de notas con los registros actualizados
        if (sobrescribirArchivoNotas(archivoNotas, matrizNotas)) {
            cout << "    - ATENCION: Registro de notas actualizado exitosamente." << endl;
            cout << endl;
        } else {
            cout << "    - ERROR: No se pudo actualizar el archivo." << endl;
            cout << endl;
        }


    } else {
        cout << "    - ATENCION: Estudiante no registrado. " << endl;
        cout << endl;

        do {
            entrada = obtenerInformacion("¿Desea ingresar otra identificacion? [S/N]: ");

            if (entrada.length() == 1) {
                char opcion = tolower(entrada[0]);

                switch (opcion) {
                    case 's':
                    case 'S':
                        modificarRegistroNotas(archivoEstudiantes, matrizEstudiantes, archivoNotas, matrizNotas);
                        opcionValida = true;
                    case 'n':
                    case 'N':
                        opcionValida = true;
                        break;
                    default:
                        cout << "    - ERROR: Opcion invalida. Ingrese solo [S/N]."<< endl;
                        cout << endl;
                        opcionValida = false;
                        break;
                }
            } else {
                cout << endl;
                cout << "    - ERROR: Opcion invalida. Ingrese una opcion valida [S/N]." << endl;
            }
        } while(!opcionValida);

    }

}

//vector<array<string, NUM_NUEVE>>
void buscarMateriasRegistradasPorEstudiante(string idEstudiante, vector<array<string, NUM_NUEVE>>& matrizNotas) { // cambiar el tipo del return por un vector de arrays
    vector<array<string, NUM_NUEVE>> registroNotasPorIdEstudiante;
    vector<int> vectorDeIndices;
    string entrada;
    int indice = -1;
    array<double, NUM_CINCO> nuevasCalificaciones;
    double nuevoPromedio;
    string nuevoEstadoCurso;
    array<string, NUM_NUEVE> nuevoRegistroNotas;

    for (size_t i = 0; i < matrizNotas.size(); ++i) {
        if (matrizNotas[i][NUM_CERO] == idEstudiante) {
            registroNotasPorIdEstudiante.push_back(matrizNotas[i]);
            vectorDeIndices.push_back(i);
        }
    }

    if (!registroNotasPorIdEstudiante.empty()) {

        mostrarMateriasRegistradasPorEstudiante(registroNotasPorIdEstudiante);

        while (true) {
            entrada = obtenerInformacion("Ingrese el indice de la materia cuyas notas desea editar: ");
            cout << endl;

            try {
                indice = stoi(entrada);

                // Validar el rango
                if (indice >= NUM_CERO && static_cast<size_t>(indice) < registroNotasPorIdEstudiante.size()) {

                    cout << "Notas actuales para " << matrizNotas[vectorDeIndices[indice]][1] << ": " << endl;
                    cout << endl;
                    cout << "    " << left << setw(15) << "- Proyecto 1: " << right << setw(4) << matrizNotas[vectorDeIndices[indice]][2] << endl;
                    cout << "    " << left << setw(15) << "- Proyecto 2: " << right << setw(4) << matrizNotas[vectorDeIndices[indice]][3] << endl;
                    cout << "    " << left << setw(15) << "- Ensayo: " << right << setw(4) << matrizNotas[vectorDeIndices[indice]][4] << endl;
                    cout << "    " << left << setw(15) << "- Foro: " << right << setw(4) << matrizNotas[vectorDeIndices[indice]][5] << endl;
                    cout << "    " << left << setw(15) << "- Defensa: " << right << setw(4) << matrizNotas[vectorDeIndices[indice]][6] << endl;
                    cout << endl;

                    break;
                } else {
                    cout << "    - ERROR: Numero fuera del rango. Intente de nuevo." << endl;
                    cout << endl;
                }

            } catch (const invalid_argument&) {
                cout << "    - ERROR: Entrada invalida. Ingrese un numero entero." << endl;
                cout << endl;
            } catch (const out_of_range&) {
                cout << "    - ERROR: Numero fuera del rango. Intente con un valor valido." << endl;
                cout << endl;
            }
        }

        cout << "Ingrese las nuevas notas para la materia de: " <<  matrizNotas[vectorDeIndices[indice]][1] << endl;
        cout << endl;

        nuevasCalificaciones = solicitarCalificaciones();
        nuevoPromedio = calcularPromedio(nuevasCalificaciones);
        nuevoEstadoCurso = determinarResultado(nuevoPromedio);

        mostrarResultadoCurso(nuevoPromedio, nuevoEstadoCurso);

        nuevoRegistroNotas = guardarNotasEnArreglo(idEstudiante, matrizNotas[vectorDeIndices[indice]][1], nuevasCalificaciones, nuevoPromedio, nuevoEstadoCurso);

        matrizNotas[vectorDeIndices[indice]] = nuevoRegistroNotas;


    } else {
        cout << "El estudiante con cedula " << idEstudiante << " no tiene materias registradas." << endl;
        cout << endl;
    }
}

// Muestra todas los cursos que coincidan con el id del estudiante
void mostrarMateriasRegistradasPorEstudiante(const vector<array<string, NUM_NUEVE>>& registroNotasPorIdEstudiante) {

    cout << "Registro de materias registradas:" << endl;
    cout << endl;

    for (size_t i = 0; i < registroNotasPorIdEstudiante.size(); ++i) {
        cout << left << setw(4) << "    " <<  "[" << i << "] " << registroNotasPorIdEstudiante[i][1] << endl;
    }

    cout << endl;
}

// Opcion 6: Reporte de estudiantes - calificaciones finales

void reporteEstudiantesYNotasFinales(const string& archivoEstudiantes, const vector<RegistroEstudiante>& matrizEstudiantes, const string& archivoNotas, const vector<array<string, NUM_NUEVE>>& matrizNotas) {
    // Reporte de calificaciones por estudiante. Combinacion de archivos.
    cout << " " << string(114, '-') << endl;
    cout << "| " << left << setw(38) << "REPORTE DE ESTUDIANTES - NOTAS FINALES" << right << setw(76) << "|" << endl;
    cout << " " << string(114, '-') << endl;
    cout << endl;

//    reporteEstudiantes(matrizEstudiantes);
//    reporteCalificaciones(matrizNotas);

    // Defino la cantidad de caracteres de cada columna
    const int anchoColmnaR[NUM_NUEVE] = {15, 30, 20, 0, 0, 0, 0, 15, 15};

    if (matrizNotas.empty() || matrizEstudiantes.empty()) {
        cout << "    - ATENCION: No hay datos que reportar. Ingrese estudiantes y notas para generar un reporte." << endl;
        cout << endl;
    } else {
        // Encabezados de la tabla
        cout << left;
        cout << setw(anchoColmnaR[0]) << "Cedula"
            << setw(anchoColmnaR[1]) << "Nombre"
            << setw(anchoColmnaR[2]) << "Materia"
            << setw(anchoColmnaR[7]) << "Promedio"
            << setw(anchoColmnaR[8]) << "Estado"
            << endl;

        cout << string(115, '-') << endl;

        for (const auto& registro : matrizNotas) {
            for (size_t i = 0; i < NUM_NUEVE; ++i) {
                if(NUM_CERO == i) {
                    cout << setw(anchoColmnaR[i]) << registro[i];
                }
                if(NUM_UNO == i) {
                    cout << setw(anchoColmnaR[i]) << conseguirNombreEstudiante(registro[NUM_CERO], matrizEstudiantes);
                }
                if(2 == i) {
                    cout << setw(anchoColmnaR[i]) << registro[NUM_UNO];
                }
                if(7 == i) {
                    cout << setw(anchoColmnaR[i]) << registro[i];
                }
                if(8 == i) {
                    cout << setw(anchoColmnaR[i]) << registro[i];
                }
            }
            cout << endl;
        }
        cout << string(115, '-') << endl;
        cout << endl;

    }
}

void reporteEstudiantes(const vector<RegistroEstudiante>& matrizEstudiantes) {
    // Defino la cantidad de caracteres de cada columna
    const int anchoColmna[NUM_SIETE] = {15, 30, 12, 20, 20, 6, 12};

    // Encabezados de la tabla
    cout << left;
    cout << setw(anchoColmna[0]) << "Cedula"
              << setw(anchoColmna[1]) << "Nombre"
              << setw(anchoColmna[2]) << "Provincia"
              << setw(anchoColmna[3]) << "Canton"
              << setw(anchoColmna[4]) << "Distrito"
              << setw(anchoColmna[5]) << "Edad"
              << setw(anchoColmna[6]) << "Genero"
              << endl;

    cout << string(115, '-') << endl;

    // Imprimir los registros de la matriz
    for (const auto& registro : matrizEstudiantes) {
        for (size_t i = 0; i < NUM_SIETE; ++i) {
            cout << setw(anchoColmna[i]) << registro[i];
        }
        cout << endl;
    }
    cout << endl;

}

void reporteCalificaciones(const vector<array<string, NUM_NUEVE>>& matrizNotas) {
    // Defino la cantidad de caracteres de cada columna
    const int anchoColmnaN[NUM_NUEVE] = {15, 20, 11, 11, 11, 11, 11, 11, 10};

    // Encabezados de la tabla
    cout << left;
    cout << setw(anchoColmnaN[0]) << "Cedula"
              << setw(anchoColmnaN[1]) << "Materia"
              << setw(anchoColmnaN[2]) << "Proyecto 1"
              << setw(anchoColmnaN[3]) << "Proyecto 2"
              << setw(anchoColmnaN[4]) << "Ensayo"
              << setw(anchoColmnaN[5]) << "Foro"
              << setw(anchoColmnaN[6]) << "Defensa"
              << setw(anchoColmnaN[7]) << "Promedio"
              << setw(anchoColmnaN[8]) << "Estado"
              << endl;

    cout << string(115, '-') << endl;

    // Imprimir los registros de la matriz
    for (const auto& registro : matrizNotas) {
        for (size_t i = 0; i < NUM_NUEVE; ++i) {
            cout << setw(anchoColmnaN[i]) << registro[i];
        }
        cout << endl;
    }
    cout << endl;
}

string conseguirNombreEstudiante(const string id, const vector<RegistroEstudiante>& matrizEstudiantes) {
    string nombreEstudiante{"sin nombre"};

    for (const auto& registro : matrizEstudiantes) {
        if (registro[NUM_CERO] == id) {
            nombreEstudiante = registro[NUM_UNO];
        }
    }
    return nombreEstudiante; // devuelve el nombre del estudiantes

}

void eliminarEstudiante(const string& archivoEstudiantes, vector<RegistroEstudiante>& matrizEstudiantes, const string& archivoNotas, vector<array<string, NUM_NUEVE>>& matrizNotas) {
    string idEstudiante;
    bool intentarDeNuevo{false};
    bool borrarRegistrosEstudiante{false};
    bool borrarNuevoRegistro{false};

    cout << " " << string(114, '-') << endl;
    cout << "| " << left << setw(38) << "BORRADO DE REGISTROS DE ESTUDIANTE" << right << setw(76) << "|" << endl;
    cout << " " << string(114, '-') << endl;
    cout << endl;

    while (true) {
        idEstudiante = obtenerIdEstudiante();
        cout << endl;

        if (!existeEstudiante(idEstudiante, matrizEstudiantes)) {
            cout << "    - ATENCION: No se encontraron registros para la identificacion ingresada." << endl;
            cout << endl;

            intentarDeNuevo = hacerPreguntaDeRespuestaBinaria("¿Desea intentar de nuevo? [S/N]: ");

            if(intentarDeNuevo) {
                continue; // comienza una nueva iteracion del ciclo
            } else {
                cout << "Regresando al menu..." << endl;
                return;
            }
        }

        cout << "Eliminar estudiante y todos sus registros de notas." << endl;

        borrarRegistrosEstudiante = hacerPreguntaDeRespuestaBinaria("¿Proceder con el borrado? [S/N]: ");
        cout << endl;

        if (!borrarRegistrosEstudiante) {

            borrarNuevoRegistro = hacerPreguntaDeRespuestaBinaria("¿Desea borrar otro estudiante? [S/N]: ");
            cout << endl;

            if(borrarNuevoRegistro) {
                continue; // comienza una nueva iteracion del ciclo
            } else {
                cout << "Regresando al menu..." << endl;
                return;
            }

        }

        //---------------BORRADO DE LOS REGISTROS DE NOTAS DE UN ESTUDIANTE------------------
        // Itero de atras para adelante para evitar un error que sucedia en casa de que hubiese que borrar el primer elemento del vector
        // ya que al iterar y borrar elementos, se incrementaba el contador primero lo que hacia que se saltara el borrado del primer elemento
        for (int i = static_cast<int>(matrizNotas.size()) - 1; i >= 0; --i) {

            if (matrizNotas[i][NUM_CERO] == idEstudiante) {
                 matrizNotas.erase(matrizNotas.begin() + i);
            }
        }

        cout << "    - ATENCION: Se han borrado todos los registros de calificaciones del estudiante." << endl;

        // Sobrescribir el archivo de notas con los registros actualizados
        if (sobrescribirArchivoNotas(archivoNotas, matrizNotas)) {
            cout << "    - ATENCION: Registro de notas actualizado exitosamente." << endl;
            cout << endl;
        } else {
            cout << "    - ERROR: No se pudo actualizar el archivo." << endl;
            cout << endl;
        }

        //---------------BORRADO DEL REGISTRO DE ESTUDIANTE------------------
        // Itero de atras para adelante para evitar un error que sucedia en casa de que hubiese que borrar el primer elemento del vector
        // ya que al iterar y borrar elementos, se incrementaba el contador primero lo que hacia que se saltara el borrado del primer elemento
        for (int i = static_cast<int>(matrizEstudiantes.size()) - 1; i >= 0; --i) {

            if (matrizEstudiantes[i][NUM_CERO] == idEstudiante) {
                 matrizEstudiantes.erase(matrizEstudiantes.begin() + i);
            }
        }

        cout << "    - ATENCION: Se han borrado todos los registros del estudiante " << endl;

        // Sobrescribir el archivo de estudiantes con los registros actualizados
        if (sobrescribirArchivoEstudiantes(archivoEstudiantes, matrizEstudiantes)) {
            cout << "    - ATENCION: Registro de estudiante actualizado exitosamente." << endl;
            cout << endl;
        } else {
            cout << "    - ERROR: No se pudo actualizar el archivo." << endl;
            cout << endl;
        }

        return;
    }

    return;
}

bool terminarPrograma() {
    string respuesta;

    while (true) {
        respuesta = obtenerInformacion("¿Desea salir del programa? (S/N): ");
        cout << endl;

        if (respuesta == "s" || respuesta == "S") {
            return true;
        } else if (respuesta == "n" || respuesta == "N") {
            return false;
        } else {
            cout << "    - ERROR: Entrada invalida. Ingrese solo [S/N]." << endl;
            cout << endl;
        }
    }
}

