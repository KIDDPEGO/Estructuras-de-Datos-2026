# Tarea 3 Estructuras-de-Datos-2026

Repositorio de tareas - Estructuras de Datos (INF-20325) 2026-2 | UTFSM

## Integrantes

- Joaquín Pego Guerrero - Rol: 202573638-1
- Luciano Cantillana Salinas - Rol: 202511593-k

## Descripción del proyecto

El programa modela la red de centros de distribución de SansaDelivery y responde
consultas sobre ella. Trabaja con dos archivos de datos:

- `datos.txt`: grafo **no dirigido** de conectividad entre centros.
- `flujos.txt`: digrafo **dirigido y pesado** con costos operativos.

Las consultas se leen desde `consultas.txt` y las respuestas se escriben en
`salida.txt`. El programa consta de 4 fases:

1. **Carga de datos**: el constructor de `Grafo` lee `datos.txt` y arma las listas
   de adyacencia; el de `Digrafo` hace lo mismo con `flujos.txt`.

2. **Estructuración en memoria**: el grafo queda como un arreglo de `|V|` listas
   dinámicas, una por centro. Cada arista `u v` se guarda dos veces (`v` en la
   lista de `u` y `u` en la lista de `v`).

3. **Ejecución de consultas**: se procesan en orden `SUGERIR`, `HUB`, `ZONAS`,
   `COBERTURA`, `CRITICOS`, `RUTA` y `CONGESTION`. Las funciones de análisis viven
   en `Logistica` y reciben el grafo como parámetro, sin pertenecer a la clase.

4. **Exportación**: los resultados se escriben en `salida.txt`, con las listas en
   orden ascendente de ID y `NINGUNO` cuando una lista queda vacía.

<!-- Joaquín: ajustar los nombres de las fases 1 y 4 si el main las organiza distinto. -->

## Características técnicas

- **Compilador:** g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
- **Estándar de C++:** C++17 (el que fija el Makefile)
- **Sin STL:** no se usa ningún contenedor ni `<algorithm>`. Todas las estructuras
  son propias y se declaran en `EstructurasAuxiliares.hpp`.
- **Compilación:** mediante make (targets `all`, `run`, `clean`) y también mediante:
  ```bash
  g++ -Wall -Wextra -std=c++17 -o tarea3 main.cpp Grafo.cpp Digrafo.cpp Logistica.cpp
  ```
- **Sistema operativo utilizado para desarrollo y pruebas:** Windows 11 con
  WSL2 (Ubuntu 24.04.1 LTS)

<!-- Ambos: confirmar versión de kernel de WSL2 y el estándar que quedará en el Makefile final. -->

## Estructura de archivos

```
Tipos.hpp                       -> structs Arista y NodoHeap, constante INFINITO
EstructurasAuxiliares.hpp/.cpp  -> Lista<T>, tCola<T>, tPila<T> y MinHeap
Grafo.hpp / .cpp                -> TDA Grafo no dirigido (listas de adyacencia)
Digrafo.hpp / .cpp              -> TDA Digrafo pesado
Logistica.hpp / .cpp            -> las 7 funciones de consulta
main.cpp                        -> lectura de consultas y escritura de salida.txt
Makefile                        -> targets: all, run, clean
Repositorio.txt                 -> enlace al repositorio privado
```

`EstructurasAuxiliares.cpp` solo incluye el `.hpp`, porque todas las estructuras son
plantillas o clases con los métodos dentro de la declaración. Así el proyecto
también compila si el comando no incluye ese `.cpp`.

## Ejecución

<!-- Joaquín: completar con los argumentos reales de main (datos, flujos, consultas, salida). -->

```bash
make          # compila y genera el ejecutable tarea3
make run      # compila y ejecuta
make clean    # borra los objetos, el ejecutable y salida.txt
```

## Pruebas de memoria

```bash
valgrind --leak-check=full --show-leak-kinds=all ./tarea3
```

## Mapeo mecánica → TDA

