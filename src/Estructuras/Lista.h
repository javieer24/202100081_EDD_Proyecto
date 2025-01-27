#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <iostream>
using namespace std;
#include "NodoLista.h"

class ListaSimple
{
private:
  NodoLS *primero;

public:
  ListaSimple();
  bool estaVacia();
  NodoLS *getPrimero();
  void insertarFinal(string dato);
  void eliminarNodo(string numeroId);
  void visualizarLista();
  ~ListaSimple();
};

ListaSimple::ListaSimple()
{
  primero = nullptr;
}

bool ListaSimple::estaVacia()
{
  return primero == nullptr;
}

NodoLS *ListaSimple::getPrimero()
{
  return this->primero;
}

void ListaSimple::insertarFinal(string dato)
{
  NodoLS *nuevo = new NodoLS(dato);
  if (ListaSimple::estaVacia())
  {
    primero = nuevo;
  }
  else
  {
    NodoLS *actual = primero;
    while (actual->getSiguiente())
    {
      actual = actual->getSiguiente();
    }
    actual->setSiguiente(nuevo);
  }
}

void ListaSimple::eliminarNodo(string numeroId)
{
  if (ListaSimple::estaVacia())
  {
    cout << "La lista está vacia\n"
         << endl;
    return;
  }
  if (primero->getDato() == numeroId)
  {
    NodoLS *temp = primero;
    primero = primero->getSiguiente();
    delete temp;
    cout << "Piloto con numero de identificacion " << numeroId << " eliminado." << endl;
    return;
  }
  NodoLS *actual = primero;
  NodoLS *anterior = nullptr;
  while (actual && actual->getDato() != numeroId)
  {
    anterior = actual;
    actual = actual->getSiguiente();
  }
  if (!actual)
  {
    cout << "No se encontró el piloto con el numero de identificacion: " << numeroId << "." << endl;
    return;
  }
  anterior->setSiguiente(actual->getSiguiente());
  delete actual;
  cout << "Piloto con numero de identificacion " << numeroId << " eliminado." << endl;
}

void ListaSimple::visualizarLista()
{
  if (ListaSimple::estaVacia())
  {
    cout << "La lista está vacia\n"
         << endl;
  }
  else
  {
    NodoLS *actual = primero;
    while (actual)
    {
      cout << actual->getDato() << " -> ";
      actual = actual->getSiguiente();
    }
    cout << "\n"
         << endl;
  }
}

ListaSimple::~ListaSimple()
{
}


#endif // LISTA_H_INCLUDED