#include <signal.h>

    pid_t pid_ping;
    pid_t pid_pong;
    int cant_emitido;

/*idea general:
1.Si estoy en el padre quiero pedir que se printee ping y llamar a pong para que se ejecute 3 veces.

*/

void handler_pong(int sign){ //funcion que va a esperar a que se la llame para printear
    bool siempre = true; //puedo enviarle una señal al proceso mientras se esta ejecutando?
    while(siempre){
        if(sign == 0 ){
            sleep(1); //banca la señal
        }else{
            print("pong");
            sign = 0; //cambio el estado de sign
        }
    }
     
}

void main(){
    bool hacemoUnaMa = true;
    while(hacemoUnaMa){
        pid_ping = getpid();
        pid_pong = fork();//no va a tomar 0 cuando tome proceso hijio?
        if(pid_pong == 0){
            pid_pong = getpid();
            handler_pong(0);
        }else{ //estoy en el padre, necesito esperar a que pong ponga a disposicion su handler
            sleep(1); //no hay algo mas especifico? esperar una señal ?
            // crear una especie de booleano que indique cuando se creo el handler. O estoy cambiando señal por señal?
            //y chequear aca cuando se haya creado, y arriba en el if poner en el codigo 
            //enviar señal cuando se cree por debajo de su linea??
            pid_ping = getpid();
            for(int i = 0; i < 3; i++){
                print("pong");
                kill(1 ,handler_pong);
            }
            kill(pid_pong, SIGKILL);

        }
        cout >> "hacemo una ma?(si o no)";
        cin >> res;
        if(res != si){
            hacemoUnaMa = false;
        }
    }    


}

pid_t pid_hijo;
pid_t pid_padre;

void handler_pong(int sign){
    while(true){ //p q nunca muera
        print("pong"); 
    }
}

void handler_ping(){
    while(true){
        print("ping"); 
        kill(pid_padre, SIGINT); //YA PRINTEE
    }
}

void main(){
    pid = fork();
    if(pid == 0){
        pid_hijo = getpid();
        //queres redifinir el comportamiento de tu procesamiento
        signal(SIGINT, handler_ping);
    }else{
        for(int i = 0 ; i < 3 ; i++){
            signal(SIGINT , handler_pong);//redefino sigint
            kill(pid_padre , SIGINT); //inicia todo
        }
    }
}