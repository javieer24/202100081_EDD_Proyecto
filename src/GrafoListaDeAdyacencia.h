#ifndef GRAFOLISTASDEADYACENCIA_H
#define GRAFOLISTASDEADYACENCIA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <unordered_map>
#include <algorithm>

class GrafoListaDeAdyacencia {
private:
    int V; // Número de vértices del grafo
    std::vector<std::list<std::pair<int, int>>> adj; // Vector de listas de pares para almacenar las listas de adyacencia
    std::unordered_map<std::string, int> ciudadAMapa; // Mapa para convertir nombres de ciudades a índices
    int contadorCiudades; // Contador para asignar índices únicos a las ciudades

    // Función privada para dividir una cadena por un delimitador
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    // Constructor que inicializa el grafo con un número inicial de vértices
    GrafoListaDeAdyacencia(int V) : V(V), adj(V), contadorCiudades(0) {}

    // Método para cargar las rutas desde un archivo de texto
    void cargarRutasDesdeArchivo(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> tokens = split(line, '/');
            if (tokens.size() < 3) {
                std::cerr << "Formato incorrecto en la línea: " << line << std::endl;
                continue;
            }

            std::string ciudad_origen = tokens[0];
            std::string ciudad_destino = tokens[1];
            int peso;
            try {
                peso = std::stoi(tokens[2]);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Peso inválido en la línea: " << line << std::endl;
                continue;
            }

            if (ciudadAMapa.find(ciudad_origen) == ciudadAMapa.end()) {
                ciudadAMapa[ciudad_origen] = contadorCiudades++;
            }
            if (ciudadAMapa.find(ciudad_destino) == ciudadAMapa.end()) {
                ciudadAMapa[ciudad_destino] = contadorCiudades++;
            }

            int u = ciudadAMapa[ciudad_origen];
            int v = ciudadAMapa[ciudad_destino];

            if (u >= adj.size() || v >= adj.size()) {
                adj.resize(std::max(u, v) + 1);
            }

            // Agregar arista bidireccional (grafo no dirigido)
            agregarArista(u, v, peso);
            agregarArista(v, u, peso);
        }
        file.close();
    }

    // Método para agregar una arista entre dos vértices con un peso dado
    void agregarArista(int u, int v, int peso) {
        adj[u].push_back(std::make_pair(v, peso));
    }

    // Método para imprimir el grafo en formato de lista de adyacencia
    void imprimirGrafo() {
        for (size_t i = 0; i < adj.size(); ++i) {
            std::cout << i << " -> ";
            for (const auto& pair : adj[i]) {
                std::cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // GRAFOLISTASDEADYACENCIA_H
