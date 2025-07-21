// David Smith Slano
// 6 de julio
// Proyecto 2

#include <iostream>
#include <locale>
#include <string>
#include <array>
#include <vector>
#include <iomanip> // Para el manejo y manipulación de los caracteres de salida para que tengan formato

using namespace std;

// Lista de los prototipos de una función.
void mostrarMenu();
void registrarEstudiante();
string obtenerIdEstudiante();
bool esIdValido(const string&);
string obtenerInformacion(const string&);
string obtenerEdadEstudiante();
bool esNumerico(const string&);
bool estaEnRango(const string&, int, int);
bool estaEnRangoNotas(const double, double, double);
void mostrarOpcionesGenero();
string obtenerGenero();
void guardarEstudianteEnArchivo(string, string, string, string, string, string);
void ingresarCalificaciones();
bool existeEstudiante(string);
array<double, 5> solicitarCalificaciones();
void mostrarNotas(const array<double, 5>&);
double calcularPromedio(const array<double, 5>&);
string determinarResultado(double&);
void mostrarResultadoCurso(double, string);
void modificarRegistroNotas();
vector<string> buscarMateriasRegistradasEnArchivo(string);
array<string, 9> mostrarMateriasRegistradasPorEstudiante(vector<string>&);
void salvarNotasModificadasEnArchivo(array<string, 9>&);

int main()
{
    setlocale(LC_ALL, "spanish");

    bool salir{false};
    int entradaMenu{0};
    string entrada;

    do {
        mostrarMenu();

        cout << "Ingrese una opción del menú: ";
        //cin >> entrada;
        getline(cin, entrada);
        cout << endl;

        try {
            entradaMenu = stoi(entrada); // Intentar convertir a número

            switch (entradaMenu) {
            case 1:
                registrarEstudiante(); // función que registra un estudiante
                break;
            case 2:
                ingresarCalificaciones();
                break;
            case 3:
                cout << "Test" << endl;
                break;
            case 4:
                modificarRegistroNotas();
                break;
            case 5:
                cout << "Test" << endl;
                break;
            case 6:
                cout << "Test" << endl;
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

void mostrarMenu() {

    cout << "* * * Menú Principal * * *" << endl;
    cout << endl;
    cout << "1. Registrar estudiante" << endl;
    cout << "2. Ingresar calificaciones" << endl;
    cout << "3. Modificar datos del estudiante" << endl;
    cout << "4. Modificar de notas por estudiante" << endl;
    cout << "5. Eliminar registro de estudiante" << endl;
    cout << "6. Reporte de estudiantes, promedios, estado" << endl;
    cout << "7. Salir del programa" << endl;
    cout << endl;
}

void registrarEstudiante(){ //Registrar a un estudiante nuevo
    string idEstudiante;
    string nombre;
    string provincia;
    string canton;
    string distrito;
    string edad;
    string genero;

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

    guardarEstudianteEnArchivo(idEstudiante, nombre,provincia, canton, distrito, genero);
    cout << endl;
    cout << "Estudiante registrado con éxito en ESTUDIANTES.txt" << endl;

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

void guardarEstudianteEnArchivo(string idEstudiante, string nombre, string provincia, string canton, string distrito, string genero) {
    cout << "Función de guardar los datos del estudiante." << endl;
}

// Opcion 2: ingresar caliicaciones

void ingresarCalificaciones() { //Registrar las calificaciones de un estudiante
    string idEstudiante;
    bool idEncontrado{false};
    bool opcionValida{false};
    string entrada;
    array<double, 5> notas;
    double promedio;
    string estadoCurso;

    idEstudiante = obtenerIdEstudiante();
    idEncontrado = existeEstudiante(idEstudiante);

    if(idEncontrado) {
        // mensaje de encontrado
        // proceder a ingresar calificaciones
        cout << "Estudiante registrado. " << endl;
        notas = solicitarCalificaciones();

        mostrarNotas(notas);

        promedio = calcularPromedio(notas);
        estadoCurso = determinarResultado(promedio);
        mostrarResultadoCurso(promedio, estadoCurso);


    } else {
        cout << "Estudiante no registrado. " << endl;
        cout << endl;
        //cout << "¿Desea ingresar otra identificación? [S/N]." << endl;
        //entrada = cin.get();

        do {
            entrada = obtenerInformacion("¿Desea ingresar otra identificación? [S/N]: ");

            if (entrada.length() == 1) {
                char opcion = tolower(entrada[0]);

                switch (opcion) {
                    case 's':
                    case 'S':
                        ingresarCalificaciones();
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

    //registrarNotasEnArchivo(idEstudiante, notas);

}

bool existeEstudiante(string id) {
    return true ;
}

array<double, 5> solicitarCalificaciones() {
    string materia;
    string calificacion;
    const double CALIF_MIN = 0.0;
    const double CALIF_MAX = 10.0;
    array<double, 5> notas;
    string entrada;
    double nota;
    int indiceActividadEvaluativa = 0;
    string actividadEvaluativa;

    materia = obtenerInformacion("Ingrese el nombre de la materia que cursa: ");

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

void mostrarNotas(const array<double, 5>& notas) {
    // Mostrar notas ingresadas
    cout << "Notas ingresadas:" << endl;

    for (size_t i = 0; i < notas.size(); ++i) {
        cout << "Nota #" << i + 1 << ": " << notas[i] << "\n";
    }
}

double calcularPromedio(const array<double, 5>& notas) {
    double notaFinal = 0.0;
    const array<double, 5> pesos = {0.1, 0.2, 0.3, 0.1, 0.3};

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

// Opción 4: Modificar registro de notas

void modificarRegistroNotas() {
    string idEstudiante;
    bool idEncontrado{false};
    vector<string> registrosPorEstudiante;
    array<string, 9> registroPorModificar;
    array<double, 5> notasPorMateriaPorEstudiante;
    int indiceRegistro = 0;

    idEstudiante = obtenerIdEstudiante();
    idEncontrado = existeEstudiante(idEstudiante);

    if(idEncontrado) {
        cout << "Estudiante registrado. " << endl;
        cout << endl;
        // Hacer lo que tiene que hacer
        registrosPorEstudiante = buscarMateriasRegistradasEnArchivo(idEstudiante); // vector con todos los registros que coincidan con el ide del estudiante
        registroPorModificar = mostrarMateriasRegistradasPorEstudiante(registrosPorEstudiante);
        salvarNotasModificadasEnArchivo(registroPorModificar);
    } else {
        cout << "Estudiante no registrado. " << endl;
    }

}

vector<string> buscarMateriasRegistradasEnArchivo(string idEstudiante) { // cambiar el tipo del return por un vector de arrays
    vector<string> registroNotasPorIdEstudiante; // convertir este vector en un vector de arrays
    // Extraer del archivo una matriz con todos los registros que coincidan con el id del estudiante y devolverlo
    registroNotasPorIdEstudiante.push_back("Ana");
    registroNotasPorIdEstudiante.push_back("Carlos");
    registroNotasPorIdEstudiante.push_back("María");
    registroNotasPorIdEstudiante.push_back("Luis");
    registroNotasPorIdEstudiante.push_back("Elena");

    return registroNotasPorIdEstudiante;
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

void salvarNotasModificadasEnArchivo(array<string, 9>& registroNotasModificadas) {
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




