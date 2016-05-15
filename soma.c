#ifndef SOMA_C
#define SOMA_C

#include "soma.h"

void soma_controle(char operando1[], char operando2[], no** ppmaq_pilha)
{
    // string sem o sinal 
    char op1_sem_sinal[TAMANHO_MEDIO];
    char op2_sem_sinal[TAMANHO_MEDIO];

    char valor[TAMANHO_MEDIO];
    bool op1_positivo;
    bool op2_positivo;

    // pega sinal dos dois operandos
    op1_positivo = operando_positivo(operando1);
    op2_positivo = operando_positivo(operando2);
    
    // pega os dois inteiros sem sinal 
    obtem_sem_sinal(operando1, op1_sem_sinal);
    obtem_sem_sinal(operando2, op2_sem_sinal);

    // chama funcao conveniente
    // positivo + positivo
    if (op1_positivo && op2_positivo)
    {
        soma(op1_sem_sinal, op2_sem_sinal, valor);
    }

    // positivo + negativo
    else if (op1_positivo && !op2_positivo)
    {
        subtrai(op1_sem_sinal, op2_sem_sinal, valor);
    }

    // negativo + positivo
    else if (!op1_positivo && op2_positivo)
    {
        subtrai(op2_sem_sinal, op1_sem_sinal, valor);
    }

    // negativo + negativo
    else
    {
        soma(op1_sem_sinal, op2_sem_sinal, valor);
        muda_sinal(valor);   
    }

    // poe valor correto na pilha   
    push(valor, ppmaq_pilha);
}

void soma(char operando1[], char operando2[], char valor[])
{
    uint32_t op1[ELEMENTOS];
    uint32_t op2[ELEMENTOS];
    uint32_t resultado[ELEMENTOS];

    // converte operando para uma sequencia de blocos de 9 digitos cada, representavel em um 
    // inteiro de 32 bits
    converte_operando(operando1, op1);
    converte_operando(operando2, op2);

    // realiza soma
    faz_soma(op1, op2, resultado);

    // converte para string
    converte_operando_string(resultado, valor);

}

void faz_soma(uint32_t op1[], uint32_t op2[], uint32_t resultado[])
{
    // itera por cada bloco 
    for (int i = 0; i < ELEMENTOS; i++)
    {
        // soma blocos
        resultado[i] = op1[i] + op2[i];

        // caso tenha havido um vai-um
        if (resultado[i] > HOUVE_CARRY)
        { 
            // corrige  
            resultado[i] -= HOUVE_CARRY;

            // passa o vai um para o proximo bloco
            op1[i+1]++;
        }
    }
}

#endif 
