#include "AVL.hpp"

/* ****
*    int maxEntero
******
*    Devuelve el mayor de dos enteros.
******
*    Input :
*        int a : primer valor
*        int b : segundo valor
******
*    Returns :
*        int, el mayor entre a y b
**** */
int maxEntero(int a, int b) {
    if(a>b){
      return a;
    }
    return b;
}

/* ****
*    int tAVL::altura
******
*    Altura de un nodo. NULL = -1, hoja = 0.
******
*    Input :
*        tNodoAVL* n : nodo a consultar (puede ser NULL)
******
*    Returns :
*        int, altura del nodo
**** */
int tAVL::altura(tNodoAVL* n) const {
    if(n != NULL){
      return n->altura;
      }
  return -1;
}

/* ****
*    int tAVL::factorBalance
******
*    Factor de equilibrio: altura(der) - altura(izq).
******
*    Input :
*        tNodoAVL* n : nodo a consultar (puede ser NULL)
******
*    Returns :
*        int, factor de equilibrio (0 si n es NULL)
**** */
int tAVL::factorBalance(tNodoAVL* n) const {
    if (n != NULL) {
        return altura(n->der) - altura(n->izq);
    }
    return 0;
}
tNodoAVL* tAVL::rotDer(tNodoAVL* n) {
    tNodoAVL* y = n->izq;
    n->izq = y->der;
    y->der = n;
    actualizarAltura(n);
    actualizarAltura(y);
    return y;
}
/* ****
*    void tAVL::actualizarAltura
******
*    Recalcula la altura de un nodo a partir de las alturas de sus hijos.
******
*    Input :
*        tNodoAVL* n : nodo cuya altura se actualiza 
******
*    Returns :
*        void
**** */
void tAVL::actualizarAltura(tNodoAVL* n) {
    if (n != NULL) {
        n->altura = 1 + maxEntero(altura(n->izq), altura(n->der));
    }
}
