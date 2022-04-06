#include <iostream>
#include <time.h>
#include <chrono>


using namespace std;
using namespace chrono;

const long int TAM = 500;

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

void imprime_matriz(long int matriz[TAM][TAM]){
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

void multiplicacao_matricial(long int A[TAM][TAM], long int B[TAM][TAM], long int C[TAM][TAM]){
    {
    Timer time;
    for(int i = 0; i <TAM ; i++){
        for(int j = 0; j < TAM ; j++){
            C[i][j] = A[i][j] * B[j][i];
        }
    }
    }
}

void multiplicacao_posicional(long int A[TAM][TAM], long int B[TAM][TAM], long int D[TAM][TAM]){
    {
    Timer time;
    for(int i = 0; i <TAM ; i++){
        for(int j = 0; j < TAM ; j++){
            D[i][j] = A[i][j] * B[i][j];
        }
    }
    }
}

int main()
{
    srand (time(NULL));

    long int matrizA[TAM][TAM];
    long int matrizB[TAM][TAM];
    long int matrizC[TAM][TAM];
    long int matrizD[TAM][TAM];

    preenche_matriz(matrizB);
    preenche_matriz(matrizA);
    cout<<endl<<"imprimindo matriz A..."<<endl;
    //imprime_matriz(matrizA);
    cout<<endl<<"imprimindo matriz B..."<<endl;
    //imprime_matriz(matrizB);
    
    multiplicacao_matricial(matrizA,matrizB,matrizC);
    multiplicacao_posicional(matrizA,matrizB,matrizD);

    cout<<"resultado da operacao matricial: "<<endl;
    //imprime_matriz(matrizC);

    cout<<"resultado da operacao posicional: "<<endl;
    //imprime_matriz(matrizD);
    return 0 ;
}
