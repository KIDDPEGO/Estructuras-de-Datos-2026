#include "tParrafo.hpp"

/*****
* void inicializarParrafo
******
* Inicializa el parrafo, apuntando los punteros headLinea y tailLinea a nullptr
* y dejando la cantidad de lineas en 0.
******
* Input:
* tParrafo &parrafo: Referencia al parrafo a inicializar
******
* Returns:
* void, no retorna valor
*****/
void inicializarParrafo(tParrafo &parrafo) {
    parrafo.headLinea = nullptr;
    parrafo.tailLinea = nullptr;
    parrafo.cantLineas = 0;
}

/*****
* void agregarLineaAlFinal
******
* Agrega una linea al final del parrafo, actualizando el puntero tailLinea
* e incrementando el contador de lineas del parrafo.
******
* Input:
* tParrafo &parrafo: Referencia al parrafo receptor
* const tListaCaracteres &linea: Contenido de la linea que se insertara
******
* Returns:
* void, no retorna valor
*****/
void agregarLineaAlFinal(tParrafo &parrafo, const tListaCaracteres &linea) {
    tNodoLinea* x = new tNodoLinea;
    inicializarLista(x->info, 1);
    copiarLista(x->info, linea);
    x->nro_linea_parrafo = parrafo.cantLineas + 1;
    x->sig = nullptr;
    if (parrafo.cantLineas == 0) {
        parrafo.headLinea = x;
    } else {
        parrafo.tailLinea->sig = x;
    }
    parrafo.tailLinea = x;
    parrafo.cantLineas++;
}

/*****
* void liberarParrafo
******
* Libera la memoria de todas las lineas del parrafo recorriendo la lista
* enlazada simple y restablece los punteros a nullptr.
******
* Input:
* tParrafo &parrafo: Referencia al parrafo a liberar
******
* Returns:
* void, no retorna valor
*****/
void liberarParrafo(tParrafo &parrafo) {
    tNodoLinea* actual = parrafo.headLinea;
    while (actual != nullptr) {
        tNodoLinea* siguiente = actual->sig;
        liberarLista(actual->info);
        delete actual;
        actual = siguiente;
    }
    parrafo.headLinea = nullptr;
    parrafo.tailLinea = nullptr;
    parrafo.cantLineas = 0;
}

/*****
* tNodoLinea* obtenerLinea
******
* Busca y retorna un puntero al nodo que contiene el numero de linea especificado.
******
* Input:
* tParrafo &parrafo: Parrafo en el cual se realizara la busqueda
* int nroLinea: Numero identificador de la linea
******
* Returns:
* tNodoLinea*, puntero al nodo correspondiente o nullptr si no existe
*****/
tNodoLinea* obtenerLinea(tParrafo &parrafo, int nroLinea) {
    tNodoLinea* actual = parrafo.headLinea;
    while (actual != nullptr) {
        if (actual->nro_linea_parrafo == nroLinea) {
            return actual;
        }
        actual = actual->sig;
    }
    return nullptr;
}

/*****
* void reflowInsertar
******
* Extrae los caracteres sobrantes (mas alla de 30) de la linea actual y los empuja
* al inicio de la linea siguiente. Si no existe linea posterior, crea un nodo nuevo
* al final del parrafo y propaga el ajuste en cascada.
******
* Input:
* tParrafo &parrafo: Referencia al parrafo donde opera el reflow
* tNodoLinea* nodoActual: Puntero al nodo donde se verifica el desborde
******
* Returns:
* void, no retorna valor
*****/
void reflowInsertar(tParrafo &parrafo, tNodoLinea* nodoActual) {
    if (nodoActual == nullptr || nodoActual->info.listSize <= 30) {
        return;
    }

    int sobrantes = nodoActual->info.listSize - 30;
    if (nodoActual->sig == nullptr) {
        nodoActual->sig = new tNodoLinea;
        inicializarLista(nodoActual->sig->info, sobrantes);
        nodoActual->sig->nro_linea_parrafo = parrafo.cantLineas + 1;
        nodoActual->sig->sig = nullptr;
        parrafo.tailLinea = nodoActual->sig;
        parrafo.cantLineas++;
    }

    for (int i = 0; i < sobrantes; i++) {
        char c = borrarCaracter(nodoActual->info, 30);
        insertarCaracter(nodoActual->sig->info, i, c);
    }

    reflowInsertar(parrafo, nodoActual->sig);
}

