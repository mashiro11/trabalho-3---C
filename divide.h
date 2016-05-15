#ifndef DIVIDE_H
#define DIVIDE_H

#include "aux.h"
#include "subtrai.h"

// funcoes
void divide_controle(char operando1[], char operando2[], no** ppmaq_pilha);
void divide(char dividendo[], char divisor[], char valor[]);
int determina_digito_quociente(char dividendo[], char divisor[], char valor[]);
void pega_prox_num_dividir(char num_a_dividir[], char parte_num_a_dividir[], int dig, char divisor[], char valor[]);
int analisa_maior_string(char string1[], char string2[]);
// inclui funcao contida no divide.c 
#include "divide.c"

#endif
