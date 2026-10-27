# Tarea 2 Estructuras-de-Datos-2026

Repositorio de tareas - Estructuras de Datos (INF-20325) 2026-2 | UTFSM

## Integrantes
- Joaquín Pego Guerrero Rol: 202573638-1
- Luciano Cantillana Salinas Rol: 202511593-k

## Descripción del proyecto

El programa consiste en un simulador por consola de un juego de cartas por turnos. 
Lee una base de datos inicial, la estructura en memoria usando cuatro TDA, 
y luego ejecuta una secuencia de comandos de partida (robar, jugar, descartar, 
atacar, imprimir y guardar). El programa consta de 4 fases:

1. **Carga inicial** (cargarInicio): lee inicio.txt por secciones
 (@GRIMORIO, @BESTIARIO, @MAZO y @HORDA), valida si el formato es el correcto
  y llena la estructuras. en caso de error de formato imprime [CARGA] ERROR y
  termina con código 2.
   
2. **Estructuración en memoria**: las cartas se guardan en un árbol AVL(grimorio),
   los enemigos en un árbol de búsqueda binario ABB(bestiario),el mazo y el descarte
   en dos pilas, y la horda de enemigos en una cola.
   
3. **Ejecución de comandos** ((procesarComandos)): lee el archivo de comandos linea por linea
   y ejecuta ROBAR, JUGAR, DESCARTAR, ATACAR, IMPRIMIR_MANO, IMPRIMIR_HORDA, IMPRIMIR_BESTIARIO,
   IMPRIMIR_AVL y GUARDAR en orden de aparicion. Tambien lleva el estado de la partida
   (vida del jugador, energía, turno, y las banderas de victoria y derrota).

4. **Exportación** (GUARDAR): escribe en un archivo de texto los recorridos
   pre-orden e in-orden del AVL, anotando la profundidad de cada nodo.

## Características técnicas

- **Compilador:** g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
- **Estándar de C++:** C++11
- **Compilación:** mediante make (targets all, run, clean) y también
  mediante:
  ```bash
  g++ -Wall -std=c++11 -o tarea2 main.cpp Pila.cpp Cola.cpp ABB.cpp AVL.cpp Juego.cpp
  ```
- **Sistema operativo utilizado para desarrollo y pruebas:** Windows 11 con
  WSL2 (Ubuntu 24.04.1 LTS), kernel 6.6.87.2-microsoft-standard-WSL2

## Estructura de archivos

```
Tipos.hpp          -> structs Carta y Enemigo, enum Efecto y operator<< de Enemigo
Pila.hpp / .cpp    -> TDA tPila (LIFO): mazo y descarte
Cola.hpp / .cpp    -> TDA tCola (FIFO): horda de enemigos
ABB.hpp / .cpp     -> TDA tABB: bestiario de enemigos
AVL.hpp / .cpp     -> TDA tAVL: grimorio de cartas
Juego.hpp / .cpp   -> cargarInicio y procesarComandos
main.cpp           -> valida argumentos y orquesta las fases del programa
Makefile           -> targets: all, run, clean
Repositorio.txt    -> enlace al repositorio privado
```
## Ejecucion
```bash
make          # compila y genera el ejecutable tarea2
make run      # compila y ejecuta con inicio.txt partida.txt arbol.txt
make clean    # borra el ejecutable
```
```bash
./tarea2 <inicio.txt> <comandos.txt> <arbol.txt>
```
`inicio.txt` y `partida.txt` son los ejemplos de la Suite A, incluidos solo para que `make run` funcione.

- `argv[1]`: archivo de inicio.
- `argv[2]`: archivo de comandos de la partida.
- `argv[3]`: ruta por defecto de `GUARDAR` cuando se invoca sin argumento.
  
## Pruebas de memoria

```bash
valgrind --leak-check=full --show-leak-kinds=all ./tarea2 inicio.txt partida.txt arbol.txt
```

## Mapeo mecánica → TDA
 
| Mecánica del juego | TDA | Archivos |
|---|---|---|
| Mazo de robo y pila de descarte | Pila tPila  | Pila.hpp/.cpp |
| Horda de enemigos de la sala | Cola tCola | Cola.hpp/.cpp |
| Bestiario de enemigos | Árbol de búsqueda binario tABB | ABB.hpp/.cpp |
| Grimorio de cartas | Árbol AVL tAVL | AVL.hpp/.cpp |
| Mano del jugador | Arreglo estático de 5 Carta (no es TDA) | Juego.cpp |
| Orquestación del juego | — | Juego.hpp/.cpp y main.cpp |
 
Por qué cada estructura:
 
- **Pila para mazo y descarte:** siempre se roba del tope del mazo y se descarta
  sobre el tope del descarte.
- **Cola para la horda:** el enemigo que lleva más tiempo esperando es el que
  recibe los golpes, y al morir sale el primero y avanza el siguiente.
- **ABB para el bestiario:** se consulta por id y se imprime ordenado por id con
  un recorrido in-orden.
- **AVL para el grimorio:** las cartas se buscan por id y se exportan a
  arbol.txt; el balanceo garantiza búsquedas e inserciones en O(log n).
  
## Complejidades
 
Sea n la cantidad de elementos de la estructura.
 
| Operación | Complejidad | Justificación |
|---|---|---|
| Pila: push, pop, topValue | O(1) | solo se modifica o lee el nodo del tope, sin recorrer la lista |
| Pila: clear | O(n) | recorre y libera cada nodo una vez |
| Cola: encolar, desencolar, frenteValue, frenteRef | O(1) | se mantienen punteros al frente y al fin, por lo que no hay recorrido |
| Cola: clear | O(n) | libera cada nodo una vez |
| ABB: insertar, buscar | O(log n) promedio, O(n) en el peor caso | en cada paso se descarta un subárbol; si las claves llegan ordenadas, el árbol degenera en una lista y su altura es n |
| ABB: inOrden, clear | O(n) | visitan cada nodo una vez |
| AVL: insertar, buscar | O(log n) garantizado | el balanceo mantiene \|FB\| ≤ 1 en todo nodo, por lo que la altura es O(log n) y se baja un solo camino |
| AVL: rotación simple o doble | O(1) | reasignan una cantidad fija de punteros y actualizan dos alturas; la doble compone dos simples |
| AVL: recorridos pre-orden e in-orden, clear | O(n) | visitan cada nodo una vez |
| ROBAR sin reciclaje | O(1) | un pop de la pila y una asignación en el arreglo de la mano |
| ROBAR con reciclaje del descarte | O(n) | transfiere carta a carta con pop y push, cada una en O(1) |
| JUGAR, DESCARTAR | O(1) | la mano tiene como máximo 5 cartas, por lo que correr las cartas cuesta una cantidad acotada de pasos; el daño usa frenteRef y desencolar, ambos O(1) |
| ATACAR | O(1) | opera solo sobre el frente de la horda |
| IMPRIMIR_MANO | O(1) | la mano tiene como máximo 5 cartas |
| IMPRIMIR_HORDA | O(n) | rotación completa: desencolar, imprimir y encolar los n enemigos, cada paso en O(1) |
| IMPRIMIR_BESTIARIO | O(n) | recorrido in-orden del ABB |
| IMPRIMIR_AVL, GUARDAR | O(n) | recorridos pre-orden e in-orden del AVL |

## Decisiones de diseño
- **Tipos.hpp:** contiene los struct Carta y Enemigo, se uso enums para los efectos(NINGUNO,
  FUEGO, HIELO, VENENO y CURACION) y el operator<< de Enemigo, declarado inline
  para evitar errores de enlazado por definición múltiple. tampoco se uso tipos.cpp.
