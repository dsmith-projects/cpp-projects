// David Smith Slano
// 6 de julio
// Proyecto 2: este proyecto trata del manejo de estudiantes y de notas de estudiantes de diferentes cursos.
// El programa también permite hacer operaciones CRUD de estudiantes y notas y persistencia de datos en archivos.

#include <iostream>
#include <locale>
#include <string>
#include <array>
#include <vector>
#include <iomanip> // Para el manejo y manipulación de los caracteres de salida para que tengan formato

#include <cstdlib> // Prototipo de exit

// Para el manejo de archivos
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

constexpr size_t NUM_CERO = 0; // Índice que contiene el id de un estudiante
constexpr size_t NUM_CINCO = 5;
constexpr size_t NUM_SIETE = 7; // constexpr es una constante computada en tiempo de compilación y no en tiempo de ejecución
constexpr size_t NUM_NUEVE = 9;

using RegistroEstudiante = array<string, NUM_SIETE>;


// Lista de los prototipos de una función.
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
//vector<array<string, NUM_NUEVE>>
void buscarMateriasRegistradasPorEstudiante(string, vector<array<string, NUM_NUEVE>>&);
array<string, 9> mostrarMateriasRegistradasPorEstudiante(vector<string>&);
void salvarNotasModificadasEnArchivo(array<string, NUM_NUEVE>&);
void reporteEstudiantes(const string&, const vector<RegistroEstudiante>&, const string&, const vector<array<string, NUM_NUEVE>>&);


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
        cout << "Se cargaron " << listaEstudiantes.size() << " registros de estudiantes." << endl;
    } else {
        cout << "Puede que el archivo estudiantes.txt no exista." << endl;
    }

    if (cargarArchivoNotasEnMemoria(nombreArchivoNotas, notasEstudiantes)) {
        cout << "Se cargaron " << notasEstudiantes.size() << " registros de calificaciones." << endl;
    } else {
        cout << "Puede que el archivo notas.txt no exista." << endl;
    }

    continuar();

    do {
        mostrarMenu();

        cout << "Ingrese una opción del menú: ";
        getline(cin, entrada);
        cout << endl;

        try {
            entradaMenu = stoi(entrada); // Intentar convertir a número

            switch (entradaMenu) {
            case 1:
                registrarEstudiante(nombreArchivoEstudiantes, listaEstudiantes); // función que registra un estudiante
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
                cout << "Test" << endl;
                break;
            case 6:
                reporteEstudiantes(nombreArchivoEstudiantes, listaEstudiantes, nombreArchivoNotas, notasEstudiantes);
                continuar();
                break;
            case 7:
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

void continuar() {
    cout << "Presione Enter para continuar...";
    cin.get();
    system("cls");
}

// Funciones de manejo de archivos. Cargar datos en memoria

bool cargarArchivoEstudiantesEnMemoria(const string& archivoEstudiantes, vector<RegistroEstudiante>& matrizEstudiantes) {

    ifstream archivo(archivoEstudiantes);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << archivoEstudiantes << endl;
        return false;
    }

    string linea;
    matrizEstudiantes.clear();

    while (getline(archivo, linea)) {
        istringstream ss(linea);

        RegistroEstudiante registro; // Alternativa a escribir array<string, 7> registro;
        string dato;

        for (size_t i = 0; i < NUM_SIETE; ++i) {
            if (!getline(ss, dato, ',')) { // Por si hay algún dato incompleto/defectuoso y deseo omitirlo
                cerr << "Advertencia: Se omitió un registro defectuoso." << endl;
                break;
            }

            registro[i] = dato;
        }

        // Solo cargamos en memoria si realmente habían datos en el archivo
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
        cerr << "Error: No se pudo abrir el archivo '" << archivoNotas << endl;
        return false;
    }

    string linea;
    matrizNotas.clear();

    while (getline(archivo, linea)) {
        istringstream ss(linea);

        array<string, NUM_NUEVE> registro;
        string dato;

        for (size_t i = 0; i < NUM_NUEVE; ++i) {
            if (!getline(ss, dato, ',')) { // Por si hay algún dato incompleto/defectuoso y deseo omitirlo
                cerr << "Advertencia: Se omitió un registro defectuoso." << endl;
                break;
            }

            registro[i] = dato;
        }

        // Solo cargamos en memoria si realmente habían datos en el archivo
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
        cerr << "Error: No se pudo abrir el archivo '" << archivoEstudiantes << "' para agregar nuevos estudiantes." << endl;
        return false;
    }

    // Se escribe cada dato del estudiante separado por una coma
    for (size_t i = 0; i < NUM_SIETE; ++i) {
        archivo << estudiante[i];
        if (i < NUM_SIETE - 1) {
            archivo << ","; // Para evitar la coma después del último dato
        }
    }
    archivo << "\n";

    archivo.close();
    return true;
}

bool agregarNotasAlArchivo(const string& archivoNotas, const array<string, NUM_NUEVE>& calificaciones) {
    ofstream archivo(archivoNotas, ios::app); // Abre el archivo en modo de agregar nuevos estudiantes

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << archivoNotas << "' para agregar nuevas calificaciones." << endl;
        return false;
    }

    // Se escribe cada dato del arreglo de calificaciones separado por una coma
    for (size_t i = 0; i < NUM_NUEVE; ++i) {
        archivo << calificaciones[i];
        if (i < NUM_NUEVE - 1) {
            archivo << ","; // Para evitar la coma después del último dato
        }
    }
    archivo << "\n";

    archivo.close();
    return true;
}

bool sobrescribirArchivoEstudiantes(const string& archivoEstudiantes, const vector<RegistroEstudiante>& matrizEstudiantes) {
    ofstream archivo(archivoEstudiantes); // abrir archivo en mode de sobrescrtura

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << archivoEstudiantes << "' para sobrescribirlo." << endl;
        return false;
    }

    for (const auto& estudiante : matrizEstudiantes) {
        for (size_t i = 0; i < NUM_SIETE; ++i) {
            archivo << estudiante[i];
            if (i < NUM_SIETE - 1) archivo << ","; // agrega el delimitador de como excepto en la última posición
        }
        archivo << "\n";
    }

    archivo.close();
    return true;
}

