# Harry Potter y los Monstruos del Laberinto
## Tabla de Contenido
1. **[Escenario](#escenario)**
2. **[Agentes](#agentes)**
    1. **[Harry Potter](#harry-potter)**
        1. **[Percepciones](#percepciones)**
        2. **[Acciones](#acciones)**
        3. **[Objetivos](#objetivos)**
        4. **[Entorno](#entorno)**
    2. **[Monstruos](#monstruos)**
        1. **[Percepciones](#percepciones-1)**
        2. **[Acciones](#acciones-1)**
        3. **[Objetivos](#objetivos-1)**
        4. **[Entorno](#entorno-1)**
3. **[Tipología de Arquitectura del Software](#tipología-de-arquitectura-del-software)**
4. **[Notas](#notas)**

## Escenario
Nuestro escenario se basa en la cuarta parte de la saga Harry Potter, El Cáliz de Fuego, donde el protagonista tiene que encontrar una copa dentro de un laberinto para poder ganar. Dentro del mismo, se encontrará con diversos enemigos.

## Agentes

### Harry Potter
Harry Potter, el niño que sobrevivió, tendrá que llegar hasta una copa dentro de un laberinto, en el cual deberá hacer frente a enemigos y sobrevivir a ellos.

#### Percepciones
* Si en alguna de las casillas adyacentes existe una pared.
* Si en alguna de las casillas adyacentes existe algun seto<sup>[1](#seto)</sup>.
* Si en alguna de las casillas adyacentes existe algún monstruo.
* Si la casilla actual es una Gragea Bertie Bott<sup>[2](#gragea)</sup>.
* Si la casilla actual es la Copa de los Tres Magos<sup>[3](#copa)</sup>.
* Cantidad de energía actual.
* Coordenadas de las Grageas encontradas hasta el momento.
* Coordenadas de los monstruos encontrados hasta el momento.
* Porcentaje descubierto del mapa.

#### Acciones
* Ocupar la casilla adyacente con menos coste.
* No ocuparla si es una pared o un seto.
* Si hay varias elegir una aleatoriamente.
* Si hay un monstruo en el medio del camino:
    * Atacar (dependiendo de una serie de parámetros).
    * Huir (dependiendo de una serie de parámetros).
* Buscar una gragea si queda poca energía.

#### Objetivos
* Sobrevivir
* Encontrar la Copa de los Tres Magos

#### Entorno
* El laberinto

### Monstruos
Los monstruos son los enemigos. Como no son muy listos, caminarán de forma aleatoria, y en caso de toparse con un agente que no sea otro Mounstro, avisará a sus amigos y atacará durante un tiempo.

#### Percepciones
* Si en alguna de las casillas adyacentes existe una pared.
* Si en alguna de las casillas adyacentes existe algun seto.
* Si en alguna de las casillas adyacentes existe algún agente.
* Si se escucha el aullido de otro monstruo y su origen.

#### Acciones
* Moverse aleatoriamente a casillas adyacentes por defecto.
* No ocuparla si es una pared o un seto.
* Si en un radio de 2 casillas hay un agente que no sea un monstruo, aullar y atacar.
* Moverse hacia él si está en un radio de 3 casillas.
* Olvidarse si está a más de 3 casillas.
* Si se es atacado, morirse

#### Objetivos
* Detectar enemigos e ir a por ellos.

#### Entorno
* El laberinto

## Tipología de Arquitectura del Software
El agente elegido es **Harry Potter**. Harry va a tener que ir que ir descubriendo el mapa, e ir recordando por donde puede serguir avanzando y qué lugares ya ha recorrido. Además de esto, tendrá que decidir si atacar monstruos en depedencia de varios factores, como la cantidad de grageas descubiertas y no usadas, cantidad de energía que le queda, porcentaje descubierto del mapa, etc. Por ejemplo, si se encontrase un monstruo y sólo queda una energía restante, pero el porcentaje descubierto del mapa es muy alto, podría decidir atacar al monstruo ya que le queda muy poco para llegar a la Copa y podría merecer la pena el riesgo.

Por estos motivos, debemos elegir un **agente basado en utilidad**.


## Notas
<ol type="1">
<li><a name="seto"><i>Seto</i></a>: Son los obstáculos del laberinto.</li>
<li><a name="gragea"><i>Gragea Bertie Bott</i></a>: Elementos que al ser usados rellenan la parte de la energía.</li>
<li><a name="copa"><i>Copa de los Tres Magos</i></a>: La copa es el destino final del agente, la salida del laberinto.</li>
</ol>

<!---
HOLA SOY UN COMENTARIO
, pero solo podrá hacerles frente a algunos de ellos. Si se agota la barra de energía, podrá recuperar parte de ella con grageas Bertie Bott dispersas por el laberinto. Si Harry no tuviese energía y se encontrase con un enemigo, tendrá que buscar una salida. Los monstruos se moverán cada dos pasos de 
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

-->
