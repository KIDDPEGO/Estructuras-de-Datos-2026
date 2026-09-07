#include "tParrafo.hpp"

/* ****
* void inicializarParrafo
******
* inicializa el parrafo, apuntando ambos punteros head y tail a nullptr
* y dejando la cantidad de parrafos en 0.
******
* Input:
* tParrafo& parrafo: parrafo a inicializar.
******
* Returns:
* void, no retorna valor
**** */  
void inicializarParrafo(tParrafo& parrafo){
    parrafo.headLinea = nullptr;
    parrafo.tailLinea = nullptr;
    parrafo.cantLineas = 0;
}
/* ****
* void agregarLineaAlFinal
******
* agrega una linea al final del parrafo, moviendo el puntero tail a esta linea
* ademas de sumar 1 a la cantidad de lineas del parrafo.
******
* Input:
* tParrafo& parrafo: parrafo al que se le agrega la linea
* const tListaCaracteres & linea: linea que se agrega al final.
******
* Returns:
* void, no retorna valor
**** */ 
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
/* ****
* void liberarParrafo
******
* libera todos los atributos del parrafo, liberando la memoria de todas las lineas de este
* y dejando los punteros head y tail apuntando a nullptr y la cantidad de lineas en 0.
******
* Input:
* tParrafo& parrafo: parrafo a liberar
******
* Returns:
* void, no retorna valor
**** */ 
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
/* ****
* void reflowInsertar
******
* extrae todos los caracteres sobrantes en una linea que tenga mas de 30 caracteres y los inserta en una lista temporal
* luego traspasa esos caracteres al inicio de la linea siguente, en caso de ser necesario, crea una linea nueva, y la conecta
* al final de la lista, y en ese caso se mueve el tail, finalmente se llama recursivamente la funcion para que se propage a las otras lineas.
******
* Input:
* tParrafo& parrafo: parrafo donde se dispara reflowinsertar
* tNodoLinea* nodoActual: puntero que apunta a el nodo donde se dispara la funcion
******
* Returns:
* void, no retorna valor
**** */
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
/* ****
* void fusionarLineas
******
* busca la linea numero 1, luego concatena el texto de la linea numero 2 al final de la linea numero 1
* luego desconecta el nodo de la linea numero 2 de la lista enlazada, luego reindexa los numeros de las lineas posteriores
* ya que se elimino una, luego disparamos reflowinsertar para asegurarnos de que todo quede en el formato de 30 caracteres.
******
* Input:
* tParrafo& parrafo: parrafo donde estan las lineas
* int nroL1: numero de la linea 1
* int nroL2: numero de la linea 2
******
* Returns:
* void, no retorna valor
**** */
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
/* ****
* tNodoLinea* obtenerLinea
******
* funcion que te devuelve un puntero que apunta a la linea con numero de indexacion entregado
****
* Input:
* tParrafo& parrafo: el parafo donde se dispara la funcion
* int nroLinea: numero de la linea a buscar
******
* Returns:
* un puntero tNodoLinea* que apunta a la linea deseada.
**** */
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
/* ****
* void reflowBorrar
******
* verifica que la linea tenga menos de 30 caracteres y que la linea siguente no es nullptr, despues revisa si la linea siguente
* ya se vacio(que tenga 0 caracteres), en este caso desconecta ese nodo y lo limpia  y reindexa las lineas siguentes, luego va la accion principal 
* de esta funcion jalando los caracteres de la linea siguente hasta que la linea actual llegue a 30 caracteres. Luego al final se dispara recursivamente
* para que esto se propage a lineas posteriores.
******
* Input:
* tParrafo& parrafo: parrafo donde se dispara reflowborrar
* tNodoLinea* nodoActual: puntero que apunta a el nodo donde se dispara la funcion
******
* Returns:
* void, no retorna valor
**** */
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

