# Tarea 2 Estructuras-de-Datos-2026

Repositorio de tareas - Estructuras de Datos (INF-20325) 2026-2 | UTFSM

## Integrantes
- Joaquín Pego Guerrero
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
./tarea2 <inicio.txt> <comandos.txt> <arbol.txt>
argv[1]: archivo de inicio.
argv[2]: archivo de comandos de la partida.
argv[3]: ruta por defecto de GUARDAR cuando se invoca sin argumento.
## Pruebas de memoria

```bash
valgrind --leak-check=full --show-leak-kinds=all ./tarea2 inicio.txt partida.txt arbol.txt
```

## Mapeo mecánica → TDA

