
pid_t pid_hijo1;
pid_t pid_hijo2;
int num;

enum {READ, WRITE};

void proceso(int i){
    while(num < 50){
        cerra escritura
        read();
        num++
        close(pipes[(i + 1) % 3][READ]); //tengo que cerar la otra punta de q estoy escrbiendo? para q no lo lean ahora?   
        escribila en el pipe


    }
}   

int main(){
    int pipes[3][2];
    pipe(pipes);

    pid_t hijo1 = fork();
    if(hijo1 == 0){
        pid_hijo1  = getpid();
        proceso(1);
    }else{
        pid_t hijo2 = fork();
        if(hijo2 == 0){
            pid_hijo1  = getpid();
            proceso(2);
        }else{
            write(pipe[0][WRITE], 0, sizeof(int));
            sleep(1);
            proceso(1);
        }
    }
}