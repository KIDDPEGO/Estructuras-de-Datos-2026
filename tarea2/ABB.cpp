#include "ABB.hpp"

/* ****
*    tABB::tABB
******
*    Constructor por defecto. Inicializa el arbol binario vacio.
******
*    Input :
*        ninguno
******
*    Returns :
*        constructor (void)
**** */
tABB::tABB() {
    raiz = NULL;
    numNodos = 0;
}

/* ****
*    tABB::~tABB
******
*    Destructor. Libera la memoria de todos los nodos en post-orden.
******
*    Input :
*        ninguno
******
*    Returns :
*        destructor (void)
**** */
tABB::~tABB() {
    clear();
}

/* ****
*    bool tABB::insertar
******
*    Inserta un enemigo en el ABB ordenado por ID en O(log n) promedio.
*    Rechaza duplicados conservando la primera aparicion.
******
*    Input :
*        const Enemigo& dato : plantilla del enemigo a registrar
******
*    Returns :
*        bool, true si se inserto con exito, false si la clave ya existia
**** */
bool tABB::insertar(const Enemigo& dato) {
    bool insertado = false;
    raiz = insertarRec(raiz, dato, insertado);
    if (insertado) {
        numNodos++;
    }
    return insertado;
}

/* ****
*    tNodoABB* tABB::insertarRec
******
*    Auxiliar recursivo para insertar en el arbol binario de busqueda.
******
*    Input :
*        tNodoABB* n : raiz del subarbol actual
*        const Enemigo& dato : enemigo a insertar
*        bool& insertado : indicador de insercion efectiva
******
*    Returns :
*        tNodoABB*, raiz del subarbol actualizado
**** */
tNodoABB* tABB::insertarRec(tNodoABB* n, const Enemigo& dato, bool& insertado) {
    if (n == NULL) {
        insertado = true;
        return new tNodoABB(dato);
    }
    if (dato.id < n->id) {
        n->izq = insertarRec(n->izq, dato, insertado);
    } else if (dato.id > n->id) {
        n->der = insertarRec(n->der, dato, insertado);
    } else {
        insertado = false;
    }
    return n;
}

/* ****
*    bool tABB::buscar
******
*    Busca un enemigo por ID en O(log n) promedio (O(n) peor caso).
******
*    Input :
*        int id : identificador unico del enemigo
*        Enemigo& out : referencia receptora de los datos si se encuentra
******
*    Returns :
*        bool, true si existe en el arbol, false si no
**** */
bool tABB::buscar(int id, Enemigo& out) const {
    tNodoABB* actual = raiz;
    while (actual != NULL) {
        if (id < actual->id) {
            actual = actual->izq;
        } else if (id > actual->id) {
            actual = actual->der;
        } else {
            out = actual->dato;
            return true;
        }
    }
    return false;
}

/* ****
*    bool tABB::vacio
******
*    Verifica si el bestiario no contiene nodos en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        bool, true si numNodos == 0, false en caso contrario
**** */
bool tABB::vacio() const {
    return numNodos == 0;
}

/* ****
*    int tABB::tamanio
******
*    Retorna la cantidad total de enemigos registrados en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        int, numero de nodos del arbol
**** */
int tABB::tamanio() const {
    return numNodos;
}

/* ****
*    void tABB::inOrden
******
*    Ejecuta el recorrido in-orden del bestiario en O(n), escribiendo
*    cada enemigo en su propia linea con 2 espacios de indentacion.
******
*    Input :
*        ostream& salida : flujo de salida donde escribir
******
*    Returns :
*        void
**** */
void tABB::inOrden(ostream& salida) const {
    inOrdenRec(raiz, salida);
}

/* ****
*    void tABB::inOrdenRec
******
*    Auxiliar recursivo in-orden (izq -> raiz -> der).
******
*    Input :
*        tNodoABB* n : subarbol actual
*        ostream& salida : flujo de salida
******
*    Returns :
*        void
**** */
void tABB::inOrdenRec(tNodoABB* n, ostream& salida) const {
    if (n == NULL) {
        return;
    }
    inOrdenRec(n->izq, salida);
    salida << "  " << n->dato << "\n";
    inOrdenRec(n->der, salida);
}

/* ****
*    void tABB::clear
******
*    Elimina recursivamente todos los nodos y restablece numNodos a 0.
******
*    Input :
*        ninguno
******
*    Returns :
*        void
**** */
void tABB::clear() {
    liberar(raiz);
    raiz = NULL;
    numNodos = 0;
}

/* ****
*    void tABB::liberar
******
*    Auxiliar recursivo en post-orden para liberar memoria de los nodos.
******
*    Input :
*        tNodoABB* n : raiz del subarbol a destruir
******
*    Returns :
*        void
**** */
void tABB::liberar(tNodoABB* n) {
    if (n == NULL) {
        return;
    }
    liberar(n->izq);
    liberar(n->der);
    delete n;
}