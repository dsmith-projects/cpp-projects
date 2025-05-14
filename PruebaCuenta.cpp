// PruebaCuenta.cpp
// Autor: Deitel&Deitel
// Crear y manipular un objeto de la clase Cuenta

#include <iostream>
#include <string>  
#include "Cuenta.h" // Definicion de la clase Cuenta

using namespace std;

int main()
{
    // Crear un objeto de la clase Cuenta
    Cuenta miCuenta; 

    cout << "El nombre inicial de la cuenta es: " << miCuenta.getNombre();

    // Solicitar y leer el nombre
    cout << "\nIngrese el nombre de la cuenta: ";
    string nombre;
    getline(cin, nombre);
    miCuenta.setNombre(nombre);

    // Muestrar el nombre almacenado en el objeto miCuenta
    cout << "El nombre de la cuenta es: " << miCuenta.getNombre() << endl;

    return 0; // Fin del programa
}
