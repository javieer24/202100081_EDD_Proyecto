# 202100081_EDD_Proyecto
# <div align="center"> SISTEMA DE GESTIÓN DE AEROPUERTO </div>
<div align="center"> 🏛 Universidad San Carlos de Guatemala</div>
<div align="center">
📕  Estructuras de Datos
</div>
<div align="center"> 📆 Escuela de Vacaciones Primer Semestre 2024</div>

<div align="center">
🙍‍♂️ Javier Andrés Monjes Solórzano -  202100081
</div>

## 🔨 Estructura
~~~
202100081_EDD_PRACTICA
├── .vscode
├── Archivos_de_Prueba
│   ├── aviones.json
│   ├── movimientos.txt
|   ├── pilotos.json
│   └── rutas.txt
├── Archivos_de_Prueba
│   ├── Documentación-202100081.pdf
│   └── Enunciado_Proyecto_EDD.pdf
├── src
│   ├── Estructuras
|   |    ├──  ArbolB.h
|   |    ├──  ArbolBB.h
|   |    ├──  Grafo.h
|   |    ├──  ListaCircularDobleCircular.h
|   |    ├──  Lista.h
|   |    ├──  ListaCircularDoble
|   |    ├──  Matriz.h
|   |    ├──  NodoBB.h
|   |    ├──  NodoLista.h
|   |    ├──  NodoListacircularDoble.h
|   |    ├──  NodoM.h
|   |    ├──  Pagina.h
|   |    ├──  TablaHash.h
|   |    ├──  Vertice.h
|   ├── Objetos
|   |    ├──  Aviones.h
|   |    ├──  Pilotos.h
|   ├── main.cpp
|   ├── main.exe
└── README.md

~~~
El Sistema de Gestión de Aeropuertos es una aplicación en C++ diseñada para gestionar eficientemente vuelos, pasajeros y equipajes utilizando estructuras de datos avanzadas. Este sistema emplea Árbol B, Lista Doble Circular, Árbol Binario de Búsqueda, Matriz Dispersa, TablaHash y Grafos para manejar diversas operaciones y procesos dentro de un entorno aeroportuario.


## 💡 Características:
- **Estructura de Datos**Implementación de estructuras de datos no lineales para manejar diferentes operaciones aeroportuarias.
- **Manejo de Memoria Dinámica**: Uso adecuado de apuntadores y asignación dinámica de memoria en C++.
- **Graphviz** Visualización de estructuras de datos mediante reportes generados.
- **Ánalisis de JSON**Lectura de datos de entrada para aviones y pasajeros desde archivos JSON.

