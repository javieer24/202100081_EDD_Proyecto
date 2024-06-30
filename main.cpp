#include "json.hpp"
#include "ListaEnlazadaDobleCircular.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "Vuelo.h"
#include "ArbolB.h"
#include "ArbolBB.h"
#include "Piloto.h"
#include <locale>
#include <windows.h>
#include "TablaHash.h"
#include "GrafoListaDeAdyacencia.h"
#include "Dijkstra.h"
#include "MatrizDispersa.h"
#include <filesystem>

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

void mostrarMenu(ArbolB& arbolAviones, ArbolBB<Piloto>& arbolPilotos, TablaHash<Piloto>& tablaPilotos, MatrizDispersa& matrizDispersa,ListaDobleCircular& listaEnlazadaCircular) {
    std::string opcion;
    GrafoListaDeAdyacencia grafo(7);

    do {
        system("cls");
        std::cout << "|     Proyecto Estructuras de Datos - 202100081           |" << std::endl;
        std::cout << "|---------------------------------------------------------|" << std::endl;
        std::cout << "|             Menú de opciones:                           |" << std::endl;
        std::cout << "|---------------------------------------------------------|" << std::endl;
        std::cout << "|         1. Carga de aviones                             |" << std::endl;
        std::cout << "|         2. Carga de pilotos                             |" << std::endl;
        std::cout << "|         3. Carga de rutas                               |" << std::endl;
        std::cout << "|         4. Carga de movimientos                         |" << std::endl;
        std::cout << "|         5. Consulta de horas de vuelo (pilotos)         |" << std::endl;
        std::cout << "|         6. Recomendar ruta                              |" << std::endl;
        std::cout << "|         7. Visualizar reportes                          |" << std::endl;
        std::cout << "|         8. Consultar piloto por ID                      |" << std::endl; 
        std::cout << "|         9. Pasar Avión de Arbol de Búsqueda a Lista Enlzada Doble" << std::endl;
        std::cout << "|         10. Salir                                       |" << std::endl;
        std::cout << "|---------------------------------------------------------|" << std::endl;

        std::cout << "Ingrese el número de opción deseada: ";
        std::cin >> opcion;

        if (opcion == "1") {
            try {
                std::string rutaAviones = "C:/Users/javie/Escritorio/202100081_EDD_Proyecto/aviones.json";
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
        } else if (opcion == "2") {
            try {
                std::string rutaPilotos = "C:/Users/javie/Escritorio/202100081_EDD_Proyecto/pilotos.json";
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
        } else if (opcion == "3") {
            try {
                grafo.cargarRutasDesdeArchivo("C:/Users/javie/Escritorio/202100081_EDD_Proyecto/rutas.txt");
                std::cout << "Rutas cargadas en el grafo con listas adyacentes exitosamente" << std::endl;
                printf("\n");
                system("pause");
            } catch (const std::exception& e) {
                std::cerr << "Error al cargar rutas: " << e.what() << std::endl;
                printf("\n");
                system("pause");
            }
        } else if (opcion == "4") {
            std::cout << "Carga de movimientos no implementada." << std::endl;
            system("pause");
        } else if (opcion == "5") {
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
        } else if (opcion == "6") {
            try {
                std::string ciudadOrigen, ciudadDestino;
                std::cout << "Ingrese la ciudad de origen: ";
                std::cin >> ciudadOrigen;
                std::cout << "Ingrese la ciudad de destino: ";
                std::cin >> ciudadDestino;

                int origen = grafo.ciudadAIndice(ciudadOrigen);
                int destino = grafo.ciudadAIndice(ciudadDestino);

                if (origen == -1 || destino == -1) {
                    std::cerr << "Ciudad origen o destino no válidas." << std::endl;
                } else {
                    std::vector<int> ruta = Dijkstra::encontrarRutaMasCorta(grafo, origen, destino);
                    if (ruta.empty()) {
                        std::cout << "No hay ruta disponible entre " << ciudadOrigen << " y " << ciudadDestino << "." << std::endl;
                    } else {
                        std::cout << "Ruta más corta entre " << ciudadOrigen << " y " << ciudadDestino << ":" << std::endl;
                        for (int i = 0; i < ruta.size(); ++i) {
                            std::cout << grafo.indiceACiudadNombre(ruta[i]);
                            if (i < ruta.size() - 1) {
                                std::cout << " -> ";
                            }
                        }
                        std::cout << std::endl;
                    }
                }
                printf("\n");
                system("pause");
            } catch (const std::exception& e) {
                std::cerr << "Error al recomendar ruta: " << e.what() << std::endl;
                printf("\n");
                system("pause");
            }
        } else if (opcion == "8") {
            std::cout << "Consulta de piloto:" << std::endl;
            std::string numero_de_id;
            std::cout << "Ingrese el número de identificación del piloto: ";
            std::cin >> numero_de_id;
            try {
                auto consulta = matrizDispersa.consultarPiloto(numero_de_id);
                std::string nombre = std::get<0>(consulta);
                std::string vuelo = std::get<1>(consulta);
                std::string ciudad_destino = std::get<4>(consulta);
                std::cout << "Nombre del piloto: " << nombre << std::endl;
                std::cout << "Vuelo asignado: " << vuelo << std::endl;
                std::cout << "Ciudad de destino: " << ciudad_destino << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error al consultar piloto: " << e.what() << std::endl;
            }
            system("pause");
        } else if (opcion == "10") {
            std::cout << "Saliendo del programa." << std::endl;
        } else if (opcion == "9") {//Eliminar del Arból de Búsqueda Orden y pasar a Lista Enlazada Doble
            std::cout << "Eliminar avión por número de registro:" << std::endl;
            std::string numero_de_registro;
            std::cout << "Ingrese el número de registro del avión: ";
            std::cin >> numero_de_registro;
            try {//Se intenta eliminar
                arbolAviones.eliminar(numero_de_registro);
                std::cout << "Avión con número de registro " << numero_de_registro << " eliminado exitosamente." << std::endl;
                arbolAviones.imprimir();//imprimir todo

            //En esta sección se ingresa a la lista enlazada doble
                std::string rutaAviones = "../../aviones.json";
                std::vector<Vuelo> vuelos = cargarVuelosDesdeJson(rutaAviones);
                bool encontrado = false;

                for (const auto& vuelo : vuelos) {
                    if (vuelo.numero_de_registro == numero_de_registro) {
                        listaEnlazadaCircular.insertarAlFinal(vuelo);
                        std::cout << "Avión con número de registro " << numero_de_registro << " cargado exitosamente en la lista enlazada doble." << std::endl;
                        encontrado = true;
                        break;
                    }
                }
            //Fin de la sección de lista enlazada doble
                
            } catch (const std::exception& e) {
                std::cerr << "Error al eliminar avión: " << e.what() << std::endl;
            }
            system("pause");
        } else if (opcion == "/") {
            std::cout << "Cargar avión en lista enlazada doble:" << std::endl;
            std::string numero_de_registro;
            std::cout << "Ingrese el número de registro del avión: ";
            std::cin >> numero_de_registro;
            try {
                std::string rutaAviones = "../../aviones.json";
                std::vector<Vuelo> vuelos = cargarVuelosDesdeJson(rutaAviones);
                bool encontrado = false;
                for (const auto& vuelo : vuelos) {
                    if (vuelo.numero_de_registro == numero_de_registro) {
                        listaEnlazadaCircular.insertarAlFinal(vuelo);
                        std::cout << "Avión con número de registro " << numero_de_registro << " cargado exitosamente en la lista enlazada doble." << std::endl;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "Avión con número de registro " << numero_de_registro << " no encontrado en el archivo JSON." << std::endl;
                }
                listaEnlazadaCircular.imprimir();
                system("pause");
            } catch (const std::exception& e) {
                std::cerr << "Error al cargar avión en la lista enlazada doble: " << e.what() << std::endl;
                system("pause");
            }
        } else {
            std::cout << "Opción inválida. Por favor, ingrese un número del 1 al 10." << std::endl;
            system("pause");
        }

    } while (opcion != "10");
}

int main() {
    std::setlocale(LC_ALL, ".utf8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    ArbolB arbolAviones;
    ArbolBB<Piloto> arbolPilotos;
    TablaHash<Piloto> tablaPilotos;
    MatrizDispersa matrizDispersa("C:/Users/javie/Escritorio/202100081_EDD_Proyecto/aviones.json", "C:/Users/javie/Escritorio/202100081_EDD_Proyecto/rutas.txt", "C:/Users/javie/Escritorio/202100081_EDD_Proyecto/pilotos.json");
    ListaDobleCircular listaEnlazadaCircular;

    mostrarMenu(arbolAviones, arbolPilotos, tablaPilotos, matrizDispersa, listaEnlazadaCircular);

    return 0;
}