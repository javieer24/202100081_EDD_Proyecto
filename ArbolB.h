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

    void eliminar(const std::string& numero_de_registro) {
        eliminar(raiz, numero_de_registro);
        if (raiz->n == 0) {
            Nodo* temp = raiz;
            if (raiz->hoja) {
                raiz = nullptr;
            } else {
                raiz = raiz->hijo[0];
            }
            delete temp;
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
            while (i >= 0 && k.numero_de_registro < x->clave[i].numero_de_registro) {
                x->clave[i + 1] = x->clave[i];
                i--;
            }
            x->clave[i + 1] = k;
            x->n = x->n + 1;
        } else {
            while (i >= 0 && k.numero_de_registro < x->clave[i].numero_de_registro) {
                i--;
            }
            i++;
            if (x->hijo[i]->n == ORDEN - 1) {
                dividirHijo(x, i, x->hijo[i]);
                if (k.numero_de_registro > x->clave[i].numero_de_registro) {
                    i++;
                }
            }
            insertarNoLleno(x->hijo[i], k);
        }
    }

    void eliminar(Nodo* x, const std::string& numero_de_registro) {
        int idx = encontrarClave(x, numero_de_registro);

        if (idx < x->n && x->clave[idx].numero_de_registro == numero_de_registro) {
            if (x->hoja) {
                eliminarDeHoja(x, idx);
            } else {
                eliminarDeNoHoja(x, idx);
            }
        } else {
            if (x->hoja) {
                std::cout << "El número de registro " << numero_de_registro << " no existe en el árbol.\n";
                return;
            }
            
            bool flag = ( (idx == x->n) ? true : false );
            if (x->hijo[idx]->n < ORDEN / 2) {
                llenar(x, idx);
            }
            if (flag && idx > x->n) {
                eliminar(x->hijo[idx - 1], numero_de_registro);
            } else {
                eliminar(x->hijo[idx], numero_de_registro);
            }
        }
    }

    int encontrarClave(Nodo* x, const std::string& numero_de_registro) {
        int idx = 0;
        while (idx < x->n && x->clave[idx].numero_de_registro < numero_de_registro) {
            idx++;
        }
        return idx;
    }

    void eliminarDeHoja(Nodo* x, int idx) {
        for (int i = idx + 1; i < x->n; i++) {
            x->clave[i - 1] = x->clave[i];
        }
        x->n--;
    }

    void eliminarDeNoHoja(Nodo* x, int idx) {
        Vuelo k = x->clave[idx];
        if (x->hijo[idx]->n >= ORDEN / 2) {
            Vuelo pre = obtenerPredecesor(x, idx);
            x->clave[idx] = pre;
            eliminar(x->hijo[idx], pre.numero_de_registro);
        } else if (x->hijo[idx + 1]->n >= ORDEN / 2) {
            Vuelo suc = obtenerSucesor(x, idx);
            x->clave[idx] = suc;
            eliminar(x->hijo[idx + 1], suc.numero_de_registro);
        } else {
            unir(x, idx);
            eliminar(x->hijo[idx], k.numero_de_registro);
        }
    }

    Vuelo obtenerPredecesor(Nodo* x, int idx) {
        Nodo* cur = x->hijo[idx];
        while (!cur->hoja) {
            cur = cur->hijo[cur->n];
        }
        return cur->clave[cur->n - 1];
    }

    Vuelo obtenerSucesor(Nodo* x, int idx) {
        Nodo* cur = x->hijo[idx + 1];
        while (!cur->hoja) {
            cur = cur->hijo[0];
        }
        return cur->clave[0];
    }

    void llenar(Nodo* x, int idx) {
        if (idx != 0 && x->hijo[idx - 1]->n >= ORDEN / 2) {
            pedirPrestadoAnterior(x, idx);
        } else if (idx != x->n && x->hijo[idx + 1]->n >= ORDEN / 2) {
            pedirPrestadoSiguiente(x, idx);
        } else {
            if (idx != x->n) {
                unir(x, idx);
            } else {
                unir(x, idx - 1);
            }
        }
    }

    void pedirPrestadoAnterior(Nodo* x, int idx) {
        Nodo* child = x->hijo[idx];
        Nodo* sibling = x->hijo[idx - 1];

        for (int i = child->n - 1; i >= 0; --i) {
            child->clave[i + 1] = child->clave[i];
        }

        if (!child->hoja) {
            for (int i = child->n; i >= 0; --i) {
                child->hijo[i + 1] = child->hijo[i];
            }
        }

        child->clave[0] = x->clave[idx - 1];

        if (!x->hoja) {
            child->hijo[0] = sibling->hijo[sibling->n];
        }

        x->clave[idx - 1] = sibling->clave[sibling->n - 1];

        child->n += 1;
        sibling->n -= 1;
    }

    void pedirPrestadoSiguiente(Nodo* x, int idx) {
        Nodo* child = x->hijo[idx];
        Nodo* sibling = x->hijo[idx + 1];

        child->clave[child->n] = x->clave[idx];

        if (!(child->hoja)) {
            child->hijo[child->n + 1] = sibling->hijo[0];
        }

        x->clave[idx] = sibling->clave[0];

        for (int i = 1; i < sibling->n; ++i) {
            sibling->clave[i - 1] = sibling->clave[i];
        }

        if (!sibling->hoja) {
            for (int i = 1; i <= sibling->n; ++i) {
                sibling->hijo[i - 1] = sibling->hijo[i];
            }
        }

        child->n += 1;
        sibling->n -= 1;
    }

    void unir(Nodo* x, int idx) {
        Nodo* child = x->hijo[idx];
        Nodo* sibling = x->hijo[idx + 1];

        child->clave[ORDEN / 2 - 1] = x->clave[idx];

        for (int i = 0; i < sibling->n; ++i) {
            child->clave[i + ORDEN / 2] = sibling->clave[i];
        }

        if (!child->hoja) {
            for (int i = 0; i <= sibling->n; ++i) {
                child->hijo[i + ORDEN / 2] = sibling->hijo[i];
            }
        }

        for (int i = idx + 1; i < x->n; ++i) {
            x->clave[i - 1] = x->clave[i];
        }

        for (int i = idx + 2; i <= x->n; ++i) {
            x->hijo[i - 1] = x->hijo[i];
        }

        child->n += sibling->n + 1;
        x->n--;

        delete sibling;
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
