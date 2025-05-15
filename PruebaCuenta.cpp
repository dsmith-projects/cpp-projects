// PruebaCuenta.cpp
// Autor: Deitel&Deitel
// Crear y manipular un objeto de la clase Cuenta
#include <iostream>
#include "Cuenta.h" // Definicion de la clase Cuenta

using namespace std;

int main() {
    // Crear un objeto de la clase Cuenta
    Cuenta cuenta1{"Juan Perez"}; // Inicializa el nombre de la cuenta
    Cuenta cuenta2{"Maria Lopez"}; // Inicializa el nombre de la cuenta

    // Mostrar el nombre de la cuenta
    cout << "El nombre de la cuenta1 es: " << cuenta1.getNombre() << endl;
    cout << "El nombre de la cuenta2 es: " << cuenta2.getNombre() << endl;

    return 0; // Fin del programa
}