bool sobrescribirArchivoNotas(const string& archivoNotas, const vector<array<string, NUM_NUEVE>>& matrizNotas) {
    ofstream archivo(archivoNotas); // abrir archivo en modo de sobrescrtura

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << archivoNotas << "' para sobrescribirlo." << endl;
        return false;
    }

    for (const auto& registro : matrizNotas) {
        for (size_t i = 0; i < NUM_NUEVE; ++i) {
            archivo << registro[i];
            if (i < NUM_NUEVE - 1) archivo << ","; // agrega el delimitador de coma excepto en la última posición
        }
        archivo << "\n";
    }

    archivo.close();
    return true;
}

void mostrarMenu() {

    cout << "* * * Menú Principal * * *" << endl;
    cout << endl;
    cout << "1. Registrar estudiante" << endl;
    cout << "2. Ingresar calificaciones" << endl;
    cout << "3. Modificar datos del estudiante" << endl;
    cout << "4. Modificar notas por estudiante" << endl;
    cout << "5. Eliminar registro de estudiante" << endl;
    cout << "6. Reporte de estudiantes y calificaciones finales" << endl;
    cout << "7. Salir del programa" << endl;
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

    cout << " ------------------------------------------------" << endl;
    cout << "|" << setw(38) << "REGISTRO DE NUEVO ESTUDIANTE" << setw(11) << "|" << endl;
    cout << " ------------------------------------------------" << endl;

    cout << endl;
    //Debe ser único, o sea, no repetido

    idEstudiante = obtenerIdEstudiante();
    cout << endl;

    nombre = obtenerInformacion("Ingrese el nombre completo (nombre y dos apellidos): ");

    cout << endl;

    cout << "Ingrese el lugar de residencia: " << endl;
    cout << "    " << left << setw(15);// << "- Provincia: ";
    provincia = obtenerInformacion("- Provincia: ");
    cout << "    " << left << setw(15);// << "- Cantón: ";
    canton = obtenerInformacion("- Cantón: ");
    cout << "    " << left << setw(15);// << "- Distrito: ";
    distrito = obtenerInformacion("- Distrito: ");

    cout << endl;

    edad = obtenerEdadEstudiante();

    cout << endl;

    mostrarOpcionesGenero();

    genero = obtenerGenero();
    cout << "Género seleccionado: " << genero << endl;

    cout << endl;

    cout << "Id: " << idEstudiante << endl;
    cout << "Nombre completo: " << nombre << endl;
    cout << "Residencia: " << provincia << " " << canton << " " << distrito << endl;
    cout << "Edad: " << edad << endl;
    cout << "Género: " << genero << endl;

    estudiante = guardarEstudianteEnArchivo(idEstudiante, nombre, provincia, canton, distrito, edad, genero);
    cout << endl;

    // Para ser consistentes debería no escribir en el archivo sino en el vector y luego escribir en el archivo toda la lista de estudiantes
    // o mejor aún, debería guardar en el archivo y actualizar el vector en memoria
    if(agregarEstudianteAlArchivo(archivoEstudiantes, estudiante)) {
        cout << "Estudiante registrado con éxito en ESTUDIANTES.txt" << endl;
    } else {
        cout << "No se pudo registrar el estudiante en el archivo ESTUDIANTES.txt" << endl;
    }
    // actualizar memoria volatil
    if(cargarArchivoEstudiantesEnMemoria(archivoEstudiantes, matrizEstudiantes)) {
        cout << "Memoria actualizada con nuevo estudiante" << endl;
    } else {
        cout << "Memoria NO actualizada con nuevo estudiante" << endl;
    }
    cout << endl;
    cout << endl;
}

