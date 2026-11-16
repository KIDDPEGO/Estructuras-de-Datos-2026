#ifndef ESTRUCTURAS_AUXILIARES_HPP
#define ESTRUCTURAS_AUXILIARES_HPP
#include <cstdlib>
#include "Tipos.hpp"

template <typename T>
struct tNodoPila {
    T dato;
    tNodoPila<T>* sig;
    tNodoPila(const T& c) : dato(c), sig(NULL) {}
};
template <typename T>
struct tNodoCola {
    T dato;
    tNodoCola<T>* sig;
    tNodoCola(const T& e) : dato(e), sig(NULL) {}
};
template <typename T>
class tCola {
public:
    tCola();
    ~tCola();

    void encolar(const T& dato);
    T desencolar();
    T frenteValue() const;
    bool vacia() const;
    int tamanio() const;
    void clear();

    tCola(const tCola&) = delete;
    tCola& operator=(const tCola&) = delete;

private:
    tNodoCola<T>* frente;
    tNodoCola<T>* fin;
    int tam;
};

/* ****
*    tCola<T>::tCola
******
*    Constructor por defecto. Inicializa la cola vacia.
******
*    Input :
*        ninguno
******
*    Returns :
*        constructor (void)
**** */
template <typename T>
tCola<T>::tCola() {
    frente = NULL;
    fin = NULL;
    tam = 0;
}

/* ****
*    tCola<T>::~tCola
******
*    Destructor. Libera todos los nodos iterativamente.
******
*    Input :
*        ninguno
******
*    Returns :
*        destructor (void)
**** */
template <typename T>
tCola<T>::~tCola() {
    clear();
}

