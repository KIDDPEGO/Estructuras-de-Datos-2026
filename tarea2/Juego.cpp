#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "Juego.hpp"
using namespace std;

/* ****
*    bool validarPos
******
*    Valida el argumento posicional de un comando (JUGAR, DESCARTAR).
*    Es valido solo si esta formado unicamente por digitos ASCII, sin
*    ceros a la izquierda (salvo el 0 solo) y si cabe en un int de 32
*    bits. Si es valido, deja el numero convertido en valor.
******
*    Input :
*        const string& texto : argumento tal como aparece en el comando
*        int& valor : variable donde se deja el numero convertido
******
*    Returns :
*        bool, true si el formato es valido, false en caso contrario
**** */
static bool validarPos(const string& texto, int& valor) {
    if (texto.empty()) return false;

    for (unsigned int i = 0; i < texto.size(); i++) {
        if (texto[i] < '0' || texto[i] > '9') return false;
    }

    if (texto[0] == '0' && texto.size() > 1) return false;

    if (texto.size() > 10) return false;
    long n = strtol(texto.c_str(), NULL, 10);
    if (n > 2147483647) return false;
    valor = (int)n;
    return true;
}

/* ****
*    int minimo
******
*    Devuelve el menor de dos enteros.
******
*    Input :
*        int a : primer valor
*        int b : segundo valor
******
*    Returns :
*        int, el menor entre a y b
**** */
static int minimo(int a, int b) {
    if (a < b) return a;
    else return b;
}

/* ****
*    string recortar
******
*    Elimina espacios en blanco, tabuladores y retornos de carro al inicio
*    y al final de una cadena, conservando intactos los espacios internos.
******
*    Input :
*        const string& s : cadena original
******
*    Returns :
*        string, cadena recortada en sus extremos
**** */
static string recortar(const string& s) {
    string::size_type inicio = s.find_first_not_of(" \t\r");
    if (inicio == string::npos) {
        return "";
    }
    string::size_type fin = s.find_last_not_of(" \t\r");
    return s.substr(inicio, fin - inicio + 1);
}

/* ****
*    bool validarEnteroRango
******
*    Valida que una cadena ya recortada represente un entero valido que
*    quepa en un int de 32 bits con signo y se encuentre dentro del rango
*    [minVal, maxVal].
******
*    Input :
*        const string& texto : cadena a validar
*        int minVal : limite inferior permitido (inclusivo)
*        int maxVal : limite superior permitido (inclusivo)
*        int& valor : referencia donde se almacena el entero convertido
******
*    Returns :
*        bool, true si es un entero valido dentro del rango, false si no
**** */
static bool validarEnteroRango(const string& texto, int minVal, int maxVal, int& valor) {
    if (texto.empty()) return false;

    unsigned int i = 0;
    if (texto[0] == '+' || texto[0] == '-') {
        if (texto.size() == 1) return false;
        i = 1;
    }

    unsigned int inicioDigitos = i;
    for (; i < texto.size(); i++) {
        if (texto[i] < '0' || texto[i] > '9') return false;
    }

    while (inicioDigitos < texto.size() && texto[inicioDigitos] == '0') {
        inicioDigitos++;
    }
    if (texto.size() - inicioDigitos > 10) return false;

    char* finPtr = NULL;
    long n = strtol(texto.c_str(), &finPtr, 10);
    if (finPtr == NULL || *finPtr != '\0') return false;
    if (n < -2147483648L || n > 2147483647L) return false;
    if (n < minVal || n > maxVal) return false;

    valor = (int)n;
    return true;
}

