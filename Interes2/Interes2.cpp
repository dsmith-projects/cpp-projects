// Interes2.cpp
// Cálculo de interés compuesto de una cuenta con ciclo for
#include <iostream>
#include <iomanip>
#include <string> // 
#include "MontoPesos.h"

using namespace std;

int main() {

    MontoPesos d1{12345};
    MontoPesos d2{1576};

    cout << "Despues de sumar d2 (" << d2.toString() << ") a d1 (" << d1.toString() << "), d1 = ";
    d1.suma(d2);
    cout << d1.toString() << "\n";

    cout << "Despues de restar d2 (" << d2.toString() << ") a d1 (" << d1.toString() << "), d1 = ";
    d1.resta(d2);
    cout << d1.toString() << "\n";

    cout << "Despues de restar d1 (" << d1.toString() << ") a d2 (" << d2.toString() << "), d2 = ";
    d2.resta(d1);
    cout << d2.toString() << "\n\n";

     cout << "Ingrese la tasa de interés entera y el divisor. Por ejemplo:\n" 
            << "para      2%, ingrese:     2  100\n"
            << "para    2.3%, ingrese:    23  1000\n"
            << "para   2.37%, ingrese:   237  10000\n"
            << "para  2.375%, ingrese:  2375  100000\n";

    int tasa;
    int divisor;
    cin >> tasa >> divisor;

    MontoPesos saldo{100000};

    cout << "\nSaldo inicial: " << saldo.toString() << endl;
    cout << "\nYear" << setw(30) << "Cantidad en deposito" << endl;
    

    for(unsigned int year{1}; year <= 10; year++){
        saldo.sumaInteres(tasa, divisor);

        cout << setw(4) << year << setw(30) << saldo.toString() << endl;
    }
    
}
