#ifndef LISTA_ENLAZADA_DOBLE_H
#define LISTA_ENLAZADA_DOBLE_H

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Vuelo.h"

using json = nlohmann::json;

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

                insertarAlFinal(vuelo);
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

#endif // LISTA_ENLAZADA_DOBLE_H