string obtenerIdEstudiante(){
    string identificacion;
    bool idEstudianteValido{false};

    do {
        cout << "Ingrese la identificación del estudiante (10 dígitos): ";
        getline(cin, identificacion);

        if(esIdValido(identificacion)) {
            idEstudianteValido = true;
        } else {
            cout << "Identificación inválida. Ingrese una identificación de 10 dígitos, sin letras, ni espacios en blanco." << endl;
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

        cout << "Ingrese un valor. Intente de nuevo." << endl;
    }

}

string obtenerEdadEstudiante(){
    string edad;
    bool edadEstudianteValida{false};

    do {
        edad = obtenerInformacion("Ingrese la edad (entre 18 y 100): ");
//        cout << "Ingrese la edad (entre 18 y 100): ";
//        getline(cin, edad);

        if(esNumerico(edad)) {
            if(estaEnRango(edad, 18, 100)) {
                edadEstudianteValida = true;
                break;
            } else {
                cout << "Edad inválida. Ingrese una edad numérica entre 18 y 100." << endl;
            }
        } else {
            cout << "Edad inválida. Ingrese una edad numérica entre 18 y 100, sin letras, ni espacios en blanco." << endl;
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
    cout << "Seleccione el género con el que se identifica: " << endl;
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
        entrada = obtenerInformacion("Ingrese una opción: ");

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
        cout << "Opción inválida. Ingrese una opción de género válida.\n";
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

    cout << "Función de guardar los datos del estudiante en un arreglo: " << endl;

    for (size_t i = 0; i < estudiante.size(); ++i) {
        cout << "   - " << i << ": " << estudiante[i] << endl;
    }

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

    idEstudiante = obtenerIdEstudiante();
    idEncontrado = existeEstudiante(idEstudiante, matrizEstudiantes);

    if(idEncontrado) {
        // mensaje de encontrado
        // proceder a ingresar calificaciones
        cout << "Estudiante registrado. " << endl;


        materia = obtenerInformacion("Ingrese el nombre de la materia que cursa: ");
        notas = solicitarCalificaciones();

        mostrarNotas(notas);

        promedio = calcularPromedio(notas);
        estadoCurso = determinarResultado(promedio);

        mostrarResultadoCurso(promedio, estadoCurso);

        calificaciones = guardarNotasEnArreglo(idEstudiante, materia, notas, promedio, estadoCurso);
        cout << endl;

        if(agregarNotasAlArchivo(archivoNotas, calificaciones)) {
            cout << "Notas registradas con éxito en NOTAS.txt" << endl;
        } else {
            cout << "No se pudo registrar las notas en el archivo NOTAS.txt" << endl;
        }
        // actualizar memoria volatil
        if(cargarArchivoNotasEnMemoria(archivoNotas, matrizNotas)) {
            cout << "Memoria actualizada con nuevo conjunto de notas" << endl;
        } else {
            cout << "Memoria NO actualizada con nuevo conjunto de notas" << endl;
        }
        cout << endl;


    } else {
        cout << "Estudiante no registrado. " << endl;
        cout << endl;

        do {
            entrada = obtenerInformacion("¿Desea ingresar otra identificación? [S/N]: ");

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
                        cout << "Opción inválida. Ingrese solo [S/N]."<< endl;
                        cout << endl;
                        opcionValida = false;
                        break;
                }
            } else {
                cout << endl;
                cout << "Opción inválida. Ingrese una opción válida [S/N]." << endl;
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

    cout << "Función de guardar los datos de las notas en un arreglo: " << endl;

    for (size_t i = 0; i < notas.size(); ++i) {
        cout << "   - " << i << ": " << notas[i] << endl;
    }

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
                    cout << "La nota debe estar entre 0.0 y 10.0." << endl;
                    cout << endl;
                }
            } catch (...) {
                cout << "Calificación inválida. Ingrese una nota válida." << endl;
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
        return "Reposición";
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

// Opción 3: Modificar datos de un estudiante

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

    while (true) {
        idEstudiante = obtenerIdEstudiante();

        if (!existeEstudiante(idEstudiante, matrizEstudiantes)) {
            cout << "No se encontraron registros de la identificación del estudiante." << endl;
            cout << endl;

            intentarDeNuevo = hacerPreguntaDeRespuestaBinaria("¿Desea intentar de nuevo? [S/N]: ");

            if(intentarDeNuevo) {
                continue; // comienza una nueva iteración del ciclo
            } else {
                cout << "Regresando al menú..." << endl;
                return;
            }
        }


        for (auto& registro : matrizEstudiantes) {
            if (registro[NUM_CERO] == idEstudiante) {
                cout << "Registro de estudiante encontrado:" << endl;

                cout << "    " << left << setw(15) << "- Edad: " << registro[5] << endl;
                cout << "    " << left << setw(15) << "- Provincia: " << registro[2] << endl;
                cout << "    " << left << setw(15) << "- Cantón: " << registro[3] << endl;
                cout << "    " << left << setw(15) << "- Distrito: " << registro[4] << endl;
                cout << endl;

                // Preguntar al usuario, ¿qué desea actualizar?
                do {
                    cout << "Puede actualizar la edad del estudiante o el lugar de residencia o ambas." << endl;
                    cout << endl;
                    entrada = obtenerInformacion("Ingrese:\n   1. Si desea actualizar la edad o\n   2. Si desea actualizar el lugar de residencia o\n   3. Ambas\n\nOpción: ");
                    cout << endl;

                    try {
                        seleccion = stoi(entrada); // Intentar convertir a número

                        switch (seleccion) {
                            case 1:
                                registro[5] = obtenerEdadEstudiante();
                                cout << endl;
                                salirCiclo = true;
                                break;
                            case 2:
                                registro[2] = obtenerInformacion("- Provincia: ");
                                registro[3] = obtenerInformacion("- Cantón: ");
                                registro[4] = obtenerInformacion("- Distrito: ");
                                cout << endl;
                                salirCiclo = true;
                                break;
                            case 3:
                                registro[5] = obtenerEdadEstudiante();
                                registro[2] = obtenerInformacion("- Provincia: ");
                                registro[3] = obtenerInformacion("- Cantón: ");
                                registro[4] = obtenerInformacion("- Distrito: ");
                                cout << endl;
                                salirCiclo = true;
                                break;
                            default:
                                cout << "Opción inválida, vuelva a intentarlo." << endl;
                                cout << endl;
                                break;
                        }
                    } catch (exception& e) {
                        cout << "ERROR: Entrada inválida. Por favor, ingrese una opción válida." << endl;
                        cout << endl;
                    }

                } while (!salirCiclo);

                break;
            }
        }


        // Sobrescribir el archivo de estudiantes con los registros actualizados
        if (sobrescribirArchivoEstudiantes(archivoEstudiantes, matrizEstudiantes)) {
            cout << "Registro de estudiante actualizado exitosamente." << endl;
        } else {
            cout << "ERROR: No se pudo actualizar el archivo." << endl;
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
                    cout << "Opción inválida. Ingrese solo [S/N]."<< endl;
                    cout << endl;
                    opcionValida = false;
                    break;
            }
        } else {
            cout << endl;
            cout << "Opción inválida. Ingrese una opción válida, solo [S/N]." << endl;
        }
    } while(!opcionValida);

    return false;
}

// Opción 4: Modificar registro de notas

void modificarRegistroNotas(const string& archivoEstudiantes, const vector<RegistroEstudiante>& matrizEstudiantes, const string& archivoNotas, vector<array<string, NUM_NUEVE>>& matrizNotas) { // agregar el nombre del archivo de estudiantes y al matriz de estudiantes
    string idEstudiante;
    bool idEncontrado{false};
    vector<array<string, NUM_NUEVE>> registrosPorEstudiante;
    array<string, NUM_NUEVE> registroPorModificar;
    array<double, NUM_CINCO> notasPorMateriaPorEstudiante;
    int indiceRegistro = 0;
    string entrada;
    bool opcionValida{false};

    idEstudiante = obtenerIdEstudiante();
    idEncontrado = existeEstudiante(idEstudiante, matrizEstudiantes);

    if(idEncontrado) {
        cout << "Estudiante registrado. " << endl;
        cout << endl;
        // Buscarlo en el archivo de notas

        //registrosPorEstudiante =
        buscarMateriasRegistradasPorEstudiante(idEstudiante, matrizNotas); // vector con todos los registros que coincidan con el ide del estudiante
//        registroPorModificar = mostrarMateriasRegistradasPorEstudiante(registrosPorEstudiante);
//        salvarNotasModificadasEnArchivo(registroPorModificar);

         // Sobrescribir el archivo de notas con los registros actualizados
        if (sobrescribirArchivoNotas(archivoNotas, matrizNotas)) {
            cout << "Registro de notas actualizado exitosamente." << endl;
        } else {
            cout << "ERROR: No se pudo actualizar el archivo." << endl;
        }


    } else {
        cout << "Estudiante no registrado. " << endl;
        cout << endl;

        do {
            entrada = obtenerInformacion("¿Desea ingresar otra identificación? [S/N]: ");

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
                        cout << "Opción inválida. Ingrese solo [S/N]."<< endl;
                        cout << endl;
                        opcionValida = false;
                        break;
                }
            } else {
                cout << endl;
                cout << "Opción inválida. Ingrese una opción válida [S/N]." << endl;
            }
        } while(!opcionValida);

    }

}

