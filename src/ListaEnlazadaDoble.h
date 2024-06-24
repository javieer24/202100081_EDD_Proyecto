#ifndef LISTA_ENLAZADA_DOBLE_H
#define LISTA_ENLAZADA_DOBLE_H

#include <iostream>
#include "Vuelo.h"

// Nodo de la lista enlazada doble
struct NodoDoble {
    Vuelo vuelo;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(const Vuelo& v) : vuelo(v), siguiente(nullptr), anterior(nullptr) {}
};

// Lista enlazada doble
class ListaEnlazadaDoble {
public:
    ListaEnlazadaDoble() : cabeza(nullptr), cola(nullptr) {}

    ~ListaEnlazadaDoble() {
        limpiar();
    }

    // Función para insertar un vuelo al final de la lista
    void insertarAlFinal(const Vuelo& vuelo) {
        NodoDoble* nuevoNodo = new NodoDoble(vuelo);
        if (cola == nullptr) {
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
    }

    // Función para imprimir la lista
    void imprimir() const {
        NodoDoble* actual = cabeza;
        while (actual != nullptr) {
            std::cout << actual->vuelo << std::endl;
            actual = actual->siguiente;
        }
    }

    // Función para limpiar la lista
    void limpiar() {
        NodoDoble* actual = cabeza;
        while (actual != nullptr) {
            NodoDoble* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza = cola = nullptr;
    }

private:
    NodoDoble* cabeza;
    NodoDoble* cola;
};

#endif // LISTA_ENLAZADA_DOBLE_H
