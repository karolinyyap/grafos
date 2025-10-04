#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream> 
#include <fstream>  
using namespace std;

void inicializar(int **matriz, int tamanho){
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            matriz[i][j] = 0;
        }
    }
}

void completarMatriz(int **matriz, int tamanho, int tipoG, int porcentagem){


    int qtdeArestas = 0;
    if (tipoG == 1) {
        qtdeArestas = tamanho * (tamanho - 1); //grafos direcionais
    } else {
        qtdeArestas = (tamanho * (tamanho - 1))/2; //grafos não-direcionais
    }

    int totalArestas = (qtdeArestas * porcentagem) / 100;

    int arestas = 0;
    while (arestas < totalArestas){
        int numeroAleatorio = rand() % tamanho;
        int numeroAleatorio2 = rand() % tamanho;

        int i = numeroAleatorio;
        int j = numeroAleatorio2;

        if(i != j && matriz[i][j] == 0){           
            matriz[i][j] = 1;
            if (tipoG == 0){
                matriz[j][i] = 1;
            }
            arestas++;
        }
        

    }
}

void imprimirMatriz(int** matriz, int tamanho) {
    printf("\nMatriz de Adjacencia Gerada:\n");
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void escreverNoArquivo(int **matriz, int tamanho, int tipoG){
    ofstream meuArquivo;
    meuArquivo.open("grafo.dot", ios::app);

    if (meuArquivo.is_open()) {
        cout << "Arquivo aberto com sucesso!" << endl;
    }

    if (tipoG == 1){
        meuArquivo << "digraph G {\n";
    } else {
        meuArquivo << "graph G {\n";
    }

    for (int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if(matriz[i][j] == 1){
                if(tipoG == 1){
                    meuArquivo << " " << i << "->" << j << ";\n";
                } else {
                    meuArquivo << "  " << i << " -- " << j << ";\n";
                }
            }
        }
    }

    meuArquivo << "}\n";
    meuArquivo.close();
}

void conexo(){
    
}

int main(){
    srand(time(NULL));
    int tamMatriz;

    //Tamanho da matriz
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &tamMatriz);

    //-------------------------------------------------
    //Direcionado ou não direcionado
    int tipoGrafico;

    printf("Digite o tipo do grafico (1 - direcionado/0 - nao direcionado): ");
    scanf("%d", &tipoGrafico);

    //-------------------------------------------------
    //Porcentagem preenchida
    int qtdePreenchida;
    printf("Digite a quantidade de arestas a serem preenchidas: ");
    scanf("%d", &qtdePreenchida);
    
    int linhas = tamMatriz;
    int colunas = tamMatriz;

    int** matriz_dinamica = new int*[linhas];

    for (int i = 0; i < linhas; ++i) {
        matriz_dinamica[i] = new int[colunas];
    }
    
    inicializar(matriz_dinamica, tamMatriz);
    completarMatriz(matriz_dinamica, tamMatriz, tipoGrafico, qtdePreenchida);
    imprimirMatriz(matriz_dinamica, tamMatriz);
    escreverNoArquivo(matriz_dinamica, tamMatriz, tipoGrafico);

    return 0;
}