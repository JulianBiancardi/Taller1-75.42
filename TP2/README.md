# TP2 - Verificador eBPF

- Materia: Taller de Programación I (75.42)
- Año y cuatrimestre: 2°C 2020
- Alumno: Biancardi, Julián
- Padrón: 103945
- [Link al repositorio](https://github.com/JulianBiancardi/tp2)

# Indice   
1. [Introducción](#id1)
2. [Especificaciones](#id2)
3. [Restricciones](#id3)
4. [Desarrollo](#id4)
5. [Flujo general](#id5)
6. [Conclusiones](#id6)

## 1. Introducción<a name="id1"></a>
En el siguiente informe se detallara todos los pasos seguidos para la resolucion del trabajo practico 2 de la materia Taller de Programacion 1, como asi tambien los detalles de implementacion. 

El mismo consiste en la implementacion de un verificador de programas eBPF. El mismo verificará la existencia o no
de bucles de código y/o instrucciones sin ejecutar.
Un programa eBPF con bugs o mal intencionado podría corromper al kernel o como mínimo colgar la
máquina. Es por esto mismo que el verificador debe detectar operaciones de memoria inválidos,
bucles de código que podrían colgar el sistema entre otras acciones que podrían degradar la performance
del sistema o incluso corromperlo.

## 2. Especificaciones<a name="id2"></a>

El programa se ejecutará pasando por línea de comandos recibiendo la cantidad de hilos y luego uno o más
archivos:


- Formato de línea de comando:

        ./tp <num hilos> <archivo> [<archivo>...]


El verificador de programas procesara los archivos pasados por línea de comandos y determinar si
tienen ciclos y/o instrucciones sin usar. Luego de esto imprimirá por salida estandar(std::cout) el nombre de cada archivo procesado y un mensaje indicando los resultados

- Salidas:

    `GOOD`​ en el caso de no haberse encontrado ciclos ni instrucciones sin uso.

    `FAIL: cycle detected`​ en el caso de haberse detectado un ciclo

    `FAIL: unused instructions detected`​ en el caso de instrucciones sin uso.
    
Si un programa eBPF tuviese ciclos e instrucciones sin uso, el verificador solo imprimirá el mensaje correspondiente al de los ciclos.

## 3. Restricciones<a name="id3"></a>

La siguiente es una lista de restricciones técnicas:
1. El sistema debe desarrollarse en **ISO C++11**.
2. Está prohibido el uso de **variables globales**.
3. Deberá haber un ​ **único objeto compartido​** que tenga los archivos y serán los hilos de
procesamiento que le irán pidiendo un archivo a la vez para procesarlos.
4. Deberá haber un ​ **único objeto compartido​** que guarde los resultados a medida que los hilos los
vayan generando. Al terminar todos los archivos, se imprimen de ahí los resultados por pantalla.

### 3.1 Supuestos

La siguiente es una lista de los supuestos adoptados para la resolución del trabajo:
1. La lina de comando puede contener nombres de archivos repetidos, por lo que la salida se obtendrá resultados repetidos.
2. Archivos vacios se consideran sin ciclos ni con instrucciones no usadas por lo tanto son correctos.
3. Archivos inexistentes se consideran sin ciclos ni con instrucciones no usadas por lo tanto son correctos.
4. Se garantiza que todos los programas eBPF serán siempre válidos sintacticamente para simplificar la implementación.

## 4. Desarrollo<a name="id4"></a>

En este apartado se explicaran a fondo los detalles de implementacion realizados para poder llevar a cabo el trabajo.

### 4.1 Parser

A partir del archivo de texto, que contendra el programa eBPF, debemos detectar las instrucciones necesarias para luego generar el grafo que nos ayudará a saber si contiene ciclos o instrucciones sin uso.

Para realizar esto contamos con la clase `Parser` que contiene las siguientes funcionalidades:

- **detect_label**: nos dará el label de la instruccion si es que tiene.
- **iterate**: a partir de una linea de codigo  nos dará los argumentos que contiene esta misma. Para poder entender mejor esto se explicará mediantes el siguiente caso general:
  - `label: inst <argumento> .... <argumento>` : nos devuelve solamente la instrucción más los argumentos, el label será descartado.

### 4.2 Grafo dirigido

Para el trabajo se optó por la implementacion de un grafo dirigido mediante una **lista de adjacencia**. Para esto tenemos una clase `Graph` la cual contiene las siguientes funcionalidades:

- **add_edge**: agrega una arista entre en el nodo inicio (start) y nodo fin (end).
- **cyclic**: nos dice si el grafo dirigido contiene al menos un ciclo.
- **nonreachable**: nos dice si a partir del nodo cabezera (head), hay algunos nodos no accesibles.
- **print**: muestra el grafo por salida estandar. Necesario para debuggear.

### 4.3 eBPF Verifier

Para la verificacion del codigo eBPF se realiza la técnica de doble pasada:

1. En una primera pasada generamos la tabla de simbolos. Esta misma contendrá las etiquetas con su respectivo valor de contador de programa (pc). Para esto usamos un [map](http://www.cplusplus.com/reference/map/map/) de la forma `<clave,valor>` donde:
- la clave sera la etiqueta/label,
- el valor sera la linea de codigo donde se encuentra la misma.

2. Una vez generado la tabla de simbolos, realizamos una segunda pasada. En esta segunda pasada obtendremos ,para cada instruccion, los argumentos necesarios para generar el grafo correspondiente. Para esto tendremos los siguientes casos:

- `inst <argumento>`: se debe generar una arista entre esta linea de codigo y la siguiente.
- `inst <argumento> ... <argumento>`: se debe generar una arista entre esta linea de codigo y la siguiente.
- `jump <etiqueta>`: se debe generar una arista entre esta linea de codigo y la linea de codigo que contenga la etiqueta.
- `jump <argumento> <etiqueta>`: se debe generar dos aristas, una entre esta linea de codigo y la siguiente y otra con la linea de codigo que contenga la etiqueta.
- `jump <argumento> <etiqueta1> <etiqueta2>`: se debe generar dos aristas cada una correspondiente a la linea de codigo que contenga cada etiqueta.
- `ret <argumento>`: no se debe generar ninguna arista, marcando asi el fin de programa.

Para los dos primeros ejemplos, las instrucciones no eran de salto. Para los demas ejemplos, la generalizacion de la instruccion jump pueden ser: `jmp,ja,jeq,jneq,jne,jlt,jle,jgt,jge,jset`.

Notar que para algunas instrucciones debemos generar una arista entre la linea de codigo actual y la linea de codigo que contenga la etiqueta en cuestión. Es por esto mismo que resulta muy util la tabla de simbolos generada en la primera pasada para poder conocer las posiciones de cada etiqueta nombrada en el codigo.

3. Luego de haber generado el grafo del codigo eBPF procedemos a verificar si contiene ciclos o instrucciones sin uso utilizando los metodos de la misma clase `Graph`.

- **isCyclic**: nos dice si el programa eBPF contiene ciclos.
- **isnonReachable**: nos dice si el programa eBPF contiene instrucciones sin uso.


### 4.5 Monitores

Ya explicamos como se puede usar la clase `ebpfVerifier` para saber si un programa eBPF contiene ciclos o instrucciones sin uso. Extrapolando esto, podemos verificar varios archivos pasados por la linea de comando.

Ahora esto ultimo seria puesto en marcha con un solo hilo de ejecución, el hilo main.

Como vimos en la sección `Especificaciones`, la linea de comando contendrá la cantidad de hilos con los que el programa sera ejecutado. Para esto se generan dos nuevas clases: `filesContainer` y `resultsContainer`.

### 4.5.1 Contenedor de archivos - Files Container

Esta clase se encargara de contener todos los nobres de archivos **a ser analizados**. Esto es un recuros compartido, puesto que varios hilos intentarán obtener un archivo para poder verificar un archivos con la clase `ebpfVerifier`.

Esta clase tiene las siguientes funcionalidades:

- **add**: agrega un nombre de archivo a la cola. Como se menciono en la seccion `Supuestos`, el contenedor podrá tener nombres de archivos repetidos.
- **getfilename**: obtenemos el primer nombre de archivo presente en la cola. Al ser un recurso compartido, debemos incluir un [mutex](http://www.cplusplus.com/reference/mutex/mutex/) para evitar *races conditions*.

### 4.5.1 Contenedor de resultados - Results Container

Esta clase se encargara de contener los resultados de los analisis realizados por parte de los diferentes hilos de ejecución. Nuevamente esto es un recurso compartido, puesto que varios hilos intentarán guardar su resultado en el contenedor.

Esta clase tiene las siguientes funcionalidades:

- **add**: agrega el resultado de la verificación. Nuevamente al ser un recurso compartido, debemos incluir un [mutex](http://www.cplusplus.com/reference/mutex/mutex/) para evitar *races conditions*.
- **show**: muestra todos los resultados agregados en el contenedor.

### 4.6  Modelo 

A continuacion de muestra un diagrama de clases del modelo general implementado, incorporando todas las clases antes mencionados para poder visualizar como funcionan en conjunto:

![Diagrama general](/imagenes/DiagramaGeneral.png)


En resumen:

- Parser: Encargado de parsear una lina de codigo ebpf.
- Graph: Encargado de la representacion del codigo ebpf en un grafo para la deteccion de ciclos o instrucciones sin uso.
- ebpfVerifier: Encargado de la generacion del grafo a partir de un archivo de texto que contiene el codigo ebpf.
- filesContainer: Encargado de almacenar todos los nombres de archivos a ser analizados.
- resultsContainer: Encargado de almacenar todos los resultados de los analisis.

El modelo consta de 5 clases ,cada uno con responsabilidades claras y un acoplamiento bajo. Esto es un buen indicio si quisieramos reutilizar los TDAs en otro proyecto.


## 5  Flujo general (main)<a name="id5"></a>

En este apartado se explica como es el flujo general del programa.

En una primera instacia se almacenan todos los nombres de archivos que el usuario ingreso por consola de comandos en el contenedor de entrada.

Una vez almacenados todos los nombres se procede a generar la cantidad de hilos ligado al parametro que nuevamente el usuario haya ingresado por consolad de comandos.

Luego se corren los hilos, donde cada uno tomará un archivo del contenedor y lo verificará.Por ultimo, este hilo alamcenará el resultado en el contenedor de salida.

Finalmente se muestran todos los resultados.

## 6. Conclusiones<a name="id6"></a>

Mediante este trabajo aprendimos a programar en el lenguaje C++ y como hacer buen eso de RAII que nos ofrece el mismo. Aprendimos tambien, de manera simplificada, como programar en concurrencia mediante los hilos de ejecución. Como evitar *races conditions* mediante el uso de mutex con su función **lock** mas sus variantes.


