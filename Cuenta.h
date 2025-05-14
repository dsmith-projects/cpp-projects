class Cuenta {
public:
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