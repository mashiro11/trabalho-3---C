#ifndef AUX_H
#define AUX_H

// define quantidade de elementos inteiros de 32 bits para se representar um inteiro de 256 bits
#define ELEMENTOS 9

// define a quantidade de digitos que cada array ira guardar
#define QTD_DIG 9

#include <stdint.h>

/* Funcao recebe uma string com o operando de uma operacao e um array de numeros de 32 bits onde o operando sera
armazenado.
* A funcao converte os caracteres da string que representam numeros e os armazena no array. 
*/
void converte_operando(char operando[], uint32_t op[]);


/* A funcao recebe uma string.
*
* A funcao reverte a ordem dos caracteres da string (primeiro caracter se torna o ultimo e o ultimo se torna o primeiro).
*/
void reverte(char string[]);


/* A funcao recebe um array de elementos de 32 bits e uma string.
*
* A funcao converte o resultado (numero de 256 bits representado por um array de elementos de 32 birs) em uma string.  
*/
void converte_operando_string(uint32_t resultado[], char valor[]);


/* A funcao recebe um operando em forma de string.  
*
* A funcao retorna se o operando e positivo (o que ocorre se o primeiro caracter da string nao for '-') e retorna true ou false.
*/
bool operando_positivo(char operando[]);


/* A funcao recebe um operando e uma string para onde esse operando sera copiado (sem sinal).
*
* A funcao verifica se o numero e positivo ou negativo. Se for negativo, copia elementos da string a partir do indice 1.
* Caso contrario, copia string via strcpy.
*/
void obtem_sem_sinal(char operando[], char op_sem_sinal[]);


/* Funcao recebe um numero em formato de string e altera o seu sinal.
*/
void muda_sinal(char valor[]);


#include "aux.c"
#endif
