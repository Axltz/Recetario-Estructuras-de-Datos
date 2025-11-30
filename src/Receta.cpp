#include "Receta.hpp"
#include <sstream>
#include <stdexcept>
#include <iostream>

Receta::Receta() : nombre(""), categoria(""), autor(""), tiempo(0), procedimiento("") {}

Receta::Receta(const std::string& n, const std::string& c,
               const std::string& a, int t, const std::string& p)
    : nombre(n), categoria(c), autor(a), tiempo(t), procedimiento(p) {}

Receta::Receta(const Receta& other)
    : nombre(other.nombre), categoria(other.categoria), autor(other.autor),
      tiempo(other.tiempo), procedimiento(other.procedimiento) {
    Nodo<Ingrediente>* p = other.ingredientes.first();
    while (p) {
        ingredientes.insertarOrdenado(p->dato);
        p = p->next;
    }
}

Receta::Receta(Receta&& other) noexcept
    : nombre(std::move(other.nombre)), categoria(std::move(other.categoria)),
      autor(std::move(other.autor)), tiempo(other.tiempo),
      procedimiento(std::move(other.procedimiento)),
      ingredientes(std::move(other.ingredientes)) {}

Receta& Receta::operator=(const Receta& other) {
    if (this == &other) return *this;
    nombre = other.nombre;
    categoria = other.categoria;
    autor = other.autor;
    tiempo = other.tiempo;
    procedimiento = other.procedimiento;

    ingredientes.anula();
    Nodo<Ingrediente>* p = other.ingredientes.first();
    while (p) {
        ingredientes.insertarOrdenado(p->dato);
        p = p->next;
    }
    return *this;
}

Receta& Receta::operator=(Receta&& other) noexcept {
    if (this == &other) return *this;
    nombre = std::move(other.nombre);
    categoria = std::move(other.categoria);
    autor = std::move(other.autor);
    tiempo = other.tiempo;
    procedimiento = std::move(other.procedimiento);
    ingredientes = std::move(other.ingredientes);
    return *this;
}

bool Receta::operator==(const Receta& other) const { return nombre == other.nombre; }
bool Receta::operator<(const Receta& other) const { return nombre < other.nombre; }

const std::string& Receta::getNombre() const { return nombre; }
const std::string& Receta::getCategoria() const { return categoria; }
const std::string& Receta::getAutor() const { return autor; }
int Receta::getTiempo() const { return tiempo; }
const std::string& Receta::getProcedimiento() const { return procedimiento; }

void Receta::setNombre(const std::string& n) { nombre = n; }
void Receta::setCategoria(const std::string& c) { categoria = c; }
void Receta::setAutor(const std::string& a) { autor = a; }
void Receta::setTiempo(int t) { tiempo = t; }
void Receta::setProcedimiento(const std::string& p) { procedimiento = p; }

void Receta::agregarIngrediente(const Ingrediente& ing) { ingredientes.insertarOrdenado(ing); }

void Receta::eliminarIngrediente(const std::string& nombreIng) {
    Ingrediente temp(nombreIng, "", 0);
    Nodo<Ingrediente>* p = ingredientes.localizar(temp);
    if (!p) throw std::runtime_error("Ingrediente no encontrado.");
    ingredientes.elimina(p->dato);
}

void Receta::eliminarTodosIngredientes() { ingredientes.anula(); }

Ingrediente* Receta::buscarIngrediente(const std::string& nombreIng) {
    Ingrediente temp(nombreIng, "", 0);
    Nodo<Ingrediente>* p = ingredientes.localizar(temp);
    if (!p) return nullptr;
    return &p->dato;
}

void Receta::imprimirIngredientes() const {
    Nodo<Ingrediente>* p = ingredientes.first();
    while (p) {
        std::cout << "- " << p->dato.toString() << "\n";
        p = p->next;
    }
}

std::string Receta::toString() const {
    std::ostringstream oss;
    oss << "=== " << nombre << " ===\n";
    oss << "Categoria: " << categoria << "\n";
    oss << "Autor: " << autor << "\n";
    oss << "Tiempo: " << tiempo << " min\n\n";
    
    oss << "Ingredientes:\n";
    Nodo<Ingrediente>* p = ingredientes.first();
    while (p) {
        oss << "  - " << p->dato.toString() << "\n";
        p = p->next;
    }

    oss << "\nProcedimiento:\n";
    oss << "" << procedimiento << "\n";

    return oss.str();
}


std::string Receta::toStringResumen() const {
    std::ostringstream oss;
    oss << nombre << " [" << categoria << "] - " << tiempo << " min";
    return oss.str();
}

void Receta::serializar(std::ostream& os) const {
    os << nombre << "@" << categoria << "@" << autor << "@" << tiempo << "@" << procedimiento << "|";
    Nodo<Ingrediente>* p = ingredientes.first();
    while (p) {
        os << p->dato.getNombre() << "@" << p->dato.getUnidad() << "@" << p->dato.getCantidad();
        if (p->next) os << "&";
        p = p->next;
    }
    os << "%\n";  
}
Receta Receta::deserializar(std::istream& is) {
    std::string linea;
    if (!std::getline(is, linea))
        throw std::runtime_error("Línea inválida.");

    size_t pos = linea.find('|');
    if (pos == std::string::npos)
        throw std::runtime_error("Formato de receta incorrecto.");

    std::string datosReceta = linea.substr(0, pos);
    std::string datosIng = linea.substr(pos + 1);

    std::stringstream ss(datosReceta);
    std::string n, c, a, tStr, proc;
    std::getline(ss, n, '@');
    std::getline(ss, c, '@');
    std::getline(ss, a, '@');
    std::getline(ss, tStr, '@');
    std::getline(ss, proc, '@');
    int t = std::stoi(tStr);

    Receta r(n, c, a, t, proc);

    if (!datosIng.empty() && datosIng.back() == '%')
        datosIng.pop_back();

    std::stringstream si(datosIng);
    std::string ingStr;
    while (std::getline(si, ingStr, '&')) {
        if (!ingStr.empty() && ingStr[0] == ' ')
            ingStr.erase(0, 1);

        std::stringstream sx(ingStr);
        std::string in, un, cantStr;
        std::getline(sx, in, '@');
        std::getline(sx, un, '@');
        std::getline(sx, cantStr, '@');
        float cant = std::stof(cantStr);
        r.agregarIngrediente(Ingrediente(in, un, cant));
    }

    return r;
}
