#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
#include <functional>
#include <ctime>
#include <atomic>

#define LIMITE 1000000
#define HILOS 2


std::atomic<long> n_suma_acumulada (0);
void Suma(std::vector<int> v, int inicio, int valor_fin)
{
    
}

int main(int argc, char** argv)
{   
    char cadena;
    std::ifstream in ;
    int   hilos   = atoi(argv[3]);
    char* p_palabra = argv[2];
    char* p_fichero = argv[1];
    char  nom, mail, contrasenya;;
    in.open(p_fichero);
    std::vector<int> v_naleatorios;
    std::vector<std::thread> vhilos;
    int size_task = LIMITE/hilos;
    int valor = 0;
    int inicio = 0;
    while (!in.eof()) {
        in >> cadena;
        if(cadena == p_palabra){
            std::cout << "El numero de hilos es " << cadena<< std::endl;  
        }
        
    }

    for (int i = 0; i < HILOS; i++)
    {
        inicio = i * size_task;
        valor = (inicio + size_task) - 1;
        if (i == hilos - 1) valor = LIMITE - 1;
        vhilos.push_back(std::thread(Suma, v_naleatorios, inicio, valor));
    }
    std::for_each(vhilos.begin(), vhilos.end(), std::mem_fn(&std::thread::join));

    
}
