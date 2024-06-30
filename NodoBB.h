//Clase Nodo para Árbol Binario de Búsqueda de Pilotos
#ifndef NODOBB_H
#define NODOBB_H

template <typename T>
class NodoBB {
public:
    T dato;
    NodoBB* izquierdo;
    NodoBB* derecho;

    NodoBB(T dato) : dato(dato), izquierdo(nullptr), derecho(nullptr) {}
};

#endif // NODOBB_H
