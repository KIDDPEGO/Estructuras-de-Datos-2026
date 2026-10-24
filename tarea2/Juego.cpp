#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
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

void procesarComandos(const string& rutaComandos, const string& rutaSalida,
                      Carta mano[5], int& tamMano,
                      tPila& mazo, tPila& descarte,
                      tCola& horda,
                      tAVL& grimorio, tABB& bestiario) {

    ifstream archivo(rutaComandos);
    string linea;
    bool derrota = false;

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
            cerr << "TODO JUGAR\n";
        }
        else if (cmd == "ATACAR") {
            cerr << "TODO ATACAR\n";
        }
        else if (cmd == "DESCARTAR") {
            cerr << "TODO DESCARTAR\n";
        }
        else if (cmd == "IMPRIMIR_MANO") {
            cerr << "TODO IMPRIMIR_MANO\n";
        }
        else if (cmd == "IMPRIMIR_HORDA") {
            cerr << "TODO IMPRIMIR_HORDA\n";
        }
        else if (cmd == "IMPRIMIR_BESTIARIO") {
            cerr << "TODO IMPRIMIR_BESTIARIO\n";
        }
        else if (cmd == "IMPRIMIR_AVL") {
            cerr << "TODO IMPRIMIR_AVL\n";
        }
        else if (cmd == "GUARDAR") {
            cerr << "TODO GUARDAR\n";
        }
        else {
            cerr << "Aviso: comando desconocido " << cmd << "\n";
        }
    }
}
