#include "tDocumento.hpp"

/*****
* int main
******
* Punto de entrada del programa. Valida argumentos posicionales, inicializa
* el documento, carga los chunks, procesa comandos y libera memoria.
******
* Input:
* int argc: Cantidad de argumentos pasados por linea de comandos
* char* argv[]: Arreglo de cadenas con rutas de binario, comandos y salida
******
* Returns:
* int, 0 si la ejecucion fue correcta o -1 si los argumentos son invalidos
*****/

int main(int argc, char* argv[]){
    if(argc != 4){ 
        return -1; 
        }
    tDocumento doc;
    inicializarDocumento(doc);
    cargarDesdeBinarioChunks(doc, argv[1]);
    procesarArchivoComandos(doc, argv[2], argv[3]);
    liberarDocumento(doc);
    return 0;
}
