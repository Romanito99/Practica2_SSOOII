# Practica2_SSOOII

Autor: César Braojos Corroto

Fecha: 15-Marzo-2021

**Práctica 1 –Llamadas al sistema y señales**

**COMPILACION DEL PROGRAMA:**

    $~make

Este comando se encargar de ejcutar los comandos para preparar la ejecucion y lo ejecutara.Concretamente se encarga de limpiar el fichero de carpetas que sobren y crear los ejecutables necesario para los test 
    
**LIMPIEZA CARPETA:**

    $~make clean
    
Este comando se encargar de eliminar las carpetas y archivos creados en la ejecución.

**RUN:**

    $~make test
    $~make test1
    $~make test2
  
 Estos comandos se  encargan de la ejecucion del programa. Dentro del archivo makefile puedes cambiar los ficheros la palabra que buscas o el numero de hilos que quierees ejecutar. He puesto tres opciones de ejecución para comprobar en distintos hilos o distntos archivos
 
    $~./$(DIREXE)SSOOIIGLE.cpp <nombre fichero> <palabra> <numero de hilos>

 Por ejemplo: 
  
    $~./$(DIREXE)SSOOIIGLE.cpp utils/books/21_leyes_del_liderazgo.txt navegación 4

