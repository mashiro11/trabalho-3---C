#ifndef SUBTRAI_H
#define SUBTRAI_H

#include "aux.h"
#include "soma.h"

#define MAIOR 1
#define MENOR -1 
#define IGUAL 0

// como cada parte do numero contem exatamente nove digitos, esse eh o valor emprestado
#define VALOR_EMPRESTADO 1000000000


// funcoes utilizadas

/*
 * subtrai dois numeros positivos
 */
void subtrai(char operando1[], char operando2[], char valor[]);

void faz_subtracao(uint32_t op1[], uint32_t op2[], uint32_t resultado[]);
int analisa_maior(uint32_t op1[], uint32_t op2[]);

// inclui funcao contida no subtrai.c 
#include "subtrai.c"

#endif