//vector<array<string, NUM_NUEVE>>
void buscarMateriasRegistradasPorEstudiante(string idEstudiante, vector<array<string, NUM_NUEVE>>& matrizNotas) { // cambiar el tipo del return por un vector de arrays
    vector<array<string, NUM_NUEVE>> registroNotasPorIdEstudiante;
    vector<int> vectorDeIndices;
    bool hayMateriasRegistradas{false};
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
        cout << "Registro de materias registradas:" << endl;

        for (size_t i = 0; i < registroNotasPorIdEstudiante.size(); ++i) {
            cout << left << setw(5) << "    " <<  "[" << i << "] " << registroNotasPorIdEstudiante[i][1] << endl;
            cout << endl;
        }


        while (true) {
            cout << "Ingrese el índice del ítem que desea editar: ";
            getline(cin, entrada);

            try {
                indice = stoi(entrada);

                // Validar el rango
                if (indice >= NUM_CERO && static_cast<size_t>(indice) < registroNotasPorIdEstudiante.size()) {
                    cout << "Índice ingresado: " << indice << endl;
                    cout << endl;
                    cout << "Notas actuales para " << matrizNotas[vectorDeIndices[indice]][1] << endl;
                    cout << "   - Proyecto 1: " << matrizNotas[vectorDeIndices[indice]][2] << endl;
                    cout << "   - Proyecto 2: " << matrizNotas[vectorDeIndices[indice]][3] << endl;
                    cout << "   - Ensayo: " << matrizNotas[vectorDeIndices[indice]][4] << endl;
                    cout << "   - Foro: " << matrizNotas[vectorDeIndices[indice]][5] << endl;
                    cout << "   - Defensa: " << matrizNotas[vectorDeIndices[indice]][6] << endl;
                    break;
                } else {
                    cout << "ERROR: Número fuera del rango. Intente de nuevo." << endl;
                }

            } catch (const invalid_argument&) {
                cout << "ERROR: Entrada inválida. Ingrese un número entero." << endl;
            } catch (const out_of_range&) {
                cout << "ERROR: Número fuera del rango. Intente con un valor válido." << endl;
            }
        }

        cout << "Aqui veremos si el Índice es el correcto: " <<  matrizNotas[vectorDeIndices[indice]][1];
        cout << endl;

        nuevasCalificaciones = solicitarCalificaciones();
        nuevoPromedio = calcularPromedio(nuevasCalificaciones);
        nuevoEstadoCurso = determinarResultado(nuevoPromedio);

        mostrarResultadoCurso(nuevoPromedio, nuevoEstadoCurso);

        nuevoRegistroNotas = guardarNotasEnArreglo(idEstudiante, matrizNotas[vectorDeIndices[indice]][1], nuevasCalificaciones, nuevoPromedio, nuevoEstadoCurso);

        matrizNotas[vectorDeIndices[indice]] = nuevoRegistroNotas;


    } else {
        cout << "El estudiante con cédula " << idEstudiante << " no tiene materias registradas." << endl;
        cout << endl;
    }

    //return registroNotasPorIdEstudiante;
}

