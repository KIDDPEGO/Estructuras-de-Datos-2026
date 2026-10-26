#include "Cola.hpp"

/* ****
*    tCola::tCola
******
*    Constructor por defecto. Inicializa la cola vacia.
******
*    Input :
*        ninguno
******
*    Returns :
*        constructor (void)
**** */
tCola::tCola() {
    frente = NULL;
    fin = NULL;
    tam = 0;
}

/* ****
*    tCola::~tCola
******
*    Destructor. Libera todos los nodos iterativamente.
******
*    Input :
*        ninguno
******
*    Returns :
*        destructor (void)
**** */
tCola::~tCola() {
    clear();
}

/* ****
*    void tCola::encolar
******
*    Inserta un enemigo al final de la cola en O(1).
******
*    Input :
*        const Enemigo& dato : enemigo a encolar
******
*    Returns :
*        void
**** */
void tCola::encolar(const Enemigo& dato) {
    tNodoCola* nuevo = new tNodoCola(dato);
    if (vacia()) {
        frente = nuevo;
        fin = nuevo;
    } else {
        fin->sig = nuevo;
        fin = nuevo;
    }
    tam++;
}

/* ****
*    Enemigo tCola::desencolar
******
*    Extrae y retorna el enemigo del frente en O(1), liberando el nodo.
*    Precondicion: !vacia()
******
*    Input :
*        ninguno
******
*    Returns :
*        Enemigo, el enemigo desencolado
**** */
Enemigo tCola::desencolar() {
    tNodoCola* aux = frente;
    Enemigo e = aux->dato;
    frente = frente->sig;
    if (frente == NULL) {
        fin = NULL;
    }
    delete aux;
    tam--;
    return e;
}

/* ****
*    Enemigo tCola::frenteValue
******
*    Retorna una copia del enemigo al frente sin modificar la cola en O(1).
*    Precondicion: !vacia()
******
*    Input :
*        ninguno
******
*    Returns :
*        Enemigo, copia del enemigo frontal
**** */
Enemigo tCola::frenteValue() const {
    return frente->dato;
}

/* ****
*    Enemigo& tCola::frenteRef
******
*    Retorna una referencia modificable al enemigo al frente en O(1).
*    Precondicion: !vacia()
******
*    Input :
*        ninguno
******
*    Returns :
*        Enemigo&, referencia al enemigo del frente
**** */
Enemigo& tCola::frenteRef() {
    return frente->dato;
}

/* ****
*    bool tCola::vacia
******
*    Verifica si la cola esta vacia en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        bool, true si tam == 0, false en caso contrario
**** */
bool tCola::vacia() const {
    return tam == 0;
}

/* ****
*    int tCola::tamanio
******
*    Retorna la cantidad actual de elementos en la cola en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        int, tamano de la cola
**** */
int tCola::tamanio() const {
    return tam;
}

/* ****
*    void tCola::clear
******
*    Libera todos los nodos iterativamente en O(n) y restablece el estado.
******
*    Input :
*        ninguno
******
*    Returns :
*        void
**** */
void tCola::clear() {
    while (frente != NULL) {
        tNodoCola* aux = frente;
        frente = frente->sig;
        delete aux;
    }
    fin = NULL;
    tam = 0;
}