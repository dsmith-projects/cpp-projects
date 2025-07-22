#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>

const size_t NUM_GRADES = 5;

struct Estudiante {
    std::string nombre;
    std::array<double, NUM_GRADES> calificaciones;
};

// ✅ Reads all students from file
std::vector<Estudiante> cargarEstudiantes(const std::string& archivoNombre) {
    std::vector<Estudiante> estudiantes;
    std::ifstream archivo(archivoNombre);
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string nombre;
        std::getline(ss, nombre, ',');

        Estudiante est;
        est.nombre = nombre;

        for (size_t i = 0; i < NUM_GRADES; ++i) {
            std::string notaStr;
            std::getline(ss, notaStr, ',');
            est.calificaciones[i] = std::stod(notaStr);
        }

        estudiantes.push_back(est);
    }

    archivo.close();
    return estudiantes;
}

// ✅ Overwrites the entire file with updated list
void guardarEstudiantes(const std::vector<Estudiante>& estudiantes, const std::string& archivoNombre) {
    std::ofstream archivo(archivoNombre);
    for (const auto& est : estudiantes) {
        archivo << est.nombre;
        for (double nota : est.calificaciones) {
            archivo << "," << nota;
        }
        archivo << "\n";
    }
    archivo.close();
}

// ✅ Updates specific student’s grades
bool actualizarNotas(std::vector<Estudiante>& estudiantes, const std::string& nombreBuscado, const std::array<double, NUM_GRADES>& nuevasNotas) {
    for (auto& est : estudiantes) {
        if (est.nombre == nombreBuscado) {
            est.calificaciones = nuevasNotas;
            return true;
        }
    }
    return false; // not found
}

int main() {
    std::string archivo = "estudiantes.txt";
    std::string nombreObjetivo = "Carlos";

    std::array<double, NUM_GRADES> nuevasNotas = {10.0, 9.5, 10.0, 9.0, 10.0};

    // 1. Load
    std::vector<Estudiante> lista = cargarEstudiantes(archivo);

    // 2. Modify
    if (actualizarNotas(lista, nombreObjetivo, nuevasNotas)) {
        std::cout << "Notas actualizadas para " << nombreObjetivo << "\n";
        // 3. Save
        guardarEstudiantes(lista, archivo);
    } else {
        std::cout << "Estudiante no encontrado.\n";
    }

    return 0;
}
