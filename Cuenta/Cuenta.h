// Cuenta.h
// Clase Cuenta
#include <string>

class Cuenta {
public:
    // Constructor por defecto
    Cuenta(std::string nombreCuenta, int saldoInicial) 
        : nombre{nombreCuenta} {
        if (saldoInicial > 0) {
            saldo = saldoInicial;
        }
    }   

    void depositar(int cantidadDepositada) {
        if (cantidadDepositada > 0) {
            saldo = saldo + cantidadDepositada;
        }
    }

    int getSaldo() const {
        return saldo;
    }

    // set
    void setNombre(std::string nombreCuenta) {
        nombre = nombreCuenta;
    }

    // get
    std::string getNombre() const { 
        return nombre; 
    }

    std::string mostrarCantidad(Cuenta c) const {
        return "Nombre de la cuenta: " + c.getNombre() + ". El saldo es: $" + std::to_string(c.getSaldo());
    }
private:
    std::string nombre;
    int saldo{0}; // Inicializa el saldo a 0
};