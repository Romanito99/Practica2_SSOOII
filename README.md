# Practica2_SSOOII

Autor: César Braojos Corroto

Fecha: 15-Marzo-2021

**Práctica 1 –Llamadas al sistema y señales**

**COMPILACION DEL PROGRAMA:**

    $~make

Este comando se encargar de ejcutar los comandos para preparar la ejecucion y lo ejecutara.
    
**LIMPIEZA CARPETA:**

    $~make clean
    
Este comando se encargar de eliminar las carpetas y archivos creados en la ejecución.


Finalmente por las caracteristicas del programa he añadido una opcion para ver los deamon que se estan ejecutando en tu ordenador , y asi poder parar el daemon de mi practica 

**RUN:**

    $~make RUN
  
 Este comando se  encarga de la ejecucion del programa. Dentro del archivo makefile puedes cambiar los ficheros la palabra que buscas o el numero de hilos que quierees ejecutar
 
    $~./$(DIREXE)SSOOIIGLE.cpp <nombre fichero> <palabra> <numero de hilos>

 Por ejemplo: 
  
    $~./$(DIREXE)SSOOIIGLE.cpp Practica2_SSOOII/utils/books/21_leyes_del_liderazgo.txt navegación 4

