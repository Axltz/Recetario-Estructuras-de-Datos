#include "Recetario.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

Recetario::Recetario() {}
Recetario::~Recetario() { recetas.anula(); }

void Recetario::agregarReceta(const Receta& r) {
    recetas.localiza = recetas.ultimo;
    recetas.insertar(r);
}

void Recetario::agregarRecetaEnPosicion(const Receta& r, int pos) {
     NodoDoble<Receta>* p = recetas.ancla->siguiente;
    int contador = 1;
    while (p && contador < pos) {
        p = p->siguiente;
        contador++;
    }

    if (!p) p = recetas.ultimo; 

    recetas.localiza = p->anterior ? p->anterior : recetas.ancla;
    recetas.insertarEnPosicion(r, pos);
}



void Recetario::eliminarRecetaPorNombre(const std::string& nombre) {
    NodoDoble<Receta>* p = recetas.ancla->siguiente;
    while (p) {
        if (p->dato.getNombre() == nombre) {
            recetas.elimina(p->dato);
            return;
        }
        p = p->siguiente;
    }
    throw std::runtime_error("Receta no encontrada");
}

void Recetario::eliminarTodasRecetas() {
    recetas.anula();
}


Receta* Recetario::buscarRecetaPorNombre(const std::string& nombre) const {
    NodoDoble<Receta>* p = recetas.ancla->siguiente;
    while (p) {
        if (p->dato.getNombre() == nombre) return &p->dato;
        p = p->siguiente;
    }
    return nullptr;
}

void Recetario::buscarPorCategoria(const std::string& categoria) {
    NodoDoble<Receta>* p = recetas.first();
    bool encontrado = false;

    while (p) {
        Receta& r = p->dato;  

        if (r.getCategoria() == categoria) {
            std::cout << r.toString() << "\n";
            std::cout << "----------------------------------------------\n";
            encontrado = true;
        }

        p = p->siguiente;  
    }

    if (!encontrado) {
        std::cout << "No se encontraron recetas en esa categoria.\n";
    }
}



void Recetario::mostrarTodas() {
    if (recetas.vacia()) {
        std::cout << "No hay recetas.\n";
        return;
    }

    std::cout << "No.  "
              << std::left << std::setw(30) << "Nombre"
              << std::setw(30) << "Categoria"
              << std::setw(30) << "Autor"
              << std::setw(15) << "Tiempo"
              << "\n";

    std::cout << "-------------------------------------------------------------------------------------------------------\n";

    NodoDoble<Receta>* p = recetas.first();  
    int num = 1;

    while (p != nullptr) {
        Receta r = p->dato; 

        std::cout << std::setw(4) << num++
                  << std::left << std::setw(30) << r.getNombre()
                  << std::setw(30) << r.getCategoria()
                  << std::setw(30) << r.getAutor()
                  << std::setw(15) << r.getTiempo()
                  << "\n";

        p = p->siguiente;
    }
}


void Recetario::ordenarPorNombre() {
    if (recetas.vacia()) return;
    NodoDoble<Receta>* nueva = recetas.mergeSortNombre(recetas.ancla->siguiente);
    recetas.ancla->siguiente = nueva;
    NodoDoble<Receta>* p = nueva;
    NodoDoble<Receta>* ant = recetas.ancla;
    while (p) {
        p->anterior = ant;
        ant = p;
        p = p->siguiente;
    }
    recetas.ultimo = ant;
}

void Recetario::ordenarPorTiempo() {
    if (recetas.vacia()) return;
    NodoDoble<Receta>* nueva = recetas.mergeSortTiempo(recetas.ancla->siguiente);
    recetas.ancla->siguiente = nueva;
    NodoDoble<Receta>* p = nueva;
    NodoDoble<Receta>* ant = recetas.ancla;
    while (p) {
        p->anterior = ant;
        ant = p;
        p = p->siguiente;
    }
    recetas.ultimo = ant;
}

void Recetario::guardarADisco(const std::string& archivo) const {
    std::ofstream os(archivo);
    if (!os) throw std::runtime_error("No se pudo abrir archivo para escritura");
    NodoDoble<Receta>* p = recetas.ancla->siguiente;
    while (p) {
        p->dato.serializar(os);
        p = p->siguiente;
    }
}

void Recetario::leerDeDisco(const std::string& archivo) {
    std::ifstream is(archivo);
    if (!is) throw std::runtime_error("No se pudo abrir archivo para lectura");

    std::string linea;
    while (std::getline(is, linea)) {
        if (linea.size() < 3) continue; 
        std::stringstream ss(linea);
        Receta r = Receta::deserializar(ss);

        recetas.localiza = recetas.ultimo; 
        recetas.insertarAlFinal(r); 
    }
}