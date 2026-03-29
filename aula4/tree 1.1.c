#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//estrutura para o funcionariuo
struct Funcionario{
    int code;              //chave mestra
    char nome[100];
    char cargo[50];
    int salario;
};

//estrutura do nós da arvore
struct node{
    struct Funcionario data;
    struct node* left;   //menor q raiz
    struct node* right;  //maior q raiz
};

//cria um novo nó
struct node* criarNo(int code, char nome[], char cargo[], int salario){
    struct node* novo = (struct node*) malloc(sizeof(struct node));

    novo->data.code = code;
    strcpy(novo->data.nome, nome);
    strcpy(novo->data.cargo, cargo);
    novo->data.salario = salario;

    novo->left = NULL;
    novo->right = NULL;

    return novo;
}

//inserir na arvore
struct node* inserir(struct node* raiz, int code, char nome[], char cargo[], int salario){
    if(raiz == NULL){
        return criarNo(code, nome, cargo, salario);
    }

    if(code < raiz->data.code){
        raiz->left = inserir(raiz->left, code, nome, cargo, salario);
    }
    else if(code > raiz->data.code){
        raiz->right = inserir(raiz->right, code, nome, cargo, salario);
    }
    else{
        printf("\nERRO! Código já cadastrado!\n");
    }

    return raiz;
}


//buscar funcionario
struct node* fetch(struct node* raiz, int code){
    if(raiz == NULL || raiz->data.code == code){
        return raiz;
    }

    if(code < raiz->data.code){
        return fetch(raiz->left, code);
    }

    return fetch(raiz->right, code);
}

//atualiza funcionário
void atualizar(struct node* raiz, int code){
    struct node* f = fetch(raiz, code);

    if(f == NULL){
        printf("\nFuncionario nao encontrado!\n");
        return;
    }

    printf("Novo nome: ");
    getchar();
    fgets(f->data.nome, 100, stdin);

    printf("Novo cargo: ");
    fgets(f->data.cargo, 50, stdin);

    printf("Novo salario: ");
    scanf("%d", &f->data.salario);
}

//printa o funcionario
void print(struct node* n){
    if(n != NULL){
        printf("\n=== FUNCIONARIO ===\n");
        printf("Codigo: %d\n", n->data.code);
        printf("Nome: %s", n->data.nome);
        printf("Cargo: %s", n->data.cargo);
        printf("Salario: %d\n", n->data.salario);
    }
}

//percorre em ordem (lista ordenada)
void percorrer(struct node* raiz){

    if(raiz != NULL){
        percorrer(raiz->left);
        print(raiz);
        percorrer(raiz->right);
    }
}


//lista todos os funcionários
void list(struct node* raiz){
    if(raiz == NULL){ //não tem nenhum funcionario ainda
        printf("\nNenhum funcionario cadastrado!\n");
        return;
    }

    printf("\n=== LISTA DE FUNCIONARIOS ===\n");
    percorrer(raiz);
}

//Libera memória da árvore
void liberar(struct node* raiz){
    if(raiz != NULL){
        liberar(raiz->left);
        liberar(raiz->right);
        free(raiz); //se tem alocacao tem liberacao
    }
}

int main(){
    struct node* raiz = NULL;

    int opcao = 0, code, salario;
    char nome[100], cargo[50];

    while(opcao != 5){

    printf("\n==== MENU ====\n");
    printf("1 - Cadastrar funcionario\n");
    printf("2 - Atualizar funcionario\n");
    printf("3 - Buscar funcionario\n");
    printf("4 - Listar funcionarios\n");
    printf("5 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch(opcao){

        case 1:
            printf("Codigo: ");
            scanf("%d", &code);

            getchar(); // limpa buffer

            printf("Nome: ");
            fgets(nome, 100, stdin);

            printf("Cargo: ");
            fgets(cargo, 50, stdin);

            printf("Salario: ");
            scanf("%d", &salario);

            raiz = inserir(raiz, code, nome, cargo, salario);
            break;

        case 2:
            printf("Digite o codigo: ");
            scanf("%d", &code);
            atualizar(raiz, code);
            break;

        case 3:{
            printf("Digite o codigo: ");
            scanf("%d", &code);

            struct node* f = fetch(raiz, code);

            if(f != NULL){
                print(f);
            } else {
                printf("\nFuncionario nao encontrado!\n");
            }
            break;
        }

        case 4:
            list(raiz);
            break;

        case 5:
            printf("Encerrando...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    }
    liberar(raiz);
    return 0;
}