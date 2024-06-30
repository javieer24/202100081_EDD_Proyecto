#ifndef LISTA_ENLAZADA_DOBLE_CIRCULAR_H
#define LISTA_ENLAZADA_DOBLE_CIRCULAR_H

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Vuelo.h"

using json = nlohmann::json;

// Nodo de la lista enlazada doble
struct NodoDoble {
    Vuelo vuelo;
    std::string numero_de_registro;
    NodoDoble* siguiente;
    NodoDoble* anterior;

        NodoDoble(const Vuelo& v, const std::string& num_reg) : vuelo(v), numero_de_registro(num_reg), siguiente(nullptr), anterior(nullptr) {}
};

// Lista doble circular
class ListaDobleCircular {
public:
    ListaDobleCircular() : cabeza(nullptr), cola(nullptr) {}

    ~ListaDobleCircular() {
        limpiar();
    }

    // Función para insertar un vuelo al final de la lista
    void insertarAlFinal(const Vuelo& vuelo, const std::string& numero_de_registro) {
        NodoDoble* nuevoNodo = new NodoDoble(vuelo, numero_de_registro);
        if (cola == nullptr) {
            cabeza = cola = nuevoNodo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            nuevoNodo->anterior = cola;
            nuevoNodo->siguiente = cabeza;
            cola->siguiente = nuevoNodo;
            cabeza->anterior = nuevoNodo;
            cola = nuevoNodo;
        }
    }

    // Función para imprimir la lista
    void imprimir() const {
        if (cabeza == nullptr) return;

        NodoDoble* actual = cabeza;
        do {
            std::cout << actual->vuelo << std::endl;
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    // Función para limpiar la lista
    void limpiar() {
        if (cabeza == nullptr) return;

        NodoDoble* actual = cabeza;
        do {
            NodoDoble* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);

        cabeza = cola = nullptr;
    }

    // Función para buscar un vuelo por número de registro
    NodoDoble* buscarPorNumeroDeRegistro(const std::string& numero_de_registro) const {
        if (cabeza == nullptr) return nullptr;

        NodoDoble* actual = cabeza;
        do {
            if (actual->numero_de_registro == numero_de_registro) {
                return actual;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        return nullptr;
    }

    // Función para eliminar un vuelo por número de registro
    bool eliminarPorNumeroDeRegistro(const std::string& numero_de_registro) {
        if (cabeza == nullptr) return false;

        NodoDoble* nodoAEliminar = nullptr;
        NodoDoble* actual = cabeza;
        do {
            if (actual->numero_de_registro == numero_de_registro) {
                nodoAEliminar = actual;
                break;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        if (nodoAEliminar == nullptr) {
            std::cerr << "El vuelo con número de registro " << numero_de_registro << " no existe en la lista." << std::endl;
            return false;
        }

        if (nodoAEliminar == cabeza) {
            cabeza = cabeza->siguiente;
        }
        if (nodoAEliminar == cola) {
            cola = cola->anterior;
        }

        nodoAEliminar->anterior->siguiente = nodoAEliminar->siguiente;
        nodoAEliminar->siguiente->anterior = nodoAEliminar->anterior;

        delete nodoAEliminar;
        return true;
    }


    // Función para cargar un vuelo desde el archivo JSON si el numero_de_registro existe
    bool cargarVueloDesdeJson(const std::string& numero_de_registro, const std::string& archivoJson) {
        std::ifstream entrada(archivoJson);

        if (!entrada.is_open()) {
            std::cerr << "No se pudo abrir el archivo JSON" << std::endl;
            return false;
        }

        json j;
        entrada >> j;

        if (j.is_null()) {
            std::cerr << "El archivo JSON está vacío o no es válido" << std::endl;
            return false;
        }

        for (const auto& item : j) {
            if (item.at("numero_de_registro").get<std::string>() == numero_de_registro) {
                Vuelo vuelo;
                vuelo.vuelo = item.at("vuelo").get<std::string>();
                vuelo.numero_de_registro = item.at("numero_de_registro").get<std::string>();
                vuelo.modelo = item.at("modelo").get<std::string>();
                vuelo.capacidad = item.at("capacidad").get<int>();
                vuelo.aerolinea = item.at("aerolinea").get<std::string>();
                vuelo.ciudad_destino = item.at("ciudad_destino").get<std::string>();
                vuelo.estado = item.at("estado").get<std::string>();

                insertarAlFinal(vuelo, numero_de_registro);
                return true;
            }
        }

        std::cerr << "No se encontró el vuelo con el numero_de_registro proporcionado" << std::endl;
        return false;
    }

private:
    NodoDoble* cabeza;
    NodoDoble* cola;
};

#endif // LISTA_ENLAZADA_DOBLE_CIRCULAR_H
