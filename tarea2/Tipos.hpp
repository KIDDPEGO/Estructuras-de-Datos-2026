#ifndef TIPOS_HPP
#define TIPOS_HPP

#include <string>
#include <iostream>

using namespace std;


enum Efecto {NINGUNO, FUEGO, HIELO, VENENO, CURACION};
struct Carta {

    string nombre;
    int id;
    int coste;
    int ataque;
    Efecto efecto;

};



struct Enemigo {

    string nombre;
    int id;
    int vida;
    int ataque;
    int vidaActual;

};

inline ostream& operator<<(ostream &os, const Enemigo &e) {
    os << e.id << " " << e.nombre << " vida=" << e.vida << " atk=" << e.ataque;
    return os;
}


#endif // TIPOS_HPP