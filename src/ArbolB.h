#ifndef ARBOLB_H
#define ARBOLB_H

#include "Vuelo.h"
#include <iostream>
#include <vector>

const int ORDEN = 5;

struct Nodo {
    int n; // Número de claves
    std::vector<Vuelo> clave;
    std::vector<Nodo*> hijo;
    bool hoja;

    Nodo() : n(0), hoja(true) {
        clave.resize(ORDEN - 1);
        hijo.resize(ORDEN, nullptr);
    }
};

class ArbolB {
public:
    ArbolB() {
        raiz = new Nodo();
    }

    Nodo* buscar(const std::string& vuelo) {
        return buscar(raiz, vuelo);
    }

    void insertar(const Vuelo& k) {
        Nodo* r = raiz;
        if (r->n == ORDEN - 1) {
            Nodo* s = new Nodo();
            raiz = s;
            s->hoja = false;
            s->n = 0;
            s->hijo[0] = r;
            dividirHijo(s, 0, r);
            insertarNoLleno(s, k);
        } else {
            insertarNoLleno(r, k);
        }
    }

    void imprimir() {
        imprimir(raiz, 0);
    }

private:
    Nodo* raiz;

    Nodo* buscar(Nodo* x, const std::string& vuelo) {
        int i = 0;
        while (i < x->n && vuelo > x->clave[i].vuelo) {
            i++;
        }
        if (i < x->n && vuelo == x->clave[i].vuelo) {
            return x;
        }
        if (x->hoja) {
            return nullptr;
        }
        return buscar(x->hijo[i], vuelo);
    }

    void dividirHijo(Nodo* x, int i, Nodo* y) {
        Nodo* z = new Nodo();
        z->hoja = y->hoja;
        z->n = ORDEN / 2 - 1;

        for (int j = 0; j < ORDEN / 2 - 1; j++) {
            z->clave[j] = y->clave[j + ORDEN / 2];
        }
        if (!y->hoja) {
            for (int j = 0; j < ORDEN / 2; j++) {
                z->hijo[j] = y->hijo[j + ORDEN / 2];
            }
        }
        y->n = ORDEN / 2 - 1;

        for (int j = x->n; j >= i + 1; j--) {
            x->hijo[j + 1] = x->hijo[j];
        }
        x->hijo[i + 1] = z;

        for (int j = x->n - 1; j >= i; j--) {
            x->clave[j + 1] = x->clave[j];
        }
        x->clave[i] = y->clave[ORDEN / 2 - 1];
        x->n = x->n + 1;
    }

    void insertarNoLleno(Nodo* x, const Vuelo& k) {
        int i = x->n - 1;
        if (x->hoja) {
            while (i >= 0 && k < x->clave[i]) {
                x->clave[i + 1] = x->clave[i];
                i--;
            }
            x->clave[i + 1] = k;
            x->n = x->n + 1;
        } else {
            while (i >= 0 && k < x->clave[i]) {
                i--;
            }
            i++;
            if (x->hijo[i]->n == ORDEN - 1) {
                dividirHijo(x, i, x->hijo[i]);
                if (k > x->clave[i]) {
                    i++;
                }
            }
            insertarNoLleno(x->hijo[i], k);
        }
    }

    void imprimir(Nodo* x, int indent) {
        if (x != nullptr) {
            for (int i = 0; i < indent; i++) {
                std::cout << " ";
            }
            for (int i = 0; i < x->n; i++) {
                std::cout << x->clave[i].vuelo << " ";
            }
            std::cout << std::endl;
            if (!x->hoja) {
                for (int i = 0; i <= x->n; i++) {
                    imprimir(x->hijo[i], indent + 4);
                }
            }
        }
    }
};

#endif // ARBOLB_H
