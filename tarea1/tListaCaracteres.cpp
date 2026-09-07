#include "tListaCaracteres.hpp"

/*****
* void inicializarLista
******
* Inicializa la lista de caracteres reservando memoria dinamica para la capacidad
* inicial indicada y dejando contadores e indices en cero.
******
* Input:
* tListaCaracteres &lista: Referencia a la lista que sera inicializada
* int capacidadInicial: Cantidad inicial de casillas a reservar en memoria
******
* Returns:
* void, no retorna valor
*****/
void inicializarLista(tListaCaracteres &lista, int capacidadInicial) {
    if (capacidadInicial < 1) {
        capacidadInicial = 1;
    }
    lista.listArray = new char[capacidadInicial];
    lista.maxSize = capacidadInicial;
    lista.listSize = 0;
    lista.curr = 0;
}

/*****
* void insertarCaracter
******
* Inserta un caracter en una posicion especifica de la lista. Si el arreglo
* esta lleno, duplica su capacidad antes de insertar y desplaza los demas caracteres.
******
* Input:
* tListaCaracteres &lista: Referencia a la lista sobre la cual se inserta
* int pos: Posicion donde se insertara el caracter
* char c: Caracter que se va a insertar
******
* Returns:
* void, no retorna valor
*****/
void insertarCaracter(tListaCaracteres &lista, int pos, char c) {
    if (pos < 0 || pos > lista.listSize) {
        return;
    }
    if (lista.listSize == lista.maxSize) {
        int nuevaCap = lista.maxSize * 2;
        if (nuevaCap < 1) {
            nuevaCap = 1;
        }
        char* nuevoArreglo = new char[nuevaCap];
        for (int i = 0; i < lista.listSize; i++) {
            nuevoArreglo[i] = lista.listArray[i];
        }
        delete[] lista.listArray;
        lista.listArray = nuevoArreglo;
        lista.maxSize = nuevaCap;
    }
    for (int i = lista.listSize - 1; i >= pos; i--) {
        lista.listArray[i + 1] = lista.listArray[i];
    }
    lista.listArray[pos] = c;
    lista.listSize++;
    lista.curr = pos;
}

/*****
* char borrarCaracter
******
* Elimina el caracter en la posicion dada y corre todos los caracteres
* siguientes una posicion hacia la izquierda para cerrar el espacio.
******
* Input:
* tListaCaracteres &lista: Referencia a la lista sobre la cual se borra
* int pos: Posicion del caracter a borrar
******
* Returns:
* char, caracter que fue eliminado o '\0' si la posicion era invalida
*****/
char borrarCaracter(tListaCaracteres &lista, int pos) {
    if (pos < 0 || pos >= lista.listSize) {
        return '\0';
    }
    char caracterEliminado = lista.listArray[pos];
    for (int i = pos; i <= lista.listSize - 2; i++) {
        lista.listArray[i] = lista.listArray[i + 1];
    }
    lista.listSize--;
    lista.curr = pos;
    return caracterEliminado;
}

/*****
* void concatenarTexto
******
* Agrega una cantidad determinada de caracteres al final de la lista, aumentando
* la capacidad del arreglo mediante duplicaciones si no alcanza el espacio.
******
* Input:
* tListaCaracteres &lista: Lista a la cual se le anexara el texto
* const char* texto: Puntero al arreglo de caracteres a agregar
* int len: Cantidad de caracteres que se agregaran
******
* Returns:
* void, no retorna valor
*****/
void concatenarTexto(tListaCaracteres &lista, const char* texto, int len) {
    if (len <= 0 || texto == nullptr) {
        return;
    }
    int capRequerida = lista.listSize + len;
    if (lista.maxSize < capRequerida) {
        int nuevaCap = lista.maxSize;
        if (nuevaCap < 1) {
            nuevaCap = 1;
        }
        while (nuevaCap < capRequerida) {
            nuevaCap = nuevaCap * 2;
        }
        char* nuevoArreglo = new char[nuevaCap];
        for (int i = 0; i < lista.listSize; i++) {
            nuevoArreglo[i] = lista.listArray[i];
        }
        delete[] lista.listArray;
        lista.listArray = nuevoArreglo;
        lista.maxSize = nuevaCap;
    }
    for (int i = 0; i < len; i++) {
        lista.listArray[lista.listSize + i] = texto[i];
    }
    lista.listSize = lista.listSize + len;
    lista.curr = lista.listSize;
}

/*****
* void copiarLista
******
* Copia el contenido de una lista a otra asegurando que la lista de destino
* tenga la capacidad suficiente con una sola reserva de memoria.
******
* Input:
* tListaCaracteres &destino: Lista receptora del contenido
* const tListaCaracteres &origen: Lista fuente a copiar
******
* Returns:
* void, no retorna valor
*****/
void copiarLista(tListaCaracteres &destino, const tListaCaracteres &origen) {
    if (destino.maxSize < origen.listSize) {
        int nuevaCap = destino.maxSize;
        if (nuevaCap < 1) {
            nuevaCap = 1;
        }
        while (nuevaCap < origen.listSize) {
            nuevaCap = nuevaCap * 2;
        }
        delete[] destino.listArray;
        destino.listArray = new char[nuevaCap];
        destino.maxSize = nuevaCap;
    }
    for (int i = 0; i < origen.listSize; i++) {
        destino.listArray[i] = origen.listArray[i];
    }
    destino.listSize = origen.listSize;
    destino.curr = origen.curr;
}

/*****
* void liberarLista
******
* Libera la memoria dinamica del arreglo de la lista y reinicia los contadores.
******
* Input:
* tListaCaracteres &lista: Lista cuya memoria sera liberada
******
* Returns:
* void, no retorna valor
*****/
void liberarLista(tListaCaracteres &lista) {
    delete[] lista.listArray;
    lista.listArray = nullptr;
    lista.listSize = 0;
    lista.maxSize = 0;
    lista.curr = 0;
}