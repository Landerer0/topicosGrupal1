# PCSA/HyperLogLog
Estimación de cardinalidad para un stream utilizando PCSA y HyperLogLog.

## Compilación
Compilar fichero con: g++ *.cpp -g -O3 -lm -std=c++17 -fopenmp -Wall -o count_distinct

## Ejecución
./count_distinct [nombre_del_archivo_1] [nombre_del_archivo_2]



