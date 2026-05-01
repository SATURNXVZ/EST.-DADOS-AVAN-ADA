/*1) Elabore um algoritmo em C para implementar a solução de torre de hanoi
utilizando recursividade.*/

#include <stdlib.h>
#include <stdio.h>

void hanoi(int num, char origem, char destino, char aux){
    if(num == 1){
        printf("\nMover disco de %c para %c", origem, destino);
        return;
    } 

    hanoi(num -1, origem, aux, destino);
    printf("\nMover disco %i de %c para %c", num, origem, destino);

    hanoi(num -1, aux, destino, origem); 
}

int main(){
    int num = 0;
    char a, b, c;

    printf("\n\n---TORRE DE HANOI---\n");
    printf("Digite o número de cilindros na torre: ");
    scanf("%i", &num);

    printf("iniciando torre...");

    hanoi(num, a, b, c);
}