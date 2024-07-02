#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <algorithm>
using namespace std;

#include "ArbolB.h"
#include "ListaCircularDoble.h"
#include "ArbolBinarioBusqueda.h"
#include "TablaHash.h"
#include "Grafo.h"
#include "Matriz.h"
#include "ListaSimple.h"
#include "Aviones.h"
#include "Pilotos.h"

int opcion;

string linea;
string filename;

//Variables globales
ListaCircularDoble listaMantenimiento;
ArbolB arbolBDisponible;
ArbolBB arbolBinarioPilotos;
TablaHash tablaPilotos;
Grafo grafoRutas(50);
Matriz matrizPilotoVuelo;

//Funcion para cargar los aviones
void cargarAviones(const string &filename, ArbolB &arbolBDisponible, ListaCircularDoble &listaMantenimiento)
{
  ifstream archivo(filename);
  if (archivo.is_open())
  {
    string linea;
//Variables para los aviones
    string vuelo;
    string numeroRegistro;
    string modelo;
    int capacidad;
    string aerolinea;
    string ciudadDestino;
    string estado;
//Leyendo el archivo de aviones
    while (getline(archivo, linea))
    {
      size_t pos = linea.find(":");
      if (pos != string::npos)
      {
        string key = linea.substr(0, pos);
        string value = linea.substr(pos + 1);
//Eliminando espacios, comillas y tabulaciones
        key.erase(remove(key.begin(), key.end(), ' '), key.end());
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        key.erase(remove(key.begin(), key.end(), '\t'), key.end());
        value.erase(0, 1);
        value.erase(remove(value.begin(), value.end(), '\"'), value.end());
        value.erase(remove(value.begin(), value.end(), ','), value.end());

        if (key == "vuelo")
        {
          vuelo = value;
        }
        else if (key == "numero_de_registro")
        {
          numeroRegistro = value;
        }
        else if (key == "modelo")
        {
          modelo = value;
        }
        else if (key == "capacidad")
        {
          capacidad = stoi(value);
        }
        else if (key == "aerolinea")
        {
          aerolinea = value;
        }
        else if (key == "ciudad_destino")
        {
          ciudadDestino = value;
        }
        else if (key == "estado")
        {
          estado = value;
        }
      }
      else if (linea.find("}") != string::npos)
      {
        if (estado == "Disponible")
        {
          Avion nuevoAvionDisp(vuelo, numeroRegistro, modelo, capacidad, aerolinea, ciudadDestino, estado);
          arbolBDisponible.insertar(nuevoAvionDisp);
        } //Si el avion esta en mantenimiento
        else if (estado == "Mantenimiento")
        {
          Avion *nuevoAvionMante = new Avion(vuelo, numeroRegistro, modelo, capacidad, aerolinea, ciudadDestino, estado);
          listaMantenimiento.insertarFinal(nuevoAvionMante);
        }
      }
    }
    cout << "Archivo de aviones cargado exitosamente." << endl;
    archivo.close();
  }
  else
  {
    cerr << "No se pudo abrir el archivo para leer." << endl;
  }
}

