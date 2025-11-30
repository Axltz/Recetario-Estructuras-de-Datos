#ifndef RECETARIO_HPP
#define RECETARIO_HPP

#include "Receta.hpp"
#include "ListaDoblementeLigada.hpp"
#include "ListaSimplementeLigada.hpp"
#include <string>
#include <iostream>

class Recetario {
private:
    ListaDoblementeLigada<Receta> recetas;

public:
    Recetario();
    ~Recetario();

    void agregarReceta(const Receta& r);
    void agregarRecetaEnPosicion(const Receta& r, int pos);
    void eliminarRecetaPorNombre(const std::string& nombre);
    void eliminarTodasRecetas(); 
    Receta* buscarRecetaPorNombre(const std::string& nombre) const;
    void buscarPorCategoria(const std::string& categoria);
    void mostrarTodas();
    void ordenarPorNombre();
    void ordenarPorTiempo();

    void guardarADisco(const std::string& archivo) const;
    void leerDeDisco(const std::string& archivo);
};

#endif
