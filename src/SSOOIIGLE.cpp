/******************************************************
* Proyecto:                Práctica 2 de Sistemas Operativos II
* 
* Nombre de la Clase:      SSOOIIGLE.cPP
* 
* Autor:                   César Braojos Corroto
* 
*  
* Proposito:               Busqueda de palabras en un fichero de texto , y mostrar por pantalla con varios datos mas  
*                          
* 
 ******************************************************/

#include <iostream>
#include <thread>
#include <string>
#include <algorithm> //std::for_each
#include <vector>
#include <list>
#include <queue>
#include <fstream> 
#include <mutex>
#include <locale>   //std::tolower
#include <functional>
#include <sstream>  //std::isstringstream 
#include <cctype>   //ispunct
#include <clocale>  //std::setlocale
#include <atomic>
#include "../include/color.h" 

#define LIMITE                  1000000
#define NUM_CARACTER_ERASE      1 //Number of characters erase when find symbols

/******************************************************
* CREACION DE LAS VARIABLE GLOBALES

*****************************************************/
std::mutex g_semaforo;
std::queue<std::queue<std::string>> g_queue;

/******************************************************
Metodo para limpiar las palabras de signos de puntuacion delanteros

(¡ ¿ << "")

*****************************************************/
std::string Simbols(std::string word){
    if(!isalpha(word[0])){
        
        word.erase(0,2);
        word=word;
        if(!isalpha(word[0])){
        word.erase(0,2);
        word=word;
        }
    }
    return word;
}
/******************************************************
Metodo para limpiar las palabras de signos de puntuacion traseros

(. , : ; ! ? )

*****************************************************/
std::string changeToLowercaseAndEraseSimbols(std::string word){
    std::for_each(word.begin(), word.end(), [](char & c){
        c = ::tolower(c);
    });

    for (unsigned i = 0; i < word.size(); i++) { 
        
        if (ispunct(word[i])){             
            word.erase(i, NUM_CARACTER_ERASE); 
        }
    }

    return word;
}
/******************************************************
Metodo para contar las lineas de un fichero

*****************************************************/
std::int16_t CountLines(char* p_fichero ){
    std::ifstream       on ;
    std::string         cadena;

    on.open(p_fichero);
    int linea=0;
    while (!on.eof()) {
        std::string    anterior;
        while (getline(on,cadena))
        {
            linea++;
        }
    }
    return linea;
}


/******************************************************
Metodo para imprimir y ordenar la salida

*****************************************************/
void Print(std::string id,int size)
{
int                                 i       =0;
std::queue<std::queue<std::string>> aux     =g_queue;
while(!aux.empty()){
            
            std::queue<std::string>lista2 = aux.front();

            if(lista2.front()==id){
                
                std::chrono::milliseconds(10);
                std::cout << BOLDBLUE << "[HILO " << RESET<< lista2.front();
                lista2.pop();
                std::cout << BOLDBLUE << " inicio: "<<RESET <<lista2.front();
                lista2.pop();
                std::cout << BOLDBLUE << " - final: "<<RESET <<lista2.front()<< BOLDBLUE<<"]::";
                lista2.pop();
                std::cout << BOLDBLUE << "linea "<<RESET <<lista2.front();
                lista2.pop();
                std::cout << BOLDBLUE << ":: ..." <<RESET<<lista2.front();
                lista2.pop();
                std::cout << " "  <<RED <<lista2.front();
                lista2.pop();
                
                std::cout <<" " << RESET<<lista2.front()<< BOLDBLUE << " ... "<< std::endl;
                lista2.pop();
                   
            }
            aux.pop();
            i++;
        
        }
}


