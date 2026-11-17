#ifndef LOGISTICA_HPP
#define LOGISTICA_HPP

#include "Grafo.hpp"
#include "EstructurasAuxiliares.hpp"
#include "Digrafo.hpp"
#include <cstdlib>

void sugerir_rutas_alternativas(const Grafo& g, int id_centro, Lista<int>& resultado);
int centro_mas_conectado(const Grafo& g);
int contar_zonas_logisticas(const Grafo& g);
int calcular_cobertura(const Grafo&, int id_centro);
void centros_criticos(const Grafo&, Lista<int>& resultado);
void centros_en_congestion(const Digrafo& d, Lista<int>& resultado);
int ruta_optima(const Digrafo& d, int id_origen, int id_destino, Lista<int>& camino);

#endif
