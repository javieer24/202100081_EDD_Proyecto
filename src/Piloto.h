#ifndef PILOTO_H
#define PILOTO_H

#include <string>
#include <iostream>

class Piloto {
public:
    std::string nombre;
    std::string nacionalidad;
    std::string numero_de_id;
    std::string vuelo;
    int horas_de_vuelo;
    std::string tipo_de_licencia;

    Piloto() : nombre(""), nacionalidad(""), numero_de_id(""), vuelo(""), horas_de_vuelo(0), tipo_de_licencia("") {}

    Piloto(const std::string& nombre, const std::string& nacionalidad, const std::string& numero_de_id,
           const std::string& vuelo, int horas_de_vuelo, const std::string& tipo_de_licencia)
           : nombre(nombre), nacionalidad(nacionalidad), numero_de_id(numero_de_id),
             vuelo(vuelo), horas_de_vuelo(horas_de_vuelo), tipo_de_licencia(tipo_de_licencia) {}

    // Sobrecarga del operador de salida para imprimir un Piloto
    friend std::ostream& operator<<(std::ostream& os, const Piloto& piloto) {
        os << "Nombre: " << piloto.nombre << ", Nacionalidad: " << piloto.nacionalidad
           << ", ID: " << piloto.numero_de_id << ", Vuelo: " << piloto.vuelo
           << ", Horas de vuelo: " << piloto.horas_de_vuelo << ", Licencia: " << piloto.tipo_de_licencia;
        return os;
    }

    // Sobrecarga del operador de comparación para ordenar por nombre
    bool operator<(const Piloto& other) const {
        return nombre < other.nombre;
    }

    bool operator>(const Piloto& other) const {
        return nombre > other.nombre;
    }

    bool operator==(const Piloto& other) const {
        return nombre == other.nombre;
    }
};

#endif // PILOTO_H
