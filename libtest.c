#include "libtest.h"
#include <string.h>

int executarTeste(Teste* t, Pilha* p, Fila* f, char* buffer) {
    buffer[0] = '\0'; //Inicializa o buffer com \0, para nao ter lixo

    //strcmp compara se t-> operação e push são iguais

    if (strcmp(t->operacao, "PUSH") == 0) {//Vericar se é Inserir na Pilha, se retornar 0 , é PUSH
        push(p, t->valor);  //chama a função, passando a pilha e o t->valor
        visualizarPilha(p, buffer); //Apos push, o buffer tera a saida que sera comparada com t-> esperado
    }
    else if (strcmp(t->operacao, "POP") == 0) {//Vericar se é Remover da Pilha, se retornar 0 , é POP
        int r = pop(p);     //Chama a função para remover e guarda o valor retornado em r(se estiver vazia pode retornar 0)
        sprintf(buffer, "%d", r);//Formata r par striing e o coloca no buffer (r == 5 passa "5")
    }
    else if (strcmp(t->operacao, "TOP") == 0) {//Vericar se é ver Topo da Pilha, se retornar 0 , é TOP
        int r = top(p);     //Chama a função para ver o topo sem remover e guarda o valor retornado em r(se estiver vazia é 0)
        sprintf(buffer, "%d", r);//Formata r par striing e o coloca no buffer (r == 5 passa "5")
    }
    else if (strcmp(t->operacao, "ENQUEUE") == 0) {//Vericar se é Inserir na fila, se retornar 0 , é ENQUEUE
        enqueue(f, t->valor);  //Chama a função de inserir passando a fila e t->valor
        visualizar(f, buffer); // Chama vizualizar que monta no buffer como ela esta atualmente, e guarda a string para ser comparda com t->esperado
    }
    else if (strcmp(t->operacao, "DEQUEUE") == 0) {//Vericar se é Remover da Fila, se retornar 0 , é DEQUEUE
        int r = dequeue(f);   //Chama a função para remover e guarda o valor retornado em r(se estiver vazia sera 0)
        sprintf(buffer, "%d", r);//Formata r par striing e o coloca no buffer (r == 5 passa "5")
    }
    else if (strcmp(t->operacao, "VISUALIZAR") == 0) {//Vericar se é Vizualizar Fila, se retornar 0 , é Visualizar
        visualizar(f, buffer); //Chama a função para escrever no buffer a representação atual da fila(sem mudar)
    }
    else {
        //Opeção nao encontrada
        sprintf(buffer, "ERRO: Operacao '%s' invalida", t->operacao);
        return 0; //Automatico sera ERRO
    }


    int comparacaoNormal = (strcmp(buffer, t->esperado) == 0);
    //comparacaoNormal recebe o resultado
    //Compara o buffer e o t->esperado
    //Vai retornar 1 se bater e 0 se nao bater

    //Sera 1 caso seja seja esperado vazio
    int vazioEsperado = (
        strcmp(t->esperado, "0") == 0 ||
        strcmp(t->esperado, "NULL") == 0 ||
        strcmp(t->esperado, "0/NULL") == 0
    );

    //Sera 1 se a saida real for 0, string vazia
    int vazioObtido = (
    strcmp(buffer, "0") == 0 ||
    strcmp(buffer, "") == 0 ||
    strcmp(buffer, "NULL") == 0
);

    return comparacaoNormal || (vazioEsperado && vazioObtido);
    //retorna 1 se as string forem iguais
    //ou o esperado é vazio e obitido tbm
    // 0 sera falha
   
}



//Registra no arquivo de saida
void registrarResultado(FILE* out, int n, Teste* t, char* obtido, int ok) {
    fprintf(out,
        "Teste %d: %s(%d) = %s -> %s\n",
        n, t->operacao, t->valor,
        obtido,
        ok ? "OK" : "ERROR"
    );//Escreve no arquivo, n, operação, valor, obitido, ok ou erro

    // Só mostra alertas se o teste estiver errado
    if (!ok) { //se for 0
        int tam = strlen(obtido);// usamos para saber se a string esta vazia ou nao

        if (obtido==NULL){
            fprintf(out, "ALERTA: Resultado retornou NULL inesperadamente!\n");
        }
        if (strstr(obtido, "Operacao") != NULL) {
            fprintf(out, "  ALERTA: A operação informada não existe.\n");
            return;
        }//A operaçao esta invalida pois strstr procura dentro de obtido a Operação 

        if (t->esperado[0] == '[') { //verica se o esperado começa com '[' e entra no if caso sim

            if (tam == 0 || obtido[0] != '[')
                fprintf(out, "  ALERTA: Faltou '[' no início da estrutura.\n");

            if (tam > 0 && obtido[tam - 1] != ']')                             //verificam obitido
                fprintf(out, "  ALERTA: Faltou ']' no final da estrutura.\n");

            if (strcmp(obtido, "[]") == 0 && strcmp(t->esperado, "[]") != 0)
                fprintf(out, "  ALERTA: Estrutura vazia, mas deveria conter valores.\n");
        }

        if (strcmp(t->esperado, "0") == 0 ||   //Verifica se o esperado é algum dos vazios se sim entra no if
            strcmp(t->esperado, "NULL") == 0 ||
            strcmp(t->esperado, "0/NULL") == 0) {

            if (strcmp(obtido, "0") != 0 &&
                strcmp(obtido, "NULL") != 0 &&  //verifica se o obitido é vazio
                strcmp(obtido, "") != 0) {

                fprintf(out, "  ALERTA: Quando vazio, deveria retornar 0, NULL ou 0/NULL.\n");
            }
        }

        if (tam == 0 && t->esperado[0] != '[') {
            fprintf(out, "  ALERTA: Resultado vazio inesperado!\n"); //ex: esperava  10 e obiteve ""
        }
    }
}

