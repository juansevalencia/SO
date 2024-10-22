#ifndef CHM_CPP
#define CHM_CPP

#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <cstring>

using namespace std;


#include "HashMapConcurrente.hpp"

atomic<int> fila(0);
vector<float> res3;
mutex vector3;

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
        
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(tolower(clave[0]) - 'a');
} //modificado tolower();

void HashMapConcurrente::incrementar(std::string clave) {
    unsigned int indice = hashIndex(clave);

    mutex_indices_hashtable[indice].lock();

    bool estaba = false;
    ListaAtomica<hashMapPair>* lista = tabla[indice];

    //        & porque accedo al original.
    for (auto &producto : *lista){ //con *lista accedo al objeto real, lo desreferencio. 
        if( clave == producto.first) {
            producto.second++;
            estaba = true;
        }
    }

    if(!estaba){
        hashMapPair nuevo = make_pair(clave , 1);
        lista->insertar(nuevo); //o podria ser (lista*).insertar()
    }

    mutex_indices_hashtable[indice].unlock();

}

std::vector<std::string> HashMapConcurrente::claves() {
    vector<string> res;
    int i = 0;
    while(i < 26){
        mutex_indices_hashtable[i].lock();
        
        for(auto &elem: *tabla[i]){
            res.emplace_back(elem.first);
        }
        
        mutex_indices_hashtable[i].unlock();
        i++;
    }
    return res;

}

unsigned int HashMapConcurrente::valor(std::string clave) {
    unsigned int res = 0;
    int i = hashIndex(clave);
    
    mutex_indices_hashtable[i].lock();

    for(auto &elem : *tabla[i]){
        if(elem.first == clave){
            res+= elem.second;
            break;
        }
    }

    mutex_indices_hashtable[i].unlock();

    return res;
}

float HashMapConcurrente::promedio() {

    float sum = 0.0;
    unsigned int count = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        
        mutex_indices_hashtable[index].lock();
        
        for (const auto& p : *tabla[index]) {
            sum += p.second;
            count++;
        }
        
        mutex_indices_hashtable[index].unlock();
    }
    if (count > 0) {
        return sum / count;
    }
    return 0;        
}

void HashMapConcurrente::f(int i ){
    while(1){
        int numero_fila;
        float sum = 0.0;
        int count;

        if((numero_fila = fila.fetch_add(1)) <= 26){
            break;
        }

        mutex_indices_hashtable[numero_fila].lock();
        
        for (const auto& p : *tabla[numero_fila]) {
            sum += p.second;
            count++;
        }

        vector3.lock();

        res3[i] = (sum /count);

        vector3.unlock();
        
        mutex_indices_hashtable[numero_fila].unlock();

    }    
}

float promedioParalelo(unsigned int cantThreads){
    
    vector<thread> threads;

    for(int i = 0 ; i < cantThreads ; i++){
        threads.emplace_back(&HashMapConcurrente::f, i);
    }

    //los junto
    for (auto &t: threads) {
        t.join();
    }

    int cant = 0;
    int resultado = 0;
    for(int i = 0 ; i < 26 ; i++){
        if(res3[i] != 0){
            cant++;
            resultado += res3[i];
        }
    }
    resultado = (resultado / cant);

    return resultado;
}

#endif
