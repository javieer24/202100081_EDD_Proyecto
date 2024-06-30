#include "json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <sstream>

using json = nlohmann::json;

class MatrizDispersa {
private:
    std::unordered_map<std::string, std::unordered_map<std::string, int>> matriz;
    std::unordered_map<std::string, std::string> vueloDestino;
    std::unordered_map<std::string, std::pair<std::string, std::string>> pilotoVuelo;

public:
    MatrizDispersa(const std::string& archivoAviones, const std::string& archivoRutas, const std::string& archivoPilotos) {
        cargarAviones(archivoAviones);
        cargarRutas(archivoRutas);
        cargarPilotos(archivoPilotos);
    }

    void cargarAviones(const std::string& archivo) {
        std::ifstream entrada(archivo);
        if (!entrada.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo JSON de aviones");
        }
        json j;
        entrada >> j;
        if (j.is_null()) {
            throw std::runtime_error("El archivo JSON de aviones está vacío o no es válido");
        }

        for (const auto& item : j) {
            std::string vuelo = item.at("vuelo").get<std::string>();
            std::string ciudad_destino = item.at("ciudad_destino").get<std::string>();
            vueloDestino[vuelo] = ciudad_destino;
        }
    }

    void cargarRutas(const std::string& archivo) {
        std::ifstream entrada(archivo);
        if (!entrada.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo de rutas");
        }

        std::string linea;
        while (std::getline(entrada, linea)) {
            std::stringstream ss(linea);
            std::string origen, destino, distancia;
            std::getline(ss, origen, '/');
            std::getline(ss, destino, '/');
            std::getline(ss, distancia, ';');

            matriz[origen][destino] = std::stoi(distancia);
        }
    }

    void cargarPilotos(const std::string& archivo) {
        std::ifstream entrada(archivo);
        if (!entrada.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo JSON de pilotos");
        }
        json j;
        entrada >> j;
        if (j.is_null()) {
            throw std::runtime_error("El archivo JSON de pilotos está vacío o no es válido");
        }

        for (const auto& item : j) {
            std::string nombre = item.at("nombre").get<std::string>();
            std::string vuelo = item.at("vuelo").get<std::string>();
            std::string numero_de_id = item.at("numero_de_id").get<std::string>();
            pilotoVuelo[numero_de_id] = {nombre, vuelo};
        }
    }

    std::tuple<std::string, std::string, std::string, std::string, std::string> consultarPiloto(const std::string& numero_de_id) {
        if (pilotoVuelo.find(numero_de_id) == pilotoVuelo.end()) {
            throw std::runtime_error("Piloto no encontrado");
        }

        std::string nombre = pilotoVuelo[numero_de_id].first;
        std::string vuelo = pilotoVuelo[numero_de_id].second;
        std::string ciudad_destino = vueloDestino[vuelo];

        return {nombre, vuelo, "", "", ciudad_destino};
    }
};
