#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

pid_t hijo;
pid_t padre;

int main(){
    int n;
    padre = getpid();
    pid_t hijo = fork();
    if(hijo != 0){
        sleep(1);
        bsend(hijo, 0);
    }else{
        hijo = getpid();
    }    
    int num = 0;
    while (num <n){
        if(hijo == 0){
            num = breceive(padre)
            bsend(padre,num++);
        }else{
            num = breceive(hijo);
            bsend(hijo, num++);
        }
    }    
    return 0;
}

int main(){
    pid_t hijo1pid;
    pid_t hijo2pid;
    int n;
    padre = getpid();
    pid_t hijo1 = fork();
    if(hijo1 != 0){
        pid_t hijo2 = fork();
        if (hijo2 == 0){
            hijo2pid = getpid();
        }else{
            sleep(1);
            bsend(hijo1, 0);
        }    
    }else{
        pid_t hijo = getpid();
        if(hijo != hijo2pid){
            hijo1pid = hijo;
        }
    }

    int num = 0;
    while (num <n){
        if(hijo1 == 0 ){
            num = breceive(padre)
            bsend(hijo1,num++);
        }else{
            if(hijo2 ==0){
                num = breceive(hijo1);
                bsend(padre, num++);
            }else{
                num = breceive(hijo2)
                bsend(hijo1, num++);
            }
        }
    }    
    return 0;
}
}