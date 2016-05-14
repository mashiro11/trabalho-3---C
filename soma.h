#ifndef SOMA_H
#define SOMA_H

#include "aux.h"

// como cada bloco do numero tem 9 digitos, o valor para ter ocorrido carry eh 10^9 
#define HOUVE_CARRY 1000000000

// funcoes para soma
void soma_controle(char operando1[], char operando2[], no** ppmaq_pilha);

/*
 * soma dois numeros positivos
 */
void soma(char operando1[], char operando2[], char valor[]);
void faz_soma(uint32_t op1[], uint32_t op2[], uint32_t resultado[]);

#include "subtrai.h"

// inclui funcao contida no soma.c 
#include "soma.c"

#endif