//Funcion para cargar los pilotos
void cargarPilotos(const string &filename, ArbolBB &arbolBinarioPilotos, TablaHash &tablaPilotos)
{
  ifstream archivo(filename);
  if (archivo.is_open())
  {
    string linea;
//Variables para los pilotos
    string nombre;
    string nacionalidad;
    string numeroId;
    string vuelo;
    int horasVuelo;
    string tipoLicencia;
//Leyendo el archivo de pilotos
    while (getline(archivo, linea))
    {
      size_t pos = linea.find(":");
      if (pos != string::npos)
      {
        string key = linea.substr(0, pos);
        string value = linea.substr(pos + 1);

        key.erase(remove(key.begin(), key.end(), ' '), key.end());
        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        key.erase(remove(key.begin(), key.end(), '\t'), key.end());
        value.erase(0, 1);
        value.erase(remove(value.begin(), value.end(), '\"'), value.end());
        value.erase(remove(value.begin(), value.end(), ','), value.end());
//Asignando valores a las variables
        if (key == "nombre")
        {
          nombre = value;
        }
        else if (key == "nacionalidad")
        {
          nacionalidad = value;
        }
        else if (key == "numero_de_id")
        {
          numeroId = value;
        }
        else if (key == "vuelo")
        {
          vuelo = value;
        }
        else if (key == "horas_de_vuelo")
        {
          horasVuelo = stoi(value);
        }
        else if (key == "tipo_de_licencia")
        {
          tipoLicencia = value;
        }
      }
      else if (linea.find("}") != string::npos)
      {
        Piloto *nuevoPiloto = new Piloto(nombre, nacionalidad, numeroId, vuelo, horasVuelo, tipoLicencia);
        arbolBinarioPilotos.insertar(nuevoPiloto);
        tablaPilotos.insertar(numeroId);
//Asignando pilotos a los vuelos
        string ciudadDestino = "";
        ciudadDestino = arbolBDisponible.buscarAvion(vuelo);
        if (ciudadDestino == "")
        {
          ciudadDestino = listaMantenimiento.buscarAvion2(vuelo);
        }
        if (ciudadDestino != "")
        {
          matrizPilotoVuelo.insertarPiloto(vuelo, numeroId, ciudadDestino);
        }
      }
    }
    cout << "Archivo de pilotos cargado exitosamente." << endl;
    archivo.close();
  }
  else
  {
    cerr << "No se pudo abrir el archivo para leer." << endl;
  }
}
//Funcion para cargar las rutas
void cargarRutas(const string &filename, Grafo &grafoRutas)
{
  ifstream file(filename);
  if (file.is_open())
  {
    string linea;
    while (getline(file, linea))
    {
      stringstream ss(linea);
      string origen, destino, dist;
//Leyendo el archivo de rutas
      getline(ss, origen, '/');
      getline(ss, destino, '/');
      getline(ss, dist, ';');
      int distancia = stoi(dist);

      grafoRutas.nuevoVertice(origen);
      grafoRutas.nuevoVertice(destino);
      grafoRutas.nuevoArco(origen, destino, distancia);
    }//Cerrando el archivo
    cout << "Rutas cargadas al sistema exitosamente." << endl;
    file.close();
  }
  else
  {//Error al abrir el archivo de rutas
    cerr << "Error al abrir el archivo de movimientos. " << endl;
  }
}

void cargarMovimientos(const string &filename, ArbolBB &arbolBinarioPilotos, TablaHash &tablaPilotos)
{
  ifstream file(filename);
  if (file.is_open())
  {
    string linea;
    while (getline(file, linea))
    {
      stringstream ss(linea);
      string comando;

      getline(ss, comando, ',');
//Leyendo el archivo de movimientos
      if (comando == "MantenimientoAviones")
      {
      }
      else if (comando.find("DarDeBaja") != string::npos)
      {
        string numeroId = comando.substr(10);
        numeroId.pop_back();
        numeroId.pop_back();
        if (!arbolBinarioPilotos.estaVacio())
        {
          string vuelo = "";
          string ciudadDestino = "";
          vuelo = arbolBinarioPilotos.buscar(numeroId);
          ciudadDestino = arbolBDisponible.buscarAvion(vuelo);
          if (ciudadDestino == "")
          {
            ciudadDestino = listaMantenimiento.buscarAvion2(vuelo);
          }
          matrizPilotoVuelo.eliminarPiloto(vuelo, ciudadDestino);
          arbolBinarioPilotos.eliminar(numeroId);
          tablaPilotos.eliminar(numeroId);
        }
      }
    }
    cout << "Movimientos cargados exitosamente al sistema." << endl;
    file.close();
  }
  else
  {
    cerr << "Error al abrir el archivo de movimientos. " << endl;
  }
}

void generarReportes(ArbolBB &arbolBinarioPilotos, TablaHash &tablaPilotos)
{
  if (arbolBinarioPilotos.estaVacio())
  {
    cout << "No se pueden generar reportes de los pilotos, no hay pilotos en la base de datos." << endl;
  }
  else
  {
    arbolBDisponible.generarReporte();
    listaMantenimiento.generarReporteMante();
    arbolBinarioPilotos.generarReporte();
  }
  tablaPilotos.generarReporte();
  grafoRutas.generarReporte();
  matrizPilotoVuelo.generarReporte();
}

