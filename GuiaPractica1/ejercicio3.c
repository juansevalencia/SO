struct PCB {
int STAT; // valores posibles KE_RUNNING, KE_READY, KE_BLOCKED, KE_NEW
int P_ID; // process ID
int PC; // valor del PC del proceso al ser desalojado
int RO; // valor del registro R0 al ser desalojado
...
int R15; // valor del registro R15 al ser desalojado
int CPU_TIME // tiempo de ejecución del proceso
}

void Ke_context_switch(PCB* pcb_0, PCB* pcb_1){
    pcb_0->PC = get_current_pc(); //guardad pc
    pcb_0->CPU_TIME += ke_current_user_Time(); 
    pcb_0->registros = save_registers(); //guardar registtors
    pcb_0->STAT = KE_READY; //cambiar estado
    //??
    //CPU TIME tengo que mandarlo a mi cronometro? o tengo que poner cuanto uso?
    //cpu time cuanta la cantidad total de tiempo que uso ese proceso la cpu?

    set_current_process(pcb_1->P_ID );//cambiar el proceso agtual
    pcb_1->STAT = KE_RUNNING; //hace falta 
    pcb_1->cpu_time = 0; 
    restore_registers(pcb_1->registers) 
    ke_reset_current_user_Time(); //resetear tiempo
    ret(); //cambiar pc
}

void system_analogo(const char *arg){    
    pid_t hijo = fork();
    if(hijo == 0){
        exec(arg);
    }    
    wait_for_child(pid);
    exit();
}

void main(){
    while true vodoke //el problema de esto es que , cuando termina el hijo el while se sigue ejecutando?
    // osea no termina más. Habria que separar en dos funciones cuando estoy en el hijo o cuando estoy en el padre
    pid_t pong = fork();
    if(pong == -1){
        exit(EXIT_FAILURE));
    }else{
        if(pong == 0){
            //quiere decir que estoy en el hijo pero yo no quiero printear hasta que se haya pasado la señal de hacerlo
            wait(signal, 1);
            print("pong");
            wait(signal, 2);
            print("pong");
            wait(signal, 3);
            print("pong")
        }else{
            if (pong == getpid()){
                    print("ping");
                    signal(handler, 1);
                    print("ping");
                    signal(handler, 2)
                    print("ping");
                    signal(handler, 3);    
            }

        }    
}