/*****
* void fusionarLineas
******
* Concatena el contenido de nroL2 al final de nroL1, desacopla y libera el nodo nroL2,
* decrementa el indice de las lineas posteriores y activa reflowInsertar sobre nroL1.
******
* Input:
* tParrafo &parrafo: Referencia al parrafo que contiene las lineas
* int nroL1: Indice de la primera linea (receptora)
* int nroL2: Indice de la segunda linea (a fusionar y eliminar)
******
* Returns:
* void, no retorna valor
*****/
void fusionarLineas(tParrafo &parrafo, int nroL1, int nroL2) {
    if (nroL1 >= nroL2) {
        return;
    }

    tNodoLinea* nodoL1 = obtenerLinea(parrafo, nroL1);
    if (nodoL1 == nullptr) {
        return;
    }

    tNodoLinea* antL2 = nodoL1;
    while (antL2 != nullptr && antL2->sig != nullptr && antL2->sig->nro_linea_parrafo != nroL2) {
        antL2 = antL2->sig;
    }

    if (antL2 == nullptr || antL2->sig == nullptr) {
        return;
    }

    tNodoLinea* nodoL2 = antL2->sig;
    concatenarTexto(nodoL1->info, nodoL2->info.listArray, nodoL2->info.listSize);

    antL2->sig = nodoL2->sig;
    if (parrafo.tailLinea == nodoL2) {
        parrafo.tailLinea = antL2;
    }

    liberarLista(nodoL2->info);
    delete nodoL2;
    parrafo.cantLineas--;

    tNodoLinea* curr = antL2->sig;
    while (curr != nullptr) {
        curr->nro_linea_parrafo--;
        if (curr->sig == nullptr) {
            parrafo.tailLinea = curr;
        }
        curr = curr->sig;
    }

    if (nodoL1->info.listSize > 30) {
        reflowInsertar(parrafo, nodoL1);
    }
}

/*****
* void reflowBorrar
******
* Completa el deficit de una linea intermedia jalando caracteres desde el inicio
* de la linea siguiente hasta alcanzar 30. Si la siguiente linea queda vacia,
* se desacopla y elimina, propagando el ajuste recursivamente.
******
* Input:
* tParrafo &parrafo: Referencia al parrafo donde opera el reflow
* tNodoLinea* nodoActual: Puntero al nodo deficitario
******
* Returns:
* void, no retorna valor
*****/
void reflowBorrar(tParrafo &parrafo, tNodoLinea* nodoActual) {
    if (nodoActual == nullptr || nodoActual->sig == nullptr) {
        return;
    }

    bool huboExtraccion = false;
    while (nodoActual->info.listSize < 30 && nodoActual->sig->info.listSize > 0) {
        char c = borrarCaracter(nodoActual->sig->info, 0);
        insertarCaracter(nodoActual->info, nodoActual->info.listSize, c);
        huboExtraccion = true;
    }

    if (nodoActual->sig->info.listSize == 0) {
        tNodoLinea* aEliminar = nodoActual->sig;
        nodoActual->sig = aEliminar->sig;
        if (parrafo.tailLinea == aEliminar) {
            parrafo.tailLinea = nodoActual;
        }
        liberarLista(aEliminar->info);
        delete aEliminar;
        parrafo.cantLineas--;

        tNodoLinea* z = nodoActual;
        while (z->sig != nullptr) {
            z->sig->nro_linea_parrafo = z->nro_linea_parrafo + 1;
            z = z->sig;
        }
        parrafo.tailLinea = z;
    }

    if (nodoActual->info.listSize < 30 && nodoActual->sig != nullptr) {
        reflowBorrar(parrafo, nodoActual);
    } else if (nodoActual->sig != nullptr && huboExtraccion) {
        if (nodoActual->sig->info.listSize < 30 && nodoActual->sig->sig != nullptr) {
            reflowBorrar(parrafo, nodoActual->sig);
        }
    }
}