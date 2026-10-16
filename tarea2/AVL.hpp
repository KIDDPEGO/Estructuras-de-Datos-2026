#ifndef AVL_HPP
#define AVL_HPP
#include "Tipos.hpp"
#include <iostream>
#include <cstdlib>
struct tNodoAVL {
Carta dato;
int altura;
tNodoAVL* izq;
tNodoAVL* der;
tNodoAVL(const Carta& c) : dato(c), altura(0), izq(NULL), der(NULL) {}
}
class tAVL { 

public :
tAVL () ;
~ tAVL () ;
bool insertar ( const Carta & c ) ; 
bool buscar (int id , Carta & out ) const ;
void guardarRecorridos ( ostream & salida ) const ; 
void clear () ;
void actualizarAltura(tNodoAVL* n);

private :
tNodoAVL * raiz ;
int altura ( tNodoAVL * n ) const ;
int factorBalance ( tNodoAVL * n ) const ;
tNodoAVL * rotDer ( tNodoAVL * n ); 
tNodoAVL * rotIzq ( tNodoAVL * n ); 
tNodoAVL * rotIzqDer ( tNodoAVL * n ) ; 
tNodoAVL * rotDerIzq ( tNodoAVL * n ) ; 
};

#endif
