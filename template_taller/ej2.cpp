#include <thread>
#include <iostream>
#include <semaphore.h>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

//16:37
#define MSG_COUNT 1

sem_t uno;
sem_t dos;

void f1_a(string s){
	for(int i = 0 ; i < MSG_COUNT ; i++){
		cout << "EJECUTANDO F1 (A) " << s << "\n"; 
		this_thread::sleep_for(100ms);
	}
}

void f1_b(string s){
	for(int i = 0 ; i < MSG_COUNT ; i++){
		cout << "EJECUTANDO F1 (B) " << s << "\n"; 
		this_thread::sleep_for(200ms);
	}
}

void f2_a(string s){
	for(int i = 0 ; i < MSG_COUNT ; i++){
		cout << "EJECUTANDO F2 (A) " << s << "\n"; 
		this_thread::sleep_for(500ms);
	}
}

void f2_b(string s){
	for(int i = 0 ; i < MSG_COUNT ; i++){
		cout << "EJECUTANDO F2 (B) " << s <<"\n";
		this_thread::sleep_for(10ms);
	}
}

void f1() {
	string b1 = "hijo1b";
	string a1 = "hijo1a";
	f1_a(a1);
	sem_post(&uno);
	sem_wait(&dos);
	f1_b(b1);
}

void f2() {
	f2_a("hijo2a");
	sem_post(&dos);
	sem_wait(&uno);
	f2_b("hijo2b");  
}

int main() {
	sem_init(&uno,1, 0 );
	sem_init(&dos, 1, 0);
	
	vector<thread> threads;
	threads.emplace_back(f1);
	threads.emplace_back(f2);
	
	
	for(auto& t: threads){	
		t.join();
	}
	sem_destroy(&uno);
	sem_destroy(&dos);
	return 0;
}

int res = main();


