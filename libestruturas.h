//inicio
#ifndef LIBESTRUTURAS_H 
#define LIBESTRUTURAS_H

//Estrutura da Pilha LIFO
typedef struct NodeP {
    int valor;
    struct NodeP* prox;
} NodeP;//Nó da pilha

//Ponteiro para Topo da Piha
typedef struct {
    NodeP* topo;
} Pilha;


//Funçoes da Pilha
void iniciaPilha(Pilha* p); //topo = NULL
void push(Pilha* p, int v); //insere no topo
int pop(Pilha* p);//remove do topo
int top(Pilha* p);//Vizualiza topo
//void visualizarPilha(Pilha* p, char* buffer);//imprime dentro de um buffer de texto



//Estrura da Fila FIFO
typedef struct NodeF {
    int valor;
    struct NodeF* prox;
} NodeF;//Nó da Fila

//Ponteiros elementos frente e tras
typedef struct {
    NodeF* frente;//Saida dos elementos sempre pela frente (dequeue)
    NodeF* tras;//Entrada dos elementos sempre por tras (enqueue)
} Fila;

//Funções da Fila
void iniciaFila(Fila* f);//Frente e tras = NULL
void enqueue(Fila* f, int v);//Insere o valor por tras 
int dequeue(Fila* f);//Remove o valor pela frente
void visualizar(Fila* f, char* buffer);//Imprime a Fila em um Buffer de Texto

//fim
#endif
