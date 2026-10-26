#include "Pila.hpp"

/* ****
*    tPila::tPila
******
*    Constructor por defecto. Inicializa la pila vacia.
******
*    Input :
*        ninguno
******
*    Returns :
*        constructor (void)
**** */
tPila::tPila() {
    tope = NULL;
    tam = 0;
}

/* ****
*    tPila::~tPila
******
*    Destructor. Libera la memoria de todos los nodos iterativamente.
******
*    Input :
*        ninguno
******
*    Returns :
*        destructor (void)
**** */
tPila::~tPila() {
    clear();
}

/* ****
*    void tPila::push
******
*    Inserta una carta en el tope de la pila en O(1).
******
*    Input :
*        const Carta& dato : carta a insertar
******
*    Returns :
*        void
**** */
void tPila::push(const Carta& dato) {
    tNodoPila* nuevo = new tNodoPila(dato);
    nuevo->sig = tope;
    tope = nuevo;
    tam++;
}

/* ****
*    Carta tPila::pop
******
*    Extrae y retorna la carta del tope en O(1), liberando el nodo.
*    Precondicion: !vacia()
******
*    Input :
*        ninguno
******
*    Returns :
*        Carta, la carta desapilada
**** */
Carta tPila::pop() {
    tNodoPila* aux = tope;
    Carta c = aux->dato;
    tope = tope->sig;
    delete aux;
    tam--;
    return c;
}

/* ****
*    Carta tPila::topValue
******
*    Retorna una copia de la carta del tope sin retirarla en O(1).
*    Precondicion: !vacia()
******
*    Input :
*        ninguno
******
*    Returns :
*        Carta, la carta del tope
**** */
Carta tPila::topValue() const {
    return tope->dato;
}

/* ****
*    bool tPila::vacia
******
*    Verifica si la pila contiene elementos en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        bool, true si tam == 0, false en caso contrario
**** */
bool tPila::vacia() const {
    return tam == 0;
}

/* ****
*    int tPila::tamanio
******
*    Retorna la cantidad actual de elementos en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        int, tamano de la pila
**** */
int tPila::tamanio() const {
    return tam;
}

/* ****
*    void tPila::clear
******
*    Libera todos los nodos iterativamente en O(n) y restablece el estado.
******
*    Input :
*        ninguno
******
*    Returns :
*        void
**** */
void tPila::clear() {
    while (tope != NULL) {
        tNodoPila* aux = tope;
        tope = tope->sig;
        delete aux;
    }
    tam = 0;
}