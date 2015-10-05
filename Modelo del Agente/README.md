# Diseño del agente
## Percepciones
1. Si en algunas de las casillas adyacentes existe un obstáculo.
2. Si alguna de las casillas adyacentes está vacía.
3. Peso de las casillas adyacentes, en caso de haber sido recorridas.
4. Si alguna de las casillas adyacentes es la de llegada.

## Acciones
1. Desplazarse siempre a la casilla que tenga menos coste.
2. Si existen varias casillas con el mismo coste, desplazarse aleatoriamente.
3. Si se encuentra sobre la casilla salida, terminar la ejecución.
4. 

## Objetivos
1. Recorrer un camino entre un punto **A** y un punto **B**.
2. Evitar obstáculos de manera inteligente.
3. Utilizar la cantidad mínima de pasos.


## Entorno
1. El agente se desplaza por una matriz.
2. Tienen obstáculos definidos aleatoriamente.
3. Siempre se asegurará la existencia de un camino entre los puntos **A** y **B**.
4. Las casillas recorridas se colorearán según la cantidad de veces que se pase sobre las mismas.
5. Al exceder el tamaño de la matriz, se considerará como una pared.