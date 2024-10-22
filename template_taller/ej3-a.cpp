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

void f(int k, vector<int>* v1, vector<int>* v2 , vector<int>* res){
	for (int i= 0 ; i < 20; i++){
		(*res)[i + k*20] = (*v1)[i + k*20] * (*v2)[i + k*20];
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
    	threads.emplace_back(f,i, &v1, &v2, &res);
    }
    // TO-DO 
    for(auto& t: threads ){
	t.join();
    }

    verify(v1, v2, res);

    return 0;
}
