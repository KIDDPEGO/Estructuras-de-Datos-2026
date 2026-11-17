# Tarea 3 Estructuras-de-Datos-2026

Repositorio de tareas - Estructuras de Datos (INF-134) 2026-2 | UTFSM

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
   de adyacencia; el método `cargarDesdeArchivo` de `Digrafo` hace lo mismo con `flujos.txt`.
2. **Estructuración en memoria**: el grafo no dirigido queda como un arreglo de `|V|` listas
   dinámicas, una por centro (guardando cada arista `u v` en ambos sentidos). El digrafo
   pesado almacena en cada lista únicamente los arcos salientes `u -> v` con su peso.
3. **Ejecución de consultas**: se procesan secuencialmente `SUGERIR`, `HUB`, `ZONAS`,
   `COBERTURA`, `CRITICOS`, `RUTA` y `CONGESTION`. Las funciones de análisis viven
   en `Logistica` y reciben el grafo o digrafo como parámetro, manteniendo el encapsulamiento.
4. **Exportación**: los resultados se escriben en `salida.txt`, con las listas en
   orden ascendente de ID, `NINGUNO` cuando una lista queda vacía e `INALCANZABLE`
   cuando no existe camino entre origen y destino.

## Características técnicas

- **Compilador:** g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
- **Estándar de C++:** C++17 (fijado en el `Makefile`)
- **Sin STL:** no se usa ningún contenedor ni `<algorithm>`. Todas las estructuras
  son propias y se declaran en `EstructurasAuxiliares.hpp`.
- **Compilación:** mediante `make` (targets `all`, `run`, `clean`) y también mediante:
  ```bash
  g++ main.cpp Grafo.cpp Digrafo.cpp Logistica.cpp -o tarea3 -Wall -Wextra -std=c++17