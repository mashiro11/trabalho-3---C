#ifndef AUX_H
#define AUX_H

// define quantidade de elementos inteiros de 32 bits para se representar um inteiro de 256 bits 
#define ELEMENTOS 9

// define a quantidade de digitos que cada array ira guardar
#define QTD_DIG 9

#include <stdint.h>

void converte_operando(char operando[], uint32_t op[]);
void reverte(char string[]);
void converte_operando_string(uint32_t resultado[], char valor[]);
bool operando_positivo(char operando[]);
void obtem_sem_sinal(char operando[], char op_sem_sinal[]);
void muda_sinal(char valor[]);


#include "aux.c"
#endif  
