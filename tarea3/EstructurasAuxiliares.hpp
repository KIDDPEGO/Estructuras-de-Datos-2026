#ifndef ESTRUCTURAS_AUXILIARES_HPP
#define ESTRUCTURAS_AUXILIARES_HPP

template <typename T>
class Lista {
private:
    T* datos;
    int tamano;
    int capacidad;

    /*****
    * void redimensionar
    ******
    * Duplica la capacidad del arreglo dinamico copiando los elementos existentes.
    ******
    * Input:
    *   int nueva_capacidad : Nueva capacidad a reservar en memoria dinamica.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void redimensionar(int nueva_capacidad) {
        T* nuevo_arreglo = new T[nueva_capacidad];
        for (int i = 0; i < tamano; i++) {
            nuevo_arreglo[i] = datos[i];
        }
        delete[] datos;
        datos = nuevo_arreglo;
        capacidad = nueva_capacidad;
    }

public:
    /*****
    * Constructor Lista
    ******
    * Inicializa una lista dinamica vacia sin memoria asignada.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   Ninguno.
    *****/
    Lista() : datos(nullptr), tamano(0), capacidad(0) {}

    /*****
    * Constructor de Copia Lista
    ******
    * Crea una copia profunda de otra lista dinamica.
    ******
    * Input:
    *   const Lista& otra : Lista origen a copiar.
    ******
    * Returns:
    *   Ninguno.
    *****/
    Lista(const Lista& otra) : datos(nullptr), tamano(0), capacidad(0) {
        for (int i = 0; i < otra.tamano; i++) {
            agregar(otra.datos[i]);
        }
    }

    /*****
    * Lista& operator=
    ******
    * Asigna profundamente el contenido de otra lista liberando la memoria previa.
    ******
    * Input:
    *   const Lista& otra : Lista origen a asignar.
    ******
    * Returns:
    *   Lista&, Referencia a la lista actual.
    *****/
    Lista& operator=(const Lista& otra) {
        if (this != &otra) {
            clear();
            for (int i = 0; i < otra.tamano; i++) {
                agregar(otra.datos[i]);
            }
        }
        return *this;
    }

    /*****
    * Destructor ~Lista
    ******
    * Libera toda la memoria dinamica reservada por la lista.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   Ninguno.
    *****/
    ~Lista() {
        clear();
    }

    /*****
    * void clear
    ******
    * Libera el arreglo dinamico de forma idempotente y reinicia contadores.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void clear() {
        if (datos != nullptr) {
            delete[] datos;
            datos = nullptr;
        }
        tamano = 0;
        capacidad = 0;
    }

    /*****
    * void agregar
    ******
    * Inserta un elemento al final de la lista, redimensionando si es necesario.
    ******
    * Input:
    *   const T& valor : Elemento a insertar.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void agregar(const T& valor) {
        if (tamano == capacidad) {
            int nueva_cap = (capacidad == 0) ? 4 : capacidad * 2;
            redimensionar(nueva_cap);
        }
        datos[tamano++] = valor;
    }

    /*****
    * int obtenerTamano
    ******
    * Retorna la cantidad actual de elementos almacenados en la lista.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   int, Cantidad de elementos.
    *****/
    int obtenerTamano() const {
        return tamano;
    }

    /*****
    * bool estaVacia
    ******
    * Indica si la lista no contiene elementos.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   bool, true si esta vacia, false en caso contrario.
    *****/
    bool estaVacia() const {
        return tamano == 0;
    }

    /*****
    * T obtener
    ******
    * Retorna el elemento ubicado en la posicion indicada.
    ******
    * Input:
    *   int indice : Posicion del elemento (0 <= indice < tamano).
    ******
    * Returns:
    *   T, Copia del elemento almacenado en indice.
    *****/
    T obtener(int indice) const {
        return datos[indice];
    }

