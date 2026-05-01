#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"
#include <signal.h>

void proceso_hijo(int i ,int pipeAntecesor[2], int pipeSig[2]){
	while(1){
		close(pipeAntecesor[PIPE_WRITE]);
		close(pipeSig[PIPE_READ]); //cierro pipe escritura ant y lectura sig
		int dato;
		printf("hijo: %d\n", i);
		printf("dato %d\n", dato);
		int qcy = read(pipeAntecesor[PIPE_READ], &dato, sizeof(int));
		dato++;
		int qcy2 = write(pipeSig[PIPE_WRITE], &dato, sizeof(int));
	}
	//tene en cuenta que no estoy tirando un exit.
}

void proceso_hijo_pref(int i, int random, int pipePadre[2], int pipeSig[2], int pipeAntecesor[2]){
	close(pipePadre[PIPE_WRITE]); //cerra el de escritura del que te vino.
	int dato;
	int qcy23 = read(pipePadre[PIPE_READ],&dato, sizeof(int)); //lee el dato
	printf("dato que vino en pref %d\n", dato);
	dato++;
	int qcy24 = write(pipeSig[PIPE_WRITE], &dato, sizeof(int)); //escribi el dato en el sig sumado 1
	//para la primera vez siemre lo pasa.

	//una vez que ya se ejecuto;
	while(1){
		//cierro WRITE DEL ANT
		close(pipeAntecesor[PIPE_WRITE]);
		int dato2;
		int qcy2 = read(pipeAntecesor[PIPE_READ], &dato2, sizeof(int));
		//si no lee se va  aquedar ahie sperando o hanria que poner un if por si
		//devuelve - 1? 
		if(dato2 >= random){ 
			int qcy3 = write(pipePadre[PIPE_WRITE], &dato2, sizeof(int));
			exit(EXIT_SUCCESS);
		}else{
			close(pipeSig[PIPE_READ]); //cierro el read del sig.
			dato2++;
			int qcy3 = write(pipeSig[PIPE_WRITE], &dato2, sizeof(int));
		}
	}
}

int generate_random_number(){
	return (rand() % 50);
}

int main(int argc, char **argv)
{	
	//Funcion para cargar nueva semilla para el numero aleatorio
	srand(time(NULL));

	int status, pid, n, start, buffer;
	n = atoi(argv[1]);
	buffer = atoi(argv[2]);
	start = atoi(argv[3]);

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
    
  	/* COMPLETAR */

    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer, start);
    
	pid_t pids[n];

	int pipe_[n + 1][2];
	for(int j = 0 ; j <= n ; j++){
		int k = pipe(pipe_[j]);
	}
	
	int qcy = write(pipe_[n][PIPE_WRITE], &buffer, sizeof(buffer));
	for (int i = 0 ; i < n ; i++){
		pid_t hijo = fork();
		if(hijo == -1){ exit(EXIT_FAILURE);}
		if(hijo == 0){
			if(i != start){
				proceso_hijo(i , pipe_[((i - 1 )% n)], pipe_[i]);
			}else{
				int random = generate_random_number() % buffer;
				proceso_hijo_pref(start, random, pipe_[n], pipe_[i], pipe_[n-1]);
			}
		}
		pids[i] = hijo;
	}

	wait(NULL); //espera a que termine el primer hijo.

	int res;
	close(pipe_[n][PIPE_WRITE]);
	int qcy99 = read(pipe_[n][PIPE_READ], &res, sizeof(int));
	//cerra todos los pipes;
	for (int i = 0; i < n ; i++){
		close(pipe_[i][PIPE_READ]);
		close(pipe_[i][PIPE_WRITE]);
		kill(pids[i], SIGKILL );
	}
	printf("la respuesta es: %d\n",res);
	return 0;
    /* COMPLETAR */   
}
