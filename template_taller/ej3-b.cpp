#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <cassert>

#define N 100
#define THREAD_COUNT 5

using namespace std;


void verify(vector<int> v1, vector<int> v2, vector<int> v3) {
    cout << "v1 = [" << v1[0] << ", " << v1[1] << ", " << ", ..., " << v1[N - 2] << ", " << v1[N - 1] << "]" << endl;
    cout << "v2 = [" << v2[0] << ", " << v2[1] << ", " << ", ..., " << v2[N - 2] << ", " << v2[N - 1] << "]" << endl;
    cout << "v3 = [" << v3[0] << ", " << v3[1] << ", " << ", ..., " << v3[N - 2] << ", " << v3[N - 1] << "]" << endl;

    for (int i = 0; i < N; ++i) {
        assert(v3[i] == v1[i] * v2[i]);
    }
}
atomic<int> count;
vector<int> n_x_thread[5];

void f(int i,vector<int>* v1, vector<int>* v2 , vector<int>* res){
	int r = 0;
	while((r= count++) < N){		
		(*res)[r] = (*v1)[r] * (*v2)[r];
		n_x_thread[i]++;
		this_thread::sleep_for(100 ms* (i+1));
	}   
}

int main() {
    vector<int> v1(N);
    vector<int> v2(N);
    iota(v1.begin(), v1.end(), 1);
    iota(v2.begin(), v2.end(), N + 1);
    
    vector<int> res(N);
    
    vector<thread> threads;
    for (int i = 0 ; i<5; i++){    	
    	threads.emplace_back(f,i  &v1, &v2, &res);
    }
    
    for(auto& t: threads ){
	t.join();
    }

    verify(v1, v2, res);

    return res;
}