/******************************************************
Metodo que ejecuta cada hilo para buscar la palabra en distintas partes del fichero

*****************************************************/
void SearchWord(int id ,int inicio , int valor,int hilos ,char* p_palabra ,char* p_fichero)
{   
    std::vector<std::list<std::string>*>    h_vector;
    std::string                             cadena,palabra;
    std::ifstream                           in ;
    std::string                             anterior;
    char*                                   palabras;
    int                                     linea               =0;
    in.open(p_fichero);
    while (!in.eof()) {
        
        while (getline(in,cadena))
        {
            linea++;
            std::string         palabra_limpia     = changeToLowercaseAndEraseSimbols(cadena);
            std::istringstream  p(palabra_limpia);
            
            if(linea>=inicio && linea<=valor){
            while(!p.eof()){
                std::string     palabra;
                p >> palabra; 
                std::string     word= Simbols(palabra);
                if(word == p_palabra){
                    std::string                 posterior;
                    std::string                 identificador       =std::__cxx11::to_string(id);
                    std::string                 numero_linea         =std::__cxx11::to_string(linea);
                    std::string                 start               =std::__cxx11::to_string(inicio);
                    std::string                 fin                 =std::__cxx11::to_string(valor);
                    std::queue<std::string>     cola_hilo;
                    p >> posterior;
                    //Introducimos los datos de la palabra encontrada en una cola 
                        cola_hilo.push(identificador);
                        cola_hilo.push(start);
                        cola_hilo.push(fin);
                        cola_hilo.push(numero_linea);
                        cola_hilo.push(anterior);
                        cola_hilo.push(word);
                        cola_hilo.push(posterior);

                    //Seccion Critica. Introducimos a la cola general la cola con los datos de la palabra
                        g_semaforo.lock();
                        g_queue.push(cola_hilo);
                        g_semaforo.unlock();
                  
                    if (posterior==word){
                        p >> posterior;
                        anterior        =word;
                        identificador   =std::__cxx11::to_string(id);
                        numero_linea     =std::__cxx11::to_string(linea);
                        std::queue<std::string>cola_hilo;
                        //Introducimos los datos de la palabra encontrada en una cola
                            cola_hilo.push(identificador);
                            cola_hilo.push(start);
                            cola_hilo.push(fin);
                            cola_hilo.push(numero_linea);
                            cola_hilo.push(anterior);
                            cola_hilo.push(word);
                            cola_hilo.push(posterior);
                        //Seccion Critica. Introducimos a la cola general la cola con los datos de la palabra
                            g_semaforo.lock();
                            g_queue.push(cola_hilo);
                            g_semaforo.unlock(); 
                    }
                }
                anterior=palabra;
            }
            }
        }
    }
    
    
}
/******************************************************
Metodo para mostrar un mensaje de bienvenida

*****************************************************/
void messageWelcome(){
    std::cout <<BOLDBLUE << "SS" << BOLDRED << "O" << BOLDYELLOW << "O"<< BOLDBLUE << "II" << BOLDGREEN << "GL" << BOLDRED << "E" << RESET;
    std::cout <<RESET<< "::BIENVENIDO A TU BUSCADOR::" << BOLDBLUE << "SS" << BOLDRED << "O" << BOLDYELLOW << "O";
    std::cout << BOLDBLUE << "II" << BOLDGREEN << "GL" << BOLDRED << "E\n" << RESET << std::endl;
    std::cout << BOLDBLUE << " "  << std::endl; 
}
/******************************************************
Metodo para mostrar un mensaje de despedida

*****************************************************/
void messageEnd(){
    std::cout << BOLDBLUE << " "  << std::endl;
    std::cout <<BOLDBLUE << "SS" << BOLDRED << "O" << BOLDYELLOW << "O"<< BOLDBLUE << "II" << BOLDGREEN << "GL" << BOLDRED << "E" << RESET;
    std::cout << RESET <<"::GRACIAS POR SU CONFIANZA::" << BOLDBLUE << "SS" << BOLDRED << "O" << BOLDYELLOW << "O" ;
    std::cout << BOLDBLUE << "II" << BOLDGREEN << "GL" << BOLDRED << "E" << RESET << std::endl; 
}


/******************************************************
Metodo principal
*****************************************************/
int main(int argc, char** argv)
{  
    messageWelcome();
    
    std::vector<std::thread>        v_hilos;
    std::ifstream                   in ;
    
    if (argc != 4)
    {
        fprintf(stderr, "ERROR! El numero de argumentos introducidos es incorrecto Prueba: ./exec/SSOOIIGLE <nombre_fichero> <palabra> <numero_hilos> ");
        return EXIT_FAILURE;
    }

    int     hilos           = atoi(argv[3]);
    char*   p_palabra       = argv[2];
    char*   p_fichero       = argv[1];
    int     lineastotales   =CountLines(p_fichero);
    int     size_task       = lineastotales/hilos;
    int     valor           = 0;
    int     inicio          = 0;

    in.open(p_fichero);

    //Creacion de hilos , y llamada diviendo el fichero dependiendo de los hilos 
    for (int i = 0; i < hilos; i++)
    {
        inicio = i * size_task;
        valor = (inicio + size_task) - 1;
        if (i == hilos - 1) valor = lineastotales;
        v_hilos.push_back(std::thread(SearchWord,i , inicio,valor,hilos,p_palabra,p_fichero));
    }
    std::for_each(v_hilos.begin(), v_hilos.end(), std::mem_fn(&std::thread::join));

    //Realizamos la impresion por hilos 
    for(int i=0;i<hilos;i++){
        std::string j =std::__cxx11::to_string(i);
        Print(j,g_queue.size());
    }
    messageEnd();
    return EXIT_SUCCESS; 
}