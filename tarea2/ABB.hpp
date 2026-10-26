#ifndef ABB_HPP
#define ABB_HPP

#include <iostream>
#include <cstdlib>
#include "Tipos.hpp"

using namespace std;

struct tNodoABB {
    int id;
    Enemigo dato;
    tNodoABB* izq;
    tNodoABB* der;
    tNodoABB(const Enemigo& e) : id(e.id), dato(e), izq(NULL), der(NULL) {}
};

class tABB {
public:
    tABB();
    ~tABB();

    bool insertar(const Enemigo& dato);
    bool buscar(int id, Enemigo& out) const;
    bool vacio() const;
    int tamanio() const;
    void inOrden(ostream& salida) const;
    void clear();

    tABB(const tABB&) = delete;
    tABB& operator=(const tABB&) = delete;

private:
    tNodoABB* raiz;
    int numNodos;

    tNodoABB* insertarRec(tNodoABB* n, const Enemigo& dato, bool& insertado);
    void inOrdenRec(tNodoABB* n, ostream& salida) const;
    void liberar(tNodoABB* n);
};

#endif // ABB_HPP