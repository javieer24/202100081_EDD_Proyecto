#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "Piloto.h" // Asegúrate de incluir correctamente el archivo de definición de Piloto

template<typename T>
class TablaHash {
private:
    static const int tamano = 18; // Tamaño inicial de la tabla hash
    std::vector<std::list<T>> tabla; // Vector de listas para la tabla hash

    // Función hash básica para obtener el índice en la tabla
    int hash(const std::string& key) {
        int hash = 0;
        for (char c : key) {
            hash += c;
        }
        return hash % tamano;
    }

public:
    TablaHash() {
        tabla.resize(tamano); // Inicializar el tamaño de la tabla
    }

    // Método para insertar un elemento en la tabla hash
    void insertar(const T& elemento) {
        int indice = hash(elemento.numero_de_id); // Obtener el índice usando la función hash

        // Verificar si el elemento ya existe en la tabla
        for (auto& it : tabla[indice]) {
            if (it.numero_de_id == elemento.numero_de_id) {
                std::cerr << "El elemento ya existe en la tabla." << std::endl;
                return;
            }
        }

        // Insertar el elemento en la lista correspondiente al índice calculado
        tabla[indice].push_back(elemento);
    }

    // Método para buscar un elemento en la tabla hash
    T* buscar(const std::string& key) {
        int indice = hash(key); // Obtener el índice usando la función hash

        // Buscar el elemento en la lista correspondiente al índice calculado
        for (auto& it : tabla[indice]) {
            if (it.numero_de_id == key) {
                return &it; // Devolver un puntero al elemento encontrado
            }
        }

        return nullptr; // Retornar nullptr si el elemento no se encuentra
    }

    // Método para eliminar un elemento de la tabla hash
    void eliminar(const std::string& key) {
        int indice = hash(key); // Obtener el índice usando la función hash

        // Buscar y eliminar el elemento de la lista correspondiente al índice calculado
        auto& lista = tabla[indice];
        auto it = std::find_if(lista.begin(), lista.end(),
            [&key](const T& elemento) { return elemento.numero_de_id == key; });

        if (it != lista.end()) {
            lista.erase(it);
            std::cout << "Elemento eliminado correctamente." << std::endl;
        } else {
            std::cerr << "Elemento no encontrado en la tabla." << std::endl;
        }
    }

    // Método para mostrar la tabla hash (para depuración)
    void mostrar() {
        for (size_t i = 0; i < tabla.size(); ++i) {
            std::cout << "[" << i << "]: ";
            for (const auto& it : tabla[i]) {
                std::cout << it.numero_de_id << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // TABLAHASH_H
