#ifndef TDOCUMENTO_HPP
#define TDOCUMENTO_HPP

#include "tParrafo.hpp"

struct tNodoParrafo {
    tNodoParrafo* ant;
    tNodoParrafo* sig;
    int id_parrafo;
    tParrafo info;
};

struct tDocumento {
    tNodoParrafo* head;
    tNodoParrafo* tail;
    int totalParrafos;
};

void inicializarDocumento(tDocumento &doc);
tNodoParrafo* obtenerCrearParrafo(tDocumento &doc, int idParrafo);
void liberarDocumento(tDocumento &doc);
void exportarTextoPlano(const tDocumento& doc, const std::string& rutaSalida);

#endif
