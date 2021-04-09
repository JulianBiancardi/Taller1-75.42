# TP0
Facultad de Ingeniería, Universidad de Buenos Aires


TP0 de la materia Taller de Programacion 1 (75.42)


Alumno: Biancardi, Julian 

Padron: 103945

(Para acceder al enunciado http://206.189.71.102:8080/course/2020c2/ej0/enunciado.pdf)

(Para acceder al repositorio https://github.com/JulianBiancardi/tp0)


## Introduccion

En el siguiente informe se detallara todos los pasos seguidos para la resolucion del trabajo practico 0 de la materia Taller de Programacion 1. Haremos enfonque en los distintos conceptos de **Compilacion / Linkeo / Ejecucion**. Tambien analizaremos los errores que puedan llegar a ocurrir mediante distintas herramientas como por ejemplo **Valgrind** o **gdb**. Veremos como funciona la plataforma *SERCOM* y como esta misma nos ayudara para poder tener un codigo sin errores y que cumpla con las normas de codificacion.

## Desarrollo

### Paso 0: Entorno de Trabajo

Se realizo el siguiente aplicativo en el entorno de trabajo:

```C
    #include <stdio.h>

    #define SUCCESS 0

    int main(int argc, char* argv[]) {
        printf("Hola mundo!\n");

        return SUCCESS;
    }
 ```

  - a. Capturas de pantalla de la ejecución del aplicativo (con y sin Valgrind).

Compilamos con el comando `gcc main.c -o tp`.

Ejecutamos con el comando `./tp` y obtenemos:

        Hola mundo!

Ejecutamos con el comando `valgrind ./tp` y obtenemos lo siguiente:

    ==8217== Memcheck, a memory error detector
    ==8217== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==8217== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==8217== Command: ./tp
    ==8217== 
    Hola mundo!
    ==8217== 
    ==8217== HEAP SUMMARY:
    ==8217==     in use at exit: 0 bytes in 0 blocks
    ==8217==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
    ==8217== 
    ==8217== All heap blocks were freed -- no leaks are possible
    ==8217== 
    ==8217== For counts of detected and suppressed errors, rerun with: -v
    ==8217== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

  - b. ¿Para qué sirve **Valgrind**? ¿Cuáles son sus opciones más comunes?

Para la segunda ejecucion del programa lo hicimos con la herramienta **Valgrind**, la cual es muy util para poder detectar errores de manejo de memoria. Estos pueden deberse comunmente cuando no se liberan los espacios de memorias reservados por el programador (por ejemplo cuando se pierden todas las referencias a estos). Veremos en el paso 4 errores de este estilo.

  - c. ¿Qué representa **sizeof()**? ¿Cuál sería el valor de salida de **sizeof(char)** y **sizeof(int)**?
  
  La funcion **sizeof()** es util para saber cuantos bytes podria ocupar un tipo de dato en memoria. Esto nos sirve para cuando se quiere reservar memoria, ya que debemos conocer la cantidad de bytes necesarios dependiendo del tipo de dato que querramos guardar. 
  Entonces con lo anteriormente mencionado con las siguientes operaciones obtendremos los siguientes resultados:

```C
                                        sizeof(char) = 1 byte
   
                                        sizeof(int) = 4 bytes
```
  - d. ¿El **sizeof()** de una struct de C es igual a la suma del **sizeof()** de cada uno sus elementos? Justifique mediante un ejemplo.
  
  Supongamosnos que tenemos el siguiente struct en C:
  
```C
                                        struct mi_struct{
                                            char variable1;
                                            char variable2;
                                            int variable3;
                                        } 
 ```
 Con lo mencionado en el item c podremos suponer los siguientes resultados:
 ```C
                                        sizeof(variable1) = sizeof (variable2) = 1 byte

                                        sizeof(variable3) = 4 bytes

                                        sizeof(mi_struct) = sizeof(variable1) + sizeof(variable2) + sizeof(variable3) = 6 bytes
```
 Pero esto no es asi. Si realizamos en cambio la siguiente operacion veriamos que el resultado obtenido es distinto:
 ```C
                                        sizeof(mi_struct) = 12 bytes
``` 
 Esto se debe a la alineacion de datos en memoria (padding).
 
  - e. Investigar la existencia de los archivos estándar: STDIN, STDOUT, STDERR. Explicar brevemente su uso y cómo redirigirlos en caso de ser necesario (caracteres **>** y **<**) y como conectar la salida estándar de un proceso a la entrada estándar de otro con un **pipe** (carácter **|** ).
 
  
  -STDIN (Standar Input): Via de comunicacion por el cual se envian datos al programa.
    
  -STDOUT (Standar Output): Via de comunicacion por el cual el programa devuelve datos durante su ejecucion.
    
  -STDERR (Standar Error): Via de comunicacion por el cual el programa informa los errores de ejecucion.
    
 Si quisieramos redirigirlos, podemos realizarlo con los caracteres `<` y `>` de la siguientes formas: 
 
 `> archivo` : Crea un nuevo archivo para la salida estandar. Si el archivo ya existe, se sobrescribe.
 
 `< archivo` : Utilizamos el archivo especificado como entrada estandar.
 
 `< archivo >` : Utilizamos el archivo especificado entrada estándar y la salida estándar.
 
 Ahora bien, si quisieramos conectar la salida estandar de un proceso a la entrada estandar de otro (realizar una "tuberia") lo haremos mediante el caracter `|` (pipe). Esto nos ofrece la posibilidad de concatenar comandos:
 
 `comando1 | comando2 .... | comandon`
 
 
### Paso 1: SERCOM - Errores de generación y normas de programación

Comenzando con el paso 1 vemos que nuestra entrega falla debido a que SERCOM no puede generar la aplicacion correctamente ya que tenemos errores de compilacion/linkeo. A su vez vemos que tenemos errores de normas de codificacion.

  - a. Captura de pantalla mostrando los problemas de estilo detectados. Explicar cada uno.
  
        /task/student//source_unsafe/paso1_wordscounter.c:27:  Missing space before ( in while(  [whitespace/parens] [5]
        /task/student//source_unsafe/paso1_wordscounter.c:41:  Mismatching spaces inside () in if  [whitespace/parens] [5]
        /task/student//source_unsafe/paso1_wordscounter.c:41:  Should have zero or one spaces inside ( and ) in if  [whitespace/parens] [5]
        /task/student//source_unsafe/paso1_wordscounter.c:47:  An else should appear on the same line as the preceding }  [whitespace/newline] [4]
        /task/student//source_unsafe/paso1_wordscounter.c:47:  If an else has a brace on one side, it should have it on both  [readability/braces] [5]
        /task/student//source_unsafe/paso1_wordscounter.c:48:  Missing space before ( in if(  [whitespace/parens] [5]
        /task/student//source_unsafe/paso1_wordscounter.c:53:  Extra space before last semicolon. If this should be an empty statement, use {} instead.  [whitespace/semicolon] [5]
        /task/student//source_unsafe/paso1_wordscounter.h:5:  Lines should be <= 80 characters long  [whitespace/line_length] [2]
        /task/student//source_unsafe/paso1_main.c:12:  Almost always, snprintf is better than strcpy  [runtime/printf] [4]
        /task/student//source_unsafe/paso1_main.c:15:  An else should appear on the same line as the preceding }  [whitespace/newline] [4]
        /task/student//source_unsafe/paso1_main.c:15:  If an else has a brace on one side, it should have it on both  [readability/braces] [5]
        Done processing /task/student//source_unsafe/paso1_wordscounter.c
        Done processing /task/student//source_unsafe/paso1_wordscounter.h
        Done processing /task/student//source_unsafe/paso1_main.c
        Total errors found: 11
  
 Se presentan diferentes tipos de errores de normas de codificacion. Los podemos dividir en los siguientes grupos:
 
  1. Whitespace/parens : Errores relacionados con espacios en blanco y parentesis. Se presentan en las siguientes lineas

      paso1_wordscounter.c:27: Cuando se escribe una sentencia del estilo `if`, `for`, `while`, etc. se debe dejar un espacio antes del `(`.
  
      paso1_wordscounter.c:41: No hay la misma cantidad de espacios entre `()`.Tambien debe de haber como maximo un espacio entre `()`.

      paso1_wordscounter.c:48: Cuando se escribe una sentencia del estilo `if`, `for`, `while`, etc. se debe dejar un espacio antes del `(`.


  2. Whitespace/newline : Errores relacionados con espacios en blanco y comienzos de nueva linea. Se presentan en las siguientes lineas
   
      paso1_wordscounter.c:47: Cuando se comienza la sentencia `else` luego de haber finalizado su sentencia `if`, este debe comenzar en la misma linea que la `{` antecesora.

      paso1_main.c:15: Mismo error que se presenta en la linea 47.
      
            
  3. Whitespace/semicolon : Errores relacionados con espacio y puntos y coma.
   
      paso1_wordscounter.c:53: Cuando se termina una linea de codigo con `;` no debe dejarse anteriormente un espacio.

   
  4. Whitespace/line_length : Errores relacionados con espacio y largos de linea.
   
      paso1_main.c:5: Las lineas de codigo deben de tener como maximo 80 caracteres de largo.
            
   
  5. Readability/braces : Errores relacionados con legibilidad y llaves. 

      paso1_wordscounter.c:47: Cuando las sentenicas `if`, `for`, `while`, etc contienen como cuerpo una sola linea de codigo, es mejor no poner `{}`. 

      paso1_main.c:15: Mismo error que se presenta en la linea 47.


  6. Runtime/printf : Errores relacionados con la ejecucion de programa y llamados a la funcion printf
   
      paso1_main.c:12: Es mejor usar `snprintf` que `strcpy` debido a que esta ultima no limita la cantidad maxima.
            
            
  - b. Captura de pantalla indicando los errores de generación del ejecutable. Explicar cada uno e indicar si se trata de errores del compilador o del **linker**.
  
        paso1_main.c:22:9: error: unknown type name ‘wordscounter_t’
           22 |         wordscounter_t counter;
              |         ^~~~~~~~~~~~~~
        paso1_main.c:23:9: error: implicit declaration of function ‘wordscounter_create’ [-Wimplicit-function-declaration]
           23 |         wordscounter_create(&counter);
              |         ^~~~~~~~~~~~~~~~~~~
        paso1_main.c:24:9: error: implicit declaration of function ‘wordscounter_process’ [-Wimplicit-function-declaration]
           24 |         wordscounter_process(&counter, input);
              |         ^~~~~~~~~~~~~~~~~~~~
        paso1_main.c:25:24: error: implicit declaration of function ‘wordscounter_get_words’ [-Wimplicit-function-declaration]
           25 |         size_t words = wordscounter_get_words(&counter);
              |                        ^~~~~~~~~~~~~~~~~~~~~~
        paso1_main.c:27:9: error: implicit declaration of function ‘wordscounter_destroy’ [-Wimplicit-function-declaration]
           27 |         wordscounter_destroy(&counter);
              |         ^~~~~~~~~~~~~~~~~~~~
              
En este caso obtuvimos dos tipos de errores:

   *unknown type name*: la etiqueta utilizada no se reconoce.
   
   *implicit declaration of function*: la funcion invocada no se ha definido antes.

Ambos errores se deben a que no se agrego la libreria necesaria. Por ende son errores de compilacion.


  - c. ¿El sistema reportó algún *WARNING*? ¿Por qué?

El sistema SERCOM **no** reporto ningun warning ya que no se han detectado escenarios riesgosos que pudieron haber sido errores.


### Paso 2: SERCOM - Errores de generación 2

Continuando con el paso 2 ahora vemos que no tenemos ningun error de normas de codificacion, pero aun asi SERCOM no puede generar la aplicacion correctamente debido a que seguimos teniendo errores de compilacion/linkeo.

  - a. Describa **en breves palabras** las correcciones realizadas respecto de la versión anterior.
  
Se evitan bastantes errores relacionados con las normas de codificacion que se presentaron en la primera entrega mediante el codigo paso1. Se ajustan todos los errores relacionados a espacios en blanco, se corrigen los errores relacionados a las lineas de codigo y tambien los errores relacionados entre una linea de codigo y su siguiente. 

  - b. Captura de pantalla indicando la correcta ejecución de verificación de normas deprogramación.
  
Con los cambios mencionados en el item *a* ya no tenemos errores de normas de codificacion

        Done processing /task/student//source_unsafe/paso2_wordscounter.c
        Done processing /task/student//source_unsafe/paso2_main.c
        Done processing /task/student//source_unsafe/paso2_wordscounter.h

  - c. Captura de pantalla indicando los errores de generación del ejecutable. Explicar cada uno eindicar si se trata de errores del compilador o del **linker**.
  
        paso2_wordscounter.h:7:5: error: unknown type name ‘size_t’
            7 |     size_t words;
              |     ^~~~~~
        paso2_wordscounter.h:20:1: error: unknown type name ‘size_t’
           20 | size_t wordscounter_get_words(wordscounter_t *self);
              | ^~~~~~
        paso2_wordscounter.h:1:1: note: ‘size_t’ is defined in header ‘<stddef.h>’; did you forget to ‘#include <stddef.h>’?
          +++ |+#include <stddef.h>
            1 | #ifndef __WORDSCOUNTER_H__
        paso2_wordscounter.h:25:49: error: unknown type name ‘FILE’
           25 | void wordscounter_process(wordscounter_t *self, FILE *text_file);
              |                                                 ^~~~
        paso2_wordscounter.h:1:1: note: ‘FILE’ is defined in header ‘<stdio.h>’; did you forget to ‘#include <stdio.h>’?
          +++ |+#include <stdio.h>
            1 | #ifndef __WORDSCOUNTER_H__
        paso2_wordscounter.c:17:8: error: conflicting types for ‘wordscounter_get_words’
           17 | size_t wordscounter_get_words(wordscounter_t *self) {
              |        ^~~~~~~~~~~~~~~~~~~~~~
Como se menciono en el paso 1, nuevamente obtenemos errores de tipo *unknown type name* los cuales son debidos a que no se agregaron las librerias necesarias para reconocer las etiquetas que se usan. Estos son errores de compilacion.

Por otra parte, los errores *unknown type name* seguidos de *note* son errores de linkeo, puesto que nos indican que librerias agregar para poder evitar estos errores.

        paso2_wordscounter.h:20:8: note: previous declaration of ‘wordscounter_get_words’ was here
           20 | size_t wordscounter_get_words(wordscounter_t *self);
              |        ^~~~~~~~~~~~~~~~~~~~~~
        paso2_wordscounter.c: In function ‘wordscounter_next_state’:
        paso2_wordscounter.c:30:25: error: implicit declaration of function ‘malloc’ [-Wimplicit-function-declaration]
           30 |     char* delim_words = malloc(7 * sizeof(char));
              |                         ^~~~~~
        paso2_wordscounter.c:30:25: error: incompatible implicit declaration of built-in function ‘malloc’ [-Werror]
        paso2_wordscounter.c:5:1: note: include ‘<stdlib.h>’ or provide a declaration of ‘malloc’
            4 | #include <stdbool.h>
          +++ |+#include <stdlib.h>
            5 |
            
En este caso obtenemos nuevamente dos tipos de errores.

   *implicit declaration of function* y *incompatible implicit declaration of built-in function*: debido a que no se agrego las librerias necesarias para la funcion que se invoca. Estos errores son de compilacion
   
   *previous declaration*: la funcion se ha declarado previamente por lo que este error es de linkeo.
    

### Paso 3: SERCOM - Errores de generación 3

Siguiendo con el paso 3, SERCOM no puede generar la aplicacion correctamente debido a que seguimos teniendo algunos errores de compilacion/linkeo.

  - a. Describa en breves palabras las correcciones realizadas respecto de la versión anterior.
 
Se agrega la libreria `stdlib` necesarias para las funciones que se invocan en el codigo y evitar asi errores de compilacion/linkeo que obtuvimos en los pasos anteriores.

  - b. Captura de pantalla indicando los errores de generación del ejecutable. Explicar cada uno e indicar si se trata de errores del compilador o del **linker**.
  
        paso3_main.c:27: undefined reference to `wordscounter_destroy'
        
En este paso obtuvimos un unico error. Este se debe a que la implementacion de la funcion **wordscounter_destroy** no se encuentra. Este error es de linkeo, ya que se han agregado las librerias necesarias pero no se ha declarado la firma de dicha funcion.


### Paso 4: SERCOM - *Memory Leaks* y *Buffer Overflows*

Vemos que al realizar la entrega en el paso 4 ya no tenemos errores de compilacion/linkeo ni errores de normas de codificacion. Etonces SERCOM genera la aplicacion correctamente y prosigue a ejecutar los casos de prueba.

  - a. Describa en breves palabras las correcciones realizadas respecto de la versión anterior.
  
 Se agrega la implementacion de la funcion **wordscounter_destroy** para evitar los errores de linkeo que obtuvimos en en el paso anterior.
 
  - b. Captura de pantalla del resultado de ejecución con **Valgrind** de la prueba ‘TDA’. Describir los errores reportados por Valgrind.

        ==00:00:00:00.000 59== Memcheck, a memory error detector
        ==00:00:00:00.000 59== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
        ==00:00:00:00.000 59== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
        ==00:00:00:00.000 59== Command: ./tp input_tda.txt
        ==00:00:00:00.000 59== Parent PID: 58
        ==00:00:00:00.000 59==
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== FILE DESCRIPTORS: 5 open at exit.
        ==00:00:00:01.007 59== Open file descriptor 4: input_tda.txt
        ==00:00:00:01.007 59==    at 0x495FEAB: open (open64.c:48)
        ==00:00:00:01.007 59==    by 0x48E2195: _IO_file_open (fileops.c:189)
        ==00:00:00:01.007 59==    by 0x48E2459: _IO_file_fopen@@GLIBC_2.2.5 (fileops.c:281)
        ==00:00:00:01.007 59==    by 0x48D4B0D: __fopen_internal (iofopen.c:75)
        ==00:00:00:01.007 59==    by 0x48D4B0D: fopen@@GLIBC_2.2.5 (iofopen.c:86)
        ==00:00:00:01.007 59==    by 0x109177: main (paso4_main.c:14)
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== Open file descriptor 3: /task/student/cases/tda/__valgrind__
        ==00:00:00:01.007 59==    <inherited from parent>
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== Open file descriptor 2: /task/student/cases/tda/__stderr__
        ==00:00:00:01.007 59==    <inherited from parent>
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== Open file descriptor 1: /task/student/cases/tda/__stdout__
        ==00:00:00:01.007 59==    <inherited from parent>
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== Open file descriptor 0: /task/student/cases/tda/__stdin__
        ==00:00:00:01.007 59==    <inherited from parent>
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== HEAP SUMMARY:
        ==00:00:00:01.007 59==     in use at exit: 1,977 bytes in 216 blocks
        ==00:00:00:01.007 59==   total heap usage: 218 allocs, 2 frees, 10,169 bytes allocated
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== 472 bytes in 1 blocks are still reachable in loss record 1 of 2
        ==00:00:00:01.007 59==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
        ==00:00:00:01.007 59==    by 0x48D4AAD: __fopen_internal (iofopen.c:65)
        ==00:00:00:01.007 59==    by 0x48D4AAD: fopen@@GLIBC_2.2.5 (iofopen.c:86)
        ==00:00:00:01.007 59==    by 0x109177: main (paso4_main.c:14)
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== 1,505 bytes in 215 blocks are definitely lost in loss record 2 of 2
        ==00:00:00:01.007 59==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
        ==00:00:00:01.007 59==    by 0x109301: wordscounter_next_state (paso4_wordscounter.c:35)
        ==00:00:00:01.007 59==    by 0x1093B5: wordscounter_process (paso4_wordscounter.c:30)
        ==00:00:00:01.007 59==    by 0x109197: main (paso4_main.c:24)
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== LEAK SUMMARY:
        ==00:00:00:01.007 59==    definitely lost: 1,505 bytes in 215 blocks
        ==00:00:00:01.007 59==    indirectly lost: 0 bytes in 0 blocks
        ==00:00:00:01.007 59==      possibly lost: 0 bytes in 0 blocks
        ==00:00:00:01.007 59==    still reachable: 472 bytes in 1 blocks
        ==00:00:00:01.007 59==         suppressed: 0 bytes in 0 blocks
        ==00:00:00:01.007 59==
        ==00:00:00:01.007 59== For lists of detected and suppressed errors, rerun with: -s
        ==00:00:00:01.007 59== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
   
   En este caso, Valgrind nos reporta errores de memoria. Estamos reservando 218 bloques de memoria de los cuales: unicamente 2 de ellos se han liberado con la funcion free,  215 se han perdido completamente (debido a que se han perdido sus referencias) y 1 puede ser recuperado para liberar la memoria.

  - c. Captura de pantalla del resultado de ejecución con **Valgrind** de la prueba ‘Long Filename’.Describir los errores reportados por Valgrind.
  
        **00:00:00:01.016 47** *** memcpy_chk: buffer overflow detected ***: program terminated
        ==00:00:00:00.000 47== Memcheck, a memory error detector
        ==00:00:00:00.000 47== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
        ==00:00:00:00.000 47== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
        ==00:00:00:00.000 47== Command: ./tp input_extremely_long_filename.txt
        ==00:00:00:00.000 47== Parent PID: 46
        ==00:00:00:00.000 47==
        **00:00:00:01.016 47** *** memcpy_chk: buffer overflow detected ***: program terminated
        ==00:00:00:01.016 47==    at 0x483E9CC: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
        ==00:00:00:01.016 47==    by 0x4843C0A: __memcpy_chk (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
        ==00:00:00:01.016 47==    by 0x109168: memcpy (string_fortified.h:34)
        ==00:00:00:01.016 47==    by 0x109168: main (paso4_main.c:13)
        ==00:00:00:01.034 47==
        ==00:00:00:01.034 47== FILE DESCRIPTORS: 4 open at exit.
        ==00:00:00:01.034 47== Open file descriptor 3: /task/student/cases/nombre_largo/__valgrind__
        ==00:00:00:01.034 47==    <inherited from parent>
        ==00:00:00:01.034 47==
        ==00:00:00:01.034 47== Open file descriptor 2: /task/student/cases/nombre_largo/__stderr__
        ==00:00:00:01.034 47==    <inherited from parent>
        ==00:00:00:01.034 47==
        ==00:00:00:01.034 47== Open file descriptor 1: /task/student/cases/nombre_largo/__stdout__
        ==00:00:00:01.034 47==    <inherited from parent>
        ==00:00:00:01.034 47==
        ==00:00:00:01.034 47== Open file descriptor 0: /task/student/cases/nombre_largo/__stdin__
        ==00:00:00:01.034 47==    <inherited from parent>
        ==00:00:00:01.034 47==
        ==00:00:00:01.034 47==
        ==00:00:00:01.034 47== HEAP SUMMARY:
        ==00:00:00:01.034 47==     in use at exit: 0 bytes in 0 blocks
        ==00:00:00:01.034 47==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
        ==00:00:00:01.034 47==
        ==00:00:00:01.034 47== All heap blocks were freed -- no leaks are possible
        ==00:00:00:01.034 47==
        ==00:00:00:01.034 47== For lists of detected and suppressed errors, rerun with: -s
        ==00:00:00:01.034 47== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

  Para este caso no tenemos erres de memoria sino que tenemos errores de **buffer overflow**.  

  - d. ¿Podría solucionarse este error utilizando la función **strncpy**? ¿Qué hubiera ocurrido con la ejecución de la prueba?
  
  Con  strncpy se puede solucionar el problema debido a que esta funcion permite definir un maximo que se puede copiar en el buffer.

  - e. Explicar de qué se trata un **segmentation fault** y un **buffer overflow**.
  
 Cuando hablamos de **segmentation fault** nos referimos a un error especifico que se debe a accesos a memorias no permitidos. Por ejemplo si el usuario quisiera acceder a la posicion 0 de memoria.
 
  En cambio, cuando hablamos de **buffer overflow** nos referimos a escrituras en memoria que modifican los valores contenidos en direcciones no deseadas. Por ejemplo cuando queremos escribir en un buffer pero modificamos los valores de las direcciones contiguas de memoria.
  
  
 ### Paso 5: SERCOM - Código de retorno y salida estándar
 
   - a. Describa en breves palabras las correcciones realizadas respecto de la versión anterior.
  
  1. Se cambia la siguiente seccion de codigo en `paso5.c`:
```C
  //Codigo del paso4                                   //Codigo del paso5
  char filepath[30];
  memcpy(filepath, argv[1], strlen(argv[1]) + 1);
  input = fopen(filepath, "r");                       input = fopen(argv[1], "r");
 ```
  2. Se agrega la siguiente seccion de codigo en `paso5.c`:
```C
                          if (input != stdin)
                                fclose(input);
 ```
  3. En `paso5_wordscounter.c`, en vez de pedir memoria y guardar en cada bloque el caracter delimitador de palabra, lo realizamos directamente con 
  ```C
                            const char* delim_words = " ,.;:\n";
  ```

  - b. Describa el motivo por el que fallan las prueba ‘Invalid File’ y ‘Single Word’. ¿Qué informaciónentrega SERCOM para identificar el error? Realice una captura de pantalla.
  
  SERCOM nos probee de la siguiente informacion:

          [=>] Comparando archivo_invalido/__return_code__...
          1c1
          < 255
          ---
          > 1


          [=>] Comparando una_palabra/__stdout__...
          1c1
          < 0
          ---
          > 1

  En ambos errores el valor de salida no es igual al valor esperado por ende las pruebas fallan.

  - c. Captura de pantalla de la ejecución del comando ​hexdump​. ¿Cuál es el último carácter del archivo input_single_word.txt?
  
Con los comandos `hd input_single_word.txt` o `hexdump -C input_single_word.txt` se obtiene la siguiente salida por consola:

      00000000  77 6f 72 64                                       |word|
      00000004

El ultimo caracter del archivo es **d** que en codigo *ASCII* es 0x64.

  - d. Captura de pantalla con el resultado de la ejecución con ​gdb​. Explique brevemente los comandos utilizados en ​gdb​. ¿Por qué motivo el debugger no se detuvo en el breakpoint de lalínea 45: self->words++;​?

`gdb ./tp`: inicializamos el debugger en nuestro codigo compilado.

`info functions`: Nos muestra las funciones de nuestro codigo.

`list wordscounter_next_state`: Nos muestra las lineas de codigo de la funcion especificada.

`list`: Nos muestra nuesto codigo.

`break 45`: se coloca un break point en la linea 45.

`run input_single_word.txt`: Corremos el debugger con el archivo especificado.

`quit`: salimos del debugger.


El debugger no se detiene en la linea 45 ya que no entra a la sentencia `ìf` que contiene a la linea de codigo `self->words++;`.

```C
                                        if (strchr(delim_words, c) != NULL) {
                                               self->words++;
                                               next_state = STATE_WAITING_WORD;
                                        }
```

 ### Paso 6: SERCOM - Entrega exitosa
 
  - a. Describa en breves palabras las correcciones realizadas respecto de la versión anterior.

  1. La constante **ERROR** se define con el valor **-1**
   
  2. Se cambia nuevamente el codigo para determinar un delimitador de palabra:
```C
  //Codigo del paso5                             //Codigo del paso6
  input = fopen(argv[1], "r");                   #define DELIM_WORDS " ,.;:\n"
 ```
  3. En `paso6_wordscounter.c` se modifica la forma de detectar palabras mediante los delimitadores.
   
   
  - b. Captura de pantalla mostrando **todas las entregas realizadas**, tanto exitosas como fallidas.

![EntregasRealizadas](EntregasRealizadas.png)

  - c. Captura de pantalla mostrando la ejecución de la prueba ‘Single Word’ **de forma local** con lasdistintas variantes indicadas.

Con el comando `$ ./tp input_single_word.txt`:
      1

Con el comando `$ ./tp <input_single_word.txt`:
      1

Con el comando `$ ./tp <input_single_word.txt >output_single_word.txt`:
      No se visualiza nada en la consola debido a que redireccionamos la salida al archivo **output_single_word.txt**. En el veremos la salida 1.


 
