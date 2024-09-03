#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <sys/types.h>
#include <sys/wait.h>

enum {READ, WRITE};

int pipe_[2]; //un punteor? o bucamos aclarar memoria? 
//res = funcion dup2

void ejecutar_func(char* file , char* arg){
    execlp(file, file, arg ,NULL); //porque dos veces file, porque el argumento es -l
}

//Ls-al
void sub_proceso1(){
    close(pipe_[READ]); //cierro lectura, la lectura de este proceso.no?
    dup2( pipe_[WRITE],STDOUT_FILENO); //Yo quiero que lo que tendria que salir por consola salga en el pipe
    ejecutar_func("ls", "-al" ); //ejecuto con los argumentos
}
//wc -l
void sub_proceso2(){
    //leer del pipe read? como se cuando dejo de leer y cuando dejo de escribir
    close(pipe_[WRITE]);
    dup2(pipe_[READ], STDIN_FILENO); //yo quiero que lo q puse en le pipe se lea como param
    ejecutar_func("wc", "-l" );
}

//dup2 , el segundo parametro es lo q quiero remplazar ,que no entre mas en juego, el primero es a odnde lo quiero remplazar

int main(int argc, char const* argv[]){
    pipe(pipe_);
    pid_t sub1 = fork();
    if(sub1 == 0){
        sub_proceso1();
    }
    pid_t sub2 = fork();
    if(sub1 == 0){
        sub_proceso2();
    }

    close(pipe_[WRITE]); //haciendo esto no podria pasar que este inyenyando escrbir el proceso1?

    //espero a que terminen los hijos
    wait(NULL);
    wait(NULL);

    return 0;
}
