#ifndef TPARRAFO_HPP
#define TPARRAFO_HPP
#include "tListaCaracteres.hpp"


void inicializarParrafo(tParrafo& parrafo, int idParrafo);
void agregarLineaAlFinal(tParrafo& parrafo, const tListaCaracteres& linea);
void fusionarLineas(tParrafo& parrafo, int nroL1, int nroL2);
void reflowInsertar(tParrafo& parrafo, tNodoLinea* nodoActual);
void reflowBorrar(tParrafo& parrafo, tNodoLinea* nodoActual);
void liberarParrafo(tParrafo& parrafo);
tNodoLinea* obtenerLinea(tParrafo& parrafo, int nroLinea);
#endif
