// Intereses.cpp
// Cálculo de interés compuesto de una cuenta con ciclo for
#include <iostream>
#include <iomanip>
#include <cmath> // función pow

using namespace std;

int main() {
    
    cout << fixed << setprecision(2); 

    double principal{1000.00};
    double tasa{0.05};

    cout << "Capital inicial: " << principal << endl;
    cout << "Tasa de interés: " << tasa << endl;
    
    cout << "\nYear" << setw(30) << "Importe del deposito" << endl;

    for(unsigned int year{1}; year <= 10; year++){
        double cantidad = principal * pow(1.0 + tasa, year);

        cout << setw(4) << year << setw(30) << cantidad << endl;
    }
    
}
