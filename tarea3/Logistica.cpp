#include "Logistica.hpp"
/*****
* void explorar
******
* BFS desde origen SIN reiniciar dist: solo avanza por los nodos que
* todavia valen -1.
******
* Input:
* const Grafo &g: grafo a recorrer
* int origen: nodo de partida
* int* dist: arreglo ya inicializado por quien llama
******
* Returns:
* void, no retorna valor
*****/
static void explorar(const Grafo &g, int origen, int* dist) {
    dist[origen] = 0; 
    tCola<int> cola;
    cola.encolar(origen);
    while(!cola.vacia()){
        int u = cola.desencolar();
        for (int i = 0; i < g.grado(u); i++) {
            int w = g.vecino(u, i);
            if (dist[w] == -1) {
                dist[w] = dist[u] + 1;
                cola.encolar(w);
            }
        }
    }
}
/*****
* void bfs
******
* Calcula la distancia minima (en aristas) desde origen a cada nodo.
* Deja -1 en los nodos no alcanzables.
******
* Input:
* const Grafo &g: grafo a recorrer
* int origen: nodo de partida
* int* dist: arreglo de tamano g.numNodos() donde se dejan las distancias
******
* Returns:
* void, no retorna valor
*****/
static void bfs(const Grafo &g, int origen, int* dist) {

    for(int i=0;i<g.numNodos();i++){
        dist[i]=-1;
    }
   explorar(g, origen, dist);
}
/*****
* int centro_mas_conectado
******
* Retorna el ID del centro con mayor grado. En caso de empate,
* retorna el de menor ID.
******
* Input:
* const Grafo &g: grafo a analizar
******
* Returns:
* int, ID del centro con mayor numero de rutas directas
*****/
int centro_mas_conectado(const Grafo &g) {
    int mejorID = 0;
    int mayorGrado = g.grado(0);
    for (int i = 1; i < g.numNodos(); i++) {
        if (g.grado(i) > mayorGrado) {
            mejorID = i;
            mayorGrado = g.grado(i);
        }
    }
    return mejorID;
}
/*****
* int calcular_cobertura
******
* Cuenta los centros distintos alcanzables a 1 o 2 saltos desde
* id_centro, sin contar el propio centro.
******
* Input:
* const Grafo &g: grafo a analizar
* int id_centro: centro de origen
******
* Returns:
* int, cantidad de centros a distancia 1 o 2 (0 si esta aislado)
*****/
int calcular_cobertura(const Grafo &g, int id_centro) {
    int* dist = new int[g.numNodos()];
    bfs(g, id_centro, dist);
    int contador = 0;
    for (int i = 0; i < g.numNodos(); i++) {
        if(dist[i]== 1 || dist[i] == 2){
            contador++;
        }
    }
    delete[] dist;
    return contador;
}
/*****
* void sugerir_rutas_alternativas
******
* Deja en resultado los centros cuya distancia minima a id_centro
* es exactamente 2 saltos.
******
* Input:
* const Grafo &g: grafo a analizar
* int id_centro: centro de origen
* Lista<int> &resultado: lista donde se dejan los centros encontrados
******
* Returns:
* void, no retorna valor
*****/
void sugerir_rutas_alternativas(const Grafo &g, int id_centro, Lista<int> &resultado) {
    int* dist = new int[g.numNodos()];
    bfs(g, id_centro, dist);
    for (int i = 0; i < g.numNodos(); i++) {
        if(dist[i] == 2){
            resultado.agregar(i);
        }
    }
    delete[] dist;
    resultado.ordenar();
}
/*****
* int contar_zonas_logisticas
******
* Cuenta las componentes conexas del grafo.
******
* Input:
* const Grafo &g: grafo a analizar
******
* Returns:
* int, cantidad de zonas logisticas
*****/
int contar_zonas_logisticas(const Grafo &g) {
    int* dist = new int[g.numNodos()];
    for(int i=0;i<g.numNodos();i++){
        dist[i] = -1;
    }
    int contador=0;
    for(int i=0;i<g.numNodos()-1;i++){
        if(dist[i]== -1){
            contador++;
            explorar(g, i, dist);
        }
    }
    delete[] dist;
    return contador;
}
/*****
* int zonas_sin_nodo
******
* Cuenta las componentes conexas del grafo ignorando el nodo removido.
******
* Input:
* const Grafo &g: grafo a analizar
* int removido: nodo que se trata como inexistente
******
* Returns:
* int, cantidad de componentes conexas sin contar el nodo removido
*****/
static int zonas_sin_nodo(const Grafo &g, int removido) {
    int* dist = new int[g.numNodos()];
    for (int i = 0; i < g.numNodos(); i++) {
        dist[i] = -1;
    }
    int contador= 0;
    dist[removido] = -2; 
    for(int i=0;i<g.numNodos();i++){
        if(dist[i]== -1){
            contador++;
            explorar(g, i, dist);
        }
    }
    delete[] dist;
    return contador;

}

/*****
* void centros_criticos
******
* Deja en resultado los puntos de articulacion, de menor a mayor ID.
******
* Input:
* const Grafo &g: grafo a analizar
* Lista<int> &resultado: lista donde se dejan los centros criticos
******
* Returns:
* void, no retorna valor
*****/
void centros_criticos(const Grafo &g, Lista<int> &resultado) {
    int original = contar_zonas_logisticas(g);
    for (int i=0; i<g.numNodos();i++){
        if(zonas_sin_nodo(g, i) > original){
            resultado.agregar(i);
        }
    }
}