| Mecánica del problema | TDA | Archivos |
|---|---|---|
| Red de centros y rutas directas (no dirigida) | Grafo | Grafo.hpp/.cpp |
| Vecinos de cada centro | Lista\<int\> (arreglo dinámico) | EstructurasAuxiliares.hpp |
| Exploración por saltos (SUGERIR, COBERTURA, ZONAS, CRITICOS) | Cola tCola\<int\> en un BFS | EstructurasAuxiliares.hpp, Logistica.cpp |
| Conjuntos de centros resultantes, en orden ascendente | Lista\<int\> con `ordenar()` | EstructurasAuxiliares.hpp |
| Red de flujos y costos | Digrafo | Digrafo.hpp/.cpp |
| Selección del nodo de menor costo en Dijkstra | MinHeap | EstructurasAuxiliares.hpp |
| Análisis de la red | — | Logistica.hpp/.cpp |

- **Grafo con listas de adyacencia:** la red es dispersa (pocas aristas por nodo), así
  que una lista por nodo ocupa O(V+E) de memoria y recorrer los vecinos de un nodo
  cuesta solo su grado.
- **Lista como arreglo dinámico:** el grado de un nodo no tiene límite conocido, así que
  el arreglo duplica su capacidad al llenarse y no impone un máximo arbitrario.
  El acceso por posición es O(1), y eso permite que `vecino(v, i)` sea directo.
- **Cola para el BFS:** los nodos más cercanos al origen deben salir primero, y eso es
  exactamente el orden FIFO. Por eso `dist` guarda la distancia mínima en saltos.
- **Pila:** `tPila` está implementada en `EstructurasAuxiliares.hpp`, pero las funciones
  1 a 5 no la usan, porque CRITICOS se resuelve sin DFS (ver decisiones de diseño).

## TDA Grafo

Es una clase que solo guarda la red y deja consultarla. Las funciones de análisis no
van dentro, sino en `Logistica`.

| Atributo (privado) | Descripción |
|---|---|
| `int n` | cantidad de nodos (`\|V\|`) |
| `Lista<int>* adyacencia` | arreglo de `n` listas; `adyacencia[u]` contiene los vecinos de `u` |

| Método | Qué hace |
|---|---|
| `Grafo(const char*)` | abre el archivo, lee `\|V\|` y `\|E\|`, reserva las listas y carga las aristas en ambos sentidos |
| `~Grafo()` | un solo `delete[]`; cada `Lista` libera su propio arreglo |
| `numNodos()` | devuelve `n` |
| `grado(v)` | devuelve el tamaño de la lista de `v` |
| `vecino(v, i)` | devuelve el i-ésimo vecino de `v`, por valor |

Ningún método devuelve la lista ni un puntero al arreglo interno, así que el
encapsulamiento se mantiene. Los IDs van de 0 a `\|V\|-1`, por lo que sirven
directamente como índice.

## Funciones de Logistica (1 a 5)

| Función | Cómo funciona |
|---|---|
| `sugerir_rutas_alternativas` | BFS desde el centro y se agregan a la lista los nodos con `dist == 2`; luego `ordenar()` |
| `centro_mas_conectado` | recorre los nodos guardando el de mayor grado; el `>` estricto hace que un empate lo gane el menor ID |
| `contar_zonas_logisticas` | cuenta componentes conexas: cada nodo sin visitar inicia una exploración nueva |
| `calcular_cobertura` | BFS desde el centro y se cuentan los nodos con `dist` igual a 1 o 2 |
| `centros_criticos` | para cada nodo, lo bloquea y compara la cantidad de zonas con la original |

Funciones auxiliares, `static` y solo visibles dentro de `Logistica.cpp`:

- **`explorar(g, origen, dist)`**: BFS que *no* reinicia `dist`. Avanza únicamente por
  los nodos cuya casilla vale `-1`.
- **`bfs(g, origen, dist)`**: llena `dist` con `-1` y llama a `explorar`.
- **`zonas_sin_nodo(g, removido)`**: cuenta zonas tratando un nodo como inexistente.

En el arreglo `dist`, `-1` significa "no visitado", un valor mayor o igual a 0 es la
distancia en saltos al origen, y `-2` marca un nodo bloqueado.

## Complejidades

Sea V la cantidad de nodos, E la de aristas, k la cantidad de elementos de una lista
y n la de una cola.

