#ifndef SUBTRAI_C
#define SUBTRAI_C

#include "subtrai.h"

void subtrai_controle(char operando1[], char operando2[], no** ppmaq_pilha)
{
    // string sem o sinal 
    char op1_sem_sinal[TAMANHO_MEDIO];
    char op2_sem_sinal[TAMANHO_MAX];

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
    // positivo - positivo
    if (op1_positivo && op2_positivo)
    {
        subtrai(op1_sem_sinal, op2_sem_sinal, valor);
    }

    // positivo - negativo
    else if (op1_positivo && !op2_positivo)
    {
        soma(op1_sem_sinal, op2_sem_sinal, valor);
    }

    // negativo - positivo
    else if (!op1_positivo && op2_positivo)
    {
        soma(op1_sem_sinal, op2_sem_sinal, valor);
        muda_sinal(valor);
    }

    // negativo - negativo
    else
    {
        subtrai(op1_sem_sinal, op2_sem_sinal, valor);
        muda_sinal(valor);   
    }

    // poe valor correto na pilha   
    push(valor, ppmaq_pilha);
}

void subtrai(char operando1[], char operando2[], char valor[])
{
    uint32_t op1[ELEMENTOS];
    uint32_t op2[ELEMENTOS];
    uint32_t resultado[ELEMENTOS];
    int op1_cmp_op2;

    // converte operando para uma sequencia de blocos de 9 digitos cada, representavel em um 
    // inteiro de 32 bits
    converte_operando(operando1, op1);
    converte_operando(operando2, op2);

    // pega qual valor eh maior
    op1_cmp_op2 = analisa_maior(op1, op2);

    // calcula o maior operando menos o menor operando e obtem resultado
    // em seguida, coloca o sinal de acordo 
    if (op1_cmp_op2 == MAIOR || op1_cmp_op2 == IGUAL)
    {
        faz_subtracao(op1, op2, resultado);
        converte_operando_string(resultado, valor);
    }
    else
    {
        faz_subtracao(op2, op1, resultado);   
        converte_operando_string(resultado, valor);
        muda_sinal(valor);
    }
}

int analisa_maior(uint32_t op1[], uint32_t op2[])
{
    // itera do bloco mais significativo ao menos significativo
    for (int i = ELEMENTOS - 1; i >= 0; i--)
    {
        // se no bloco atual op 1 eh maior
        if (op1[i] > op2[i])
        {
            // retorna codigo correspondente
            return MAIOR;
        }

        // se no bloco atual op 2 eh maior
        else if (op1[i] < op2[i])
        {
            // retorna codigo correspondente
            return MENOR;
        }
    }

    // retorna igual     
    return IGUAL;
}

void faz_subtracao(uint32_t op1[], uint32_t op2[], uint32_t resultado[])
{
    // itera por todos os blocos, do menor ao maior
    for (int i = 0; i < ELEMENTOS; i++)
    {
        // caso o bloco atual do operando maior seja menor que o bloco atual do operando menor
        if (op1[i] < op2[i])
        {    
            // pega carry correspondente do proximo bloco 
            resultado[i] = (op1[i] + VALOR_EMPRESTADO) - op2[i]; 

            // decrementa prox bloco 
            op1[i+1]--;
        }

        // faz a subtracao do bloco atual do operando maior pelo bloco atual do operando menor 
        else
        {
            resultado[i] = op1[i] - op2[i];
        }
    }
}

#endif
