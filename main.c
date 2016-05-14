/*
 * main file for the project
 */

#include <stdio.h> 
#include <string.h> 

// arquivos necessarios para o projeto 
#include "maq_pilha.h"
#include "soma.h"
#include "subtrai.h"
#include "multiplica.h"
#include "divide.h"

int main(int argc, char* argv[])
{
    char expressao[TAMANHO_MAX];
    char operando1[TAMANHO_MEDIO]; 
    char operando2[TAMANHO_MEDIO]; 
    no* plista_aux;
    no* pmaq_pilha = NULL;

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
    plista_aux = constroi_posfixa(expressao);
    imprime_lista(plista_aux);
    printf("\n");
    
    // itera ate a expressao acabar
    while (plista_aux != NULL)
    {
        
        // se o token atual eh um numero
        if ( isdigit(plista_aux->valor[0])  || isdigit(plista_aux->valor[1]))
        {
            // acrescenta ele a maquina de pilha
            push(plista_aux->valor, &pmaq_pilha);
        }

        // se o token eh um operador
        else
        {
            // todas as operacoes precisam de dois operandos, pega entao os dois operandos 
            pop(operando2, &pmaq_pilha); // veja que operando 2 eh o que esta em primeiro na pilha
            pop(operando1, &pmaq_pilha); // operando 1 eh o que esta mais embaixo na pilha

            switch (plista_aux->valor[0])
            {
                case '+':
                    soma_controle(operando1, operando2, &pmaq_pilha);
                    break;

                case '-':
                    subtrai_controle(operando1, operando2, &pmaq_pilha);
                    break;

                case '*':
                    multiplica(operando1, operando2, &pmaq_pilha);
                    break;

                case '/':
                    divide(operando1, operando2, &pmaq_pilha);
                    break;

                default:
                    printf("Operando invalido na pilha!\n");
            }
        }   

        // passa para o proximo simbolo da lista 
        plista_aux = plista_aux->prox;
    }
    
    printf("Resultado na pilha: %s", pmaq_pilha->valor);
    return 0;
}