/* ****
*    int separarCamposPipe
******
*    Divide una linea por el caracter '|' y aplica recorte de espacios
*    extremos a cada campo resultante.
******
*    Input :
*        const string& linea : linea cruda del archivo
*        string campos[] : arreglo de capacidad 6 donde guardar los campos
******
*    Returns :
*        int, cantidad de campos obtenidos (o -1 si supera 5 campos)
**** */
static int separarCamposPipe(const string& linea, string campos[6]) {
    int cant = 0;
    string actual = "";
    for (unsigned int i = 0; i < linea.size(); i++) {
        if (linea[i] == '|') {
            if (cant >= 5) return -1;
            campos[cant] = recortar(actual);
            cant++;
            actual = "";
        } else {
            actual += linea[i];
        }
    }
    campos[cant] = recortar(actual);
    cant++;
    return cant;
}

/* ****
*    void limpiarTodo
******
*    Libera toda la memoria acumulada en los cuatro TDAs en caso de abortar
*    la carga inicial por error de formato.
******
*    Input :
*        tABB& bestiario : arbol ABB de enemigos
*        tAVL& grimorio : arbol AVL de cartas
*        tPila& mazo : pila del mazo
*        tCola& horda : cola de la horda
******
*    Returns :
*        void
**** */
static void limpiarTodo(tABB& bestiario, tAVL& grimorio, tPila& mazo, tCola& horda) {
    bestiario.clear();
    grimorio.clear();
    mazo.clear();
    horda.clear();
}

