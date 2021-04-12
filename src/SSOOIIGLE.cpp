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

#define LIMITE 1000000
#define HILOS 4

#define  NUM_CARACTER_ERASE 1 //Number of characters erase when find symbols


std::string simbolos(std::string word){
    
   

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
std::string changeToLowercaseAndEraseSimbols(std::string word){
    std::string delimitador;
    delimitador[1]='¿';
    std::string aux;
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

std::int16_t cuenta_lineas(char* p_fichero ){
    std::ifstream on ;
    std::string cadena;
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
void Suma(int id ,int inicio , int valor,int hilos ,char* p_palabra ,char* p_fichero)
{
    std::string cadena,palabra;
    std::ifstream in ;
    in.open(p_fichero);
    char* palabras;
    int linea=0;
    while (!in.eof()) {
        std::string    anterior;
        
        while (getline(in,cadena))
        {
            
            linea++;
            std::string     word_search = changeToLowercaseAndEraseSimbols(cadena);
            std::istringstream p(word_search);
            
            if(linea>inicio && linea<valor){
            while(!p.eof()){

                std::string palabra;
                p >> palabra; 
                std::string     word= simbolos(palabra);
                
                if(word == p_palabra){
                    std::string    posterior;
                    p >> posterior;
                    std::string identificador=std::__cxx11::to_string(id);
                        std::string numerolinea=std::__cxx11::to_string(linea);
                        std::list<std::string>lista;
                        lista.push_back(identificador);
                        lista.push_back(numerolinea);
                        lista.push_back(anterior);
                        lista.push_back(word);
                        lista.push_back(posterior);
                        std::cout << BOLDBLUE << "HILO " << RESET<< lista.front();
                        lista.pop_front();
                        std::cout << BOLDBLUE << ",linea "<<RESET<<lista.front();
                        lista.pop_front();
                        std::cout << BOLDBLUE << ",palabra " << RESET<<lista.front() ;
                        lista.pop_front();
                        std::cout << BOLDBLUE << ",anterior " <<RESET<<lista.front();
                        lista.pop_front();
                        std::cout << BOLDBLUE << ",posterior "<< RESET<<lista.front()<< std::endl;
                        lista.pop_front();

                        
                        
                       
                        
                        
                        
                    if (posterior==word){
                        p >> posterior;
                        anterior=word;
                       std::string identificador=std::__cxx11::to_string(id);
                        std::string numerolinea=std::__cxx11::to_string(linea);
                        std::list<std::string>lista;
                        lista.push_back(identificador);
                        lista.push_back(numerolinea);
                        lista.push_back(anterior);
                        lista.push_back(word);
                        lista.push_back(posterior);
                        std::cout << BOLDBLUE << "HILO " << RESET<< lista.front();
                        lista.pop_front();
                        std::cout << BOLDBLUE << ",linea "<<RESET<<lista.front();
                        lista.pop_front();
                        std::cout << BOLDBLUE << ",palabra " << RESET<<lista.front() ;
                        lista.pop_front();
                        std::cout << BOLDBLUE << ",anterior " <<RESET<<lista.front();
                        lista.pop_front();
                        std::cout << BOLDBLUE << ",posterior "<< RESET<<lista.front()<< std::endl;
                        lista.pop_front();
                    }
                }
                    
            
                anterior=word;
            }
            
            }
        }
    }
    
}


int main(int argc, char** argv)
{   
    std::string cadena,palabra;
    std::ifstream in ;
    char* palabras;
    int linea=0;
    int   hilos   = atoi(argv[3]);
    char* p_palabra = argv[2];
    char* p_fichero = argv[1];
    in.open(p_fichero);
   
    int lineastotales=cuenta_lineas(p_fichero);
    int size_task = lineastotales/hilos;

    std::vector<std::thread> vhilos;
    int valor = 0;
    int inicio = 0;
    for (int i = 0; i < hilos; i++)
    {
        inicio = i * size_task;
        valor = (inicio + size_task) - 1;
        if (i == HILOS - 1) valor = LIMITE - 1;
        vhilos.push_back(std::thread(Suma,i , inicio,valor,hilos,p_palabra,p_fichero));
    }

    std::for_each(vhilos.begin(), vhilos.end(), std::mem_fn(&std::thread::join));

    /*while (!in.eof()) {
        std::string    anterior;
        while (getline(in,cadena,8))
        {
            
            linea++;
            std::string     word_search = changeToLowercaseAndEraseSimbols(cadena);
            std::istringstream p(word_search);
            
    
            while(!p.eof()){

                std::string palabra;
                p >> palabra; 
                std::string     word= simbolos(palabra);
                
                if(word == p_palabra){
                    std::string    posterior;
                    p >> posterior;
                    std::cout <<"linea "<<linea<< " palabra " << word <<" , " <<anterior<<" , "<< posterior<< std::endl;
                    if (posterior==word){
                        p >> posterior;
                        anterior=word;
                        std::cout <<"linea "<<linea<< " palabra " << anterior <<" , " <<word<<" , "<< posterior<< std::endl;
                    }
                }
                    
            
                anterior=word;
            }
            
            }
        }*/
    

    

    
}