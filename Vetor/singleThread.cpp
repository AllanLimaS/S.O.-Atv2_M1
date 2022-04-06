#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;
using namespace chrono;

const long int TAM = 400000;

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

void vetor_int(){
    int vetor[TAM];
    long int vetorSum = 0;
    long int i;

    for(i = 0 ; i < TAM ; i++){
        vetor[i] = 22;
        //vetor[i] = rand() % 1000;
        vetorSum = vetorSum + vetor[i];  
        //cout<<".";
    }
    cout<<endl<< "soma do vetor de inteiros: " <<vetorSum;
}

void vetor_float(){
    float vetor[TAM];
    float vetorSum = 0;
    long int i;

    for(i = 0 ; i < TAM ; i++){
        vetor[i] = 22.2;
        vetor[i] = rand()%100;
        vetor[i] = vetor[i]/100 + rand()%100;
        vetorSum = vetorSum + vetor[i];  
        //cout<<".";
    }
    cout<<endl<< "soma do vetor de floats: " <<vetorSum;
}


int main()
{
    srand (time(NULL));
    {
    Timer timer;
        vetor_int();
    }
    {
    Timer timer;
        vetor_float();
    }
    return 0;
}