void mostrarMenu()
{
  cout << endl;
  cout << "||----------------------- Proyecto-Esrtuctura de Datos-202100081 -----------------------||" << endl;
  cout << "||-----------------------------------------MENU-----------------------------------------||" << endl;
  cout << "||                          1. Carga de aviones                                         ||" << endl;
  cout << "||                          2. Carga de pilotos                                         ||" << endl;
  cout << "||                          3. Carga de rutas                                           ||" << endl;
  cout << "||                          4. Carga de movimientos                                     ||" << endl;
  cout << "||                          5. Consulta horas de vuelo                                  ||" << endl;
  cout << "||                          6. Recomendar ruta                                          ||" << endl;
  cout << "||                          7. Visualizar reportes                                      ||" << endl;
  cout << "||                          8. Salir                                                    ||" << endl;
  cout << "||--------------------------------------------------------------------------------------||" << endl;
  cout << "Elija la opcion que desee realizar: ";
}

void mostrarMenuRecorridos()
{
  int opcionRecorrido;

  cout << endl;
  cout << "---- Seleccione el recorrido ----" << endl;
  cout << "  1. Preorden" << endl;
  cout << "  2. Inorden" << endl;
  cout << "  3. Postorden" << endl;
  cout << endl;
  cout << "Elija la opcion que desee realizar: ";
  cin >> opcionRecorrido;

  switch (opcionRecorrido)
  {
  case 1:
  {
    arbolBinarioPilotos.RecorridoPre();
  }
  break;
  case 2:
  {
    arbolBinarioPilotos.RecorridoIn();
  }
  break;
  case 3:
  {
    arbolBinarioPilotos.RecorridoPost();
  }
  break;
  default:
  {
    cout << " -- La opcion elegida no es valida. \n"
         << endl;
    Sleep(600);
  }
  break;
  }
}

int main()
{
  int opcion;
  do
  {
    mostrarMenu();
    cin >> opcion;

    switch (opcion)
    {
    case 1:
    {
      string rutaAviones ="C:/Users/javie/Escritorio/202100081_EDD_Proyecto/Archivos_de_Prueba/aviones.json";
      cargarAviones(rutaAviones, arbolBDisponible, listaMantenimiento);
    }
    break;
    case 2:
    {
      string rutaPilotos="C:/Users/javie/Escritorio/202100081_EDD_Proyecto/Archivos_de_Prueba/pilotos.json";
      cargarPilotos(rutaPilotos, arbolBinarioPilotos, tablaPilotos);
    }
    break;
    case 3:
    {
      string rutaRutas="C:/Users/javie/Escritorio/202100081_EDD_Proyecto/Archivos_de_Prueba/rutas.txt";
      cargarRutas(rutaRutas, grafoRutas);
    }
    break;
    case 4:
    {
      string rutaMovimientos="C:/Users/javie/Escritorio/202100081_EDD_Proyecto/Archivos_de_Prueba/movimientos.txt";
      cargarMovimientos(rutaMovimientos, arbolBinarioPilotos, tablaPilotos);
    }
    break;
    case 5:
    {
      mostrarMenuRecorridos();
    }
    break;
    case 6:
    {
      string nodoInicio, nodoFin;
      cout << "Ingrese la Ciudad de Origen: ";
      cin >> nodoInicio;
      cout << "Ingrese la Ciudad de Destino: ";
      cin >> nodoFin;

      grafoRutas.caminoMasCorto(nodoInicio, nodoFin);
    }
    break;
    case 7:
    {
      generarReportes(arbolBinarioPilotos, tablaPilotos);
    }
    break;
    case 8:
    {
      cout << "Saliendo del programa..." << endl;
      exit(EXIT_SUCCESS);
    }
    break;
    default:
    {
      cout << " -- La opcion elegida no es valida. \n"
           << endl;
      Sleep(600);
    }
    break;
    }
    cin.clear();
  } while (opcion != 8);
  return 0;
}
