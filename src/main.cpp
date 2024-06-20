#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "Vuelo.h"
#include "ArbolB.h"

using json = nlohmann::json;

std::vector<Vuelo> cargarVuelosDesdeJson(const std::string& archivo) {
    std::ifstream entrada(archivo);
    json j;
    entrada >> j;
    std::vector<Vuelo> vuelos;
    for (const auto& item : j) {
        Vuelo v;
        v.vuelo = item.at("vuelo").get<std::string>();
        v.numero_de_registro = item.at("numero_de_registro").get<std::string>();
        v.modelo = item.at("modelo").get<std::string>();
        v.capacidad = item.at("capacidad").get<int>();
        v.aerolinea = item.at("aerolinea").get<std::string>();
        v.ciudad_destino = item.at("ciudad_destino").get<std::string>();
        v.estado = item.at("estado").get<std::string>();
        vuelos.push_back(v);
    }
    return vuelos;
}

int main() {
    std::vector<Vuelo> vuelos = cargarVuelosDesdeJson("aviones.json");

    ArbolB arbol;

    for (const auto& vuelo : vuelos) {
        arbol.insertar(vuelo);
    }

    arbol.imprimir();

    std::string buscar_vuelo = "A104";
    Nodo* resultado = arbol.buscar(buscar_vuelo);
    if (resultado != nullptr) {
        for (const auto& vuelo : resultado->clave) {
            if (vuelo.vuelo == buscar_vuelo) {
                std::cout << "Vuelo encontrado: " << vuelo << std::endl;
            }
        }
    } else {
        std::cout << "Vuelo no encontrado." << std::endl;
    }

    return 0;
}
