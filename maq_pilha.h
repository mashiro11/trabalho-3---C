#ifndef MAQ_PILHA_H
#define MAQ_PILHA_H

#define TAMANHO_MAX 400
#define TAMANHO_MEDIO 100

// definicao de um no de uma lista dupla  
typedef struct no 
{
    char valor[TAMANHO_MEDIO];

    // proximo frame
    struct no* prox; 

    // frame anterior
    struct no* ant;
} 
no;


// funcoes da pilha

/*
 * a funcao recebe uma expressao 
 * 
 * a funcao monta a pilha com os tokens na ordem polonesa reversa
 *
 * a funcao retorna um ponteiro para o comeco da lista
 */
no* constroi_posfixa(char expressao[]);

/*
 * a funcao recebe uma expressao e um ponteiro para uma lista
 * 
 * a funcao processa a expressao - a qual deve ser valida - 
 * e vai colocando tokens na lista.
 *
 * no fim, a funcao retorna um ponteiro para o comeco dessa lista 
 */
no* converte_para_lista(char expressao[], no* plista_input);

/*
 * a funcao recebe um token e um ponteiro para ponteiro de uma pilha
 * 
 * a funcao cria um novo no na lista,contendo o conteudo do token
 * a funcao atualiza o ponteiro de ponteiro passado, de modo que o ponteiro aponte 
 * para o topo do stack apos a insercao
 *
 * a funcao nao retorna nada
 */
void push(char token[], no** pp_lista);

/*
 * a funcao recebe um token e um ponteiro para ponteiro de uma pilha
 *
 * a funcao remove o no no topo da lista, transferindo o seu conteudo para token
 * a funcao atualiza o ponteiro passado
 *
 * nada eh retornado pela funcao
 */
void pop(char token[], no** pp_lista);

/*
 * a funcao recebe um ponteiro para o comeco de uma lista
 *
 * a funcao imprime a lista
 */
void imprime_lista(no* plista);

/*
 * a funcao recebe um ponteiro para o fim de uma lista dupla
 * a funcao deleta a lista
 */
void deleta_lista(no* plista);

#include "maq_pilha.c"
#endif
