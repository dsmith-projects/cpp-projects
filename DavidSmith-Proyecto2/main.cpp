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
bool estaEnRango(const string&);
void mostrarOpcionesGenero();
string obtenerGenero();
void ingresarCalificaciones();
bool validacionIdentificacion(string);
bool existeEstudiante(string);

int main()
{
    setlocale(LC_ALL, "spanish");

    bool salir{false};
    int entradaMenu{0};
    string entrada;
    bool regresarAMenu = false;

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
                cout << "Test" << endl;
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

    //USar enums y crear un switch
    mostrarOpcionesGenero();
//    cout << "Seleccione el género con el que se identifica: " << endl;
//    cout << "    " << left << setw(15) << "[1] Femenino" << endl;
//    cout << "    " << left << setw(15) << "[2] Masculino" << endl;
//    cout << "    " << left << setw(15) << "[3] Femenino" << endl;
//    cout << "    " << left << setw(15) << "[4] No binario" << endl;
//    cout << "    " << left << setw(15) << "[5] Género fluido" << endl;
//    cout << "    " << left << setw(15) << "[6] Prefiere no decir" << endl;
//    cout << "    " << left << setw(15) << "[7] Otro" << endl;

    genero = obtenerGenero();
//    cout << "Opción: ";
//    getline(cin, genero);
    cout << "Género seleccionado: " << genero << endl;

    cout << endl;

    cout << "Id: " << idEstudiante << endl;
    cout << "Nombre completo: " << nombre << endl;
    cout << "Residencia: " << provincia << " " << canton << " " << distrito << endl;
    cout << "Edad: " << edad << endl;
    cout << "Género: " << genero << endl;

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

    cout << enunciado;
    getline(cin, datos);

    return datos;
}

string obtenerEdadEstudiante(){
    string edad;
    bool edadEstudianteValida{false};

    do {
        cout << "Ingrese la edad (entre 18 y 100): ";
        getline(cin, edad);

        if(esNumerico(edad)) {
            if(estaEnRango(edad)) {
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

bool esNumerico(const string& edad) {
    bool esValida = true;

    if(edad.empty()){
        esValida = false;
    } else {
        for(char caracter : edad) {
            if(!isdigit(caracter)) {
                esValida = false;
                break;
            }
        }
    }

    return esValida;
}

bool estaEnRango(const string& edad) {
    bool estaEnRango = false;
    int edadEstudiante = stoi(edad);

    if(edadEstudiante >= 18 && edadEstudiante <= 100) {
        estaEnRango = true;
    }

    return estaEnRango;
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

    while (true) {
        cout << "Ingrese una opción: ";
        getline(cin, entrada);

        if (entrada.length() == 1) {
            char opcion = tolower(entrada[0]);

            switch (opcion) {
                case '1':
                    return "femenino";
                case '2':
                    return "masculino";
                case '3':
                    return "no binario";
                default:
                    break;
            }
        }
        cout << endl;
        cout << "Opción inválida. Ingrese una opción de género válida.\n";
    }
}


void ingresarCalificaciones() { //Registrar las calificaciones de un estudiante
    string idEstudiante;
    bool esIdValida{false};
    bool idEncontrado{false};
    char entrada;

    do {

        cout << "Ingrese la identificación del estudiante (10 dígitos): ";
        getline(cin, idEstudiante);

        esIdValida = validacionIdentificacion(idEstudiante);

        //validar identificacion identificacionValida(const &idEstudiante)
        if(esIdValida) {
            esIdValida = true;

            idEncontrado = existeEstudiante(idEstudiante);

            if(idEncontrado) {
                // mensaje de encontrado
                // proceder a ingresar calificaciones
                cout << "Estudiante registrado. " << endl;
            } else {
                cout << "Estudiante no registrado. " << endl;
                cout << "¿Desea ingresar otra identificación? [S/N]." << endl;
                entrada = cin.get();

                if(entrada == 'S' || entrada == 's') {
                    esIdValida = false;
                }
            }

        } else {
            cout << "Identificación inválida. Intente de nuevo: ";
            cout << endl;
        }
    } while(!esIdValida);
}

bool validacionIdentificacion(string id) {
    return true;
}

bool existeEstudiante(string id) {
    return true;
}
