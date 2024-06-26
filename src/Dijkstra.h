#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <queue>
#include <iostream>
#include "GrafoListaDeAdyacencia.h"

struct Estado {
    int nodo;
    int costo;
    Estado(int _nodo, int _costo) : nodo(_nodo), costo(_costo) {}
    bool operator<(const Estado& otro) const {
        return costo > otro.costo; // Prioridad mínima
    }
};

class Dijkstra {
public:
    static std::vector<int> encontrarRutaMasCorta(const GrafoListaDeAdyacencia& grafo, int inicio, int fin) {
        int V = grafo.obtenerNumeroDeVertices();
        std::vector<int> distancia(V, INT_MAX);
        std::vector<int> previo(V, -1);
        std::priority_queue<Estado> pq;

        distancia[inicio] = 0;
        pq.push(Estado(inicio, 0));

        while (!pq.empty()) {
            Estado actual = pq.top();
            pq.pop();

            int u = actual.nodo;

            if (u == fin) break;

            for (const auto& vecino : grafo.obtenerListaDeAdyacencia()[u]) {
                int v = vecino.first;
                int peso = vecino.second;

                if (distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    previo[v] = u;
                    pq.push(Estado(v, distancia[v]));
                }
            }
        }

        std::vector<int> ruta;
        for (int at = fin; at != -1; at = previo[at]) {
            ruta.push_back(at);
        }
        std::reverse(ruta.begin(), ruta.end());

        if (ruta.size() == 1 && ruta[0] != inicio) {
            ruta.clear(); // No hay ruta
        }

        return ruta;
    }
};

#endif // DIJKSTRA_H
