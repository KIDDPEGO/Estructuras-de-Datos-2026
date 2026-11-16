#include <fstream>
#include "Grafo.hpp"

using namespace std;

/*****
* Grafo (constructor)
******
* Lee el archivo y construye la lista de adyacencia.
******
* Input:
* const char* nombreArchivo: nombre del archivo, ej. "datos.txt"
******
* Returns:
* No retorna valor
*****/
Grafo::Grafo(const char* nombreArchivo) {
ifstream archivo(nombreArchivo);
int m;
archivo >> n >> m;
adyacencia = new Lista<int>[n];
for (int i=0; i<m;i++){
    int u, v;
    archivo >> u >> v;
    adyacencia[u].agregar(v);
    adyacencia[v].agregar(u);
}
}

/*****
* ~Grafo (destructor)
******
* Libera el arreglo de listas.
******
* Input:
* void
******
* Returns:
* No retorna valor
*****/
Grafo::~Grafo() {
    delete[] adyacencia;
}

/*****
* int numNodos
******
* Devuelve la cantidad de nodos del grafo.
******
* Input:
* void
******
* Returns:
* int, cantidad de nodos
*****/
int Grafo::numNodos() const {
    return n;
}

/*****
* int grado
******
* Devuelve cuantos vecinos tiene el nodo v.
******
* Input:
* int v: nodo a consultar
******
* Returns:
* int, grado del nodo v
*****/
int Grafo::grado(int v) const {
    return adyacencia[v].tamano();
}

/*****
* int vecino
******
* Devuelve el i-esimo vecino del nodo v, por valor.
******
* Input:
* int v: nodo a consultar
* int i: posicion del vecino, 0 <= i < grado(v)
******
* Returns:
* int, ID del vecino
*****/
int Grafo::vecino(int v, int i) const {
    return adyacencia[v].obtener(i);
}
