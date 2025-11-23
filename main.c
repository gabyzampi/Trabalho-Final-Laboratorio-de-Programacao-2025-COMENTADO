#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libestruturas.h"
#include "libtest.h"

#define MAX_LINE 200
//Tamanho maximo de linhas


//validação de argumentos
int main(int argc, char* argv[]) {
//argc numero de argumentos
//argv vetor de string com os argumentos

    if (argc != 3) {
        printf("Uso: %s <testes.txt> <resultados.txt>\n", argv[0]);//argv[0] imprime o nome do programa
        return 1;
    }

    FILE* in = fopen(argv[1], "r");// abre o arquivo teste para ler
    FILE* out = fopen(argv[2], "w");// abre o arquivo resultados para escrever

    if (!in || !out) {
        printf("Erro abrindo arquivos.\n");//se algum nao abrir para
        return 1;
    }

    Pilha p; // cria pilha
    Fila f; // cria fila
    iniciaPilha(&p); //inicializa
    iniciaFila(&f); //inicializa

    char linha[MAX_LINE];//cada linha de teste
    int n = 1; // contador de testes

    //laço para ler linhas do arquivode entrada
    while (fgets(linha, MAX_LINE, in)) {
        if (strlen(linha) < 2) continue;// geralmente tem \n ou \0 que tem tamanho 1 entao <2 vazio, continue faz o programa ignorar a linha e pular para proxima

        Teste t; // a struct teste que guarda, operação, valor  e esperado
        t.valor = 0; // valor caso a linha nao tenha

        char separ[3]; //auxiliar para armazenar "|"

        //strstr busca | em linha , que significa que nao foi passado valor (Operação|Esperado)
        if (strstr(linha, "|")) {
            sscanf(linha, "%s %2s %[^\n]", t.operacao, separ, t.esperado);
            //%s le a operaçao, %2s le dois carac do separador
            //%[^\n]le tuda a linha e gurada em esperado
        }
        else {//com numero separado
            sscanf(linha, "%s %d %99[^\n]", t.operacao, &t.valor, t.esperado);
        }

        char obtido[200]; //onde fica a funçao testada
        int ok = executarTeste(&t, &p, &f, obtido);//executa e compara com o esperado

        registrarResultado(out, n++, &t, obtido, ok);//resgistra no arquivo de saida
    }

    fclose(in);//fecha o arquivo
    fclose(out);//fecha o arquivo

    printf("Testes concluídos. Resultados gravados em %s\n", argv[2]);
    return 0;
}
