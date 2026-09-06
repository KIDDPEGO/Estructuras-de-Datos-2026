#include "tDocumento.hpp"

void inicializarDocumento(tDocumento &doc) {
    doc.head = nullptr;
    doc.tail = nullptr;
    doc.totalParrafos = 0;
}

tNodoParrafo* obtenerCrearParrafo(tDocumento &doc, int idParrafo) {
    if (idParrafo <= doc.totalParrafos) {
        tNodoParrafo* actual = doc.head;
        while (actual != nullptr) {
            if (actual->id_parrafo == idParrafo) {
                return actual;
            }
            actual = actual->sig;
        }
        return nullptr;
    }

    for (int i = doc.totalParrafos + 1; i <= idParrafo; i++) {
        tNodoParrafo* nuevoNodo = new tNodoParrafo;
        nuevoNodo->id_parrafo = i;
        nuevoNodo->sig = nullptr;
        nuevoNodo->ant = doc.tail;
        
        inicializarParrafo(nuevoNodo->info);

        if (doc.head == nullptr) {
            doc.head = nuevoNodo;
        } else {
            doc.tail->sig = nuevoNodo;
        }
        doc.tail = nuevoNodo;
        doc.totalParrafos++;
    }

    return doc.tail;
}

void liberarDocumento(tDocumento &doc) {
    tNodoParrafo* actual = doc.head;
    while (actual != nullptr) {
        tNodoParrafo* siguiente = actual->sig;
        liberarParrafo(actual->info);
        delete actual;
        actual = siguiente;
    }
    doc.head = nullptr;
    doc.tail = nullptr;
    doc.totalParrafos = 0;
}