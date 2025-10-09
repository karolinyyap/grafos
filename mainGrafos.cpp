#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream> 
#include <fstream>  
using namespace std;

//Inicializando matriz
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
        qtdeArestas = (tamanho * (tamanho - 1))/ 2; //grafos não-direcionais
    }

    int totalArestas = (qtdeArestas * porcentagem) / 100;

    int arestas = 0;
    while (arestas < totalArestas){
        //Número aleatório
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

//Imprimindo a matriz
void imprimirMatriz(int** matriz, int tamanho) {
    printf("\nMatriz de Adjacencia Gerada:\n");
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

//Criando arquivo .dot
void escreverNoArquivo(int **matriz, int tamanho, int tipoG){
    ofstream meuArquivo;
    meuArquivo.open("grafo.dot");

    if (meuArquivo.is_open()) {
        cout << "Arquivo aberto com sucesso!" << endl;
    }

    if (tipoG == 1){
        meuArquivo << "digraph G {\n";
        //Gravando no arquivo
        for(int i = 0; i < tamanho; i++){
            meuArquivo <<  i << ";\n";
        }
        for (int i = 0; i < tamanho; i++){
            for(int j = 0; j < tamanho; j++){
                if(matriz[i][j] == 1){
                    meuArquivo << " " << i << "->" << j << ";\n";
                }
            }
        }

    } else {
        meuArquivo << "graph G {\n";
        //Gravando no arquivo
        for(int i = 0; i < tamanho; i++){
            meuArquivo <<  i << ";\n";
        }
        for (int i = 0; i < tamanho; i++){
            for(int j = i+1; j < tamanho; j++){
                if(matriz[i][j] == 1){
                    meuArquivo << "  " << i << " -- " << j << ";\n";
                }
            }
        }
    }

    
    meuArquivo << "}\n";
    meuArquivo.close();
}

void ehConexo(int **matriz, int tamanho, int tipoG){
    bool *visitado = new bool[tamanho];

    for (int i = 0; i < tamanho; i++) {
        visitado[i] = false;
    }

    if (tipoG == 0){
        visitado[0] = true;
        for (int i = 0; i < tamanho; i++){
            if(visitado[i] == true){
                for(int j = 0; j < tamanho; j++){
                    if(matriz[i][j] == 1){
                        visitado[j] = true;
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < tamanho; i++){
            visitado[0] = true;
            for (int j = 0; j < tamanho; j++){
                if(visitado[j] == true){
                    for(int k = 0; k < tamanho; k++){
                        if(matriz[j][k] == 1){
                            visitado[k] = true;
                        }
                    }
                }
            }
        }
    }
    

    bool conexo = true;
    for(int i = 0; i < tamanho; i++){
        if(visitado[i] == false){
            conexo = false;
            break;
        }
    }

    if(conexo){
        cout << "\nEh conexo!!" << endl;
    } else {
        cout << "\nNao eh conexo!!" << endl;
    }
}

void lerArquivoDot(const char* nomeArquivo, int tipoG, int **matriz){
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char linha[100];
    int origem, destino;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if(tipoG ==  1){
            if(fscanf(arquivo, "%d -> %d", &origem, &destino) == 2){
                matriz[origem][destino] = 1;
            }
        } else {
            if(fscanf(arquivo, "%d -- %d", &origem, &destino) == 2){
                matriz[origem][destino] = 1;
                matriz[destino][origem] = 1;
            }
        }
        
    }
    
    fclose(arquivo);
}

int main(){
    srand(time(NULL));
    int tamMatriz;
    int opcao, qtdePreenchida;

    //Tamanho da matriz
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &tamMatriz);

    //-------------------------------------------------
    //Direcionado ou não direcionado
    int tipoGrafico;

    printf("Digite o tipo do grafico (1 - direcionado / 0 - nao direcionado): ");
    scanf("%d", &tipoGrafico);
    
    int linhas = tamMatriz;
    int colunas = tamMatriz;

    int** matriz_dinamica = new int*[linhas];

    for (int i = 0; i < linhas; ++i) {
        matriz_dinamica[i] = new int[colunas];
    }
    
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Gerar grafo aleatorio\n");
        printf("2 - Imprimir matriz de adjacencia\n");
        printf("3 - Salvar grafo em arquivo .dot\n");
        printf("4 - Ler grafo do arquivo .dot\n");
        printf("5 - Verificar se eh conexo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a porcentagem de arestas: ");
                scanf("%d", &qtdePreenchida);
                inicializar(matriz_dinamica, tamMatriz);
                completarMatriz(matriz_dinamica, tamMatriz, tipoGrafico, qtdePreenchida);
                printf("Grafo gerado com sucesso!\n");
                break;

            case 2:
                imprimirMatriz(matriz_dinamica, tamMatriz);
                break;

            case 3:
                escreverNoArquivo(matriz_dinamica, tamMatriz, tipoGrafico);
                break;

            case 4:
                inicializar(matriz_dinamica, tamMatriz);
                lerArquivoDot("grafo.dot", tipoGrafico, matriz_dinamica);
                printf("Grafo lido do arquivo com sucesso!\n");
                break;

            case 5:
                ehConexo(matriz_dinamica, tamMatriz, tipoGrafico);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}