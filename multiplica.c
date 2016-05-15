#ifndef MULTIPLICA_C
#define MULTIPLICA_C

#include "multiplica.h"

void multiplica_controle(char operando1[], char operando2[], no** ppmaq_pilha)    
{
    char valor[TAMANHO_MEDIO];

    // string sem o sinal 
    char op1_sem_sinal[TAMANHO_MEDIO];
    char op2_sem_sinal[TAMANHO_MEDIO];
    // pega sinal dos dois operandos
    bool op1_positivo;
    bool op2_positivo;

    // pega sinal dos dois operandos
    op1_positivo = operando_positivo(operando1);
    op2_positivo = operando_positivo(operando2);
    
    // pega os dois inteiros sem sinal 
    obtem_sem_sinal(operando1, op1_sem_sinal);
    obtem_sem_sinal(operando2, op2_sem_sinal);

    // chama funcao conveniente
    if ((op1_positivo && op2_positivo) || (!op1_positivo && !op2_positivo))
    {
        multiplica(op1_sem_sinal, op2_sem_sinal, valor);
    } 
    else
    {
        multiplica(op1_sem_sinal, op2_sem_sinal, valor);
        muda_sinal(valor);
    }

    push(valor, ppmaq_pilha);
}

void multiplica(char operando1[], char operando2[], char valor[])
{
    uint32_t op1[ELEMENTOS];
    uint32_t op2[ELEMENTOS];
    uint32_t resultado[ELEMENTOS];
    uint64_t temp;
    uint32_t temp1; 

    // zera o conteudo de resultado 
    for (int i = 0; i < ELEMENTOS; i++)
    {
        resultado[i] = 0;
    }

    // converte operando para uma sequencia de blocos de 9 digitos cada, representavel em um 
    // inteiro de 32 bits
    converte_operando(operando1, op1);
    converte_operando(operando2, op2);

    // itera por cada bloco do primeiro operando  
    for (int i = 0; i < ELEMENTOS; i++)
    {
        // itera por cada bloco do segundo operando
        for (int j = 0; j < ELEMENTOS; j++)
        {
            // faz multiplicacao
            temp = op1[i] * op2[j];
            
            // poe parte menos significativa no resultado 
            if (i + j < ELEMENTOS)
            {
                resultado[i + j] += (uint32_t)temp;
            }

            // poe parte mais significativa no resultado, se couber
            if (i + j + 1 < ELEMENTOS)
            {
                resultado[i + j + 1] += (uint32_t) (temp >> 32); 
            } 
        }
    }

    // converte resultado para string
    converte_operando_string(resultado, valor);
}
#endif
