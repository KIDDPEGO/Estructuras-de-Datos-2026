#include <fstream>
#include <string>
#include "Grafo.hpp"
#include "Digrafo.hpp"
#include "Logistica.hpp"
#include "EstructurasAuxiliares.hpp"

/*****
* void escribirLista
******
* Escribe en el flujo de salida los elementos de una lista separados por un
* unico espacio, o la palabra NINGUNO si la lista esta vacia.
******
* Input:
*   std::ofstream& out : Flujo de salida asociado a salida.txt.
*   const Lista<int>& lista : Lista de enteros a escribir.
******
* Returns:
*   void, No retorna valor.
*****/
static void escribirLista(std::ofstream& out, const Lista<int>& lista) {
    if (lista.tamano() == 0) {
        out << "NINGUNO";
        return;
    }
    for (int i = 0; i < lista.tamano(); i++) {
        if (i > 0) {
            out << " ";
        }
        out << lista.obtener(i);
    }
}

/*****
* int main
******
* Punto de entrada del programa. Carga la red logistica desde datos.txt y
* flujos.txt, procesa secuencialmente las consultas de consultas.txt y
* escribe los resultados en salida.txt.
******
* Input:
*   Ninguno.
******
* Returns:
*   int, 0 si la ejecucion finaliza correctamente, 1 si falla la apertura de archivos.
*****/
int main() {
    Grafo grafo("datos.txt");
    Digrafo digrafo;
    if (!digrafo.cargarDesdeArchivo("flujos.txt")) {
        return 1;
    }

    std::ifstream consultas("consultas.txt");
    if (!consultas.is_open()) {
        return 1;
    }

    std::ofstream salida("salida.txt");
    if (!salida.is_open()) {
        consultas.close();
        return 1;
    }

    int total_consultas = 0;
    consultas >> total_consultas;

    Lista<int> resultado;

    for (int i = 0; i < total_consultas; i++) {
        std::string tipo;
        consultas >> tipo;

        if (tipo == "SUGERIR") {
            int id_centro = 0;
            consultas >> id_centro;
            sugerir_rutas_alternativas(grafo, id_centro, resultado);
            salida << "SUGERIR " << id_centro << ": ";
            escribirLista(salida, resultado);
            salida << "\n";
        } else if (tipo == "HUB") {
            int hub = centro_mas_conectado(grafo);
            salida << "HUB: " << hub << "\n";
        } else if (tipo == "ZONAS") {
            int zonas = contar_zonas_logisticas(grafo);
            salida << "ZONAS: " << zonas << "\n";
        } else if (tipo == "COBERTURA") {
            int id_centro = 0;
            consultas >> id_centro;
            int cob = calcular_cobertura(grafo, id_centro);
            salida << "COBERTURA " << id_centro << ": " << cob << "\n";
        } else if (tipo == "CRITICOS") {
            centros_criticos(grafo, resultado);
            salida << "CRITICOS: ";
            escribirLista(salida, resultado);
            salida << "\n";
        } else if (tipo == "RUTA") {
            int origen = 0;
            int destino = 0;
            consultas >> origen >> destino;
            int costo = ruta_optima(digrafo, origen, destino, resultado);
            salida << "RUTA " << origen << " " << destino << ": ";
            if (costo == INFINITO) {
                salida << "INALCANZABLE\n";
            } else {
                salida << "costo " << costo << ", camino ";
                escribirLista(salida, resultado);
                salida << "\n";
            }
        } else if (tipo == "CONGESTION") {
            centros_en_congestion(digrafo, resultado);
            salida << "CONGESTION: ";
            escribirLista(salida, resultado);
            salida << "\n";
        }
    }

    consultas.close();
    salida.close();
    return 0;
}