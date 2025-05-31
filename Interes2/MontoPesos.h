#include <string>
#include <cmath>
#include <cstdint>

class MontoPesos {
public:
    explicit MontoPesos(int64_t valor) : cantidad{valor} { }

    void suma(MontoPesos right) {
        cantidad += right.cantidad;
    }
    void resta(MontoPesos right) {
        cantidad -= right.cantidad;
    }
    void sumaInteres(int tasa, int divisor) {
        MontoPesos interes{
            (cantidad * tasa + divisor / 2) / divisor
        };
        suma(interes);
    }

    std::string toString() const {
        std::string pesos{std::to_string(cantidad / 100)};
        std::string centavos{std::to_string(std::abs(cantidad % 100))};
        
        return pesos + "." + (centavos.size() == 1 ? "0" : "") + centavos;
    }
private:
    int64_t cantidad{0}; // Monto en centavos
};