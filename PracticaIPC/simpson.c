#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <sys/types.h>
#include <sys/wait.h>

enum {READ, WRITE};
enum {LESTER, ELIZA};

int main(){
    int pipes[2][2];

    pipe(pipes[0]);
    pipe(pipes[1]);

    pid_t lester = fork();
    if(lester == 0){
        int num_lester = (rand() + 3) % 7;
        printf("soy lester y saque %d\n", num_lester);
        write(pipes[LESTER][WRITE] , &num_lester ,sizeof(num_lester) ); 
        exit(EXIT_SUCCESS);
    }

    pid_t eliza = fork();
    if(eliza == 0){
        int num_eliza = rand() % 7;
        printf("soy eliza y saque %d\n", num_eliza);
        write(pipes[ELIZA][WRITE], &num_eliza,sizeof(num_eliza));
        exit(EXIT_SUCCESS);
    }
    

    wait(NULL);
    wait(NULL);
    int res_lester;
    read(pipes[LESTER][READ], &res_lester ,sizeof(res_lester)); 
    int res_liza;
    read(pipes[ELIZA][READ], &res_liza, sizeof(res_lester)); 
    if( res_lester >= res_lester){
        write(1, "lester\n",6 );
    }else{
        write(1, "eliza\n", 5);
    }
    exit(EXIT_SUCCESS);
    return 0;
}