/* ****
*    void tCola<T>::encolar
******
*    Inserta un T al final de la cola en O(1).
******
*    Input :
*        const T& dato : T a encolar
******
*    Returns :
*        void
**** */
template <typename T>
void tCola<T>::encolar(const T& dato) {
    tNodoCola<T>* nuevo = new tNodoCola<T>(dato);
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
*    T tCola<T>::desencolar
******
*    Extrae y retorna el T del frente en O(1), liberando el nodo.
*    Precondicion: !vacia()
******
*    Input :
*        ninguno
******
*    Returns :
*        T, el T desencolado
**** */
template <typename T>
T tCola<T>::desencolar() {
    tNodoCola<T>* aux = frente;
    T e = aux->dato;
    frente = frente->sig;
    if (frente == NULL) {
        fin = NULL;
    }
    delete aux;
    tam--;
    return e;
}

/* ****
*    T tCola<T>::frenteValue
******
*    Retorna una copia del T al frente sin modificar la cola en O(1).
*    Precondicion: !vacia()
******
*    Input :
*        ninguno
******
*    Returns :
*        T, copia del T frontal
**** */
template <typename T>
T tCola<T>::frenteValue() const {
    return frente->dato;
}

/* ****
*    bool tCola<T>::vacia
******
*    Verifica si la cola esta vacia en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        bool, true si tam == 0, false en caso contrario
**** */
template <typename T>
bool tCola<T>::vacia() const {
    return tam == 0;
}

/* ****
*    int tCola<T>::tamanio
******
*    Retorna la cantidad actual de elementos en la cola en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        int, tamano de la cola
**** */
template <typename T>
int tCola<T>::tamanio() const {
    return tam;
}

/* ****
*    void tCola<T>::clear
******
*    Libera todos los nodos iterativamente en O(n) y restablece el estado.
******
*    Input :
*        ninguno
******
*    Returns :
*        void
**** */
template <typename T>
void tCola<T>::clear() {
    while (frente != NULL) {
        tNodoCola<T>* aux = frente;
        frente = frente->sig;
        delete aux;
    }
    fin = NULL;
    tam = 0;
}
template <typename T>
class tPila {
public:
    tPila();
    ~tPila();

    void push(const T& dato);
    T pop();
    T topValue() const;
    bool vacia() const;
    int tamanio() const;
    void clear();

    tPila(const tPila&) = delete;
    tPila& operator=(const tPila&) = delete;

private:
    tNodoPila<T>* tope;
    int tam;
};

/* ****
*    tPila<T>::tPila
******
*    Constructor por defecto. Inicializa la pila vacia.
******
*    Input :
*        ninguno
******
*    Returns :
*        constructor (void)
**** */
template <typename T>
tPila<T>::tPila() {
    tope = NULL;
    tam = 0;
}

/* ****
*    tPila<T>::~tPila
******
*    Destructor. Libera la memoria de todos los nodos iterativamente.
******
*    Input :
*        ninguno
******
*    Returns :
*        destructor (void)
**** */
template <typename T>
tPila<T>::~tPila() {
    clear();
}

/* ****
*    void tPila<T>::push
******
*    Inserta un T en el tope de la pila en O(1).
******
*    Input :
*        const T& dato : T a insertar
******
*    Returns :
*        void
**** */
template <typename T>
void tPila<T>::push(const T& dato) {
    tNodoPila<T>* nuevo = new tNodoPila<T>(dato);
    nuevo->sig = tope;
    tope = nuevo;
    tam++;
}

/* ****
*    T tPila<T>::pop
******
*    Extrae y retorna la T del tope en O(1), liberando el nodo.
*    Precondicion: !vacia()
******
*    Input :
*        ninguno
******
*    Returns :
*        T, la T desapilada
**** */
template <typename T>
T tPila<T>::pop() {
    tNodoPila<T>* aux = tope;
    T c = aux->dato;
    tope = tope->sig;
    delete aux;
    tam--;
    return c;
}

/* ****
*    T tPila<T>::topValue
******
*    Retorna una copia de la T del tope sin retirarla en O(1).
*    Precondicion: !vacia()
******
*    Input :
*        ninguno
******
*    Returns :
*        T, la T del tope
**** */
template <typename T>
T tPila<T>::topValue() const {
    return tope->dato;
}

/* ****
*    bool tPila<T>::vacia
******
*    Verifica si la pila contiene elementos en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        bool, true si tam == 0, false en caso contrario
**** */
template <typename T>
bool tPila<T>::vacia() const {
    return tam == 0;
}

/* ****
*    int tPila<T>::tamanio
******
*    Retorna la cantidad actual de elementos en O(1).
******
*    Input :
*        ninguno
******
*    Returns :
*        int, tamano de la pila
**** */
template <typename T>
int tPila<T>::tamanio() const {
    return tam;
}

/* ****
*    void tPila<T>::clear
******
*    Libera todos los nodos iterativamente en O(n) y restablece el estado.
******
*    Input :
*        ninguno
******
*    Returns :
*        void
**** */
template <typename T>
void tPila<T>::clear() {
    while (tope != NULL) {
        tNodoPila<T>* aux = tope;
        tope = tope->sig;
        delete aux;
    }
    tam = 0;
}
template <typename T>
class Lista {
private:
    T* listArray;
    int listSize;
    int maxSize;

    /*****
    * void agrandar
    ******
    * Duplica la capacidad del arreglo: reserva uno nuevo del doble de tamano,
    * copia los elementos, libera el arreglo viejo y actualiza maxSize.
    ******
    * Input:
    * void
    ******
    * Returns:
    * void, no retorna valor
    *****/
    void agrandar() {
        int nuevaCap = maxSize * 2;
        if (nuevaCap < 1) {
            nuevaCap = 1;
        }
        T* nuevoArreglo = new T[nuevaCap];
        for (int i = 0; i < listSize; i++) {
            nuevoArreglo[i] = listArray[i];
        }
        delete[] listArray;
        listArray = nuevoArreglo;
        maxSize = nuevaCap;
    }

    // La lista no se copia: evita doble delete[] sobre el mismo arreglo.
    Lista(const Lista&);
    Lista& operator=(const Lista&);

public:
    /*****
    * Lista (constructor)
    ******
    * Reserva memoria dinamica para la capacidad inicial indicada (minimo 1)
    * y deja la lista vacia.
    ******
    * Input:
    * int capacidadInicial: Cantidad inicial de casillas (por defecto 1)
    ******
    * Returns:
    * No retorna valor
    *****/
    Lista(int capacidadInicial = 1) {
        if (capacidadInicial < 1) {
            capacidadInicial = 1;
        }
        listArray = new T[capacidadInicial];
        maxSize = capacidadInicial;
        listSize = 0;
    }

    /*****
    * ~Lista (destructor)
    ******
    * Libera automaticamente la memoria dinamica del arreglo.
    ******
    * Input:
    * void
    ******
    * Returns:
    * No retorna valor
    *****/
    ~Lista() {
        delete[] listArray;
    }

    /*****
    * void agregar
    ******
    * Agrega un elemento al final de la lista. Si el arreglo esta lleno,
    * duplica su capacidad antes de insertar.
    ******
    * Input:
    * const T &x: Elemento a agregar
    ******
    * Returns:
    * void, no retorna valor
    *****/
    void agregar(const T &x) {
        if (listSize == maxSize) {
            agrandar();
        }
        listArray[listSize] = x;
        listSize++;
    }

    /*****
    * T& obtener
    ******
    * Entrega una referencia al elemento de la posicion i. El llamador debe
    * asegurar 0 <= i < tamano().
    ******
    * Input:
    * int i: Posicion del elemento
    ******
    * Returns:
    * T&, referencia al elemento en la posicion i
    *****/
    T& obtener(int i) {
        return listArray[i];
    }

    const T& obtener(int i) const {
        return listArray[i];
    }

    /*****
    * int tamano
    ******
    * Entrega la cantidad de elementos almacenados.
    ******
    * Input:
    * void
    ******
    * Returns:
    * int, cantidad de elementos de la lista
    *****/
    int tamano() const {
        return listSize;
    }

    /*****
    * void clear
    ******
    * Vacia la lista y la deja con capacidad 1 (libera el arreglo anterior).
    ******
    * Input:
    * void
    ******
    * Returns:
    * void, no retorna valor
    *****/
    void clear() {
        delete[] listArray;
        listArray = new T[1];
        maxSize = 1;
        listSize = 0;
    }

    /*****
    * void ordenar
    ******
    * Ordena la lista de menor a mayor usando insercion directa. T debe
    * tener definido operator<.
    ******
    * Input:
    * void
    ******
    * Returns:
    * void, no retorna valor
    *****/
    void ordenar() {
        for (int i = 1; i < listSize; i++) {
            T clave = listArray[i];
            int j = i - 1;
            while (j >= 0 && clave < listArray[j]) {
                listArray[j + 1] = listArray[j];
                j--;
            }
            listArray[j + 1] = clave;
        }
    }
};

class MinHeap {
private:
    NodoHeap* datos;
    int capacidad;
    int tam;

    /*****
    * void redimensionar
    ******
    * Duplica la capacidad del arreglo dinamico del monticulo cuando se llena.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void redimensionar() {
        int nueva_cap = (capacidad < 1) ? 1 : capacidad * 2;
        NodoHeap* nuevo_arr = new NodoHeap[nueva_cap];
        for (int i = 0; i < tam; i++) {
            nuevo_arr[i] = datos[i];
        }
        delete[] datos;
        datos = nuevo_arr;
        capacidad = nueva_cap;
    }

    /*****
    * void flotar
    ******
    * Restaura la propiedad de Min-Heap hacia arriba desde el indice dado.
    ******
    * Input:
    *   int idx : Indice del elemento a reubicar hacia la raiz.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void flotar(int idx) {
        while (idx > 0) {
            int padre = (idx - 1) / 2;
            if (datos[idx].distancia < datos[padre].distancia) {
                NodoHeap aux = datos[idx];
                datos[idx] = datos[padre];
                datos[padre] = aux;
                idx = padre;
            } else {
                break;
            }
        }
    }

    /*****
    * void hundir
    ******
    * Restaura la propiedad de Min-Heap hacia abajo desde el indice dado.
    ******
    * Input:
    *   int idx : Indice del elemento a reubicar hacia las hojas.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void hundir(int idx) {
        while (true) {
            int izq = 2 * idx + 1;
            int der = 2 * idx + 2;
            int menor = idx;

            if (izq < tam && datos[izq].distancia < datos[menor].distancia) {
                menor = izq;
            }
            if (der < tam && datos[der].distancia < datos[menor].distancia) {
                menor = der;
            }
            if (menor != idx) {
                NodoHeap aux = datos[idx];
                datos[idx] = datos[menor];
                datos[menor] = aux;
                idx = menor;
            } else {
                break;
            }
        }
    }

    MinHeap(const MinHeap&) = delete;
    MinHeap& operator=(const MinHeap&) = delete;

public:
    /*****
    * Constructor MinHeap
    ******
    * Inicializa una cola de prioridad minima con capacidad inicial dinamica.
    ******
    * Input:
    *   int cap_inicial : Capacidad inicial del arreglo (por defecto 16).
    ******
    * Returns:
    *   Ninguno.
    *****/
    MinHeap(int cap_inicial = 16) {
        if (cap_inicial < 1) {
            cap_inicial = 1;
        }
        datos = new NodoHeap[cap_inicial];
        capacidad = cap_inicial;
        tam = 0;
    }

    /*****
    * Destructor ~MinHeap
    ******
    * Libera la memoria dinamica utilizada por el monticulo.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   Ninguno.
    *****/
    ~MinHeap() {
        delete[] datos;
    }

    /*****
    * bool vacio
    ******
    * Indica si el monticulo no contiene elementos en O(1).
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   bool, true si esta vacio, false en caso contrario.
    *****/
    bool vacio() const {
        return tam == 0;
    }

    /*****
    * void insertar
    ******
    * Inserta un par (vertice, distancia) en O(log n).
    ******
    * Input:
    *   int vertice : Identificador del nodo.
    *   int distancia : Costo acumulado hacia el nodo.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void insertar(int vertice, int distancia) {
        if (tam == capacidad) {
            redimensionar();
        }
        datos[tam].vertice = vertice;
        datos[tam].distancia = distancia;
        flotar(tam);
        tam++;
    }

    /*****
    * NodoHeap extraerMin
    ******
    * Extrae y retorna el elemento con menor distancia en O(log n).
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   NodoHeap, Nodo con la menor distancia acumulada.
    *****/
    NodoHeap extraerMin() {
        NodoHeap minimo = datos[0];
        tam--;
        if (tam > 0) {
            datos[0] = datos[tam];
            hundir(0);
        }
        return minimo;
    }

    /*****
    * void clear
    ******
    * Vacia el monticulo de forma idempotente reiniciando su tamanio.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void clear() {
        tam = 0;
    }
};

#endif
