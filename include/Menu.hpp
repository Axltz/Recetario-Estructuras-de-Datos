#ifndef MENU_HPP
#define MENU_HPP

#include "Recetario.hpp"
#include <string>

class Menu {
private:
    Recetario recetario;
public:
    void agregarReceta();
    void mostrarRecetas();
    void buscarReceta();
    void eliminarReceta();
    void eliminarTodasRecetas();
    void ordenarRecetas();
    void editarReceta();
    void guardarRecetario();
    void leerRecetario();
    void iniciar();
};

#endif
