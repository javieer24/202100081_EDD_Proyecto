//Clase Árbol Binario de Búsqueda
#ifndef ARBOLBB_H
#define ARBOLBB_H

#include "NodoBB.h"
#include <iostream>

template <typename T>
class ArbolBB {
private:
    NodoBB<T>* raiz;

    void insertarRec(NodoBB<T>*& nodo, T dato) {
        if (nodo == nullptr) {
            nodo = new NodoBB<T>(dato);
        } else if (dato.horas_de_vuelo < nodo->dato.horas_de_vuelo) {
            insertarRec(nodo->izquierdo, dato);
        } else {
            insertarRec(nodo->derecho, dato);
        }
    }

    void preordenRec(NodoBB<T>* nodo) const {
        if (nodo != nullptr) {
            std::cout << nodo->dato.horas_de_vuelo << " - " << nodo->dato.nombre << std::endl;
            preordenRec(nodo->izquierdo);
            preordenRec(nodo->derecho);
        }
    }

    void inordenRec(NodoBB<T>* nodo) const {
        if (nodo != nullptr) {
            inordenRec(nodo->izquierdo);
            std::cout << nodo->dato.horas_de_vuelo << " - " << nodo->dato.nombre << std::endl;
            inordenRec(nodo->derecho);
        }
    }

    void postordenRec(NodoBB<T>* nodo) const {
        if (nodo != nullptr) {
            postordenRec(nodo->izquierdo);
            postordenRec(nodo->derecho);
            std::cout << nodo->dato.horas_de_vuelo << " - " << nodo->dato.nombre << std::endl;
        }
    }

public:
    ArbolBB() : raiz(nullptr) {}

    void insertar(T dato) {
        insertarRec(raiz, dato);
    }

    void preorden() const {
        preordenRec(raiz);
    }

    void inorden() const {
        inordenRec(raiz);
    }

    void postorden() const {
        postordenRec(raiz);
    }
};

#endif // ARBOLBB_H
