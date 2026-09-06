#include "tListaCaracteres.hpp"

void inicializarLista(tListaCaracteres &lista, int capacidadInicial) {
    if (capacidadInicial < 1) {
        capacidadInicial = 1;
    }
    lista.listArray = new char[capacidadInicial];
    lista.maxSize = capacidadInicial;
    lista.listSize = 0;
    lista.curr = 0;
}

void insertarCaracter(tListaCaracteres &lista, int pos, char c) {
    if (0 <= pos && pos <= lista.listSize) {
        if (lista.listSize == lista.maxSize) {
            char* x = new char[lista.maxSize * 2];
            for (int i = 0; i < lista.listSize; i++) {
                x[i] = lista.listArray[i];
            }
            delete[] lista.listArray;
            lista.listArray = x;
            lista.maxSize *= 2;
        }
        for (int i = lista.listSize - 1; i >= pos; i--) {
            lista.listArray[i + 1] = lista.listArray[i];
        }
        lista.listArray[pos] = c;
        lista.listSize++;
    }
}

char borrarCaracter(tListaCaracteres &lista, int pos) {
    char y = lista.listArray[pos];
    for (int i = pos; i <= lista.listSize - 2; i++) {
        lista.listArray[i] = lista.listArray[i + 1];
    }
    lista.listSize--;
    return y;
}

void concatenarTexto(tListaCaracteres &lista, const char* texto, int len) {
    if (len > 0) {
        while (lista.maxSize < lista.listSize + len) {
            char* x = new char[lista.maxSize * 2];
            for (int i = 0; i < lista.listSize; i++) {
                x[i] = lista.listArray[i];
            }
            delete[] lista.listArray;
            lista.listArray = x;
            lista.maxSize *= 2;
        }
        int l = 0;
        for (int i = lista.listSize; i < lista.listSize + len; i++) {
            lista.listArray[i] = texto[l++];
        }
        lista.listSize += len;
    }
}

void copiarLista(tListaCaracteres &destino, const tListaCaracteres &origen) {
    if (destino.maxSize == 0) {
        destino.maxSize = 1;
        destino.listArray = new char[1];
    }
    while (destino.maxSize < origen.listSize) {
        char* x = new char[destino.maxSize * 2];
        delete[] destino.listArray;
        destino.listArray = x;
        destino.maxSize *= 2;
    }
    for (int i = 0; i < origen.listSize; i++) {
        destino.listArray[i] = origen.listArray[i];
    }
    destino.listSize = origen.listSize;
}

void liberarLista(tListaCaracteres &lista) {
    delete[] lista.listArray;
    lista.listArray = nullptr;
    lista.listSize = 0;
    lista.maxSize = 0;
    lista.curr = 0;
}