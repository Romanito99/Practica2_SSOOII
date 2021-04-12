#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
#include <functional>
#include <ctime>
#include <atomic>
#define LIMITE 1000000
#define HILOS 16

std::atomic<long> n_suma_acumulada (0);
void Suma(std::vector<int> v, int inicio, int valor_fin)
{
    
    for (int i = inicio; i <= valor_fin; i++)
    {
        n_suma_acumulada += v[i];
    }
}

int main()
{
    unsigned t0, t1;
    t0 = clock();
    std::vector<int> v_naleatorios;
    std::vector<std::thread> vhilos;
    int size_task = LIMITE/HILOS;
    long suma = 0;
    for (unsigned i = 0; i < LIMITE; i++)
    {   srand(time(NULL));
        int numero = rand();
        v_naleatorios.push_back(numero);
        suma +=numero;
    }
    std::cout << "La suma acumulada es: " << suma << std::endl;
    int valor = 0;
    int inicio = 0;
    for (int i = 0; i < HILOS; i++)
    {

        inicio = i * size_task;
        valor = (inicio + size_task) - 1;
        if (i == HILOS - 1) valor = LIMITE - 1;
        vhilos.push_back(std::thread(Suma, v_naleatorios, inicio, valor));
    }

    std::for_each(vhilos.begin(), vhilos.end(), std::mem_fn(&std::thread::join));
    std::cout << "La suma acumulada por los hilos es: " << n_suma_acumulada.load() << std::endl;
    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    std::cout << "Execution Time: " << time << std::endl;
}






