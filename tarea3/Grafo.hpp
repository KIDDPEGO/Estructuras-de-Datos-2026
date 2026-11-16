#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "EstructurasAuxiliares.hpp"   

class Grafo {
private:
  
    int n;                      
    Lista<int>* adyacencia; 
    Grafo(const Grafo&);
    Grafo& operator=(const Grafo&);

public:
   
    Grafo(const char* nombreArchivo);
    ~Grafo();
    int numNodos() const;
    int grado(int v) const;
    int vecino(int v, int i) const;
};

#endif
