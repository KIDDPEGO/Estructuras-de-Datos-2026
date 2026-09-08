#include "tDocumento.hpp"

/*****
* void inicializarDocumento
******
* Inicializa el documento dejando los punteros head y tail en nullptr
* y la cantidad de parrafos en 0.
******
* Input:
* tDocumento &doc: Documento que se va a inicializar.
******
* Returns:
* void, no retorna nada.
*****/
void inicializarDocumento(tDocumento &doc) {
    doc.head = nullptr;
    doc.tail = nullptr;
    doc.totalParrafos = 0;
}

/*****
* tNodoParrafo* obtenerCrearParrafo
******
* Busca un parrafo por su id. Si el id ya existe lo busca recorriendo la lista,
* y si el id es mayor a la cantidad actual de parrafos, crea en orden los parrafos
* que faltan hasta llegar a ese id y los conecta al final de la lista doble.
******
* Input:
* tDocumento &doc: Documento donde se busca o crean los parrafos.
* int idParrafo: Numero del parrafo que se busca o se quiere crear.
******
* Returns:
* tNodoParrafo*, puntero al nodo del parrafo correspondiente, o nullptr si no se encuentra.
*****/
tNodoParrafo* obtenerCrearParrafo(tDocumento &doc, int idParrafo) {
    if (idParrafo <= 0) {
        return nullptr;
    }

    if (idParrafo <= doc.totalParrafos) {
        tNodoParrafo* actual = doc.head;
        while (actual != nullptr) {
            if (actual->id_parrafo == idParrafo) {
                return actual;
            }
            actual = actual->sig;
        }
        return nullptr;
    }

    for (int i = doc.totalParrafos + 1; i <= idParrafo; i++) {
        tNodoParrafo* nuevoNodo = new tNodoParrafo;
        nuevoNodo->id_parrafo = i;
        nuevoNodo->sig = nullptr;
        nuevoNodo->ant = doc.tail;
        
        inicializarParrafo(nuevoNodo->info);

        if (doc.head == nullptr) {
            doc.head = nuevoNodo;
        } else {
            doc.tail->sig = nuevoNodo;
        }
        doc.tail = nuevoNodo;
        doc.totalParrafos++;
    }

    return doc.tail;
}

/*****
* void liberarDocumento
******
* Libera la memoria de todos los parrafos de la lista doble llamando a
* liberarParrafo en cada uno y haciendo delete a los nodos, dejando el
* documento vacio.
******
* Input:
* tDocumento &doc: Documento al que se le va a liberar la memoria.
******
* Returns:
* void, no retorna nada.
*****/
void liberarDocumento(tDocumento &doc) {
    tNodoParrafo* actual = doc.head;
    while (actual != nullptr) {
        tNodoParrafo* siguiente = actual->sig;
        liberarParrafo(actual->info);
        delete actual;
        actual = siguiente;
    }
    doc.head = nullptr;
    doc.tail = nullptr;
    doc.totalParrafos = 0;
}

