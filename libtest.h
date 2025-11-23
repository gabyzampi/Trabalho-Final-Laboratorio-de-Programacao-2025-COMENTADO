//inicio
#ifndef LIBTEST_H
#define LIBTEST_H

#include "libestruturas.h" //Importa pois o tese utliza as funçoes da lib
#include <stdio.h>//Entrada/Saida File

//Struct para cada teste
typedef struct {
    char operacao[20]; //Guarda o nome da operação
    int valor;         //O valor inserido
    char esperado[100];//Resultado esperado
} Teste; 

//Fução executa teste
int executarTeste(Teste* t, Pilha* p, Fila* f, char* buffer);
//Teste* t = o teste que vai realizar
//Pipla* p = a pilha para testar as operações
//Fila* f = a fila para testa as operações
//char* buffer = onde sera guardado o resultado caso impresso

//Função salva os resultados do teste no arquivo
void registrarResultado(FILE* out, int n, Teste* t, char* obtido, int ok);
//File* out = ponteiro parao arquivo de saida, ode seram salvas as informações
//int n = serve para contar a quantidade de teste e numerar no arquivo
//Teste * t = Ponteiro para a struct, que guarda a operação do teste (t diz o que deve acontecer)
//char* obtido = string que tem o resultado obtido ao executar o teste e sera comparada ao t->esperado
//int ok = indica sucesso ou falha ok = 1 certo e ok = 0 errado


//fim
#endif
