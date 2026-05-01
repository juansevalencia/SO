#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>

#define CANT_THREADS 10

using namespace std;

void creando() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    puts("¡Hola! Soy un thread");
}

int main() {
    vector<std::thread> threads; // Usamos un vector para almacenar los threads

    // Crear los threads
    for (int i = 0; i < CANT_THREADS; i++) {
        //threads.emplace_back(creando); Agregamos el thread al vector, creacion in-place
        std::thread t(creando);
        t.detach(); //desvincula el thread del objeto, deja de ser joinable. Se reclaman los recursos una vez que termina automaticamente.
        //sleep(1) Espera 1 segundo antes de crear el siguiente thread
        sleep(1);
    }

    // No unirse a los threads
    //for (auto& t : threads) {
    //    //t.join(); Esta línea se ha comentado
    //    t.detach();
    //}

    cout << "Todos los threads han terminado." << endl; // Puede ejecutarse antes que los threads
    return 0;
}
//echo $? procesos vivos.

