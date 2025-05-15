// Cuenta.h
// Clase Cuenta
#include <string>

class Cuenta {
public:
    // Constructor por defecto
    explicit Cuenta(std::string nombreCuenta) 
        : nombre{nombreCuenta} {
        // Cuerpo vacío
    }

    // set
    void setNombre(std::string nombreCuenta) {
        nombre = nombreCuenta;
    }

    // get
    std::string getNombre() const { 
        return nombre; 
    }
private:
    std::string nombre;
};