/*****
* void cargarDesdeBinarioChunks
******
* Abre el archivo binario y lo lee por bloques (chunks). Lee la cabecera con
* el total de chunks y el tamano de cada bloque, y luego va sacando los fragmentos
* de texto segun sus bytes utiles para agregarlos como lineas al parrafo que le toca.
******
* Input:
* tDocumento &doc: Documento donde se guardara el texto cargado.
* const std::string &rutaBinario: Ruta del archivo binario a leer.
******
* Returns:
* void, no retorna nada.
*****/
void cargarDesdeBinarioChunks(tDocumento &doc, const std::string &rutaBinario) {
    std::ifstream archivo(rutaBinario.c_str(), std::ios::binary);
    if (!archivo.is_open()) {
        return;
    }

    int total_chunks = 0;
    int chunk_size = 0;
    archivo.read(reinterpret_cast<char*>(&total_chunks), 4);
    archivo.read(reinterpret_cast<char*>(&chunk_size), 4);

    for (int i = 0; i < total_chunks; i++) {
        int bytes_utiles = 0;
        archivo.read(reinterpret_cast<char*>(&bytes_utiles), 4);

        char* payload = new char[chunk_size];
        archivo.read(payload, chunk_size);

        int pos = 0;
        while (pos < bytes_utiles) {
            int id_parrafo = 0;
            char* ptr_id = reinterpret_cast<char*>(&id_parrafo);
            for (int b = 0; b < 4; b++) {
                ptr_id[b] = payload[pos++];
            }

            int cant_caracteres = 0;
            char* ptr_cant = reinterpret_cast<char*>(&cant_caracteres);
            for (int b = 0; b < 4; b++) {
                ptr_cant[b] = payload[pos++];
            }

            tListaCaracteres lineaFragmento;
            inicializarLista(lineaFragmento, cant_caracteres);

            for (int k = 0; k < cant_caracteres; k++) {
                insertarCaracter(lineaFragmento, lineaFragmento.listSize, payload[pos++]);
            }

            tNodoParrafo* parrafoDestino = obtenerCrearParrafo(doc, id_parrafo);
            if (parrafoDestino != nullptr) {
                agregarLineaAlFinal(parrafoDestino->info, lineaFragmento);
            }

            liberarLista(lineaFragmento);
        }

        delete[] payload;
    }

    archivo.close();
}

/*****
* void exportarTextoPlano
******
* Escribe todo el documento en un archivo de texto plano. Coloca saltos de
* linea normales entre las lineas de un parrafo y saltos dobles para separar
* parrafos distintos, sin dejar lineas vacias extra al final.
******
* Input:
* const tDocumento &doc: Documento que se quiere guardar.
* const std::string &rutaSalida: Ruta del archivo de texto donde se escribira.
******
* Returns:
* void, no retorna nada.
*****/
void exportarTextoPlano(const tDocumento &doc, const std::string &rutaSalida) {
    std::ofstream archivo(rutaSalida.c_str());
    if (!archivo.is_open()) {
        return;
    }

    bool primeraLineaDoc = true;
    tNodoParrafo* parrafoActual = doc.head;

    while (parrafoActual != nullptr) {
        if (parrafoActual->info.cantLineas > 0) {
            bool primeraLineaParrafo = true;
            tNodoLinea* lineaActual = parrafoActual->info.headLinea;

            while (lineaActual != nullptr) {
                if (primeraLineaDoc) {
                    primeraLineaDoc = false;
                } else if (primeraLineaParrafo) {
                    archivo << "\n\n";
                } else {
                    archivo << "\n";
                }
                primeraLineaParrafo = false;

                for (int i = 0; i < lineaActual->info.listSize; i++) {
                    archivo << lineaActual->info.listArray[i];
                }
                lineaActual = lineaActual->sig;
            }
        }
        parrafoActual = parrafoActual->sig;
    }

    archivo.close();
}

