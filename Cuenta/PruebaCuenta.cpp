// PruebaCuenta.cpp
// Crear y manipular un objeto de la clase Cuenta
#include <iostream>
#include "Cuenta.h" // Definicion de la clase Cuenta

using namespace std;

int main() {
    // Crear un objeto de la clase Cuenta
    Cuenta cuenta1{"Juan Perez", 50}; // Inicializa el nombre de la cuenta
    Cuenta cuenta2{"Maria Lopez", -7}; // Inicializa el nombre de la cuenta

    cout << cuenta1.mostrarCantidad(cuenta1) << endl; // Muestra el saldo de la cuenta1
    cout << cuenta2.mostrarCantidad(cuenta2) << endl; // Muestra el saldo de la cuenta2

    
    cout << "Ingrese el monto el monto del deposito para la cuenta1: $";
    int cantidadDepositada;
    cin >> cantidadDepositada;
    cout << "Agregando $" << cantidadDepositada << " al saldo de la cuenta1." << endl;
    cuenta1.depositar(cantidadDepositada); // Deposita la cantidad en la cuenta1

    cout << cuenta1.mostrarCantidad(cuenta1) << endl; // Muestra el saldo de la cuenta1
    cout << cuenta2.mostrarCantidad(cuenta2) << endl; // Muestra el saldo de la cuenta2
    
    cout << "Ingrese el monto el monto del deposito para la cuenta2: $";
    cin >> cantidadDepositada;
    cout << "Agregando $" << cantidadDepositada << " al saldo de la cuenta2." << endl;
    cuenta2.depositar(cantidadDepositada); // Deposita la cantidad en la cuenta1

    cout << cuenta1.mostrarCantidad(cuenta1) << endl; // Muestra el saldo de la cuenta1
    cout << cuenta2.mostrarCantidad(cuenta2) << endl; // Muestra el saldo de la cuenta2

    return 0; // Fin del programa
}
