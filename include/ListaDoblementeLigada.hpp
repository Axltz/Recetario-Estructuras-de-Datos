#ifndef LISTA_DOBLEMENTE_LIGADA_HPP
#define LISTA_DOBLEMENTE_LIGADA_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>

template <typename T>
class NodoDoble {
public:
    T dato;
    NodoDoble<T>* siguiente;
    NodoDoble<T>* anterior;
    NodoDoble(const T& d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaDoblementeLigada {
public:
    NodoDoble<T>* ancla;
    NodoDoble<T>* localiza;
    NodoDoble<T>* ultimo;

    ListaDoblementeLigada() {
        ancla = new NodoDoble<T>(T());
        ancla->siguiente = nullptr;
        ancla->anterior = nullptr;
        localiza = nullptr;
        ultimo = nullptr;
    }

    ~ListaDoblementeLigada() {
        anula();
        delete ancla;
    }

    bool vacia() const {
        return ancla->siguiente == nullptr;
    }

    NodoDoble<T>* first() const {
        if (vacia()) throw std::runtime_error("La lista esta vacia");
        return ancla->siguiente;
    }

    NodoDoble<T>* last() const {
        if (vacia()) throw std::runtime_error("La lista esta vacia");
        return ultimo;
    }

    NodoDoble<T>* nextNode(NodoDoble<T>* nodo) const {
        if (!nodo) throw std::runtime_error("Nodo invalido");
        return nodo->siguiente;
    }

    NodoDoble<T>* previousNode(NodoDoble<T>* nodo) const {
        if (!nodo) throw std::runtime_error("Nodo invalido");
        if (nodo == ancla->siguiente) return ancla;
        if (!nodo->anterior) throw std::runtime_error("Nodo no pertenece a la lista");
        return nodo->anterior;
    }

    NodoDoble<T>* localizaValor(const T& valor) {
        NodoDoble<T>* p = ancla->siguiente;
        while (p != nullptr) {
            if (p->dato == valor) {
                localiza = p;
                return p;
            }
            p = p->siguiente;
        }
        localiza = nullptr;
        return nullptr;
    }

void insertar(const T& dato) {
    if (!localiza) localiza = ancla;  
    NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
    NodoDoble<T>* siguiente = localiza->siguiente;
    nuevo->siguiente = siguiente;
    nuevo->anterior = localiza;
    localiza->siguiente = nuevo;
    if (siguiente) siguiente->anterior = nuevo;
    if (localiza == ultimo) ultimo = nuevo;
    localiza = nuevo;  
}
void insertarEnPosicion(const T& dato, int pos) {
    NodoDoble<T>* p = ancla;
    int contador = 0;
    while (p->siguiente && contador < pos) {
        p = p->siguiente;
        contador++;
    }
    localiza = p;
    insertar(dato);
}
void insertarAlFinal(const T& dato) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(dato);
    if (!ancla->siguiente) { 
        ancla->siguiente = nuevo;
        nuevo->anterior = ancla;
        ultimo = nuevo;
    } else {
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        ultimo = nuevo;
    }
}

    void elimina(const T& valor) {
        if (vacia()) throw std::runtime_error("La lista esta vacia");
        NodoDoble<T>* p = ancla->siguiente;
        while (p != nullptr && !(p->dato == valor)) p = p->siguiente;
        if (!p) throw std::runtime_error("Elemento no encontrado");
        NodoDoble<T>* A = p->anterior;
        NodoDoble<T>* S = p->siguiente;
        A->siguiente = S;
        if (S) S->anterior = A;
        if (p == ultimo) {
            if (A == ancla) ultimo = nullptr;
            else ultimo = A;
        }
        delete p;
        localiza = nullptr;
    }

    NodoDoble<T>* dividirMitad(NodoDoble<T>* cabeza) {
        if (!cabeza || !cabeza->siguiente) return nullptr;
        NodoDoble<T>* lento = cabeza;
        NodoDoble<T>* rapido = cabeza->siguiente;
        while (rapido && rapido->siguiente) {
            lento = lento->siguiente;
            rapido = rapido->siguiente->siguiente;
        }
        NodoDoble<T>* mitad = lento->siguiente;
        lento->siguiente = nullptr;
        if (mitad) mitad->anterior = nullptr;
        return mitad;
    }

    NodoDoble<T>* mergeNombre(NodoDoble<T>* a, NodoDoble<T>* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->dato.getNombre() < b->dato.getNombre()) {
            a->siguiente = mergeNombre(a->siguiente, b);
            if (a->siguiente) a->siguiente->anterior = a;
            a->anterior = nullptr;
            return a;
        } else {
            b->siguiente = mergeNombre(a, b->siguiente);
            if (b->siguiente) b->siguiente->anterior = b;
            b->anterior = nullptr;
            return b;
        }
    }