| Operación | Complejidad | Justificación |
|---|---|---|
| Lista: `obtener`, `tamano` | O(1) | acceso directo al arreglo |
| Lista: `agregar` | O(1) amortizado | solo escribe al final; cuando se llena, duplicar la capacidad cuesta O(k), pero ocurre pocas veces |
| Lista: `clear` | O(k) | libera el arreglo y reserva uno nuevo de capacidad 1 |
| Lista: `ordenar` | O(k²) peor caso, O(k) si ya está ordenada | inserción directa: cada elemento se desplaza solo sobre los mayores que él |
| Cola: `encolar`, `desencolar`, `vacia` | O(1) | se mantienen punteros al frente y al fin, sin recorridos |
| Cola: `clear` | O(n) | libera cada nodo una vez |
| Grafo: constructor | O(V+E) | lee `E` aristas y cada una hace dos `agregar` amortizados O(1); reservar las listas cuesta O(V) |
| Grafo: `numNodos`, `grado`, `vecino` | O(1) | acceso por índice a una lista |
| `explorar` | O(V+E) | cada nodo entra a la cola una sola vez (porque deja de valer `-1`) y la suma de los grados es 2E |
| `bfs` | O(V+E) | llenar `dist` cuesta O(V) y luego `explorar` |
| `centro_mas_conectado` | O(V) | una pasada por los nodos, con `grado` en O(1) |
| `contar_zonas_logisticas` | O(V+E) | `dist` no se reinicia, así que entre todas las llamadas a `explorar` cada nodo y cada arista se recorren una vez |
| `calcular_cobertura` | O(V+E) | un BFS y una pasada de O(V) |
| `sugerir_rutas_alternativas` | O(V+E) | un BFS y una pasada de O(V); los nodos se agregan en orden ascendente de ID, así que `ordenar()` recibe la lista ya ordenada y cuesta O(k) |
| `centros_criticos` | O(V·(V+E)) | calcula las zonas originales en O(V+E) y repite `zonas_sin_nodo`, que es O(V+E), una vez por cada nodo |

<!-- Joaquín: agregar aquí las filas de Digrafo, MinHeap, RUTA y CONGESTION. -->

## Decisiones de diseño

- **Funciones de análisis fuera del Grafo:** `Grafo` solo expone `numNodos`, `grado` y
  `vecino`. Con esas tres consultas, `Logistica` puede recorrer toda la red.
- **Cada arista se guarda dos veces:** el grafo es no dirigido, así que la línea `u v`
  agrega `v` a la lista de `u` y `u` a la de `v`. La suma de todos los grados
  debe dar `2·\|E\|`, y se usó como comprobación (42 en el ejemplo del enunciado).
- **Copia deshabilitada:** `Grafo`, `Lista`, `tCola` y `tPila` declaran privados (o
  `delete`) el constructor de copia y el `operator=`. Dos objetos que compartieran el
  mismo arreglo harían doble `delete[]`.
- **`dist` hace de lista de visitados:** un solo arreglo guarda la distancia y, a la vez,
  indica si un nodo ya fue descubierto, así que no hace falta un arreglo `bool` aparte.
- **`explorar` separado de `bfs`:** para contar zonas hay que no reiniciar `dist` entre
  una componente y la siguiente, por lo que el llenado con `-1` se hace fuera de
  `explorar`.
- **CRITICOS por remoción de nodo, en vez de DFS con low-link:** el algoritmo de
  puntos de articulación con DFS y valores low-link cuesta O(V+E), mejor que el
  O(V·(V+E)) de esta versión. Se eligió la remoción por ser más simple de escribir y de
  verificar, reutilizar `explorar` y `contar_zonas_logisticas`, y no requerir DFS
  recursivo ni pila explícita. Un nodo `v` es crítico cuando, al bloquearlo, hay
  **más** zonas que las originales; la comparación es `>` y no `!=` porque quitar un
  nodo aislado reduce las zonas en 1 sin dividir nada.
- **Bloqueo de nodos con `-2`:** `explorar` solo avanza por nodos con `-1`, así que
  marcar uno con `-2` lo deja fuera del recorrido sin modificar el `Grafo`.
- **Listas de resultados recibidas por referencia:** `sugerir_rutas_alternativas` y
  `centros_criticos` reciben una `Lista<int>&` y la llenan, porque la copia de `Lista`
  está deshabilitada y no puede devolverse por valor. Quien llama debe pasar una
  lista vacía en cada consulta. La palabra `NINGUNO` la imprime `main` cuando
  `resultado.tamano() == 0`.
- **Sin validaciones de archivo:** el enunciado garantiza que los archivos existen y están
  bien formados, y que no hay aristas repetidas ni auto-ciclos.


Se compiló con `-Wall -Wextra` sin warnings y se revisó con Valgrind sin fugas de memoria.