/* ****
*    bool cargarInicio
******
*    Lee y valida el archivo de configuracion inicial por secciones
*    (@GRIMORIO, @BESTIARIO, @MAZO, @HORDA), poblando los TDAs. Ante
*    cualquier error de formato limpia las estructuras y retorna false.
*    Los errores semanticos (duplicados o referencias inexistentes) emiten
*    aviso por stderr e ignoran la fila.
******
*    Input :
*        const string& ruta : ruta del archivo inicio.txt
*        tABB& bestiario : ABB donde cargar los enemigos
*        tAVL& grimorio : AVL donde cargar las cartas
*        tPila& mazo : pila donde cargar el mazo inicial
*        tCola& horda : cola donde cargar la horda inicial
******
*    Returns :
*        bool, true si la carga fue exitosa, false si hubo error de formato
**** */
bool cargarInicio(const string& ruta,
                  tABB& bestiario, tAVL& grimorio,
                  tPila& mazo, tCola& horda) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        return false;
    }

    int seccion = 0; // 0: ninguna, 1: GRIMORIO, 2: BESTIARIO, 3: MAZO, 4: HORDA
    bool esperandoHeader = false;
    bool vistoGrimorio = false;
    bool vistoBestiario = false;
    bool vistoMazo = false;
    bool vistoHorda = false;

    string linea;
    while (getline(archivo, linea)) {
        string limpia = recortar(linea);
        if (limpia.empty() || limpia[0] == '#') {
            continue;
        }

        if (limpia[0] == '@') {
            if (esperandoHeader) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }
            if (limpia == "@GRIMORIO") {
                if (vistoGrimorio || vistoMazo) {
                    limpiarTodo(bestiario, grimorio, mazo, horda);
                    return false;
                }
                vistoGrimorio = true;
                seccion = 1;
                esperandoHeader = true;
            } else if (limpia == "@BESTIARIO") {
                if (vistoBestiario || vistoHorda) {
                    limpiarTodo(bestiario, grimorio, mazo, horda);
                    return false;
                }
                vistoBestiario = true;
                seccion = 2;
                esperandoHeader = true;
            } else if (limpia == "@MAZO") {
                if (vistoMazo) {
                    limpiarTodo(bestiario, grimorio, mazo, horda);
                    return false;
                }
                vistoMazo = true;
                seccion = 3;
                esperandoHeader = true;
            } else if (limpia == "@HORDA") {
                if (vistoHorda) {
                    limpiarTodo(bestiario, grimorio, mazo, horda);
                    return false;
                }
                vistoHorda = true;
                seccion = 4;
                esperandoHeader = true;
            } else {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }
            continue;
        }

        if (seccion == 0) {
            limpiarTodo(bestiario, grimorio, mazo, horda);
            return false;
        }

        string campos[6];
        int numCampos = separarCamposPipe(linea, campos);
        if (numCampos == -1) {
            limpiarTodo(bestiario, grimorio, mazo, horda);
            return false;
        }

        if (esperandoHeader) {
            bool headerOk = false;
            if (seccion == 1 && numCampos == 5 &&
                campos[0] == "ID" && campos[1] == "NOMBRE" &&
                campos[2] == "COSTE" && campos[3] == "ATAQUE" && campos[4] == "EFECTO") {
                headerOk = true;
            } else if (seccion == 2 && numCampos == 4 &&
                       campos[0] == "ID" && campos[1] == "NOMBRE" &&
                       campos[2] == "VIDA" && campos[3] == "ATAQUE") {
                headerOk = true;
            } else if ((seccion == 3 || seccion == 4) && numCampos == 1 && campos[0] == "ID") {
                headerOk = true;
            }

            if (!headerOk) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }
            esperandoHeader = false;
            continue;
        }

        if (seccion == 1) {
            if (numCampos != 5) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }
            int id, coste, ataque;
            if (!validarEnteroRango(campos[0], 1, 9999, id) ||
                campos[1].empty() || campos[1].size() > 31 ||
                !validarEnteroRango(campos[2], 0, 9, coste) ||
                !validarEnteroRango(campos[3], 0, 99, ataque)) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }

            Efecto ef;
            if (campos[4] == "NINGUNO") ef = NINGUNO;
            else if (campos[4] == "FUEGO") ef = FUEGO;
            else if (campos[4] == "HIELO") ef = HIELO;
            else if (campos[4] == "VENENO") ef = VENENO;
            else if (campos[4] == "CURACION") ef = CURACION;
            else {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }

            Carta c;
            c.id = id;
            c.nombre = campos[1];
            c.coste = coste;
            c.ataque = ataque;
            c.efecto = ef;

            if (!grimorio.insertar(c)) {
                cerr << "Aviso: carta duplicada ID " << id << "\n";
            }
        } else if (seccion == 2) {
            if (numCampos != 4) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }
            int id, vida, ataque;
            if (!validarEnteroRango(campos[0], 1, 9999, id) ||
                campos[1].empty() || campos[1].size() > 31 ||
                !validarEnteroRango(campos[2], 1, 9999, vida) ||
                !validarEnteroRango(campos[3], 0, 999, ataque)) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }

            Enemigo e;
            e.id = id;
            e.nombre = campos[1];
            e.vida = vida;
            e.ataque = ataque;
            e.vidaActual = vida;

            if (!bestiario.insertar(e)) {
                cerr << "Aviso: enemigo duplicado ID " << id << "\n";
            }
        } else if (seccion == 3) {
            if (numCampos != 1) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }
            int id;
            if (!validarEnteroRango(campos[0], 1, 9999, id)) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }
            Carta c;
            if (!grimorio.buscar(id, c)) {
                cerr << "Aviso: carta inexistente en mazo ID " << id << "\n";
            } else {
                mazo.push(c);
            }
        } else if (seccion == 4) {
            if (numCampos != 1) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }
            int id;
            if (!validarEnteroRango(campos[0], 1, 9999, id)) {
                limpiarTodo(bestiario, grimorio, mazo, horda);
                return false;
            }
            Enemigo e;
            if (!bestiario.buscar(id, e)) {
                cerr << "Aviso: enemigo inexistente en horda ID " << id << "\n";
            } else {
                e.vidaActual = e.vida;
                horda.encolar(e);
            }
        }
    }

    if (esperandoHeader) {
        limpiarTodo(bestiario, grimorio, mazo, horda);
        return false;
    }

    return true;
}

