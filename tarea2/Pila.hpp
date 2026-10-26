#ifndef PILA_HPP
#define PILA_HPP

#include <cstdlib>
#include "Tipos.hpp"

struct tNodoPila {
    Carta dato;
    tNodoPila* sig;
    tNodoPila(const Carta& c) : dato(c), sig(NULL) {}
};

class tPila {
public:
    tPila();
    ~tPila();

    void push(const Carta& dato);
    Carta pop();
    Carta topValue() const;
    bool vacia() const;
    int tamanio() const;
    void clear();

    tPila(const tPila&) = delete;
    tPila& operator=(const tPila&) = delete;

private:
    tNodoPila* tope;
    int tam;
};

#endif // PILA_HPP