    NodoDoble<T>* mergeSortNombre(NodoDoble<T>* cabeza) {
        if (!cabeza || !cabeza->siguiente) return cabeza;
        NodoDoble<T>* mitad = dividirMitad(cabeza);
        NodoDoble<T>* izq = mergeSortNombre(cabeza);
        NodoDoble<T>* der = mergeSortNombre(mitad);
        return mergeNombre(izq, der);
    }

    NodoDoble<T>* mergeTiempo(NodoDoble<T>* a, NodoDoble<T>* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->dato.getTiempo() < b->dato.getTiempo()) {
            a->siguiente = mergeTiempo(a->siguiente, b);
            if (a->siguiente) a->siguiente->anterior = a;
            a->anterior = nullptr;
            return a;
        } else {
            b->siguiente = mergeTiempo(a, b->siguiente);
            if (b->siguiente) b->siguiente->anterior = b;
            b->anterior = nullptr;
            return b;
        }
    }

    NodoDoble<T>* mergeSortTiempo(NodoDoble<T>* cabeza) {
        if (!cabeza || !cabeza->siguiente) return cabeza;
        NodoDoble<T>* mitad = dividirMitad(cabeza);
        NodoDoble<T>* izq = mergeSortTiempo(cabeza);
        NodoDoble<T>* der = mergeSortTiempo(mitad);
        return mergeTiempo(izq, der);
    }

    void anula() {
        NodoDoble<T>* p = ancla->siguiente;
        while (p != nullptr) {
            NodoDoble<T>* aux = p;
            p = p->siguiente;
            delete aux;
        }
        ancla->siguiente = nullptr;
        ultimo = nullptr;
        localiza = nullptr;
    }

    T recuperar(NodoDoble<T>* nodo) const {
        if (!nodo) throw std::runtime_error("Nodo invalido");
        return nodo->dato;
    }

    int size() const {
        int c = 0;
        NodoDoble<T>* p = ancla->siguiente;
        while (p != nullptr) { c++; p = p->siguiente; }
        return c;
    }

    std::string toString() const {
        std::ostringstream oss;
        NodoDoble<T>* p = ancla->siguiente;
        int i = 1;
        while (p != nullptr) {
            try { oss << i << ". " << p->dato.toString() << "\n"; }
            catch (...) { oss << i << ". [dato]\n"; }
            p = p->siguiente;
            i++;
        }
        return oss.str();
    }

    ListaDoblementeLigada<T>& operator=(const ListaDoblementeLigada<T>& other) {
        if (this == &other) return *this;
        anula();
        NodoDoble<T>* p = other.ancla->siguiente;
        NodoDoble<T>* ult = nullptr;
        while (p != nullptr) {
            NodoDoble<T>* nuevo = new NodoDoble<T>(p->dato);
            if (!ult) {
                ancla->siguiente = nuevo;
                nuevo->anterior = ancla;
            } else {
                ult->siguiente = nuevo;
                nuevo->anterior = ult;
            }
            ult = nuevo;
            p = p->siguiente;
        }
        ultimo = ult;
        localiza = nullptr;
        return *this;
    }
};

#endif
