#ifndef VUELO_H
#define VUELO_H

#include <iostream>
#include <string>

struct Vuelo {
    std::string vuelo;
    std::string numero_de_registro;
    std::string modelo;
    int capacidad;
    std::string aerolinea;
    std::string ciudad_destino;
    std::string estado;

    bool operator<(const Vuelo& otro) const {
        return vuelo < otro.vuelo;
    }
    bool operator==(const Vuelo& otro) const {
        return vuelo == otro.vuelo;
    }
};

std::ostream& operator<<(std::ostream& os, const Vuelo& v) {
    os << "Vuelo: " << v.vuelo << ", Registro: " << v.numero_de_registro
       << ", Modelo: " << v.modelo << ", Capacidad: " << v.capacidad
       << ", Aerolinea: " << v.aerolinea << ", Destino: " << v.ciudad_destino
       << ", Estado: " << v.estado;
    return os;
}

#endif // VUELO_H
