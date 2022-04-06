#include <iostream>
#include <time.h>
#include <chrono>
#include <pthread.h>

#define NUM_THREADS 4

pthread_mutex_t exclusao_mutua = PTHREAD_MUTEX_INITIALIZER;

using namespace std;
using namespace chrono;

const long int TAM = 400000;

long int vetorSumI = 0;
int sumI[NUM_THREADS] = { 0 };
float vetorSumF = 0;
float sumF[NUM_THREADS] = { 0 };
int part = 0;

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

void *vetor_int(void *){
    int vetor[TAM];
    long int i;

    int thread_part = part++;
    
    for (int i = thread_part * (TAM / 4); i < (thread_part + 1) * (TAM / 4); i++){
        vetor[i] = 22;
        //vetor[i] = rand() % 1000;
        sumI[thread_part] += vetor[i];
        //cout<<".";
    }

}

void *vetor_float(void *){
    float vetor[TAM];
    long int i;

    int thread_part = part++;
    
    for (int i = thread_part * (TAM / 4); i < (thread_part + 1) * (TAM / 4); i++){
        vetor[i] = 22.2;
        //vetor[i] = rand()%100;
        //vetor[i] = vetor[i]/100 + rand()%100;
        sumF[thread_part] += vetor[i];
        //cout<<".";
    }

}


int main()
{
    
    pthread_t threads_int[NUM_THREADS];
    pthread_t threads_float[NUM_THREADS];
    
    {
    Timer timer;
    
        for(int i = 0; i < NUM_THREADS; i++ ) {
        cout << "main() : creating thread, " << i << endl;
        pthread_create(&threads_int[i], NULL, vetor_int,NULL);
        }
        
        for(int i = 0; i < NUM_THREADS; i++ ) {
        pthread_join(threads_int[i],NULL);
        }

        for(int i = 0; i < NUM_THREADS; i++){
            vetorSumI += sumI[i];
        } 
    }
    cout<<"valor da soma: "<< vetorSumI<<endl;
    part = 0;
    {  
    Timer timer;
        for(int i = 0; i < NUM_THREADS; i++ ) {
        cout << "main() : creating thread, " << i << endl;
        pthread_create(&threads_float[i], NULL, vetor_float,NULL);
        }
        
        for(int i = 0; i < NUM_THREADS; i++ ) {
        pthread_join(threads_float[i],NULL);
        }

        for(int i = 0; i < NUM_THREADS; i++){
            vetorSumF += sumF[i];
        } 
    
    }
    cout<<"valor da soma: "<< vetorSumF<<endl;

    return 0;

}
