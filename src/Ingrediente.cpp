#include "Ingrediente.hpp"
#include <sstream>
#include <iomanip>

Ingrediente::Ingrediente() : nombre(""), unidad(""), cantidad(0.0f) {}

Ingrediente::Ingrediente(const std::string& n, const std::string& u, float c)
    : nombre(n), unidad(u), cantidad(c) {}

std::string Ingrediente::getNombre() const { return nombre; }
std::string Ingrediente::getUnidad() const { return unidad; }
float Ingrediente::getCantidad() const { return cantidad; }

void Ingrediente::setNombre(const std::string& n) { nombre = n; }
void Ingrediente::setUnidad(const std::string& u) { unidad = u; }
void Ingrediente::setCantidad(float c) { cantidad = c; }

std::string Ingrediente::toString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << nombre << " - " << cantidad << " " << unidad;
    return oss.str();
}

bool Ingrediente::operator==(const Ingrediente& other) const {
    return nombre == other.nombre;
}

bool Ingrediente::operator<(const Ingrediente& other) const {
    return nombre < other.nombre;
}
