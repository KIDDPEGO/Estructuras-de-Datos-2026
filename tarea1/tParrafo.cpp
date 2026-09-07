#include "tParrafo.hpp"


void inicializarParrafo(tParrafo& parrafo){
    parrafo.headLinea = nullptr;
    parrafo.tailLinea = nullptr;
    parrafo.cantLineas = 0;
}
void agregarLineaAlFinal ( tParrafo & parrafo , const tListaCaracteres & linea ){
    tNodoLinea* x = new tNodoLinea;
    inicializarLista(x->info, 1);
    copiarLista(x->info,linea);
    x->nro_linea_parrafo = parrafo.cantLineas+1;
    x->sig = nullptr;
    if(parrafo.cantLineas==0){
        parrafo.headLinea = x;
    }
    else{
        parrafo.tailLinea->sig = x;
    }
    parrafo.tailLinea = x;
    parrafo.cantLineas++;
}
void liberarParrafo ( tParrafo & parrafo ){
    tNodoLinea* actual = parrafo.headLinea;
    while(actual != nullptr){
        tNodoLinea* siguiente = actual->sig;
        liberarLista(actual->info);
        delete actual;
        actual = siguiente;
    }
    parrafo.headLinea = nullptr;
    parrafo.tailLinea = nullptr;
    parrafo.cantLineas = 0;
}
void liberarParrafo ( tParrafo & parrafo ){
    tNodoLinea* actual = parrafo.headLinea;
    while(actual != nullptr){
        tNodoLinea* siguiente = actual->sig;
        liberarLista(actual->info);
        delete actual;
        actual = siguiente;
    }
    parrafo.headLinea = nullptr;
    parrafo.tailLinea = nullptr;
    parrafo.cantLineas = 0;
}
void reflowInsertar(tParrafo& parrafo, tNodoLinea* nodoActual){
    tListaCaracteres x;
    inicializarLista(x, 1);
    while (nodoActual->info.listSize > 30){
        insertarCaracter(x,0,borrarCaracter(nodoActual->info, 30));
        }
    if (x.listSize > 0){
    if(nodoActual->sig == nullptr){
        nodoActual->sig = new tNodoLinea;
        inicializarLista(nodoActual->sig->info, 1);
        nodoActual->sig->nro_linea_parrafo = parrafo.cantLineas+1;
        nodoActual->sig->sig = nullptr;
        parrafo.tailLinea = nodoActual->sig;
        parrafo.cantLineas++;
        }
    for(int i=0;i<x.listSize;i++){
        insertarCaracter(nodoActual->sig->info,0,x.listArray[i]);
        }
    reflowInsertar(parrafo, nodoActual->sig);
    }
    liberarLista(x);
}
