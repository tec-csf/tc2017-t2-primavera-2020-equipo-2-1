# Tarea *2*. *Análisis de Algoritmos*

---

##### Integrantes:
1. *Abraham García Del Corral* - *A01023256* - *CSF*
2. *Andrés Barragán Salas* - *A01026567* - *CSF*
3. *Rodrigo Quiroz Reyes* - *A01026546* - *CSF*
4. *[Poner aquí Nombre y Apellidos del integrante 4]* - *[Poner aquí su Matrícula]* - *[Poner aquí su campus]*
5. *[Poner aquí Nombre y Apellidos del integrante 5]* - *[Poner aquí su Matrícula]* - *[Poner aquí su campus]*

---
## 1. Aspectos generales

Las orientaciones de la tarea se encuentran disponibles en la plataforma **Canvas**.

Este documento es una guía sobre qué información debe entregar como parte de la tarea, qué requerimientos técnicos debe cumplir y la estructura que debe seguir para organizar su entrega.


### 1.1 Requerimientos técnicos

A continuación se mencionan los requerimientos técnicos mínimos de la tarea, favor de tenerlos presente para que cumpla con todos.

* El código debe desarrollarse en C++, cumpliendo con el último estándar [C++17](https://isocpp.org/std/the-standard).
* Toda la programación debe realizarse utilizando Programación Genérica.
* Deben utilizarse las [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md).
* Todo el código debe estar correctamente documentado, siguiendo los lineamientos que aparecen en [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html).
* Todo el código de la tarea debe alojarse en este repositorio de GitHub.
* Debe configurar su repositorio para que utilice el sistema de Integración Continua [Travis CI](https://travis-ci.org/).

### 1.2 Estructura del repositorio

El proyecto debe seguir la siguiente estructura de carpetas:
```
- / 			        # Raíz del repositorio
    - README.md			# Archivo con la información general de la actividad (este archivo)
    - sources  			# Códigos fuente con la solución
    - examples			# Archivos de ejemplo que pueden utilizarse para verificar que la solución funciona.
```

## 2. Solución
---
#### Árbol AVL
La solución implementada para la construcción del árbol AVL en memoria se baso en la implementación recursiva de un arbol binario común. Para ello, se crearon nodos simliares a aquellos utilizados en una árbol binario, únicamente que los nodos utilizados en el AVL contienen una variable que almacena la altura que los nodos tienen dentro del arbol. De esta manera, utilizando la altura de los nodos dentro del arbol, un nodo padre puede conocer su factor de balanceo realizando una diferencia entre las alturas de los 2 nodos hijos y dependiendo de hacia donde se encuentre cargado, podrá realizar las rotaciones correspondientes. Se definieron metodos responsables de realizar las rotaciones (rotación simple a la derecha, rotacion simple a la izquierda, rotación doble a la derecha y rotación doble a ala izquierda) de manera que métodos con la capacidad de desbalancear el árbol, como lo son *insertar* y *eliminar* fueran capaces de regresar al árbol a su estado balanceado. De esta manera, cada vez que se inserta o elimina un nodo dentro del árbol, se verifica el factor de balanceo en cada uno de los nodos recorridos y, en caso de ser mayor a 1 o menor a -1, se realizarán las rotaciones correspondientes a ese caso en especifico. Finalmente, la operación de *buscar* funciona de la misma manera que los hace un árbol binario, recursivamente, para este método no se requieren rotaciones. 
---
#### Árbol B
La solución implementada para la construcción del árbol B en disco se baso principalmente en la misma implementación utilizada para un árbol B implementado en memoria. Para lograr lo anterior, se utilizaron metodos para escribir, leer y recorrer con facilidad dentro de un archivo de tipo *.bin*, en combinación con fórmulas matématicas para hacer posible lo anterior. Los nodos, escritos en el disco, mantenian la misma estructura que los nodos utilizados comunmente, siguiendo la siguiente estructura: en la posición 0 se encontraria la posición dentro del archivo que posee el nodo en cuestión, en la posición 1 el número de elementos que se encuentran actualmente en el nodo, en la posición 2 se determina el tipo de nodo (0:No Hoja, 1:Hoja), y en las posteriores posiciones estarían espacios para almacenar los elementos, seguidos de espacios para almacenar las posiciones de los nodos hijos. De esta manera, utilizando metodos para recorrer los nodos similarmente al tradicional sistema de apuntadores, se creó un árbol B en el disco, cuyo orden será establecido al ser declarado y tendra *2n-1* elementos y *2n* nodos. Para las operaciones *insertar* y *eliminar* en ocaciones se requiere realizar *merges*, eliminando nodos hoja, o incluso eliminar raices de manera que este se mantenga balanceado y su numero de niveles se mantenga lo más reducido posible, siempre procurando crecer horizontalmente y no verticalmente. La operación *buscar* simplemente recorre el arbol hasta encontrar el valor buscado o no encontrarlo si es que ya ha llegado a un nodo hoja. 
---
#### Programa de prueba (main)
El *main* que implementa las clases *AVL* y *BTree* se encarga de preguntar al usuariio en primera instacnia el número de elementos que desea ingresar a cada uno de los arboles, entonces creará un arreglo de *n* elementos aleatorios e *insertar*á cada uno a cada árbol. Posteriormente, el programa creará un arreglo con 10 elementos aleatorios y porcederá a *buscar*los en cada uno de los árboles (tomando en cuenta que ambos árboles tienen los mismo valores, los 2 deberían llegar a las mismas conclusiones). Por útlimo, el programará mandará a *eliminar* cada uno de los 10 elementos establecidos en cada uno de los arboles. Para cada una de las de las operaciones previamente mencionadas el programa se encargará de medir los tiempos e imprimira una tabla con ellos para que su análisis y comparación sea más sencilla. Para generar el reporte de ésta tarea se ejecutó *main* desde una Raspberry Pi, estos resultados fueron almacenados como archivos de texto (*.txt*) en la carpeta *resultados_raspberryPi*. 

### 2.1 Pasos a seguir para utilizar la aplicación

Lo primero que se debe realizar clonar el repositorio de GitHub, para realizar dicha acción, el usuario se deberá colocar en el directorio donde desea almacenar el repositorio y ahí deberá llamar el siguiente comando:

    $ git clone https://github.com/tec-csf/tc2017-t2-primavera-2020-equipo-2-1.git

Una vez clonado el repositorio, el usuario deberá ingresára a él, utilizando el siguiente comando: 

    $ cd tc2017-t2-primavera-2020-equipo-2-1

Al estar dentro del repositorio, lo único que falta por hacer es compilar los archivos utilizados y ejecutar el main, con los siguientes dos comandos:

    $ g++ sources/main.cpp sources/avl.cpp sources/BTree.cpp

    $ ./a.out

Al estar ejecutando el programa, este le pedirá al usuario que ingrese el numero de elementos que desea insertar a los arboles, para lo cual debe insertar un número entero, como en el siguiente ejemplo: 

    $ Ingrese la cantidad de elementos a ingresar a los arboles: *1000*
---
Si es que se desea observar el funcionamiento de cada arbol por separado, se recomienda acceder a los codigos en la carpeta *examples* corriendo cada una de las clases por separado (en este caso ya contienen su propio *main*). Para ver el funcionamiento del Árbol AVL se correrían lo siguientes comandos:

    $ g++ example/avl_example.cpp

    $ ./a.out

Y para ver el funcionamiento del Árbol B se correrían los siguientes comandos: 

    $ g++ example/BTree_example.cpp

    $ ./a.out

## 3. Referencias

    Rodewad, A. (2012) AVL Tree | Set 2 (Deletion). *Geeks for Geeks*. Obtenido de: https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

    Balasubramanian, N. (2019) Delete Operation in B-Tree. *Geeks for Geeks*. Obtenido de: https://www.geeksforgeeks.org/delete-operation-in-b-tree/

En varias ocasiones se acuidó a las implementaciones publicadas por *Geeks for Geeks* para la realización de ambos árboles, la lógica que se sigue en cada una de las clases se encuentra muy apegada a la establecida por ellos en ambos árboles. 

    cplusplus.com. (2020) <cstdio> (stdio.h). *cplusplus.com*. Obtenido de: http://www.cplusplus.com/reference/cstdio/

Por útlimo, para la implementación del Árbol B en el disco, se utilizó la API publicada por *cplusplus.com* con respecto a su librería *stdio.h*, cuyos métodos resultaron ser muy útiles para escribir, leer y desplazarse por un archivo de tipo *.bin* y lograr almacenar la información de los nodos en el disco como resultado. 
