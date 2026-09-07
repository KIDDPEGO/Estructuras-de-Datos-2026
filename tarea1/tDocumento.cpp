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

void cargarDesdeBinarioChunks(tDocumento &doc, const std::string &rutaBinario) {
    std::ifstream archivo(rutaBinario, std::ios::binary);
    if (!archivo.is_open()) {
        return;
    }

    int total_chunks = 0;
    int chunk_size = 0;
    archivo.read(reinterpret_cast<char*>(&total_chunks), 4);
    archivo.read(reinterpret_cast<char*>(&chunk_size), 4);

    for (int i = 0; i < total_chunks; i++) {
        int bytes_utiles = 0;
        archivo.read(reinterpret_cast<char*>(&bytes_utiles), 4);

        char* payload = new char[chunk_size];
        archivo.read(payload, chunk_size);

        int pos = 0;
        while (pos < bytes_utiles) {
            int id_parrafo = 0;
            char* ptr_id = reinterpret_cast<char*>(&id_parrafo);
            for (int b = 0; b < 4; b++) {
                ptr_id[b] = payload[pos++];
            }

            int cant_caracteres = 0;
            char* ptr_cant = reinterpret_cast<char*>(&cant_caracteres);
            for (int b = 0; b < 4; b++) {
                ptr_cant[b] = payload[pos++];
            }

            tListaCaracteres lineaFragmento;
            inicializarLista(lineaFragmento, cant_caracteres);

            for (int k = 0; k < cant_caracteres; k++) {
                insertarCaracter(lineaFragmento, lineaFragmento.listSize, payload[pos++]);
            }

            tNodoParrafo* parrafoDestino = obtenerCrearParrafo(doc, id_parrafo);
            if (parrafoDestino != nullptr) {
                agregarLineaAlFinal(parrafoDestino->info, lineaFragmento);
            }

            liberarLista(lineaFragmento);
        }

        delete[] payload;
    }

    archivo.close();
}