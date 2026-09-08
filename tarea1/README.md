# Estructuras-de-Datos-2026

Repositorio de tareas - Estructuras de Datos (INF-20325) 2026-2 | UTFSM

## Integrantes

- Luciano Cantillana Salinas
- Joaquín Pego Guerrero

## Descripción del proyecto

El programa reconstruye un documento el cual está fragmentado en un binario
mediante chunks, lo estructura en memoria usando tres TDA jerárquicos, y
luego aplica una secuencia de comandos de edición (fusiones, inserciones,
borrados, etc). El programa consta de 4 fases:

1. **Carga y reconstrucción binaria** (cargarDesdeBinarioChunks): lee el
   .bin por bloques de tamaño fijo y reconstruye las líneas de cada
   párrafo.

2. **Estructuración en memoria**: los párrafos quedan en una lista
   doblemente enlazada (tDocumento), y cada uno con sus líneas en una
   lista simplemente enlazada (tParrafo).

3. **Edición por comandos y reflow** (procesarArchivoComandos): ejecuta
   FUSIONAR_LINEA, APPEND_LINEA, INSERTAR_CHAR y BORRAR_CHAR desde
   un archivo de texto, disparando también las funciones reflowInsertar y
   reflowBorrar en cascada para asegurarse de que todas las líneas queden
   con el formato de 30 caracteres.

4. **Exportación** (exportarTextoPlano): escribe el resultado final a un
   archivo .txt plano mediante el comando GUARDAR.

## Características técnicas

- **Compilador:** g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
- **Estándar de C++:** C++11
- **Compilación:** mediante make (targets all, run, clean) y también
  mediante:
  ```bash
  g++ main.cpp tListaCaracteres.cpp tParrafo.cpp tDocumento.cpp -o tarea1 -Wall
  ```
- **Sistema operativo utilizado para desarrollo y pruebas:** Windows 11 con
  WSL2 (Ubuntu 24.04.1 LTS), kernel 6.6.87.2-microsoft-standard-WSL2

## Estructura de archivos

```
tListaCaracteres.hpp / .cpp   -> TDA Nivel 1: arreglo dinámico de caracteres
tParrafo.hpp / .cpp           -> TDA Nivel 2: lista simple de líneas + reflow
tDocumento.hpp / .cpp         -> TDA Nivel 3: lista doble de párrafos,
                                  carga binaria, comandos y exportación
main.cpp                      -> Orquesta las 4 fases del programa
Makefile                      -> targets: all, run, clean
comandos.txt / documento.bin  -> Caso de prueba de ejemplo
resultado.txt                 -> Salida esperada para el caso de prueba
```

## Pruebas de memoria

```bash
valgrind --leak-check=full ./tarea1 documento.bin comandos.txt salida.txt
```

## Decisiones de diseño

- **Indexación:** las columnas dentro de una línea (tListaCaracteres,
  INSERTAR_CHAR, BORRAR_CHAR) son 0-indexadas. Los párrafos y las líneas
  dentro de un párrafo son 1-indexados (FUSIONAR_LINEA, APPEND_LINEA,
  obtenerLinea).
