#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <cstdlib>
#include "Tipos.hpp"

using namespace std;

struct tNodoAVL {
    Carta dato;
    int altura;
    tNodoAVL* izq;
    tNodoAVL* der;
    tNodoAVL(const Carta& c) : dato(c), altura(0), izq(NULL), der(NULL) {}
};

class tAVL {
public:
    tAVL();
    ~tAVL();
    bool insertar(const Carta& c);
    bool buscar(int id, Carta& out) const;
    void guardarRecorridos(ostream& salida) const;
    void clear();

    tAVL(const tAVL&) = delete;
    tAVL& operator=(const tAVL&) = delete;

private:
    tNodoAVL* raiz;
    void actualizarAltura(tNodoAVL* n);
    void preOrden(tNodoAVL* n, int prof, ostream& salida, bool& primero) const;
    void inOrden(tNodoAVL* n, int prof, ostream& salida, bool& primero) const;
    tNodoAVL* insertarRec(tNodoAVL* n, const Carta& c, bool& insertado);
    void liberar(tNodoAVL* n);
    int altura(tNodoAVL* n) const;
    int factorBalance(tNodoAVL* n) const;
    tNodoAVL* rotDer(tNodoAVL* n);
    tNodoAVL* rotIzq(tNodoAVL* n);
    tNodoAVL* rotIzqDer(tNodoAVL* n);
    tNodoAVL* rotDerIzq(tNodoAVL* n);
};

#endif