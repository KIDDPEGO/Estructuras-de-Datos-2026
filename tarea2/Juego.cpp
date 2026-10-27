#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "Juego.hpp"
using namespace std;

static bool validarPos(const string& texto, int& valor) {
    
    if(texto.empty()) return false;

    for(unsigned int i=0; i< texto.size(); i++){
        if(texto[i]< '0' || texto[i] > '9' ) return false;
    }

    if(texto[0] == '0' && texto.size() > 1) return false;

    if(texto.size()> 10) return false;
    long n = strtol(texto.c_str(), NULL, 10); 
    if(n > 2147483647) return false;
    valor = (int)n;
    return true;
}
int minimo(int a, int b){
    if(a<b) return a;
    else return b;
}

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
        
        for (unsigned int i = 0; i < cmd.size(); i++){
            if (cmd[i] >= 'a' && cmd[i] <= 'z'){
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
            if(tamMano == 5){
                cout << "ROBAR -> MANO_LLENA\n";
                continue;
            }
            if(mazo.vacia()){
                if(!descarte.vacia()){
                    cout << "RECICLAJE: descarte -> mazo\n";
                    while (!descarte.vacia()) {
                        mazo.push(descarte.pop());
                    }
                }
                else {
                    cout << "ROBAR -> MAZO_VACIO\n";
                    continue;
                }
            }
            Carta c = mazo.pop();
            mano[tamMano]= c;
            tamMano++;
            cout << "ROBAR -> " << c.id << " (mano=" << tamMano << ")" << endl;
        } else if (cmd == "JUGAR") {
            if (derrota) continue;

            if(hayArg == false || hayExtra == true ){
                cerr << "falta un argumento o sobra un argumento\n";
                continue;
            }
            if(!validarPos(arg, pos)){
                cerr << "posicion invalida\n";
                continue;
            }
            if(pos < 1 || pos > tamMano){
                cout << "JUGAR " << arg << " -> POS_INVALIDA\n";
                continue;
            }
            Carta c = mano[pos - 1];
            if(c.coste > energia){
                cout << "JUGAR " << arg << " -> ENERGIA_INSUFICIENTE\n";
                continue;
            }
            energia = energia - c.coste;
            for (int i=(pos - 1); i<tamMano - 1;i++){
                mano[i]=mano[i+1];
            }
            tamMano--;
            descarte.push(c);
            cout << "JUGAR " << pos << " -> " << c.id << " (energia=" << energia <<")";
            
            if(!horda.vacia()){
            Enemigo& f = horda.frenteRef();
            int dano = minimo(c.ataque, f.vidaActual);
            f.vidaActual = f.vidaActual - dano;
            if(f.vidaActual == 0){
                cout << " MATA " << f.id;
                horda.desencolar();
            }
            }
            if(c.efecto == CURACION){
                int n = minimo(3, 30 - vida);
                vida = vida + n;
                if(n >= 1){
                    cout << " CURA +" << n;
                }
            }
            cout << endl;
            if(horda.vacia() && victoriaImpresa == false){
                cout << "VICTORIA\n";
                victoriaImpresa = true;
            }

        }
        else if (cmd == "DESCARTAR") {
            if(derrota == true) continue;
            if(hayArg == false || hayExtra == true ){
                cerr << "falta un argumento o sobra un argumento\n";
                continue;
            }
            if(!validarPos(arg, pos)){
                cerr << "posicion invalida\n";
                continue;
            }
            if(pos < 1 || pos > tamMano){
                cout << "DESCARTAR " << pos << " -> " << arg << "\n";
                continue;
            }
            Carta c = mano[pos - 1];
            for (int i=(pos - 1); i<tamMano - 1;i++){
                mano[i]=mano[i+1];
            }
            tamMano--;
            descarte.push(c);
            cout << "DESCARTAR " << pos << " -> " << c.id << "\n";

        }
        else if (cmd == "ATACAR") {
            if(derrota == true) continue;
            if(hayArg == true){
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            if(horda.vacia()){
                cout << "ATACAR -> HORDA_VACIA\n";
            }
            else {
                Enemigo& f = horda.frenteRef();
                if(!horda.vacia()){
                    Enemigo& f = horda.frenteRef();
                    int dano = minimo(4, f.vidaActual);
                    f.vidaActual = f.vidaActual - dano;
                    turno++;
                    energia = 3;
                    cout << "ATACAR -> dmg=" << dano << " turno=" << turno;
                }
                if(f.vidaActual == 0){
                    cout << " MATA "<< f.id;
                    horda.desencolar();
                }
                else {
                    int n = minimo(f.ataque, vida); 
                    vida = vida - n;
                    cout << " CONTRAATAQUE -" << n << " (hp=" << vida << ")";
                    if(vida == 0){
                        derrota = true;
                        }
                    }
                    cout << endl;
                }
            if(derrota == true){
                cout << "DERROTA\n";
            }
            if(horda.vacia() && !victoriaImpresa){
                cout << "VICTORIA\n";
                victoriaImpresa = true;
            }
        }
        else if (cmd == "IMPRIMIR_MANO") {
            if(hayArg == true){
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            if (tamMano == 0) {
                cout << "MANO: (vacia)\n";
                continue;
            }
            else {
                cout << "MANO:";
                for (int i = 0; i < tamMano; i++) {
                    Carta c = mano[i];
                    cout << " " << c.id;
                }
                cout << endl;
            }
        }
        else if (cmd == "IMPRIMIR_HORDA") {
            if(hayArg == true){
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            if(horda.vacia()){
                cout << "HORDA: (vacia)\n";
            }
            else{
                cout << "HORDA:";
                int n = horda.tamanio();
            for (int i = 0; i < n; i++) {
                Enemigo e = horda.desencolar();
                cout << " " << e.id << "(vida=" << e.vidaActual << ")";
                horda.encolar(e);
                }
                cout << "\n";
            }
        }
        else if (cmd == "IMPRIMIR_BESTIARIO") {
            if(hayArg == true){
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            cout << "BESTIARIO (in-orden):\n";
            if(bestiario.vacio()){
                cout << "  (vacio)\n";
            }
            else {
                 bestiario.inOrden(cout);
            }
        }
        else if (cmd == "IMPRIMIR_AVL") {
            if(hayArg == true){
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            grimorio.guardarRecorridos(cout);
        }
        else if (cmd == "GUARDAR") {
            if(hayExtra == true){
                cerr << "ARGUMENTO EXTRA\n";
                continue;
            }
            string ruta = rutaSalida;
            if(hayArg){
                ruta = arg;
            }
            ofstream archivo(ruta);
            if (!archivo) {
                cerr << "NO SE PUDO ABRIR ARCHIVO\n";
                continue;
            }
            else {
                grimorio.guardarRecorridos(archivo);
                cout << "GUARDADO " << ruta << "\n";
            }
        }
        else {
            cerr << "Aviso: comando desconocido " << cmd << "\n";
        }
    }
}
