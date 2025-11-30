#ifndef RECETA_HPP
#define RECETA_HPP

#include <string>
#include <iostream>
#include "ListaSimplementeLigada.hpp"
#include "Ingrediente.hpp"
class Receta {
private:
    std::string nombre;
    std::string categoria;
    std::string autor;
    int tiempo;
    std::string procedimiento;
    ListaSimplementeLigada<Ingrediente> ingredientes;

public:
    Receta();
    Receta(const std::string& n, const std::string& c,
           const std::string& a, int t, const std::string& p);
    Receta(const Receta& other);
    Receta(Receta&& other) noexcept;

    Receta& operator=(const Receta& other);
    Receta& operator=(Receta&& other) noexcept;
    bool operator==(const Receta& other) const;
    bool operator<(const Receta& other) const;

    const std::string& getNombre() const;
    const std::string& getCategoria() const;
    const std::string& getAutor() const;
    int getTiempo() const;
    const std::string& getProcedimiento() const;

    void setNombre(const std::string& n);
    void setCategoria(const std::string& c);
    void setAutor(const std::string& a);
    void setTiempo(int t);
    void setProcedimiento(const std::string& p);

    void agregarIngrediente(const Ingrediente& ing);
    void eliminarIngrediente(const std::string& nombreIng);
    void eliminarTodosIngredientes();
    Ingrediente* buscarIngrediente(const std::string& nombreIng);
    void imprimirIngredientes() const;

    std::string toString() const;
    std::string toStringResumen() const;

    void serializar(std::ostream& os) const;
    static Receta deserializar(std::istream& is);
};

#endif
