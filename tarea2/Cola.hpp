#ifndef COLA_HPP
#define COLA_HPP

#include <cstdlib>
#include "Tipos.hpp"

struct tNodoCola {
    Enemigo dato;
    tNodoCola* sig;
    tNodoCola(const Enemigo& e) : dato(e), sig(NULL) {}
};

class tCola {
public:
    tCola();
    ~tCola();

    void encolar(const Enemigo& dato);
    Enemigo desencolar();
    Enemigo frenteValue() const;
    Enemigo& frenteRef();
    bool vacia() const;
    int tamanio() const;
    void clear();

    tCola(const tCola&) = delete;
    tCola& operator=(const tCola&) = delete;

private:
    tNodoCola* frente;
    tNodoCola* fin;
    int tam;
};

#endif // COLA_HPP