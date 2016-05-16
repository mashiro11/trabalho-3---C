#ifndef DIVIDE_H
#define DIVIDE_H

#include "aux.h"
#include "subtrai.h"

/* Funcao recebe os dois operandos da divisao e o ponteiro para a pilha.
*
*  Funcao determina o sinal dos operandos, chama a funcao de divisao (usando os operandos sem sinal), adiciona o sinal ao
resultado caso seja necessario e então armazena o resultado na pilha.
*/
void divide_controle(char operando1[], char operando2[], no** ppmaq_pilha);

/* Recebe o dividendo, divisor e o valor, onde o resultado da divisao sera armazenado.
*
* Enquanto o dividendo for menor que o divisor,
*/
void divide(char dividendo[], char divisor[], char valor[]);
int determina_digito_quociente(char dividendo[], char divisor[], char valor[]);
void pega_prox_num_dividir(char num_a_dividir[], char parte_num_a_dividir[], int dig, char divisor[], char valor[]);
int analisa_maior_string(char string1[], char string2[]);
// inclui funcao contida no divide.c
#include "divide.c"

#endif