## 📋 Tabla de Contenidos
-[📋 Tabla de Contenidos](#-tabla-de-contenidos)
- [202100081\_EDD\_Proyecto](#202100081_edd_proyecto)
- [ SISTEMA DE GESTIÓN DE AEROPUERTO ](#-sistema-de-gestión-de-aeropuerto-)
  - [🔨 Estructura](#-estructura)
  - [💡 Características:](#-características)
  - [📋 Tabla de Contenidos](#-tabla-de-contenidos)
  - [📟Instalación](#instalación)
    - [⚒  Requerimientos](#--requerimientos)
    - [🗂 Windows](#-windows)
    - [⚡ Inicio Rápido](#-inicio-rápido)
  - [📁 Formato de Archivos de Entrada](#-formato-de-archivos-de-entrada)
    - [Aviones](#aviones)
    - [Pilotos](#pilotos)
    - [Rutas](#rutas)
    - [Aviones](#aviones-1)
  - [🗂️ Generación de Reportes](#️-generación-de-reportes)
  - [💻 Ejemplo de Interfaz de Usuario](#-ejemplo-de-interfaz-de-usuario)
  - [📖 Documentación](#-documentación)
  - [Contribuciones](#contribuciones)

## 📟Instalación 
 ### ⚒  Requerimientos
- Compilador C++ (g++ recomendado o MinGW)
- Graphviz
- Make


### 🗂 Windows
1. Instalar [MinGW](https://sourceforge.net/projects/mingw/) y asegúrate de que `mingw32-gcc-g++` esté seleccionado.
2. Añade `C:\MinGW\bin` a tu variable de entorno PATH del sistema.
3. Instala [Graphviz](https://graphviz.org/download/).

### ⚡ Inicio Rápido
1. Clona el repositorio en la carpeta deseada.
```sh
git clone https://github.com/javieer24/202100081_EDD_Proyecto.git
```
2. Compila el proyecto
```sh
c++ .\main.cpp -o .\main
```

3. Ejecuta el proyecto 
```sh
.\main.exe
```

4. Carga los archivos de entrada (formato JSON y TXT) para aviones, pilotos, rutas y movimientos a través del menú de la aplicación.
   
## 📁 Formato de Archivos de Entrada

### Aviones
La información de los aviones debe proporcionarse en un archivo JSON con el siguiente formato:
``` js
[
    {
        "vuelo": "V700",
        "numero_de_registro": "N70000",
        "modelo": "Boeing 737",
        "capacidad": 180,
        "aerolinea": "AirlineX",
        "ciudad_destino": "Girona",
        "estado": "Mantenimiento"
    },
    {
        "vuelo": "V701",
        "numero_de_registro": "N70001",
        "modelo": "Boeing 737",
        "capacidad": 180,
        "aerolinea": "AirlineX",
        "ciudad_destino": "Madrid",
        "estado": "Disponible"
    }
]
```
### Pilotos
La información de los aviones debe proporcionarse en un archivo JSON con el siguiente formato:
``` js
[{
        "nombre": "John Doe",
        "nacionalidad": "Estados Unidos",
        "numero_de_id": "X10000123",
        "vuelo": "V715",
        "horas_de_vuelo": 300,
        "tipo_de_licencia": "PPL"
    },
    {
        "nombre": "Jane Smith",
        "nacionalidad": "Reino Unido",
        "numero_de_id": "X20000123",
        "vuelo": "V714",
        "horas_de_vuelo": 100,
        "tipo_de_licencia": "CPL"
    }]
```
### Rutas
La información de los aviones debe proporcionarse en un archivo JSON con el siguiente formato:
``` txt
Girona/Madrid/23;
Madrid/Girona/26;
Madrid/Barcelona/21;
Barcelona/Madrid/35;
Barcelona/Zaragoza/30;
Barcelona/Sevilla/40;
Sevilla/Valencia/11;
Sevilla/Bilbao/24;
Bilbao/Granada/17;
Bilbao/Sevilla/24;
Granada/Murcia/9;
Granada/Córdoba/16;
Granada/Girona/29;
Murcia/Girona/19;
Murcia/Madrid/40;
Córdoba/Bilbao/22;
```
### Aviones
La información de los aviones debe proporcionarse en un archivo JSON con el siguiente formato:
``` txt

MantenimientoAviones,Ingreso,N70014;
MantenimientoAviones,Salida,N70015;
DarDeBaja(X07000123);
DarDeBaja(X10000123);

```
## 🗂️ Generación de Reportes
Los informes se generan utilizando Graphviz y se pueden acceder a ellos a través del menú de la aplicación. Asegúrate de que Graphviz esté correctamente instalado y añadido a la variable PATH de tu sistema.

## 💻 Ejemplo de Interfaz de Usuario

<p align="center">
    <img src="Documentación\IMG\menu.png">
</p>

## 📖 Documentación
Para comprender de mejor manera el funcionamiento del sistema puede dirigirse a lo siguiente:
    <ul>
       <li><a href="https://github.com/javieer24/202100081_EDD_Proyecto/blob/main/Documentaci%C3%B3n/Enunciado_Proyecto_EDD.pdf" target="_blank">:point_right:Planteamiento de proyecto</a></li>
        <li><a href="https://github.com/javieer24/202100081_EDD_Proyecto/blob/main/Documentaci%C3%B3n/Documentaci%C3%B3n-202100081.pdf" target="_blank">:point_right:Documentacion Ensayo</a></li>
    </ul>

## Contribuciones
¡Las contribuciones son bienvenidas! Por favor, haz un fork de este repositorio y envía una pull request para cualquier mejora o corrección de errores.