/*****
* void procesarArchivoComandos
******
* Lee el archivo de comandos linea por linea, identifica cual instruccion se
* debe ejecutar y saca sus parametros para llamar a la funcion que corresponda
* (fusionar, agregar texto, insertar o borrar letras) y termina al guardar.
******
* Input:
* tDocumento &doc: Documento sobre el que se aplican los comandos.
* const std::string &rutaComandos: Ruta del archivo con las instrucciones.
* const std::string &rutaSalidaDefecto: Ruta de guardado por defecto si no se indica otra.
******
* Returns:
* void, no retorna nada.
*****/
void procesarArchivoComandos(tDocumento &doc, const std::string &rutaComandos, const std::string &rutaSalidaDefecto) {
    std::ifstream archivo(rutaComandos.c_str());
    if (!archivo.is_open()) {
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (!linea.empty() && linea[linea.size() - 1] == '\r') {
            linea.erase(linea.size() - 1);
        }
        if (linea.empty()) {
            continue;
        }

        int idx = 0;
        while (idx < (int)linea.size() && linea[idx] != ' ') {
            idx++;
        }
        std::string comando = linea.substr(0, idx);

        if (comando == "FUSIONAR_LINEA") {
            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int p = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                p = p * 10 + (linea[idx] - '0');
                idx++;
            }

            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int l1 = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                l1 = l1 * 10 + (linea[idx] - '0');
                idx++;
            }

            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int l2 = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                l2 = l2 * 10 + (linea[idx] - '0');
                idx++;
            }

            tNodoParrafo* nodoP = obtenerCrearParrafo(doc, p);
            if (nodoP != nullptr) {
                fusionarLineas(nodoP->info, l1, l2);
            }

        } else if (comando == "APPEND_LINEA") {
            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int p = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                p = p * 10 + (linea[idx] - '0');
                idx++;
            }

            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int l = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                l = l * 10 + (linea[idx] - '0');
                idx++;
            }

            if (idx < (int)linea.size() && linea[idx] == ' ') {
                idx++;
            }

            const char* textoAppend = linea.c_str() + idx;
            int lenAppend = (int)linea.size() - idx;

            tNodoParrafo* nodoP = obtenerCrearParrafo(doc, p);
            if (nodoP != nullptr) {
                tNodoLinea* nodoL = obtenerLinea(nodoP->info, l);
                if (nodoL != nullptr) {
                    concatenarTexto(nodoL->info, textoAppend, lenAppend);
                    if (nodoL->info.listSize > 30) {
                        reflowInsertar(nodoP->info, nodoL);
                    }
                }
            }

        } else if (comando == "INSERTAR_CHAR") {
            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int p = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                p = p * 10 + (linea[idx] - '0');
                idx++;
            }

            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int l = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                l = l * 10 + (linea[idx] - '0');
                idx++;
            }

            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int c = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                c = c * 10 + (linea[idx] - '0');
                idx++;
            }

            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            char caracter = (idx < (int)linea.size()) ? linea[idx] : '\0';

            tNodoParrafo* nodoP = obtenerCrearParrafo(doc, p);
            if (nodoP != nullptr) {
                tNodoLinea* nodoL = obtenerLinea(nodoP->info, l);
                if (nodoL != nullptr) {
                    insertarCaracter(nodoL->info, c, caracter);
                    if (nodoL->info.listSize > 30) {
                        reflowInsertar(nodoP->info, nodoL);
                    }
                }
            }

        } else if (comando == "BORRAR_CHAR") {
            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int p = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                p = p * 10 + (linea[idx] - '0');
                idx++;
            }

            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int l = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                l = l * 10 + (linea[idx] - '0');
                idx++;
            }

            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            int c = 0;
            while (idx < (int)linea.size() && linea[idx] >= '0' && linea[idx] <= '9') {
                c = c * 10 + (linea[idx] - '0');
                idx++;
            }

            tNodoParrafo* nodoP = obtenerCrearParrafo(doc, p);
            if (nodoP != nullptr) {
                tNodoLinea* nodoL = obtenerLinea(nodoP->info, l);
                if (nodoL != nullptr) {
                    borrarCaracter(nodoL->info, c);
                    if (nodoL->info.listSize < 30 && nodoL->sig != nullptr) {
                        reflowBorrar(nodoP->info, nodoL);
                    } else if (nodoL->info.listSize == 0 && nodoP->info.cantLineas > 1 && nodoL == nodoP->info.tailLinea) {
                        tNodoLinea* ant = nodoP->info.headLinea;
                        while (ant != nullptr && ant->sig != nodoL) {
                            ant = ant->sig;
                        }
                        if (ant != nullptr) {
                            ant->sig = nullptr;
                            nodoP->info.tailLinea = ant;
                            nodoP->info.cantLineas--;
                            liberarLista(nodoL->info);
                            delete nodoL;
                        }
                    }
                }
            }

        } else if (comando == "GUARDAR") {
            while (idx < (int)linea.size() && linea[idx] == ' ') idx++;
            std::string rutaGuardado = rutaSalidaDefecto;
            if (idx < (int)linea.size()) {
                rutaGuardado = linea.substr(idx);
            }
            exportarTextoPlano(doc, rutaGuardado);
            break;
        }
    }

    archivo.close();
}