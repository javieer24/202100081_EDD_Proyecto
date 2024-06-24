#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "Vuelo.h"
#include "ArbolB.h"
#include "ArbolBB.h"
#include "Piloto.h"
#include <locale>
//#define NOMINMAX 
#include <windows.h>
#include "ListaEnlazadaDoble.h"
#include "TablaHash.h" // Incluir la clase TablaHash
#include "GrafoListaDeAdyacencia.h"//Incluir Grafo utilizando lista de adyacencia

using json = nlohmann::json;

std::vector<Vuelo> cargarVuelosDesdeJson(const std::string& archivo) {
    std::ifstream entrada(archivo);
    
    if (!entrada.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo JSON");
    }

    json j;
    entrada >> j;

    if (j.is_null()) {
        throw std::runtime_error("El archivo JSON está vacío o no es válido");
    }

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

std::vector<Piloto> cargarPilotosDesdeJson(const std::string& archivo) {
    std::ifstream entrada(archivo);

    if (!entrada.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo JSON");
    }

    json j;
    entrada >> j;

    if (j.is_null()) {
        throw std::runtime_error("El archivo JSON está vacío o no es válido");
    }

    std::vector<Piloto> pilotos;
    for (const auto& item : j) {
        Piloto p;
        p.nombre = item.at("nombre").get<std::string>();
        p.nacionalidad = item.at("nacionalidad").get<std::string>();
        p.numero_de_id = item.at("numero_de_id").get<std::string>();
        p.vuelo = item.at("vuelo").get<std::string>();
        p.horas_de_vuelo = item.at("horas_de_vuelo").get<int>();
        p.tipo_de_licencia = item.at("tipo_de_licencia").get<std::string>();
        pilotos.push_back(p);
    }
    return pilotos;
}

void mostrarArbolPreorden(ArbolBB<Piloto>& arbolPilotos) {
    std::cout << "Árbol de Pilotos - Recorrido Preorden:" << std::endl;
    arbolPilotos.preorden();
    std::cout << std::endl;
}

void mostrarArbolInorder(ArbolBB<Piloto>& arbolPilotos) {
    std::cout << "Árbol de Pilotos - Recorrido Inorder:" << std::endl;
    arbolPilotos.inorden();
    std::cout << std::endl;
}

void mostrarArbolPostorden(ArbolBB<Piloto>& arbolPilotos) {
    std::cout << "Árbol de Pilotos - Recorrido Postorden:" << std::endl;
    arbolPilotos.postorden();
    std::cout << std::endl;
}

void mostrarMenu(ArbolB& arbolAviones, ArbolBB<Piloto>& arbolPilotos, TablaHash<Piloto>& tablaPilotos) {
    std::string opcion;
    GrafoListaDeAdyacencia grafo(7); // Inicialmente asumiendo 7 vértices

    do {
        a:
        system("cls"); // limpiamos pantalla
        std::cout << "\nMenú de opciones:" << std::endl;
        std::cout << "1. Carga de aviones" << std::endl;
        std::cout << "2. Carga de pilotos" << std::endl;
        std::cout << "3. Carga de rutas" << std::endl;
        std::cout << "4. Carga de movimientos" << std::endl;
        std::cout << "5. Consulta de horas de vuelo (pilotos)" << std::endl;
        std::cout << "6. Recomendar ruta" << std::endl;
        std::cout << "7. Visualizar reportes" << std::endl;
        std::cout << "8. Salir" << std::endl;

        std::cout << "Ingrese el número de opción deseada: ";
        std::cin >> opcion;

        // Validación del menú
        if (opcion != "1" && opcion != "2" && opcion != "3" && opcion != "4" &&
            opcion != "5" && opcion != "6" && opcion != "7" && opcion != "8") {
            std::cout << "Opción inválida. Ingrese un número del 1 al 8. \n";
            system("pause"); // pregunta para presionar una tecla
            goto a;
        }

        switch (stoi(opcion)) {
            case 1:
                try {
                    std::string rutaAviones = "../../aviones.json";
                    std::vector<Vuelo> vuelos = cargarVuelosDesdeJson(rutaAviones);
                    for (const auto& vuelo : vuelos) {
                        arbolAviones.insertar(vuelo);
                    }
                    std::cout << "Aviones cargados exitosamente." << std::endl;
                    printf("\n");
                    system("pause");
                } catch (const std::exception& e) {
                    std::cerr << "Error al cargar aviones: " << e.what() << std::endl;
                    printf("\n");
                    system("pause");
                }
                break;

            case 2:
                try {
                    std::string rutaPilotos = "../../pilotos.json";
                    std::vector<Piloto> pilotos = cargarPilotosDesdeJson(rutaPilotos);
                    for (const auto& piloto : pilotos) {
                        arbolPilotos.insertar(piloto);
                        tablaPilotos.insertar(piloto);
                    }
                    std::cout << "Pilotos cargados exitosamente." << std::endl;
                    printf("\n");
                    system("pause");
                } catch (const std::exception& e) {
                    std::cerr << "Error al cargar pilotos: " << e.what() << std::endl;
                    printf("\n");
                    system("pause");
                }
                break;

            case 3:
                try {
                    grafo.cargarRutasDesdeArchivo("../../rutas.txt");
                    //grafo.imprimirGrafo();
                    std::cout << "Rutas cargadas en el grafo con listas adyacentes exitosamente" << std::endl;
                    printf("\n");
                    system("pause");
                } catch (const std::exception& e) {
                    std::cerr << "Error al cargar rutas: " << e.what() << std::endl;
                    printf("\n");
                    system("pause");
                }
                break;

            case 4:
                std::cout << "Carga de movimientos no implementada." << std::endl;
                system("pause");
                break;

            case 5:
                // Consulta de horas de vuelo (pilotos)
                std::cout << "Consulta de horas de vuelo de pilotos:" << std::endl;
                std::cout << "Selecciona el orden de recorrido del árbol:" << std::endl;
                std::cout << "1. Preorden" << std::endl;
                std::cout << "2. Inorder" << std::endl;
                std::cout << "3. Postorden" << std::endl;
                std::cout << "4. Ver Tabla Hash" << std::endl;
                std::cout << "Ingrese el número de opción deseada: ";
                std::cin >> opcion;
                switch (stoi(opcion)) {
                    case 1:
                        mostrarArbolPreorden(arbolPilotos);
                        break;
                    case 2:
                        mostrarArbolInorder(arbolPilotos);
                        break;
                    case 3:
                        mostrarArbolPostorden(arbolPilotos);
                        break;
                    case 4:
                        std::cout << "Contenido de la tabla hash de pilotos:" << std::endl << std::endl;
                        tablaPilotos.mostrar();
                        break;
                    default:
                        std::cout << "Opción inválida. Volviendo al menú principal." << std::endl;
                        break;
                }
                system("pause");
                break;

            case 6:
                std::cout << "Recomendar ruta no implementado." << std::endl;
                system("pause");
                break;

            case 7:
                std::cout << "Visualizar reportes no implementado." << std::endl;
                system("pause");
                break;

            case 8:
                std::cout << "Saliendo del programa." << std::endl;
                break;

            default:
                std::cout << "Opción inválida. Volviendo al menú principal." << std::endl;
                system("pause");
                break;
        }

    } while (opcion != "8");
}

int main() {
    // Configurar el locale para UTF-8
    std::setlocale(LC_ALL, ".utf8");
    SetConsoleCP(CP_UTF8); // Input codepage (affects cin, scanf, etc.)
    SetConsoleOutputCP(CP_UTF8); // Output codepage (affects cout, printf, etc.)

    // Crear instancias de los árboles
    ArbolB arbolAviones;
    ArbolBB<Piloto> arbolPilotos;
    TablaHash<Piloto> tablaPilotos;
    
    //Mostrar el menú principal
    mostrarMenu(arbolAviones, arbolPilotos, tablaPilotos);
    
    return 0;
}
