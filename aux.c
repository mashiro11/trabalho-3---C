#ifndef AUX_C
#define AUX_C

#include <string.h>
#include "aux.h"

void converte_operando(char operando[], uint32_t op[])
{   
    int tamanho;
    int ind_operando, ind_array, ind_9dig;
    char nove_digitos[TAMANHO_MEDIO];

    // pega tamanho da string
    tamanho = strlen(operando);

    // preenche entradas do array de modo correto
    ind_array = 0;
    ind_9dig = 0;
    for (int i = tamanho - 1; i >= 0; i--)
    {
        nove_digitos[ind_9dig] = operando[i];  
        ind_9dig++;

        // caso tenhamos chegado ao fim de um numero
        if (ind_9dig == QTD_DIG)
        {
            // transfere nove_digitos para a posicao certa do array 
            nove_digitos[ind_9dig] = '\0';
            reverte(nove_digitos);
            op[ind_array] = (uint32_t) atoi(nove_digitos); 
            ind_array++;
            memset(nove_digitos, '\0', TAMANHO_MEDIO);
            
            // corrige para proxima iteracao
            ind_9dig = 0;

        }
        
        // caso tenhamos chegado ao fim do operando 
        else if (i == 0)
        {
            // transfere nove_digitos para a posicao certa do array 
            nove_digitos[ind_9dig] = '\0';
            reverte(nove_digitos);
            op[ind_array] = (uint32_t) atoi(nove_digitos); 
            ind_array++;
            memset(nove_digitos, '\0', TAMANHO_MEDIO);
        }
    }

    // preenche outras entradas do array que sobraram
    for (int i = ind_array; i < ELEMENTOS; i++)
    {
        op[i] = 0;
    }
}

void reverte(char string[])
{
    int temp, ind1, ind2;
    
    ind1 = 0;
    ind2 = strlen(string) - 1;

    while (ind1 < ind2)
    {
        // troca caracteres
        temp = string[ind1];
        string[ind1] = string[ind2];
        string[ind2] = temp;

        // atualiza indices
        ind1++;
        ind2--;
    }
}

void converte_operando_string(uint32_t resultado[], char valor[])
{
    char temp[TAMANHO_MEDIO];
    bool chance_zero_esq = true;

    // limpa o conteudo de valor
    memset(valor, '\0', TAMANHO_MEDIO);

    // itera por todos os blocos do resultado
    for (int i = ELEMENTOS - 1; i >= 0; i--)
    { 
        // se o resultado em i for um zero a esquerda e nao estivermos no primeiro bloco
        if (chance_zero_esq && resultado[i] == 0 && i != 0)
        {
            // zero a esquerda nao deve ser adicionado 
            continue;
        }
        
        else
        {
            chance_zero_esq = false;

            // converte bloco para string
            sprintf(temp, "%d", resultado[i]);

            // adiciona em valor
            strcat(valor, temp);
        }
    }
}

bool operando_positivo(char operando[])
{
    if (operando[0] == '-')
    {
        return false;
    }
    return true;
}

void obtem_sem_sinal(char operando[], char op_sem_sinal[])
{
    int tamanho = strlen(operando);

    // se o operando eh negativo
    if (!operando_positivo(operando))
    {
        // cada posicao do operando eh uma a menos 
        for (int i = 1; i < tamanho; i++)
        {
            op_sem_sinal[i-1] = operando[i];
        }
        op_sem_sinal[tamanho-1] = '\0';
    }   

    // senao, copia
    strcpy(op_sem_sinal, operando);
}

void muda_sinal(char valor[])
{
    char temp[TAMANHO_MEDIO];
    
    // se tem sinal 
    if (!operando_positivo(valor))
    {
        // obtem sem sinal
        obtem_sem_sinal(valor, temp);
        strcpy(valor, temp);
    }
    
    // se nao tem sinal 
    else
    {
        temp[0] = '-';
        temp[1] = '\0';
        strcat(temp, valor);
        strcpy(valor, temp);
    }   
}
#endif 
