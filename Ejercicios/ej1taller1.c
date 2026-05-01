#include <sys/wait.h>
#include <unistd.h>
#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

bool vivos[10];
pid_t pid_hijos[10];
pid_t pid_padre;
int n;
int j;

void sacar_numero(){
    int num = rand() % (n);
    if(num == j){
        write(1, "la quede", 8);
        int actual = getpid();
        write(STDOUT_FILENO, actual, strlen(actual));
        kill(pid_padre,SIGUSR1);
        exit(EXIT_SUCCESS);
    }else{
        kill(pid_padre, SIGUSR2);
    }

}

void sala_de_espera(){
    signal(SIGTERM, sacar_numero());
    while(1);
}

void seMurio(int i){
    vivos[i] = false;
}

void padre(int k){
    pid_padre = getpid();
    int cpy_n = n;
    while(cpy_n>0){
        vivos[cpy_n] = true;
        pid_t son = fork();
        if(son == 0){
            pid_hijos[cpy_n] = getpid();
            sala_de_espera();
        }else{
            cpy_n --;
        }
    }
    while(k>0){
        for(int i = 0; i < n ; i++){
            if(pid[i]){
                kill(SIGTERM, pid[i]);
                signal(SIGUSR1, seMurio(i));
                signal(SIGUSR2, SIG_IGN);
                wait();
                vivos[i] = false;
                sleep(1);
            }
        }
        k--
    }
}

int main(){
    printf("Introducir cantidad de hijos");
    scanf("%d" , &n);

    int k;
    printf("Introducir cantidad de rondas");
    scanf("%d" , &k);

    printf("Introducir numero malidito");
    scanf("%d" , &j);

    for (int i = 0; i < n; ++i) {
        vivos[i] = false;
    }
    
    padre(k);
}

