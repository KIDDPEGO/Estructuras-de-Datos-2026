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
tNodoAVL* tAVL::rotIzq(tNodoAVL* n) {
    tNodoAVL* y = n->der;
    n->der = y->izq;
    y->izq = n;
    actualizarAltura(n);
    actualizarAltura(y);
    return y;
}
tNodoAVL* tAVL::rotIzqDer(tNodoAVL* n) {
    n->izq = rotIzq(n->izq);
    return rotDer(n);
}
tNodoAVL* tAVL::rotDerIzq(tNodoAVL* n) {
    n->der = rotDer(n->der);
    return rotIzq(n);
}
bool tAVL::insertar(const Carta& c) {
    Carta tmp;
    if (buscar(c.id, tmp)) {      // ya existe
        return false;
    }
    raiz = insertarRec(raiz, c);  // seguro que es nuevo
    return true;
}
tNodoAVL* tAVL::insertarRec(tNodoAVL* n, const Carta& c, bool& insertado){
    if(n == NULL){
        n = new tNodoAVL(c);
        insertado = true;
        return n;
    }
    if(c.id < n->dato.id){
        n->izq = insertarRec(n->izq, c, insertado);
    }
    else if(c.id > n->dato.id){
        n->der = insertarRec(n->der, c, insertado);
    }
    else{
        insertado = false;
        return n;
    }
    actualizarAltura(n);
    if(factorBalance(n)== -2 && factorBalance(n->izq)== -1){
        return rotDer(n);
    }
    if(factorBalance(n)== -2 && factorBalance(n->izq)== 1){
        return rotIzqDer(n);
    }
    if(factorBalance(n)== 2 && factorBalance(n->der)== 1){
        return rotIzq(n);
    }
    if(factorBalance(n)== 2 && factorBalance(n->der)== -1){
        return rotDerIzq(n);
    }
    return(n);
}
bool tAVL::buscar(int id, Carta& out) const {
     tNodoAVL* actual = raiz;
    while (actual != NULL) {
        if(id < actual->dato.id){
            actual=actual->izq;
        }
        else if(id > actual->dato.id){
            actual=actual->der;
        }
        else{
            out = actual->dato;
            return true;
        }
    }
    return false;
}
