#include "AVL.hpp"

using namespace std;

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
    if (a > b) {
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
    if (n != NULL) {
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

/* ****
*    tNodoAVL* tAVL::rotDer
******
*    Rotacion simple a la derecha (caso LL).
******
*    Input :
*        tNodoAVL* n : nodo desbalanceado
******
*    Returns :
*        tNodoAVL*, nueva raiz del subarbol
**** */
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

/* ****
*    tNodoAVL* tAVL::rotIzq
******
*    Rotacion simple a la izquierda (caso RR).
******
*    Input :
*        tNodoAVL* n : nodo desbalanceado
******
*    Returns :
*        tNodoAVL*, nueva raiz del subarbol
**** */
tNodoAVL* tAVL::rotIzq(tNodoAVL* n) {
    tNodoAVL* y = n->der;
    n->der = y->izq;
    y->izq = n;
    actualizarAltura(n);
    actualizarAltura(y);
    return y;
}

/* ****
*    tNodoAVL* tAVL::rotIzqDer
******
*    Rotacion doble izquierda-derecha (caso LR).
******
*    Input :
*        tNodoAVL* n : nodo desbalanceado
******
*    Returns :
*        tNodoAVL*, nueva raiz del subarbol
**** */
tNodoAVL* tAVL::rotIzqDer(tNodoAVL* n) {
    n->izq = rotIzq(n->izq);
    return rotDer(n);
}

/* ****
*    tNodoAVL* tAVL::rotDerIzq
******
*    Rotacion doble derecha-izquierda (caso RL).
******
*    Input :
*        tNodoAVL* n : nodo desbalanceado
******
*    Returns :
*        tNodoAVL*, nueva raiz del subarbol
**** */
tNodoAVL* tAVL::rotDerIzq(tNodoAVL* n) {
    n->der = rotDer(n->der);
    return rotIzq(n);
}

/* ****
*    bool tAVL::insertar
******
*    Inserta una carta en el arbol manteniendo el balance AVL.
******
*    Input :
*        const Carta& c : carta a insertar
******
*    Returns :
*        bool, true si se inserto, false si el ID ya existia
**** */
bool tAVL::insertar(const Carta& c) {
    bool ok = false;
    raiz = insertarRec(raiz, c, ok);
    return ok;
}

/* ****
*    tNodoAVL* tAVL::insertarRec
******
*    Auxiliar recursivo para insertar y rebalancear si corresponde.
******
*    Input :
*        tNodoAVL* n : nodo actual
*        const Carta& c : carta a insertar
*        bool& insertado : referencia de exito
******
*    Returns :
*        tNodoAVL*, raiz del subarbol posiblemente rotada
**** */
tNodoAVL* tAVL::insertarRec(tNodoAVL* n, const Carta& c, bool& insertado) {
    if (n == NULL) {
        n = new tNodoAVL(c);
        insertado = true;
        return n;
    }
    if (c.id < n->dato.id) {
        n->izq = insertarRec(n->izq, c, insertado);
    } else if (c.id > n->dato.id) {
        n->der = insertarRec(n->der, c, insertado);
    } else {
        insertado = false;
        return n;
    }

    actualizarAltura(n);

    if (factorBalance(n) == -2 && factorBalance(n->izq) == -1) {
        return rotDer(n);
    }
    if (factorBalance(n) == -2 && factorBalance(n->izq) == 1) {
        return rotIzqDer(n);
    }
    if (factorBalance(n) == 2 && factorBalance(n->der) == 1) {
        return rotIzq(n);
    }
    if (factorBalance(n) == 2 && factorBalance(n->der) == -1) {
        return rotDerIzq(n);
    }
    return n;
}

/* ****
*    bool tAVL::buscar
******
*    Busca una carta por su ID en el AVL.
******
*    Input :
*        int id : ID a buscar
*        Carta& out : referencia donde se almacena la copia si se encuentra
******
*    Returns :
*        bool, true si existe, false si no
**** */
bool tAVL::buscar(int id, Carta& out) const {
    tNodoAVL* actual = raiz;
    while (actual != NULL) {
        if (id < actual->dato.id) {
            actual = actual->izq;
        } else if (id > actual->dato.id) {
            actual = actual->der;
        } else {
            out = actual->dato;
            return true;
        }
    }
    return false;
}

/* ****
*    void tAVL::preOrden
******
*    Recorrido pre-orden que imprime id(profundidad).
******
*    Input :
*        tNodoAVL* n : nodo actual
*        int prof : nivel de profundidad actual
*        ostream& salida : flujo de salida
*        bool& primero : flag para manejo de espacios
******
*    Returns :
*        void
**** */
void tAVL::preOrden(tNodoAVL* n, int prof, ostream& salida, bool& primero) const {
    if (n == NULL) {
        return;
    }
    if (!primero) {
        salida << ' ';
    }
    salida << n->dato.id << '(' << prof << ')';
    primero = false;
    preOrden(n->izq, prof + 1, salida, primero);
    preOrden(n->der, prof + 1, salida, primero);
}

/* ****
*    void tAVL::inOrden
******
*    Recorrido in-orden que imprime id(profundidad).
******
*    Input :
*        tNodoAVL* n : nodo actual
*        int prof : nivel de profundidad actual
*        ostream& salida : flujo de salida
*        bool& primero : flag para manejo de espacios
******
*    Returns :
*        void
**** */
void tAVL::inOrden(tNodoAVL* n, int prof, ostream& salida, bool& primero) const {
    if (n == NULL) {
        return;
    }
    inOrden(n->izq, prof + 1, salida, primero);
    if (!primero) {
        salida << ' ';
    }
    salida << n->dato.id << '(' << prof << ')';
    primero = false;
    inOrden(n->der, prof + 1, salida, primero);
}

/* ****
*    void tAVL::guardarRecorridos
******
*    Exporta los recorridos pre-orden e in-orden con profundidad.
*    Si el arbol esta vacio escribe dos lineas vacias.
******
*    Input :
*        ostream& salida : flujo donde escribir
******
*    Returns :
*        void
**** */
void tAVL::guardarRecorridos(ostream& salida) const {
    if (raiz == NULL) {
        salida << "\n\n";
        return;
    }
    bool primero = true;
    preOrden(raiz, 0, salida, primero);
    salida << "\n";
    primero = true;
    inOrden(raiz, 0, salida, primero);
    salida << "\n";
}

/* ****
*    tAVL::tAVL
******
*    Constructor por defecto.
******
*    Input :
*        ninguno
******
*    Returns :
*        constructor (void)
**** */
tAVL::tAVL() {
    raiz = NULL;
}

/* ****
*    tAVL::~tAVL
******
*    Destructor. Libera la memoria dinamica de los nodos.
******
*    Input :
*        ninguno
******
*    Returns :
*        destructor (void)
**** */
tAVL::~tAVL() {
    clear();
}

/* ****
*    void tAVL::clear
******
*    Libera todos los nodos y deja el arbol vacio.
******
*    Input :
*        ninguno
******
*    Returns :
*        void
**** */
void tAVL::clear() {
    liberar(raiz);
    raiz = NULL;
}

/* ****
*    void tAVL::liberar
******
*    Auxiliar recursivo en post-orden para eliminar nodos.
******
*    Input :
*        tNodoAVL* n : subarbol a liberar
******
*    Returns :
*        void
**** */
void tAVL::liberar(tNodoAVL* n) {
    if (n == NULL) {
        return;
    }
    liberar(n->izq);
    liberar(n->der);
    delete n;
}