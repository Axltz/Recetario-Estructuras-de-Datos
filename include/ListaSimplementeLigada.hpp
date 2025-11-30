#ifndef LISTA_SIMPLEMENTE_LIGADA_HPP
#define LISTA_SIMPLEMENTE_LIGADA_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>

template <typename T>
class Nodo {
public:
    T dato;
    Nodo* next;

    Nodo(const T& d) : dato(d), next(nullptr) {}
};

template <typename T>
class ListaSimplementeLigada {
public:
    Nodo<T>* ancla;
    Nodo<T>* localiza;
    Nodo<T>* ultimo;

    ListaSimplementeLigada() {
        ancla = new Nodo<T>(T());
        ancla->next = nullptr;
        localiza = nullptr;
        ultimo = nullptr;
    }

    ListaSimplementeLigada(const ListaSimplementeLigada<T>& other) {
        ancla = new Nodo<T>(T());
        localiza = nullptr;
        ultimo = nullptr;

        Nodo<T>* p = other.ancla->next;
        Nodo<T>* prev = ancla;

        while (p != nullptr) {
            Nodo<T>* nuevo = new Nodo<T>(p->dato);
            prev->next = nuevo;
            prev = nuevo;
            ultimo = nuevo;
            p = p->next;
        }
    }

    ListaSimplementeLigada(ListaSimplementeLigada<T>&& other) noexcept {
        ancla = other.ancla;
        localiza = other.localiza;
        ultimo = other.ultimo;

        other.ancla = new Nodo<T>(T());
        other.localiza = nullptr;
        other.ultimo = nullptr;
    }

    ListaSimplementeLigada<T>& operator=(const ListaSimplementeLigada<T>& other) {
        if (this == &other) return *this;

        anula();

        Nodo<T>* p = other.ancla->next;
        Nodo<T>* prev = ancla;

        while (p != nullptr) {
            Nodo<T>* nuevo = new Nodo<T>(p->dato);
            prev->next = nuevo;
            prev = nuevo;
            ultimo = nuevo;
            p = p->next;
        }

        return *this;
    }

    ListaSimplementeLigada<T>& operator=(ListaSimplementeLigada<T>&& other) noexcept {
        if (this == &other) return *this;

        ancla = other.ancla;
        localiza = other.localiza;
        ultimo = other.ultimo;

        other.ancla = new Nodo<T>(T());
        other.localiza = nullptr;
        other.ultimo = nullptr;

        return *this;
    }

    ~ListaSimplementeLigada() {
        anula();
        delete ancla;
    }

    bool vacia() const {
        return ancla->next == nullptr;
    }

    Nodo<T>* first() const {
        if (vacia()) return nullptr;
        return ancla->next;
    }


    void insertarOrdenado(const T& dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        Nodo<T>* ant = ancla;
        Nodo<T>* act = ancla->next;

        while (act && act->dato < dato) {
            ant = act;
            act = act->next;
        }

        ant->next = nuevo;
        nuevo->next = act;

        if (act == nullptr)
            ultimo = nuevo;
    }

    void elimina(const T& valor) {
        if (vacia()) throw std::runtime_error("La lista está vacía.");
        Nodo<T>* ant = ancla;
        Nodo<T>* act = ancla->next;
        while (act && !(act->dato == valor)) {
            ant = act;
            act = act->next;
        }
        if (!act) throw std::runtime_error("Elemento no encontrado.");
        if (act == ultimo) {
            ultimo = (ant == ancla ? nullptr : ant);
        }
        ant->next = act->next;
        delete act;
    }

    Nodo<T>* localizar(const T& dato) const {
        Nodo<T>* p = ancla->next;
        while (p && !(p->dato == dato)) p = p->next;
        return p;
    }

    void anula() {
        Nodo<T>* p = ancla->next;

        while (p != nullptr) {
            Nodo<T>* aux = p;
            p = p->next;
            delete aux;
        }

        ancla->next = nullptr;
        ultimo = nullptr;
        localiza = nullptr;
    }

    std::string toString() const {
        std::ostringstream oss;
        Nodo<T>* p = ancla->next;
        int i = 1;

        while (p != nullptr) {
            oss << i++ << ". " << p->dato << "\n";
            p = p->next;
        }

        return oss.str();
    }
};

#endif
