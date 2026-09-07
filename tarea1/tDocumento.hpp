#ifndef TDOCUMENTO_HPP
#define TDOCUMENTO_HPP

#include <string>
#include <fstream>
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
<<<<<<< HEAD
void exportarTextoPlano(const tDocumento& doc, const std::string& rutaSalida);
=======
>>>>>>> 93bdb6f (estructure tParrafo.hpp y declare prototipos de comandos y exportacion en tDocumento.hpp)
void cargarDesdeBinarioChunks(tDocumento &doc, const std::string &rutaBinario);
void exportarTextoPlano(const tDocumento &doc, const std::string &rutaSalida);
void procesarArchivoComandos(tDocumento &doc, const std::string &rutaComandos, const std::string &rutaSalidaDefecto);

#endif
