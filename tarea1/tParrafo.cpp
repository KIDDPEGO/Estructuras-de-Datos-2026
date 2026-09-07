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
