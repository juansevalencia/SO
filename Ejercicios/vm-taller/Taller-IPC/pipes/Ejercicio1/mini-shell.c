#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include "mini-shell-parser.c"

typedef char*** matrix;

/*
	Explicacion del argumento progs:

	Corresponde con una matriz donde cada fila representa el iesimo programa pasado
	dividido por el pipe. En cada fila esta el nombre del programa 
	en su primera posicion y los parametros en las posiciones restantes.

	Ejemplo: 'du -h /home | head -n 10 | sort -rh'
	
	Representacion:
	[
		['du', '-h', '/home'],
		['head', '-n', '10'],
		['sort', '-rh']
	]

*/

void sub_proceso(int i , int pipe_[][2], size_t count, char** instruccion){
	//cerra todos los pipes que no uses
	for(int j = 0 ; j < count ; j++){
		if(j != i - 1 && j != i ){
			int qcy = close(pipe_[j][PIPE_READ]);
			int qcy2 = close(pipe_[j][PIPE_WRITE]);
		}	
	}
	if(i == 0){
		//cerra el de lectura asi el sig proceso no lee
		int qcy4 = close(pipe_[i][PIPE_READ]);
		int ejnormal2 = dup2(pipe_[i][PIPE_WRITE], STDOUT_FILENO);
		//ejecuta
	}else{
		if(i == count - 1){
			 //cerra el de escritura del anterior
			 int qcy3 = close(pipe_[i - 1][PIPE_WRITE]);
			 int ejnormal = dup2(pipe_[i][PIPE_READ], STDIN_FILENO); //Lee de atras-
			 //ejecuta

		}else{
			int qcy3 = close(pipe_[i - 1][PIPE_WRITE]);//cerra de donde te escribieron la info
			int qcy4 = close(pipe_[i][PIPE_READ]); //Cerra la lectura a donde vas a escribir
			int ejnormal = dup2(pipe_[i][PIPE_READ], STDIN_FILENO); //lee del pipe la info
			int ejnormal2 = dup2(pipe_[i][PIPE_WRITE], STDOUT_FILENO); //escribi en el pipe sig
			//EJECUTA
		}
	}
	execvp(instruccion[0], instruccion); //no se supone que debe ejecutar el iesimo?

}

static int run(matrix progs, size_t count)
{	
	int r, status;

	//Reservo memoria para el arreglo de pids
	//TODO: Guardar el PID de cada proceso hijo creado en children[i]
	pid_t *children = malloc(sizeof(*children) * count);

	//TODO: Pensar cuantos procesos necesito
	
	//TODO: Pensar cuantos pipes necesito. Cada pipe va a poner informacion excepto el ultimo.Asi que es count -1
	int pipe_[count][2];

	for(int i = 0 ; i < count ; i++){
		pipe(pipe_[i]);
	}

	//creo los procesos
	for(int i = 0 ; i < count ; i++){
		pid_t son = fork();
		if (son == -1)exit(1);
		if(son == 0){
			sub_proceso(i , pipe, count, progs);
		}
		children[i] = son;
	}

	for(int i = 0 ; i < count ; i++){
		close(pipe_[i][PIPE_READ]);
		close(pipe_[i][PIPE_WRITE]);
	}	
	//TODO: Para cada proceso hijo:
			//1. Redireccionar los file descriptors adecuados al proceso
			//2. Ejecutar el programa correspondiente

	//Espero a los hijos y verifico el estado que terminaron
	for (int i = 0; i < count; i++) {
		waitpid(children[i], &status, 0);

		if (!WIFEXITED(status)) {
			fprintf(stderr, "proceso %d no terminó correctamente [%d]: ",
			    (int)children[i], WIFSIGNALED(status));
			perror("");
			return -1;
		}
	}
	r = 0;
	free(children);

	return r;
}


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("El programa recibe como parametro de entrada un string con la linea de comandos a ejecutar. \n"); 
		printf("Por ejemplo ./mini-shell 'ls -a | grep anillo'\n");
		return 0;
	}
	int programs_count;
	matrix programs_with_parameters = parse_input(argv, &programs_count);

	printf("status: %d\n", run(programs_with_parameters, programs_count));

	fflush(stdout);
	fflush(stderr);

	return 0;
}
