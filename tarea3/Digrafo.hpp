#ifndef DIGRAFO_HPP
#define DIGRAFO_HPP

#include <string>
#include "Tipos.hpp"
#include "EstructurasAuxiliares.hpp"

class Digrafo {
private:
    int num_nodos;
    int num_arcos;
    Lista<Arista>* adyacencia;

public:
    Digrafo();
    ~Digrafo();

    void clear();
    bool cargarDesdeArchivo(const std::string& nombre_archivo);
    void agregarArco(int u, int v, int peso);

    int obtenerNumNodos() const;
    int obtenerGradoSalida(int u) const;
    Arista obtenerArco(int u, int indice) const;
};

#endif