#ifndef TLISTACARACTERES_HPP
#define TLISTACARACTERES_HPP

struct tListaCaracteres {
    char* listArray;
    int listSize;
    int maxSize;
    int curr;
};

void inicializarLista(tListaCaracteres &lista, int capacidadInicial);
void insertarCaracter(tListaCaracteres &lista, int pos, char c);
char borrarCaracter(tListaCaracteres &lista, int pos);
void concatenarTexto(tListaCaracteres &lista, const char* texto, int len);
void copiarLista(tListaCaracteres &destino, const tListaCaracteres &origen);
void liberarLista(tListaCaracteres &lista);

#endif