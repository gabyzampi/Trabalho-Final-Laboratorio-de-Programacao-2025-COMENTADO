#include "libestruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializações

void iniciaPilha(Pilha* p) {
    p->topo = NULL;
}
//Aponta para o topo que é NULL (vazia)


void iniciaFila(Fila* f) {
    f->frente = NULL;
    f->tras = NULL;
}
//Ambos frente e tras apontam para NULL(vazia)


//Verificação

int pilhaVazia(Pilha* p) {
    return p->topo == NULL;
}
//Se topo NULL, Pilha vazia


int filaVazia(Fila* f) {
    return f->frente == NULL;
}
//Se frente NULL, Fila vazia


// ==================================== Pilha ====================================
void push(Pilha* p, int v) {
    NodeP* novo = malloc(sizeof(NodeP));///Cria/Reserva espaço para novo nó com a função malloc
    novo->valor = v;//Armazena o valor
    novo->prox = p->topo;//Vai apontar para antigo Topo, pois pila é embaixo
    p->topo = novo;//O Topo agora é  o novo nó
}//Função Inserir

int pop(Pilha* p) {
    if (pilhaVazia(p)) return 0;//Faz a verificação
    NodeP* temp = p->topo;//Cria uma variavel ponteiro temporaria para o no Topo
    int val = temp->valor;//Cria uma varavel int val para guardar o valor que esta nesse nó
    p->topo = temp->prox;//Move o Topo para o proximo
    free(temp);//Libera a memoria do nó
    return val;//Retorna o Valor
}//Função Remover

int top(Pilha* p) {
    if (pilhaVazia(p)) return 0;//Faz a verificação
    return p->topo->valor;//Retorna o Topo sem remover
}//Vizualizar Topo


//Nao esta como pedido no trabalho
// Imprime pilha no formato [20, 10], concatenada
//strcat (destino,origem)
void visualizarPilha(Pilha* p, char* buffer) {
    buffer[0] = '\0';//Inicia como string vazia
    strcat(buffer, "[");//Adiciona ao final da string do buffer [

    NodeP* atual = p->topo;//Ponteiro atual que começa no Topo
    while (atual) {       //enquanto existir atual !=NULL, percorre o laço
        char aux[20];     //decla um array local, com espaço 19 + \0
        sprintf(aux, "%d", atual->valor);//Formata o valor int para string e armazena em aux
        strcat(buffer, aux);//Concatena "[aux"

        if (atual->prox) strcat(buffer, ", ");//Se tem proximo nó, adiciona virgula
        atual = atual->prox;//Avança para o prox e conclui o while
    }
    strcat(buffer, "]");//Pega o buffer e adiciona ] no final
}



//========================================= Fila =======================================
void enqueue(Fila* f, int v) {
    NodeF* novo = malloc(sizeof(NodeF));//Cria/Reserva espaço para o ponteiro novo 
    novo->valor = v;// Recebe o valor 
    novo->prox = NULL;//Prox sempre aponta para NULL, pois é sempre o ultimo a ser inserido

    if (filaVazia(f)) {//Faz a verificação
        f->frente = novo;//Se vazia frente sera novo
    } else {
        f->tras->prox = novo; //Se nao, liga o no prox do atual ao novo
    }
    f->tras = novo;//Independente tras atualiza para apontar para novo
}//Inserir na Fila (por tras)


int dequeue(Fila* f) {
    if (filaVazia(f)) return 0;//Faz a verificação
    NodeF* temp = f->frente;//Cria um ponteiro temp para receber nó frente
    int val = temp->valor;//Cria uma variavel int para guardar o valor
    f->frente = temp->prox;//Atualiza o nó frente para o proximo (pode ficar NULL)
    if (!f->frente) f->tras = NULL;//Verifica se a Fila ficou vazia, faz tbm com que tras seja NULL
    free(temp);//Libera a momeria do nó
    return val;//Retorna o valor
}//Remover da Fila (pela frente)


void visualizar(Fila* f, char* buffer) {
    buffer[0] = '\0';//Inicia como string vazia
    strcat(buffer, "[");//coloca [                       //strcat (destino,origem) 

    NodeF* atual = f->frente;//Cria um ponteiro atual que começa na frente
    while (atual) {  //Enquano for atual ou seja diferente de NULL, percorre o laço
        char aux[20]; //decla um array local, com espaço 19 carac + \0
        sprintf(aux, "%d", atual->valor);//A função sprintf formata os dados em uma string, no caso não osnumeros direto, mas os coloca no aux
        strcat(buffer, aux);//Ex: [ 30

        if (atual->prox) strcat(buffer, ", ");//Verifica se tem um proximo ecoloca , Ex: [ 30, 
        atual = atual->prox;//Avança para o prox e conclui o while
    }
    strcat(buffer, "]");//Ex : [ 30, 50, 60]
}//Vizualiza a fila
