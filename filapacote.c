#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //para utilizar sleep

// NÓ DA FILA
struct Pacote {
    int bytes;
    struct Pacote *prox;
};

typedef struct Pacote Pacote;

void desenharTransferencia(int enviados, int total, int pontos, int numeroPacote, int bytesPacote) {

    system("clear"); //torna a animaçao dinamica

    printf("\nOrigem: ");

    for(int i = 0; i < enviados; i++) {
        printf(" "); //pacotes que ja sairam da fila
    }

    for(int i = enviados; i < total; i++) {
        printf("▢"); //pacotes que ainda serao enviados
    }

    printf(" ");

    for(int i = 0; i < pontos; i++) {
        printf("."); //animacao dos 3 pontos
    }

    printf("      Destino: ");

    for(int i = 0; i < enviados; i++) {
        printf("▢"); //pacotes recebidos
    }

    printf("\n\nEnviando pacote %d de %d bytes\n", numeroPacote, bytesPacote); //pacote enviado no momento e oo seu tamanho de bytes
}

int main() {
    //começo com a fila vazia
    Pacote *inicio = NULL;
    Pacote *fim = NULL;

    int tamanhoArquivo;
    int tamanhoPacote;

    printf("TRANSFERINDO PACOTES DE BYTES UTILIZANDO FILAS:\n");

    printf("Tamanho total do arquivo em bytes: ");
    scanf("%d", &tamanhoArquivo);

    printf("Tamanho maximo do pacote em bytes: ");
    scanf("%d", &tamanhoPacote);

    int pacotesInteiros = tamanhoArquivo / tamanhoPacote; //pacotes completos
    int pacoteQuebrado = tamanhoArquivo % tamanhoPacote; //ultimo pacote menor

    for(int i = 1; i <= pacotesInteiros; i++) { 

        Pacote *novo = (Pacote*) malloc(sizeof(Pacote)); //criando pacotes completos

        novo->bytes = tamanhoPacote;
        novo->prox = NULL; //indica que é o ultimo da fila

        if(inicio == NULL) { //se a fila estiver vazia
            inicio = novo;
            fim = novo;
        }
        else { //fila ja possui elementos
            fim->prox = novo; 
            fim = novo;
        }
    }

    if(pacoteQuebrado > 0) { //se houver o ultimo pacote menor ou for criado apenas um pacote menor

        Pacote *novo = (Pacote*) malloc(sizeof(Pacote));

        novo->bytes = pacoteQuebrado;
        novo->prox = NULL;

        if(inicio == NULL) { //se a fila estiver vazia
            inicio = novo;
            fim = novo;
        }
        else {
            fim->prox = novo;
            fim = novo;
        }
    }

    int countPacotes; //calculando a quantidade de pacotes criados

    if(pacoteQuebrado > 0) {
        countPacotes = pacotesInteiros + 1;
    }
    else {
        countPacotes = pacotesInteiros;
    }

    printf("\nPacotes criados: %d", countPacotes);
    sleep(2);

    printf("\n\nENVIANDO PACOTES...\n");
    sleep(2);
    system("clear");

    int enviados = 0; //quantos pacotes ja foram enviados
    int numeroPacote = 1; //numero atual do pacote que estou enviando

    while(inicio != NULL) { //enquanto a fila nao estiver vazia

        int bytesPacote = inicio->bytes; //quantidades de bytes de cada pacote

        for(int pontos = 1; pontos <= 3; pontos++) { //para os 3 pontos

            desenharTransferencia(enviados, countPacotes, pontos, numeroPacote, bytesPacote);
            sleep(2);
        }
        
        //preparando para remover o pacote
        Pacote *aux = inicio; //utilizo um ponteiro auxiliar
        inicio = inicio->prox; //o segundo da fila passa a ser o novo inicio
        free(aux); //libero a memoria do antigo no inicial
        
        //atualizando variaveis de controle
        enviados++;
        numeroPacote++;
    }

    system("clear");
    
    //exibiçao final para o usuario
    printf("\nOrigem: ");

    for(int i = 0; i < countPacotes; i++) {
        printf(" ");
    }

    printf("      Destino: ");

    for(int i = 0; i < countPacotes; i++) {
        printf("▢");
    }

    printf("\n\nTransferencia concluida!\n");

    return 0;
}