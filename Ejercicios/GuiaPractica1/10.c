#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void main(int argc ,char const *argv[]){
    write(1, "Soyh juan\n" , 11); //(1)
    pid_t julieta = fork();
    if(julieta == 0){ //pid 10552
        write(1, "soy JUlieta\n" ,12); //(2) 
        sleep(1); 
        pid_t jennifer = clone(); 
        if(jennifer == 0){ //10557
            write(1, "soyJennifer\n" ,14 );
            //quine hace que se frene le wirte? /(DEBAJO DEL WRITE SOY JENNIFER)
        }
    }else{ //pid 10551
        sleep(1);
        wait(NULL);
        //clone aqui ()
        pid_t jorge = clone();
        if(jorge == 0){
            write(1, "soyJorge\n", 10);
            sleep(1);
        }

    }
    exit(EXIT_SUCCESS);
}