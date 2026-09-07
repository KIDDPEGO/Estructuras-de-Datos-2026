#ifndef TPARRAFO_HPP
#define TPARRAFO_HPP
#include "tListaCaracteres.hpp"
struct tNodoLinea{
    tNodoLinea* sig;
    int nro_linea_parrafo;
    tListaCaracteres info;
};

struct tParrafo {
    tNodoLinea* headLinea;
    tNodoLinea* tailLinea;
    int cantLineas;
};

void inicializarParrafo(tParrafo& parrafo);
void agregarLineaAlFinal(tParrafo& parrafo, const tListaCaracteres& linea);
void fusionarLineas(tParrafo& parrafo, int nroL1, int nroL2);
void reflowInsertar(tParrafo& parrafo, tNodoLinea* nodoActual);
void reflowBorrar(tParrafo& parrafo, tNodoLinea* nodoActual);
void liberarParrafo(tParrafo& parrafo);
tNodoLinea* obtenerLinea(tParrafo& parrafo, int nroLinea);
#endif
