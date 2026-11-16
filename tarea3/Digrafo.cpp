#include "Digrafo.hpp"
#include <fstream>

/*****
* Constructor Digrafo
******
* Inicializa un digrafo pesado vacio sin memoria asignada.
******
* Input:
*   Ninguno.
******
* Returns:
*   Ninguno.
*****/
Digrafo::Digrafo() : num_nodos(0), num_arcos(0), adyacencia(nullptr) {}

/*****
* Destructor ~Digrafo
******
* Libera toda la memoria dinamica asociada a las listas de adyacencia.
******
* Input:
*   Ninguno.
******
* Returns:
*   Ninguno.
*****/
Digrafo::~Digrafo() {
    clear();
}

/*****
* void clear
******
* Libera la memoria de forma idempotente y reinicia los contadores del digrafo.
******
* Input:
*   Ninguno.
******
* Returns:
*   void, No retorna valor.
*****/
void Digrafo::clear() {
    if (adyacencia != nullptr) {
        delete[] adyacencia;
        adyacencia = nullptr;
    }
    num_nodos = 0;
    num_arcos = 0;
}

/*****
* bool cargarDesdeArchivo
******
* Lee el archivo flujos.txt y construye el digrafo dirigido con arcos valorados.
******
* Input:
*   const std::string& nombre_archivo : Ruta del archivo de flujos.
******
* Returns:
*   bool, true si el archivo se abrio y cargo correctamente, false en caso contrario.
*****/
bool Digrafo::cargarDesdeArchivo(const std::string& nombre_archivo) {
    std::ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        return false;
    }

    clear();
    int total_nodos = 0;
    int total_arcos = 0;
    archivo >> total_nodos >> total_arcos;

    num_nodos = total_nodos;
    num_arcos = total_arcos;
    adyacencia = new Lista<Arista>[num_nodos];

    for (int i = 0; i < total_arcos; i++) {
        int u = 0;
        int v = 0;
        int peso = 0;
        archivo >> u >> v >> peso;
        agregarArco(u, v, peso);
    }

    archivo.close();
    return true;
}

/*****
* void agregarArco
******
* Inserta un arco dirigido desde u hacia v con su respectivo costo operativo.
******
* Input:
*   int u : Nodo origen.
*   int v : Nodo destino.
*   int peso : Peso positivo del arco.
******
* Returns:
*   void, No retorna valor.
*****/
void Digrafo::agregarArco(int u, int v, int peso) {
    Arista nuevo_arco;
    nuevo_arco.destino = v;
    nuevo_arco.peso = peso;
    adyacencia[u].agregar(nuevo_arco);
}

/*****
* int obtenerNumNodos
******
* Retorna la cantidad total de nodos del digrafo.
******
* Input:
*   Ninguno.
******
* Returns:
*   int, Numero total de vertices.
*****/
int Digrafo::obtenerNumNodos() const {
    return num_nodos;
}

/*****
* int obtenerGradoSalida
******
* Retorna la cantidad de arcos salientes desde el nodo u.
******
* Input:
*   int u : Identificador del nodo origen.
******
* Returns:
*   int, Grado de salida de u.
*****/
int Digrafo::obtenerGradoSalida(int u) const {
    return adyacencia[u].tamano();
}

/*****
* Arista obtenerArco
******
* Retorna el arco ubicado en la posicion indice de la lista de adyacencia de u.
******
* Input:
*   int u : Identificador del nodo origen.
*   int indice : Posicion dentro de la lista de adyacencia de u.
******
* Returns:
*   Arista, Estructura con destino y peso del arco.
*****/
Arista Digrafo::obtenerArco(int u, int indice) const {
    return adyacencia[u].obtener(indice);
}