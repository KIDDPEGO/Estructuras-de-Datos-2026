# Estructuras-de-Datos-2026
Repositorio de tareas - Estructuras de Datos (INF-20325) 2026-2 | UTFSM

## Integrantes - Luciano Cantillana Salinas - Nombre Apellido1 Apellido2 (Juako)

El programa reconstruye un documento el cual esta fracmentado en un binaro mediante chunks, lo estructura en memoria usando tres TDA jerárquicos, y luego aplica una secuencia de comandos de edición (fusiones, inserciones, borrados,etc).
el programa consta de 4 fases:

## 1. carga y reconstruccion binaria: 
(cargarDesdeBinarioChunks): lee el .bin por bloques de tamaño fijo y reconstruye las líneas de cada párrafo.
## 2. Estructuración en memoria: 
los párrafos quedan en una lista doblemente enlazada (tDocumento), y cada uno con sus líneas en una lista simplemente enlazada (tParrafo).
