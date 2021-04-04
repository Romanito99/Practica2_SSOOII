#include <iostream>
#include <thread>
#include <string>
#include <algorithm> //std::for_each
#include <vector>
#include <queue>
#include <fstream> 
#include <mutex>
#include <locale>   //std::tolower
#include <functional>
#include <sstream>  //std::isstringstream 
#include <cctype>   //ispunct
#include <clocale>  //std::setlocale
#define LIMITE 1000000
#define HILOS 2

#define  NUM_CARACTER_ERASE 1 //Number of characters erase when find symbols



void Suma(std::vector<int> v, int inicio, int valor_fin)
{
    
}
std::string simbolos(std::string word){
    
   
    

    if(!isalpha(word[0]) && !isblank(word[0])){
        
        word.erase(0,2);
    word=word;
    
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
    std::vector<int> v_naleatorios;
    std::vector<std::thread> vhilos;
    
    int valor = 0;
    int inicio = 0;
    
    int lineastotales=cuenta_lineas(p_fichero);
    int size_task = lineastotales/hilos;
    for (int j = 0; j < hilos; j++)
    {
        inicio = j * size_task;
        valor = (inicio + size_task) - 1;
        if (j == hilos - 1) valor = lineastotales ;
        std::cout <<"linea "<<inicio<< " palabra " <<valor << std::endl;}
        //vhilos.push_back(std::thread(Suma, v_naleatorios, inicio, valor));
    
    //std::for_each(vhilos.begin(), vhilos.end(), std::mem_fn(&std::thread::join));

    while (!in.eof()) {
        std::string    anterior;
        while (getline(in,cadena))
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
                  
                    std::cout <<"linea "<<lineastotales<< " palabra " << word <<" , " <<anterior<<" , "<< posterior<< std::endl;}
                   
                    
            
                anterior=word;
            }
            
            }
        }
    

    

    
}
