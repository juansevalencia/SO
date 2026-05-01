#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <mutex>

#define CANT_THREADS 10

using namespace std;
std:: mutex m;

void creando(int i, std::string s) {
    m.lock();
    printf (" %s %i\n", s . c_str () , i );
    printf("termine %i\n", i);
    m.unlock();
}

int main() {
    vector<std::thread> threads; // Usamos un vector para almacenar los threads
    // Crear los threads
    for (int i = 0; i < CANT_THREADS; i++) {
        threads.emplace_back(creando, i, "Hola! Soy el thread: "); //Agregamos el thread al vector, creacion in-place
    }

    // No unirse a los threads
    for (auto& t : threads) {
        t.join();
    }

    cout << "Todos los threads han terminado." << endl; // Puede ejecutarse antes que los threads
    return 0;
}
//echo $? procesos vivos.

