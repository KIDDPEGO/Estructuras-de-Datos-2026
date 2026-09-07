#include "tListaCaracteres.hpp"

/* ****
* void inicializarLista
******
* inicializa una lista, deja los valores en 0 y comprueba que la capacidad inicial no sea menor a 1, y crea el arreglo de caracteres.
******
* Input:
* tListaCaracteres & lista: lista de caracteres la cual sera inicializada
* int capacidadInicial: capacidad incial de la lista.
******
* Returns:
* void, no retorna valor
**** */
void inicializarLista ( tListaCaracteres & lista , int capacidadInicial ){
    if (capacidadInicial < 1) {
        capacidadInicial = 1;
    }
    lista.listArray = new char[capacidadInicial];
    lista.maxSize = capacidadInicial;
    lista.listSize = 0;
    lista.curr = 0;
} 
/* ****
* void insertarCaracter
******
* Inserta un caracter en una posicion especifica dentro de la lista
* de caracteres, desplazando los caracteres posteriores una posicion
* hacia adelante. Si la lista esta llena, duplica su capacidad antes
* de insertar.
******
* Input:
* tListaCaracteres& lista: la linea de texto donde se inserta el caracter
* int pos: la posicion (0-indexada) donde se inserta
* char c: el caracter a insertar
******
* Returns:
* void, no retorna valor
**** */
void insertarCaracter ( tListaCaracteres & lista , int pos , char c ){
    if(0<=pos && pos<=lista.listSize){
    if(lista.listSize==lista.maxSize){
        char* x = new char[lista.maxSize*2];
        for(int i=0;i<lista.listSize;i++){
            x[i]=lista.listArray[i];
        }
        delete[] lista.listArray;
        lista.listArray = x;
        lista.maxSize= lista.maxSize*2;
    }
    for(int i = lista.listSize - 1; i >= pos; i--){
        lista.listArray[i+1] = lista.listArray[i];
    }
    lista.listArray[pos]=c;
    lista.listSize++;
    }
}
/* ****
* char borrarCaracter
******
* Elimina el caracter ubicado en la posicion indicada dentro de la
* lista de caracteres, desplazando los caracteres posteriores una
* posicion hacia atras para cerrar el espacio dejado.
******
* Input:
* tListaCaracteres& lista: la linea de texto de la cual se borra el caracter
* int pos: la posicion (0-indexada) del caracter a eliminar
******
* Returns:
* char, el caracter que fue eliminado
**** */
char borrarCaracter ( tListaCaracteres & lista , int pos ){
    char y = lista.listArray[pos];
    for(int i=pos;i<=lista.listSize-2;i++){
        lista.listArray[i]= lista.listArray[i+1];
    }
    lista.listSize--;
    return y;
}
/* ****
* void concatenarTexto
******
* concatena texto de una lista de caracteres con una cantidad especifica
* de caracteres de un arreglo de caracteres
* y duplica el tamaño del arreglo de la lista de caracteres de ser necesario.
******
* Input:
* tListaCaracteres& lista: la linea de texto a la que se le concatenara el texto
* const char * texto: arreglo de caracteres a concatenar
* int len: cantidad de caracteres a concatenar
******
* Returns:
* void, no retorna valor
**** */
void concatenarTexto ( tListaCaracteres & lista , const char * texto , int len ){
    if(0<len){
    while(lista.maxSize<lista.listSize+len){
        char* x = new char[lista.maxSize*2];
        for(int i=0;i<lista.listSize;i++){
            x[i]=lista.listArray[i];
        }
        delete[] lista.listArray;
        lista.listArray = x;
        lista.maxSize= lista.maxSize*2;
        }
    int l=0;
    for(int i=lista.listSize;i<lista.listSize+len;i++){
        lista.listArray[i]=texto[l++];
    }
    lista.listSize= lista.listSize+len;
    }
}
/* ****
* void liberarLista
******
* libera una lista, libera el arreglo de caracteres, y deja todos los valores en 0.
******
* Input:
* tListaCaracteres & lista: lista a liberar
******
* Returns:
* void, no retorna valor
**** */
void liberarLista ( tListaCaracteres & lista ){
    delete[] lista.listArray;
    lista.listArray= nullptr;
    lista.listSize=0;
    lista.maxSize=0;
    lista.curr=0;
}
/* ****
* void copiarLista
******
* copia la lista de caracteres de origen en la lista de caracteres destino, en caso de de que 
* el tamaño maximo de la lista de caracteres no sea suficiente lo duplica.
******
* Input:
* tListaCaracteres& destino: lista donde se copiara la de origen
* const tListaCaracteres& origen: lista que sera copiada
******
* Returns:
* void, no retorna valor
**** */
void copiarLista(tListaCaracteres& destino, const tListaCaracteres& origen){
    if (destino.maxSize == 0) { 
        destino.maxSize = 1; 
    }
    while(destino.maxSize<origen.listSize){
        char* x = new char[destino.maxSize*2];
        delete[] destino.listArray;
        destino.listArray = x;
        destino.maxSize= destino.maxSize*2;
    }
    for(int i=0;i<origen.listSize;i++){
        destino.listArray[i]=origen.listArray[i];
    }
    destino.listSize=origen.listSize;
}
