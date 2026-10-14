#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <string>

#include "Tipos.hpp"
#include "Pila.hpp"
#include "Cola.hpp"
#include "ABB.hpp"
#include "AVL.hpp"

bool cargarInicio(const std::string &ruta,
                  tABB &bestiario, tAVL &grimorio,
                  tPila &mazo, tCola &horda);

void procesarComandos(const std::string &rutaComandos, const std::string &rutaSalida,
                      Carta mano[5], int &tamMano,
                      tPila &mazo, tPila &descarte,
                      tCola &horda,
                      tAVL &grimorio, tABB &bestiario);

#endif // JUEGO_HPP