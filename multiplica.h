#ifndef MULTIPLICA_H
#define MULTIPLICA_H

#include "aux.h"

void multiplica_controle(char operando1[], char operando2[], no** ppmaq_pilha);
void multiplica(char operando1[], char operando2[], char valor[]);

// inclui funcao contida no multiplica.c 
#include "multiplica.c"

#endif
