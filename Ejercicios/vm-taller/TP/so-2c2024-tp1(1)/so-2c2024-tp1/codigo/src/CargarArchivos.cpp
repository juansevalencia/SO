#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

#include "CargarArchivos.hpp"

using namespace std;

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        hashMap.incrementar(palabraActual);
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}


void tomar_archivos_disponibles( vector<string>& filePath , atomic<int>& n_archivo , HashMapConcurrente& hashMap ){
    while(1){
        int numero;
        if((numero = n_archivo.fetch_add(1)) > size(filePath) ){
            break;
        }
        int cant = cargarArchivo( hashMap, filePath[numero]);
    }
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {

    vector<thread> threads;

    atomic<int> n_archivo(0);

    
    for(int i = 0 ; i < cantThreads ; i++){
        threads.emplace_back(tomar_archivos_disponibles,  &filePaths , &n_archivo, &hashMap);
    }

    for(auto &elem: threads ){
        elem.join();
    }
}

#endif
