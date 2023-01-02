# Modelo de MonteCarlo para lechería.
Trataremos de simular, mediante un modelo de Monte Carlo, una lechería. La
lechería producirá leche por la mañana, llenará las botellas, las pondrá en el
depósito. A la vez, habrá recido todos los pedidos de esa misma tarde. Una vez
finalizado la mañana se despachará todos los pedidos a los clientes, teniendo en
cuenta que la capacidad de la tienda es limitada y por ello se pueden "rechazar" pedidos,
es decir, tener ventas perdidas.

# Tabla de probabilidades
| 1 euro    | 1.50 euros    | 2 euros   | Demanda   |
| ---       | ---           | ---       | ---       |
| 0.10 | 0.15 | 0.30 | 50 |
| 0.20 | 0.30 | 0.40 | 90 |
| 0.30 | 0.35 | 0.20 | 130 |
| 0.40 | 0.20 | 0.10 | 170  |

Precio del día:
- Más de 125 latas, al día siguiente se vende a 1 euro.
- Menos de 75 latas, al día siguiente la lata se vende a 2 euros.
- En cualquier otro caso, al día siguiente se vende a 1.5 euros.

Se producen por defecto 1000 litros de leche al día, cada botella debe almacenar 10L.

# Como ejecutar
Se recomienda antes de empezar, construir el ejecutable con `cmake . && make`
- `./bin/dairy-store 1 100 20 200 1000 125 75`
    - `streambuffer`: El primer parámetro hace alusión a la salida del programa. 0:terminal, 1:archivo.
        - los archivos se guardan en `resultados/`. Tienen un nombre único asociado a los parámetros.
    - `simulaciones`: El segundo es el número de veces que se simula 30 días de trabajo.
    - `capacidad_actual`: El tercer es la cantidad de botellas al comenzar el primer día.
    - `capacidad_maxima`: El cuarto es el tamaño de nuestro almacén de botellas.
    - [OPCIONALES]: Los siguientes parámetros son opcionales
        - `leches_diario`: El quinto es la cantidad de leche que producimos cada mañana.
        - `MIN_FOR_1`: El sexto es la cantidad mínima de botellas en almacén para que, si tenemos más, vender a 1 euro la botella.
        - `MIN_FOR_2`: El séptimo es la cantidad máxima de botellas en el almacén para que, si tenemos menos vender a 2 euros la botella.
- `resultados/getGraphs.plt`: Si nos vamos a la carpeta `resultados`:
```
gnuplot -e "filename='dairy-N:20-M:500-L:1000-M1:125-M2:75.txt';apartado='ejemplo'" getGraphs.plt
```
- Nos permite generar una gráfica de cada parámetro a estudiar en la carpeta `resultados/graphs/ejemplo` del archivo `dairy-N:20-M:500-L:1000-M1:125-M2:75.txt`.