    /*****
    * void establecer
    ******
    * Sobrescribe el elemento ubicado en la posicion indicada.
    ******
    * Input:
    *   int indice : Posicion del elemento (0 <= indice < tamano).
    *   const T& valor : Nuevo valor a almacenar.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void establecer(int indice, const T& valor) {
        datos[indice] = valor;
    }
};

template <typename T>
class Cola {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d) : dato(d), siguiente(nullptr) {}
    };

    Nodo* frente;
    Nodo* final;
    int tamano;

public:
    /*****
    * Constructor Cola
    ******
    * Inicializa una cola FIFO vacia.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   Ninguno.
    *****/
    Cola() : frente(nullptr), final(nullptr), tamano(0) {}

    /*****
    * Destructor ~Cola
    ******
    * Libera iterativamente todos los nodos de la cola.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   Ninguno.
    *****/
    ~Cola() {
        clear();
    }

    /*****
    * void clear
    ******
    * Elimina iterativamente todos los nodos de forma idempotente.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void clear() {
        while (frente != nullptr) {
            Nodo* temporal = frente;
            frente = frente->siguiente;
            delete temporal;
        }
        final = nullptr;
        tamano = 0;
    }

    /*****
    * void encolar
    ******
    * Inserta un elemento al final de la cola.
    ******
    * Input:
    *   const T& valor : Elemento a encolar.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void encolar(const T& valor) {
        Nodo* nuevo = new Nodo(valor);
        if (final == nullptr) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        tamano++;
    }

    /*****
    * T desencolar
    ******
    * Extrae y retorna el elemento ubicado al frente de la cola.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   T, Elemento extraido del frente.
    *****/
    T desencolar() {
        Nodo* temporal = frente;
        T valor = temporal->dato;
        frente = frente->siguiente;
        if (frente == nullptr) {
            final = nullptr;
        }
        delete temporal;
        tamano--;
        return valor;
    }

    /*****
    * bool estaVacia
    ******
    * Verifica si la cola no tiene elementos.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   bool, true si esta vacia, false en caso contrario.
    *****/
    bool estaVacia() const {
        return frente == nullptr;
    }
};

template <typename T>
class Pila {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d, Nodo* sig) : dato(d), siguiente(sig) {}
    };

    Nodo* tope;

public:
    /*****
    * Constructor Pila
    ******
    * Inicializa una pila LIFO vacia.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   Ninguno.
    *****/
    Pila() : tope(nullptr) {}

    /*****
    * Destructor ~Pila
    ******
    * Libera iterativamente todos los nodos de la pila.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   Ninguno.
    *****/
    ~Pila() {
        clear();
    }

    /*****
    * void clear
    ******
    * Elimina iterativamente todos los nodos de forma idempotente.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void clear() {
        while (tope != nullptr) {
            Nodo* temporal = tope;
            tope = tope->siguiente;
            delete temporal;
        }
    }

    /*****
    * void apilar
    ******
    * Inserta un elemento en el tope de la pila.
    ******
    * Input:
    *   const T& valor : Elemento a apilar.
    ******
    * Returns:
    *   void, No retorna valor.
    *****/
    void apilar(const T& valor) {
        tope = new Nodo(valor, tope);
    }

    /*****
    * T desapilar
    ******
    * Extrae y retorna el elemento en el tope de la pila.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   T, Elemento extraido del tope.
    *****/
    T desapilar() {
        Nodo* temporal = tope;
        T valor = temporal->dato;
        tope = tope->siguiente;
        delete temporal;
        return valor;
    }

    /*****
    * T verTope
    ******
    * Retorna el elemento en el tope sin extraerlo.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   T, Copia del elemento en el tope.
    *****/
    T verTope() const {
        return tope->dato;
    }

    /*****
    * bool estaVacia
    ******
    * Verifica si la pila no contiene elementos.
    ******
    * Input:
    *   Ninguno.
    ******
    * Returns:
    *   bool, true si esta vacia, false en caso contrario.
    *****/
    bool estaVacia() const {
        return tope == nullptr;
    }
};

#endif