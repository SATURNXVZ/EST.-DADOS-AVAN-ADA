#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//cria a forma do funcionario
struct Funcionario{
    int code;
    char nome[100];
    char cargo[50];
    int salario;
};

//cria uma sruct de ponteiros para facilitar uso
struct node{
    struct Funcionario data; //dados do funcionario
    struct node* left; //proximo code menor
    struct node* right; //proximo code maior
};

//funcao que cria novo funcionario
struct node* new (int code, char nome[], char cargo[], int salario){
    struct node* novoFunc = (struct node*) malloc(sizeof(struct node)); //alem de criar um novo, aloca memoria
    
    //preenche os dados do novo funcioario
    novoFunc->data.code = code;
    strcpy(novoFunc->data.nome, nome);
    strcpy(novoFunc -> data.cargo, cargo);
    novoFunc->data.salario = salario;
    
    //declara que os ponteiros estão nulos
    novoFunc->left = NULL;
    novoFunc->right = NULL;
    return novoFunc;
}

//insere o novo func na árvore
struct node* inserir(struct node* raiz, int code, char nome[], char cargo[], int salario){
    //se a raiz for nula, então vai criar um novo funcionario como raiz
    if(raiz == NULL){
        return new (code, nome, cargo, salario);
    }

    //aqui já não é raiz mais, chama a funcao recusrsivamente
    //se o codigo for menor do que o codigo da raiz, então vai ficar à esquerda
    if(code < raiz->data.code){
        raiz->left = inserir(raiz->left, code, nome, cargo, salario);
    } //se for maior, vai pra direita 
    else if(code > raiz->data.code){
        raiz-> right = inserir(raiz->right, code, nome, cargo, salario);
    } //como "default", código já existe
    else{
        printf("\n\nERRO! FUNCIONARIO COM CODIGO %i JÁ CADASTRADO!", code);
    }

    return raiz;
}

//busca o funcionario usando a chave
struct node* fetch(struct node* raiz, int code){
    //se a raiz for nula, ou tiver encontrado, retornará a raiz;
    //caso base da recursão
    if(raiz == NULL || raiz->data.code == code){
        return raiz;
    } 

    //chamada recursiva indo pra esquerda
    if(code < raiz->data.code){
        return fetch(raiz->left, code);
    }

    //chamada recursiva pra direita
    return fetch(raiz->right, code);

}

//printa os dados do funcionário
void print(struct node* node){
    
    if(node != NULL){
        printf("\n=== DADOS DO FUNCIONARIO ===\n");
        printf("Codigo: %i\n", node->data.nome);
        printf("Nome: %s\n", node->data.nome);
        printf("Cargo: %s\n", node->data.cargo);
        printf("Salario: %i", node->data.salario);
    }
}

//função recursiva que percorre a arvore
void percorrer(struct node* raiz){
    if(raiz != NULL){
        percorrer(raiz->left);
        print(raiz);
        percorrer(raiz->right);
    }
}

//função principal que lista todos os funconarios
void list(struct node* raiz){
    if(raiz == NULL) {
        printf("\n\nERRO! Nenhum funcionario cadastrado\n\n");
        return;
    }

    printf("\n=== LISTA DE FUNCIONARIOS ===\n");
    print(raiz);

}

int main(){
    struct node* raiz = NULL;
    int esc = 0, code = 0, salario;
    char nome[100], cargo[50];

    //menu interativo com as escolhas 
    while (esc != 4){
        printf("\n==== CADASTRO DE FUNCIONÁRIOS ===");
        printf("1- Cadastrar novo funcionário;\n");
        printf("2- Atualizar funcionário existente;\n");
        printf("3- Buscar informações do funcionário;\n");
        printf("4- Listar todos os funcionparios;\n");    
        printf("Sua escolha: ");
        scanf("%i", &esc);

        switch(esc){
            case 1: 
                printf("Digite um nome: ");
                fgets(nome, 101, stdin);
                printf("Digite o nome do cargo: ");
                fgets(cargo, 51, stdin);
                printf("Digite o salário: ");
                scanf("%i", &salario);

                inserir(raiz, code, nome, cargo, salario);
        }   //case 2:
    }

    free(raiz);

}