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
void fusionarLineas ( tParrafo & parrafo , int nroL1 , int nroL2 ){
    tNodoLinea* actual = obtenerLinea(parrafo, nroL1);
    tNodoLinea* siguiente = nullptr;  
    if(actual != nullptr){
        siguiente = actual->sig; 
        }
    if(actual != nullptr && siguiente != nullptr){
        concatenarTexto(actual->info, siguiente->info.listArray,siguiente->info.listSize);
        actual->sig = siguiente->sig;
        siguiente->sig = nullptr;
        liberarLista(siguiente->info);
        delete siguiente;
        tNodoLinea* nodoFusionado = actual;
        while(actual->sig != nullptr){
            actual->sig->nro_linea_parrafo = actual->sig->nro_linea_parrafo - 1;
            actual = actual->sig;
        }
        parrafo.cantLineas--;
        parrafo.tailLinea = actual;
        reflowInsertar(parrafo,nodoFusionado);
        }
}
tNodoLinea* obtenerLinea(tParrafo& parrafo, int nroLinea){
    tNodoLinea* actual = parrafo.headLinea;
    while(actual != nullptr){
    if(actual->nro_linea_parrafo == nroLinea){
        return actual;
        }
        actual = actual->sig;   
    }
    return nullptr;
}
void reflowBorrar(tParrafo& parrafo, tNodoLinea* nodoActual){
    bool extraccion = false;
    while (nodoActual->info.listSize < 30 && nodoActual->sig != nullptr){
        if(nodoActual->sig->info.listSize == 0){
            tNodoLinea* y = nodoActual->sig;
            nodoActual->sig = y->sig;  
            if(parrafo.tailLinea == y){  
                parrafo.tailLinea = nodoActual;        
                }
        liberarLista(y->info);
        delete y;
        parrafo.cantLineas--;
        tNodoLinea* z = nodoActual;
        while(z->sig !=nullptr){
            z->sig->nro_linea_parrafo = z->sig->nro_linea_parrafo-1;
            z = z->sig;
        }
        parrafo.tailLinea = z;
        }
        if(nodoActual->sig != nullptr){
        insertarCaracter(nodoActual->info, nodoActual->info.listSize, borrarCaracter(nodoActual->sig->info, 0));
            }
        extraccion = true;
        }
        if(nodoActual->sig != nullptr && extraccion == true){
        reflowBorrar(parrafo, nodoActual->sig);
    }
}

