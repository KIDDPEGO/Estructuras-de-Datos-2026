#ifndef TIPOS_HPP
#define TIPOS_HPP

const int INFINITO = 1000000000;

struct Arista {
    int destino;
    int peso;
};

struct NodoHeap {
    int vertice;
    int distancia;
};

#endif