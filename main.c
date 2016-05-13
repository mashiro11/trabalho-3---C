/*
 * main file for the project
 */

#include <stdio.h> 
#include <string.h> 

// arquivos necessarios para o projeto 
#include "maq_pilha.h"

int main(int argc, char* argv[])
{
    char expressao[TAMANHO_MAX];
    no* plista_aux;

    // pega expressao passada 
    if (argc == 2)
    {
        strcpy(expressao, argv[1]);
    }
    else
    {
        printf("Voce nao colocou uma expressao ao chamar o programa\n");
        printf("Por favor, digite ela agora: ");
        fgets(expressao, TAMANHO_MAX, stdin);
    }

    // da expressao, infixada e podendo conter parênteses, poe na lista auxiliar usando notacao
    // polonesa reversa
    plista_aux = constroi_pilha(expressao);
    imprime_lista(plista_aux);
    
    return 0;
}