// Muestra todas los cursos que coincidan con el id del estudiante y devuelve el registro basado en la materia seleccionada por el usuario
array<string, 9> mostrarMateriasRegistradasPorEstudiante(vector<string>& registroNotas) { // creo que lo recibe es un vector de arreglos de 9 posiciones
    array<string, 9> registroPorModificar;

    cout << "Materias registradas:" << endl;
    cout << endl;
    cout << "1. Matematicas" << endl;
    cout << "2. Historia" << endl;
    cout << endl;

    //Aquí quiero iterar sobre el vector de registro de notas y mostrarlas
    // Le pido al usuario seleccionar la materia cuyas notas desea cambiar
    return registroPorModificar;
}

void salvarNotasModificadasEnArchivo(array<string, NUM_NUEVE>& registroNotasModificadas) {
    // Guardar el archivo con las notas modificadas
    cout << "Guardar el archivo con las notas modificadas" << endl;
    cout << endl;
//    string entrada;
//    bool opcionValida{false};
//    int indice{0};

//    do {
//        entrada = obtenerInformacion("Ingrese una opción: ");
//
//        if (entrada.length() == 1) {
//            char opcion = tolower(entrada[0]);
//
//            switch (opcion) {
//                case '1':
//                    return "femenino";
//                    opcionValida = true;
//                case '2':
//                    return "masculino";
//                    opcionValida = true;
//                case '3':
//                    return "no binario";
//                    opcionValida = true;
//                default:
//                    break;
//            }
//        }
//        cout << endl;
//        cout << "Opción inválida. Ingrese una opción de género válida.\n";
//    } while (!opcionValida);
}

// Opción 6: Reporte de estudiantes - calificaciones finales

void reporteEstudiantes(const string& archivoEstudiantes, const vector<RegistroEstudiante>& matrizEstudiantes, const string& archivoNotas, const vector<array<string, NUM_NUEVE>>& matrizNotas) {
    // Defino la cantidad de caracteres de cada columna
    const int anchoColmna[NUM_SIETE] = {15, 30, 12, 20, 20, 6, 12};

    // Encabezados de la tabla
    cout << left;
    cout << setw(anchoColmna[0]) << "Cédula"
              << setw(anchoColmna[1]) << "Nombre"
              << setw(anchoColmna[2]) << "Provincia"
              << setw(anchoColmna[3]) << "Cantón"
              << setw(anchoColmna[4]) << "Distrito"
              << setw(anchoColmna[5]) << "Edad"
              << setw(anchoColmna[6]) << "Género"
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



    // Defino la cantidad de caracteres de cada columna
    const int anchoColmnaN[NUM_NUEVE] = {15, 20, 11, 11, 11, 11, 11, 11, 10};

    // Encabezados de la tabla
    cout << left;
    cout << setw(anchoColmnaN[0]) << "Cédula"
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




