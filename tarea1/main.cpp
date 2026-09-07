#include "tDocumento.hpp"

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
