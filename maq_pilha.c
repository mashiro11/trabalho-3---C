/* 
 * maq_pilha.c
 * contem as funcoes para lidar com a maquina de pilha 
 */

#ifndef MAQ_PILHA_C
#define MAQ_PILHA_C

#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "maq_pilha.h"

no* constroi_pilha(char expressao[])
{
    char temp[TAMANHO_MEDIO];

    // declara ponteiros necessarios, nao esquecao de coloca-los em NULL
    // pois ainda nao foram inicializados
    no* pmaq_pilha = NULL;
    no* ppilha_operadores = NULL;
    no* plista_input = NULL; 

    // converte a expressao, dada como uma string em uma lista de input 
    plista_input = converte_para_lista(expressao, plista_input);
    
    // itera pela lista, da esquerda para a direita
    while(plista_input != NULL)
    {
        // se o token atual eh um operando
        if ( isdigit(plista_input->valor[0]))
        {
            // coloca ele no fim da maquina de pilha
            push(plista_input->valor, &pmaq_pilha);
        } 

        // se o token eh um "abre-parenteses", coloca ele na lista de operadores
        else if (plista_input->valor[0] == '(')
        {
            push(plista_input->valor, &ppilha_operadores);
        }

        // se o token eh um "fecha-parenteses"
        else if (plista_input->valor[0] == ')')
        {
            // desempilha tudo da pilha de operadores que esta ate o 
            // "abre-parenteses" associado. Os operadores que nao sao "(" ou ")" 
            // sao adicionados a maquina de pilha
            while(true)
            {
                pop(temp, &ppilha_operadores);

                if (temp[0] == '(')
                {
                    break;
                }

                else if (temp[0] == ')')
                {
                    continue;
                }
                
                // operador nao eh parenteses
                else
                {
                    push(temp, &pmaq_pilha);
                }
            } 
        }

        // se um token for um operador,
        else
        {
            //  remove operadores com precedencia maior ou igual 
            while(ppilha_operadores != NULL)
            {
                // remove o operador - agora temos que analisar se colocamos ele de volta
                // ou se colocamos na maquina de pilha
                pop(temp, &ppilha_operadores);

                // + ou - 
                if (plista_input->valor[0] == '+' || plista_input->valor[0] == '-')
                {
                    // se for um parenteses, a precedencia eh menor
                    // coloca na pilha de operadores e para a execucao
                    if (temp[0] == '(' || temp[0] == ')')
                    {
                        push(temp, &ppilha_operadores); 
                        break;
                    }  
                    
                    // senao poe na maquina de pilha 
                    else
                    {
                        push(temp, &pmaq_pilha);
                    }
                }

                // * ou /
                else
                {
                    if (temp[0] == '/' || temp[0] == '*')
                    {
                        push(temp, &pmaq_pilha);
                    }

                    else
                    {
                        push(temp, &ppilha_operadores);
                        break;
                    }
                }
            }

            //  e adiciona o token a lista de operadores
            push(plista_input->valor, &ppilha_operadores);
        }

        // vai para proximo elemento
        plista_input = plista_input->prox;
    }

    // adiciona operadores que por ventura tenham ficado na pilha de operadores no fim da maquina de pilha
    while(ppilha_operadores != NULL)
    {
        pop(temp, &ppilha_operadores);
        push(temp, &pmaq_pilha);
    }

    // vai para o comeco da lista
    while (pmaq_pilha != NULL && pmaq_pilha->ant != NULL)
    {
       pmaq_pilha = pmaq_pilha->ant; 
    }
    
    // deleta listas auxiliares
    deleta_lista(ppilha_operadores);
    deleta_lista(plista_input);

    // retorna ponteiro para maquina de pilha
    return pmaq_pilha;
}

no* converte_para_lista(char expressao[], no* plista_input)
{
    char token_atual[TAMANHO_MAX];
    int tamanho, token_ind;

    // tamanho da string
    tamanho = strlen(expressao);
    
    // indice do token
    token_ind = 0; 

    // itera pela expressao, caractere a caractere
    for (int i = 0; i < tamanho; i++)
    {   

        // se o caractere eh um espaco em branco ou um '\n'
        if (expressao[i] == ' ' || expressao[i] == '\n')
        {
            // se o comprimento do token atual for zero, nao lemos nada ainda, 
            // continua na proxima iteracao
            if (token_ind == 0)
            {
                continue;
            }

            // acabamos de ler um token, salva ele na lista
            token_atual[token_ind] = '\0';
            push(token_atual, &plista_input);
            
            // limpa o token, para proxima iteracao
            memset(token_atual, '\0', TAMANHO_MAX);
            token_ind = 0;
        }

        // se o caractere eh um numero 
        else if (isdigit(expressao[i]))
        {
            // adiciona ele ao token atual
            token_atual[token_ind] = expressao[i];
            token_ind++; 
        }

        // se o caractere eh um operador
        else
        {
            // se antes do operador veio um operando
            if (token_ind != 0)
            {
                // salva token atual e adiciona ele na lista
                token_atual[token_ind] = '\0';
                push(token_atual, &plista_input);
                memset(token_atual, '\0', TAMANHO_MAX);
                token_ind = 0;
            }

            // cria um novo token para o operador lido e tb salva ele na lista
            token_atual[token_ind] = expressao[i];
            push(token_atual, &plista_input);
            memset(token_atual, '\0', TAMANHO_MAX);
            token_ind = 0;
        }
    }

    // se a expressao acabou com o token_ind sem processar o ultimo numero
    if (token_ind != 0)
    {
        // salva token atual e adiciona ele na lista
        token_atual[token_ind] = '\0';
        push(token_atual, &plista_input);
    }
        
    // coloca o ponteiro no comeco da lista
    while(plista_input != NULL && plista_input->ant != NULL)
    {
        plista_input = plista_input->ant;
    }

    // retorna
    return plista_input; 
}

void push(char token[], no** pp_lista)
{
    no* novo_no;
    
    // inicializa novo no, com valor correto
    novo_no = malloc(sizeof(no));
    strcpy(novo_no->valor, token);

    // liga novo no a lista
    novo_no->prox = NULL;
    novo_no->ant = *pp_lista;
    if (*pp_lista != NULL)
    {
        (*pp_lista)->prox = novo_no; // so executa se a lista nao tiver vazia
    }

    // modifica cabeca da lista para ficar no novo no
    *pp_lista = novo_no;
}

void pop(char token[], no** pp_lista)
{
    // checagem de erro
    if (*pp_lista == NULL)
    {
        printf("um erro foi cometido, nao pode-se retirar valor de um stack vazio");
        exit(1);
    }

    // pega valor no topo do stack
    strcpy(token, (*pp_lista)->valor);

    // remove ultimo valor do stack
    *pp_lista = (*pp_lista)->ant;
    if (*pp_lista != NULL)
    {
        free((*pp_lista)->prox);
        (*pp_lista)->prox = NULL; // so pode executar se *pplista nao for null
    }
}

void imprime_lista(no* plista)
{
    while(plista != NULL)
    {
        printf("%s  ", plista->valor);
        plista = plista->prox;
    }
}

void deleta_lista(no* plista)
{
    // remove ultimo valor do stack
    while (plista != NULL)
    {
        plista = plista->ant;
        free(plista->prox);
        plista->prox = NULL; 
    }
}
#endif
