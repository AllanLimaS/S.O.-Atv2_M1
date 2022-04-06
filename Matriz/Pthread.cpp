#include <iostream>
#include <time.h>
#include <chrono>
#include <pthread.h>

#define NUM_THREADS 2

pthread_mutex_t exclusao_mutua = PTHREAD_MUTEX_INITIALIZER;

using namespace std;
using namespace chrono;

const  int TAM = 500;

class Timer
{
public:
	Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		Stop();
	}

	void Stop()
	{
		auto entTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
		auto stop = std::chrono::time_point_cast<std::chrono::milliseconds>(entTimepoint).time_since_epoch().count();

		auto duration = stop - start;
		double s = duration * 0.001;

		std::cout << "\nTempo da Rotina: " << duration << " microsegundos"<<endl;
	}
private:
	std::chrono::time_point< std::chrono::high_resolution_clock> m_StartTimepoint;
};


void imprime_matriz(int matriz[TAM][TAM]){
    for(int i = 0; i <TAM ; i++){
        for(int j = 0; j < TAM ; j++){
            cout<<"["<<matriz[i][j]<<"]\t";
        }
        cout<<endl;
    }
}

void preenche_matriz(long int matriz[TAM][TAM]){
    for(int i = 0; i <TAM ; i++){
        for(int j = 0; j < TAM ; j++){
            matriz[i][j] = rand() % 10;
        }
    }
}

void *multiplicacao_matricial(void *){
    long int matrizA[TAM][TAM];
    long int matrizB[TAM][TAM];
    long int matrizC[TAM][TAM];
    preenche_matriz(matrizB);
    preenche_matriz(matrizA);

    {
    Timer time;
    for(int i = 0; i <TAM ; i++){
        for(int j = 0; j < TAM ; j++){
            matrizC[i][j] = matrizA[i][j] * matrizB[j][i];
        }
    }
    }

    cout<<"resultado da operacao matricial: "<<endl;
    //imprime_matriz(matrizC);
}

void *multiplicacao_posicional(void *){
    long int matrizA[TAM][TAM];
    long int matrizB[TAM][TAM];
    long int matrizC[TAM][TAM];
    preenche_matriz(matrizB);
    preenche_matriz(matrizA);

    {
    Timer time;
    for(int i = 0; i <TAM ; i++){
        for(int j = 0; j < TAM ; j++){
            matrizC[i][j] = matrizA[i][j] * matrizB[i][j];
        }
    }
    }

    cout<<"resultado da operacao posicional: "<<endl;
    //imprime_matriz(matrizC);
}

int main()
{

    pthread_t threads_mult;
    pthread_t threads_pos;
    srand (time(NULL));
   
    pthread_create(&threads_mult,NULL, multiplicacao_matricial,NULL);
    pthread_create(&threads_pos,NULL, multiplicacao_posicional,NULL);
    pthread_join(threads_mult,NULL);
    pthread_join(threads_pos,NULL);

    return 0 ;
}
