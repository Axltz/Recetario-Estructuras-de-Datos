#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

#include <string>
#include <sstream>
#include <iomanip>


class Ingrediente {
private:
    std::string nombre;
    std::string unidad;
    float cantidad;

public:
    Ingrediente();
    Ingrediente(const std::string& n, const std::string& u, float c);

    std::string getNombre() const;
    std::string getUnidad() const;
    float getCantidad() const;

    void setNombre(const std::string& n);
    void setUnidad(const std::string& u);
    void setCantidad(float c);

    std::string toString() const;

    bool operator==(const Ingrediente& other) const;
    bool operator<(const Ingrediente& other) const;
};

#endif
