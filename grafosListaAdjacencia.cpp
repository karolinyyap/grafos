#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream> 
#include <fstream>  
using namespace std;

struct Vertice;
struct Vizinho;

struct Vertice {
    int id;
    Vizinho *vizinhos;
};

struct Vizinho {
    Vertice *vizinho;
    Vizinho *proximoVizinho;
};

Vertice *grafo;

void inicializa(int tamanho){
    grafo = new Vertice[tamanho];
    for(int i = 0; i < tamanho; i++){
        grafo[i].id = i;
        grafo[i].vizinhos = NULL;
    }
}

bool vizinhoExiste(Vertice *a, Vertice *b) {
    Vizinho *atual = a->vizinhos;
    while (atual != NULL) {
        if (atual->vizinho == b) {
            return true;
        }
        atual = atual->proximoVizinho;
    }
    return false; 
}

void adicionaVizinho(Vertice *a, Vertice *b, int tipoGrafico){

    if (a == NULL || b == NULL){
        return;
    }

    //Direcionado
    Vizinho *temp = new Vizinho;
    temp->vizinho = b;
    temp->proximoVizinho = NULL;

    if(a->vizinhos == NULL){
        a->vizinhos = temp;
    } else {
        Vizinho *aux;
        aux = a->vizinhos;
        while (aux->proximoVizinho != NULL){
            aux = aux->proximoVizinho;
        }
        aux->proximoVizinho = temp;
    }

    if(tipoGrafico == 0) {
        //Não direcionado
        Vizinho *aux2;
        Vizinho *temp2 = new Vizinho;
        temp2->vizinho = a;
        temp2->proximoVizinho = NULL;

        if(!vizinhoExiste(b, a)){
            if (b->vizinhos == NULL){
                b->vizinhos = temp2;
            } else {
                aux2 = b->vizinhos;
                while (aux2->proximoVizinho != NULL){
                    aux2 = aux2->proximoVizinho;
                }
                aux2->proximoVizinho = temp2;
            }
        } 
    }
}


void criarListaAdjacencia(int tamanho, int tipoGrafico, int preenchido){
    int qtdeArestas = 0;
    if (tipoGrafico == 1) {
        qtdeArestas = tamanho * (tamanho - 1); //grafos direcionais
    } else {
        qtdeArestas = (tamanho * (tamanho - 1))/ 2; //grafos não-direcionais
    }

    int totalArestas = (qtdeArestas * preenchido) / 100;

    int arestas = 0;
    while (arestas < totalArestas){
        //Número aleatório
        int numeroAleatorio = rand() % tamanho;
        int numeroAleatorio2 = rand() % tamanho;

        int i = numeroAleatorio;
        int j = numeroAleatorio2;

        if(i != j && !vizinhoExiste(&grafo[i], &grafo[j])){           
            adicionaVizinho(&grafo[i], &grafo[j], tipoGrafico);
            arestas++;
        }
    }
}

void imprimirGrafo(int tamanho, int tipoGrafico) {
    if (tipoGrafico == 1) {
        cout << "Grafo Direcional:" << endl;
    } else {
        cout << "Grafo Nao-Direcional:" << endl;
    }

    for (int i = 0; i < tamanho; i++) {
        cout << "Vertice " << grafo[i].id << ":";
        Vizinho* aux = grafo[i].vizinhos;
        if (aux == NULL) {
            cout << " (nenhum vizinho)";
        } else {
            while (aux != NULL) {
                cout << " -> " << aux->vizinho->id;
                aux = aux->proximoVizinho;
            }
        }
        cout << endl;
    }
}

//Criando arquivo .dot
void escreverNoArquivo(int tamanho, int tipoG){
    ofstream meuArquivo;
    meuArquivo.open("grafo.dot");

    if (meuArquivo.is_open()) {
        cout << "Arquivo aberto com sucesso!" << endl;
    }

    if (tipoG == 1){
        //Direcional
        meuArquivo << "digraph G {\n";
        //Gravando no arquivo
        for(int i = 0; i < tamanho; i++){
            meuArquivo <<  i  << ";\n";
        }
        for (int i = 0; i < tamanho; i++){
            Vizinho *aux = grafo[i].vizinhos;
            while (aux != NULL){
                meuArquivo << " " << i << "->" << aux->vizinho->id << ";\n";
                aux = aux->proximoVizinho;
            }
        }


    } else {
        //Não-direcional
        meuArquivo << "graph G {\n";
        //Gravando no arquivo
        for(int i = 0; i < tamanho; i++){
            meuArquivo <<  i << ";\n";
        } 
        for (int i = 0; i < tamanho; i++){
            Vizinho *aux = grafo[i].vizinhos;
            while (aux != NULL){
                int j = aux->vizinho->id;
                if (i < j) {
                    meuArquivo << " " << i << "--" << j << ";\n";
                }
                aux = aux->proximoVizinho;
            }
        }
        
    }

    meuArquivo << "}\n";
    meuArquivo.close();
}

/*void ehConexo(int tamanho, int tipoG){
    bool *visitado = new bool[tamanho];

    for (int i = 0; i < tamanho; i++) {
        visitado[i] = false;
    }

    if (tipoG == 0){
        visitado[0] = true;
        for (int i = 0; i < tamanho; i++){
            if(visitado[i] == true){
                Vizinho *aux = grafo[i].vizinhos;
                while (aux != NULL){
                    if (){
                        visitado[i] = true;
                    }
                    aux = aux->proximoVizinho;
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
}*/

void lerArquivoDot(const char* nomeArquivo, int tipoG){
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
                adicionaVizinho(&grafo[origem], &grafo[destino], 1);
            }
        } else {
            if(fscanf(arquivo, "%d -- %d", &origem, &destino) == 2){
                adicionaVizinho(&grafo[origem], &grafo[destino], 0);
                adicionaVizinho(&grafo[destino], &grafo[origem], 0);
            }
        }
        
    }
    
    fclose(arquivo);
}

int main(){
    srand(time(NULL));
    int tamLista;
    int opcao, qtdePreenchida;

    //Tamanho da matriz
    printf("Digite o tamanho da lista: ");
    scanf("%d", &tamLista);

    //-------------------------------------------------
    //Direcionado ou não direcionado
    int tipoGrafico;

    printf("Digite o tipo do grafico (1 - direcionado / 0 - nao direcionado): ");
    scanf("%d", &tipoGrafico);
    
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Gerar grafo aleatorio\n");
        printf("2 - Imprimir lista de adjacencia\n");
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
                inicializa(tamLista);
                criarListaAdjacencia(tamLista, tipoGrafico, qtdePreenchida);
                printf("Grafo gerado com sucesso!\n");
                break;

            case 2:
                imprimirGrafo(tamLista, tipoGrafico);
                break;

            case 3:
                escreverNoArquivo(tamLista, tipoGrafico);
                break;

            case 4:
                lerArquivoDot("grafo.dot", tipoGrafico);
                printf("Grafo lido do arquivo com sucesso!\n");
                break;

            case 5:
                //ehConexo(matriz_dinamica, tamMatriz, tipoGrafico);
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