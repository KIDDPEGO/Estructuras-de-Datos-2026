#include <fstream>
#include <string>
#include "Tipos.hpp"
#include "EstructurasAuxiliares.hpp"
#include "Grafo.hpp"
#include "Digrafo.hpp"
#include "Logistica.hpp"

/*****
* void escribirListaCentros
******
* Escribe en el archivo de salida los elementos de una lista de centros
* separados por un espacio, o "NINGUNO" si la lista esta vacia.
******
* Input:
*   std::ofstream& salida : Flujo de salida abierto hacia salida.txt.
*   const Lista<int>& lista : Lista ordenada ascendentemente de IDs de centros.
******
* Returns:
*   void, No retorna valor.
*****/
static void escribirListaCentros(std::ofstream& salida, const Lista<int>& lista) {
    int n = lista.tamano();
    if (n == 0) {
        salida << "NINGUNO";
        return;
    }
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            salida << " ";
        }
        salida << lista.obtener(i);
    }
}

/*****
* int main
******
* Punto de entrada del programa. Carga la red de conectividad (datos.txt) y
* la red de flujos (flujos.txt), procesa secuencialmente las consultas desde
* consultas.txt y escribe los resultados en salida.txt sin emitir salida por consola.
******
* Input:
*   Ninguno.
******
* Returns:
*   int, Codigo de estado de ejecucion (0 si finaliza correctamente).
*****/
int main() {
    Grafo red_conectividad("datos.txt");

    Digrafo red_flujos;
    red_flujos.cargarDesdeArchivo("flujos.txt");

    std::ifstream consultas("consultas.txt");
    std::ofstream salida("salida.txt");

    if (!consultas.is_open() || !salida.is_open()) {
        return 1;
    }

    int num_consultas = 0;
    consultas >> num_consultas;

    for (int i = 0; i < num_consultas; i++) {
        std::string comando;
        consultas >> comando;

        if (comando == "SUGERIR") {
            int id_centro = 0;
            consultas >> id_centro;

            Lista<int> resultado;
            sugerir_rutas_alternativas(red_conectividad, id_centro, resultado);

            salida << "SUGERIR " << id_centro << ": ";
            escribirListaCentros(salida, resultado);
            salida << "\n";
        } else if (comando == "HUB") {
            int hub = centro_mas_conectado(red_conectividad);
            salida << "HUB: " << hub << "\n";
        } else if (comando == "ZONAS") {
            int zonas = contar_zonas_logisticas(red_conectividad);
            salida << "ZONAS: " << zonas << "\n";
        } else if (comando == "COBERTURA") {
            int id_centro = 0;
            consultas >> id_centro;

            int cobertura = calcular_cobertura(red_conectividad, id_centro);
            salida << "COBERTURA " << id_centro << ": " << cobertura << "\n";
        } else if (comando == "CRITICOS") {
            Lista<int> criticos;
            centros_criticos(red_conectividad, criticos);

            salida << "CRITICOS: ";
            escribirListaCentros(salida, criticos);
            salida << "\n";
        } else if (comando == "RUTA") {
            int id_origen = 0;
            int id_destino = 0;
            consultas >> id_origen >> id_destino;

            Lista<int> camino;
            int costo = ruta_optima(red_flujos, id_origen, id_destino, camino);

            salida << "RUTA " << id_origen << " " << id_destino << ": ";
            if (costo == INFINITO) {
                salida << "INALCANZABLE\n";
            } else {
                salida << "costo " << costo << ", camino ";
                for (int j = 0; j < camino.tamano(); j++) {
                    if (j > 0) {
                        salida << " ";
                    }
                    salida << camino.obtener(j);
                }
                salida << "\n";
            }
        } else if (comando == "CONGESTION") {
            Lista<int> congestionados;
            centros_en_congestion(red_flujos, congestionados);

            salida << "CONGESTION: ";
            escribirListaCentros(salida, congestionados);
            salida << "\n";
        }
    }

    consultas.close();
    salida.close();

    return 0;
}