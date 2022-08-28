#PCSA/HyperLogLog
Estimación de cardinalidad para un stream utilizando PCSA y HyperLogLog.

## Compilación
Compilar fichero con: g++ *.cpp -std=c++17 -o count_distinct

## Ejecución
./count_distinct <nombre_del_archivo> <estimador>

### Donde <estimador> puede ser:
- HLL.
- PCSA.
- Si no se especifíca, se ejecutan ambos.