/* ****
*    void procesarComandos
******
*    Lee el archivo de comandos linea por linea y ejecuta cada comando en
*    orden: ROBAR, JUGAR, DESCARTAR, ATACAR,
*    IMPRIMIR_MANO, IMPRIMIR_HORDA, IMPRIMIR_BESTIARIO, IMPRIMIR_AVL y
*    GUARDAR. Ignora lineas vacias y comentarios (#); el nombre del comando
*    no distingue mayusculas. Lleva internamente el estado de la partida
*    (vida del jugador, energia, turno y las banderas de derrota y victoria).
******
*    Input :
*        const string& rutaComandos : archivo con los comandos de la partida
*        const string& rutaSalida : ruta por defecto de GUARDAR
*        Carta mano[5] : mano del jugador
*        int& tamMano : cantidad de cartas que hay en la mano
*        tPila& mazo : mazo de robo
*        tPila& descarte : pila de descarte
*        tCola& horda : enemigos de la sala
*        tAVL& grimorio : arbol AVL con las cartas
*        tABB& bestiario : arbol ABB con los enemigos
******
*    Returns :
*        void
**** */
void procesarComandos(const string& rutaComandos, const string& rutaSalida,
                      Carta mano[5], int& tamMano,
                      tPila& mazo, tPila& descarte,
                      tCola& horda,
                      tAVL& grimorio, tABB& bestiario) {

    ifstream archivo(rutaComandos);
    string linea;
    bool derrota = false;
    int pos;
    int energia = 3;
    int vida = 30;
    int turno = 0;
    bool victoriaImpresa = false;

    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string cmd, arg, extra;

        if (!(ss >> cmd)) continue;

        if (cmd[0] == '#') continue;

        for (unsigned int i = 0; i < cmd.size(); i++) {
            if (cmd[i] >= 'a' && cmd[i] <= 'z') {
                cmd[i] = cmd[i] - 'a' + 'A';
            }
        }

        bool hayArg = false;
        if (ss >> arg) hayArg = true;
        bool hayExtra = false;
        if (ss >> extra) hayExtra = true;

        if (cmd == "ROBAR") {
            if (derrota) continue;

            if (hayArg) {
                cerr << "Aviso: ROBAR no lleva argumentos\n";
                continue;
            }
            if (tamMano == 5) {
                cout << "ROBAR -> MANO_LLENA\n";
                continue;
            }
            if (mazo.vacia()) {
                if (!descarte.vacia()) {
                    cout << "RECICLAJE: descarte -> mazo\n";
                    while (!descarte.vacia()) {
                        mazo.push(descarte.pop());
                    }
                } else {
                    cout << "ROBAR -> MAZO_VACIO\n";
                    continue;
                }
            }
            Carta c = mazo.pop();
            mano[tamMano] = c;
            tamMano++;
            cout << "ROBAR -> " << c.id << " (mano=" << tamMano << ")" << endl;
        } else if (cmd == "JUGAR") {
            if (derrota) continue;

            if (hayArg == false || hayExtra == true) {
                cerr << "falta un argumento o sobra un argumento\n";
                continue;
            }
            if (!validarPos(arg, pos)) {
                cerr << "posicion invalida\n";
                continue;
            }
            if (pos < 1 || pos > tamMano) {
                cout << "JUGAR " << arg << " -> POS_INVALIDA\n";
                continue;
            }
            Carta c = mano[pos - 1];
            if (c.coste > energia) {
                cout << "JUGAR " << arg << " -> ENERGIA_INSUFICIENTE\n";
                continue;
            }
            energia = energia - c.coste;
            for (int i = (pos - 1); i < tamMano - 1; i++) {
                mano[i] = mano[i + 1];
            }
            tamMano--;
            descarte.push(c);
            cout << "JUGAR " << pos << " -> " << c.id << " (energia=" << energia << ")";

            if (!horda.vacia()) {
                Enemigo& f = horda.frenteRef();
                int dano = minimo(c.ataque, f.vidaActual);
                f.vidaActual = f.vidaActual - dano;
                if (f.vidaActual == 0) {
                    cout << " MATA " << f.id;
                    horda.desencolar();
                }
            }
            if (c.efecto == CURACION) {
                int n = minimo(3, 30 - vida);
                vida = vida + n;
                if (n >= 1) {
                    cout << " CURA +" << n;
                }
            }
            cout << endl;
            if (horda.vacia() && victoriaImpresa == false) {
                cout << "VICTORIA\n";
                victoriaImpresa = true;
            }
        } else if (cmd == "DESCARTAR") {
            if (derrota == true) continue;
            if (hayArg == false || hayExtra == true) {
                cerr << "falta un argumento o sobra un argumento\n";
                continue;
            }
            if (!validarPos(arg, pos)) {
                cerr << "posicion invalida\n";
                continue;
            }
            if (pos < 1 || pos > tamMano) {
                cout << "DESCARTAR " << arg << " -> POS_INVALIDA\n";
                continue;
            }
            Carta c = mano[pos - 1];
            for (int i = (pos - 1); i < tamMano - 1; i++) {
                mano[i] = mano[i + 1];
            }
            tamMano--;
            descarte.push(c);
            cout << "DESCARTAR " << pos << " -> " << c.id << "\n";
        } else if (cmd == "ATACAR") {
            if (derrota == true) continue;
            if (hayArg == true) {
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            if (horda.vacia()) {
                cout << "ATACAR -> HORDA_VACIA\n";
            } else {
                Enemigo& f = horda.frenteRef();
                int dano = minimo(4, f.vidaActual);
                f.vidaActual = f.vidaActual - dano;
                turno++;
                energia = 3;
                cout << "ATACAR -> dmg=" << dano << " turno=" << turno;

                if (f.vidaActual == 0) {
                    cout << " MATA " << f.id;
                    horda.desencolar();
                } else {
                    int n = minimo(f.ataque, vida);
                    vida = vida - n;
                    cout << " CONTRAATAQUE -" << n << " (hp=" << vida << ")";
                    if (vida == 0) {
                        derrota = true;
                    }
                }
                cout << endl;
            }
            if (derrota == true) {
                cout << "DERROTA\n";
            }
            if (horda.vacia() && !victoriaImpresa) {
                cout << "VICTORIA\n";
                victoriaImpresa = true;
            }
        } else if (cmd == "IMPRIMIR_MANO") {
            if (hayArg == true) {
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            if (tamMano == 0) {
                cout << "MANO: (vacia)\n";
                continue;
            } else {
                cout << "MANO:";
                for (int i = 0; i < tamMano; i++) {
                    Carta c = mano[i];
                    cout << " " << c.id;
                }
                cout << endl;
            }
        } else if (cmd == "IMPRIMIR_HORDA") {
            if (hayArg == true) {
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            if (horda.vacia()) {
                cout << "HORDA: (vacia)\n";
            } else {
                cout << "HORDA:";
                int n = horda.tamanio();
                for (int i = 0; i < n; i++) {
                    Enemigo e = horda.desencolar();
                    cout << " " << e.id << "(vida=" << e.vidaActual << ")";
                    horda.encolar(e);
                }
                cout << "\n";
            }
        } else if (cmd == "IMPRIMIR_BESTIARIO") {
            if (hayArg == true) {
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            cout << "BESTIARIO (in-orden):\n";
            if (bestiario.vacio()) {
                cout << "  (vacio)\n";
            } else {
                bestiario.inOrden(cout);
            }
        } else if (cmd == "IMPRIMIR_AVL") {
            if (hayArg == true) {
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            grimorio.guardarRecorridos(cout);
        } else if (cmd == "GUARDAR") {
            if (hayExtra == true) {
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            string ruta = rutaSalida;
            if (hayArg) {
                ruta = arg;
            }
            ofstream archivoOut(ruta);
            if (!archivoOut) {
                cerr << "NO SE PUDO ABRIR ARCHIVO\n";
                continue;
            } else {
                grimorio.guardarRecorridos(archivoOut);
                cout << "GUARDADO " << ruta << "\n";
            }
        } else {
            cerr << "Aviso: comando desconocido " << cmd << "\n";
        }
    }
}