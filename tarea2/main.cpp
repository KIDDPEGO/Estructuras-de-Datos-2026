#include <iostream>
#include <fstream>
#include "Tipos.hpp"
#include "Pila.hpp"
#include "Cola.hpp"
#include "ABB.hpp"
#include "AVL.hpp"
#include "Juego.hpp"

using namespace std;

/* ****
*    int main
******
*    Punto de entrada. Valida los argumentos, crea las estructuras del
*    juego, carga inicio.txt y procesa el archivo de comandos.
******
*    Input :
*        int argc : cantidad de argumentos recibidos
*        char* argv[] : argv[1] = inicio, argv[2] = comandos,
*                       argv[3] = ruta por defecto de GUARDAR
******
*    Returns :
*        int, 0 = ok, 1 = error de argumentos o de archivo de comandos,
*        2 = error de formato en inicio.txt
**** */
int main(int argc, char* argv[]) {

    if (argc != 4) {
       cerr << "Uso correcto. ./tarea2 <inicio> <comandos> <salida>" << endl;
        return 1;
    }
    tABB bestiario;
    tAVL grimorio;
    tPila mazo;
    tPila descarte;
    tCola horda;
    Carta mano[5];
    int tamMano = 0;
    if (!cargarInicio(argv[1], bestiario, grimorio, mazo, horda)) {
        cout << "[CARGA] ERROR" << endl;
        return 2;
    }
    ifstream f(argv[2]);
    if (!f.is_open()) { 
      cerr << "El archivo" << argv[2] << "no se pudo abrir" << endl;
      return 1;
      }
    f.close();
    procesarComandos(argv[2], argv[3], mano, tamMano,
                     mazo, descarte, horda, grimorio, bestiario);

    return 0;
}
